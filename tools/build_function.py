#!/usr/bin/env python3
"""Build one local C candidate and emit a strict, read-only selection proposal.

The command composes the existing local compiler and selection preflight. It
does not edit the production manifest or build a ROM.
"""
from __future__ import annotations

import argparse
from concurrent.futures import ThreadPoolExecutor, as_completed
from datetime import datetime, timezone
import hashlib
import json
from pathlib import Path
import re
import socket
import sys
import time


ROOT = Path(__file__).resolve().parents[1]
COMPARE = ROOT / "tools/compare_module_build.py"
PREFLIGHT = ROOT / "tools/prepare_module_selection.py"
JOBS_SCHEMA = "single-function-jobs-v1"
DEFAULT_JOBS = 2
MAX_JOBS = 8
DAEMON_MAX_RESPONSE_BYTES = 65536
sys.path.insert(0, str(ROOT / "tools"))
import compare_module_build  # noqa: E402
import prepare_module_selection  # noqa: E402


class BuildFunctionError(ValueError):
    """An invocation failed a local path or job-file safety check."""


def sha256_file(path: Path) -> str:
    digest = hashlib.sha256()
    with path.open("rb") as stream:
        for chunk in iter(lambda: stream.read(1024 * 1024), b""):
            digest.update(chunk)
    return digest.hexdigest()


def write_json(path: Path, value: dict) -> None:
    path.write_text(json.dumps(value, sort_keys=True, indent=2) + "\n")


def strict_file(value: str | Path, label: str) -> Path:
    try:
        return Path(value).expanduser().resolve(strict=True)
    except OSError as exc:
        raise BuildFunctionError(f"{label} does not exist: {value}") from exc


def output_path(value: str | Path, label: str) -> Path:
    return Path(value).expanduser().resolve()


def is_within(path: Path, directory: Path) -> bool:
    try:
        path.relative_to(directory)
        return True
    except ValueError:
        return False


def paths_overlap(left: Path, right: Path) -> bool:
    return is_within(left, right) or is_within(right, left)


def validate_external_output(directory: Path, repo: Path, inputs: list[Path], label: str) -> None:
    if is_within(directory, repo) or is_within(repo, directory):
        raise BuildFunctionError(f"{label} must be outside and not contain the repository")
    for path in inputs:
        if paths_overlap(directory, path):
            raise BuildFunctionError(f"{label} overlaps input path: {path}")
    if directory.exists() and (not directory.is_dir() or any(directory.iterdir())):
        raise BuildFunctionError(f"{label} must be new or empty: {directory}")


def validate_daemon_socket(value: Path | str) -> Path:
    path = strict_file(value, "local build daemon socket")
    if not path.is_socket():
        raise BuildFunctionError(f"local build daemon path is not a Unix socket: {path}")
    return path


def daemon_build(socket_path: Path, job: dict, output: Path, no_cache: bool) -> dict:
    """Request one local compilation without starting a second Python CLI."""
    request = {
        "op": "build",
        "module": job["module"],
        "candidate_module": str(job["candidate_module"]) if job["candidate_module"] else None,
        "output_dir": str(output.resolve()),
        "use_cache": not no_cache,
    }
    payload = json.dumps(request, separators=(",", ":")).encode("utf-8") + b"\n"
    if len(payload) > DAEMON_MAX_RESPONSE_BYTES:
        raise BuildFunctionError("daemon request exceeds 64 KiB")
    try:
        with socket.socket(socket.AF_UNIX, socket.SOCK_STREAM) as connection:
            # A real local compile can take minutes. The deadline bounds a
            # wedged service without imposing the ordinary 10-second RPC limit.
            connection.settimeout(1800)
            connection.connect(str(socket_path))
            connection.sendall(payload)
            with connection.makefile("rb") as stream:
                raw = stream.readline(DAEMON_MAX_RESPONSE_BYTES + 1)
    except OSError as exc:
        raise BuildFunctionError(f"local build daemon request failed: {exc}") from exc
    if len(raw) > DAEMON_MAX_RESPONSE_BYTES or not raw.endswith(b"\n"):
        raise BuildFunctionError("daemon response is missing a newline or exceeds 64 KiB")
    try:
        response = json.loads(raw)
    except (UnicodeDecodeError, json.JSONDecodeError) as exc:
        raise BuildFunctionError(f"daemon returned invalid JSON: {exc}") from exc
    if not isinstance(response, dict) or response.get("ok") is not True:
        message = response.get("error", "invalid daemon response") if isinstance(response, dict) else "invalid daemon response"
        raise BuildFunctionError(f"local build daemon rejected request: {message}")
    if response.get("op") != "build" or response.get("module") != job["module"]:
        raise BuildFunctionError("daemon response does not match the requested build")
    if response.get("stale") is not False:
        raise BuildFunctionError("daemon reports stale build inputs")
    report_path = response.get("report")
    expected_report = (output / "report.json").resolve()
    if not isinstance(report_path, str) or Path(report_path).resolve() != expected_report:
        raise BuildFunctionError("daemon report path is outside the requested output directory")
    if not expected_report.is_file():
        raise BuildFunctionError("daemon reported success without writing report.json")
    return response


def load_jobs_file(path: Path) -> list[dict]:
    try:
        document = json.loads(path.read_text())
    except (OSError, json.JSONDecodeError) as exc:
        raise BuildFunctionError(f"invalid jobs file {path}: {exc}") from exc
    if not isinstance(document, dict) or document.get("schema") != JOBS_SCHEMA:
        raise BuildFunctionError(f"jobs file schema must be {JOBS_SCHEMA}")
    jobs = document.get("jobs")
    if not isinstance(jobs, list) or not jobs:
        raise BuildFunctionError("jobs file must contain a nonempty jobs array")
    resolved = []
    base = path.parent
    for index, item in enumerate(jobs):
        if not isinstance(item, dict) or set(item) != {"module", "candidate_module", "output_dir"}:
            raise BuildFunctionError(
                f"job {index} must explicitly contain module, candidate_module, and output_dir")
        if not isinstance(item.get("module"), str) or not item["module"]:
            raise BuildFunctionError(f"job {index} needs a nonempty module name")
        if not isinstance(item.get("output_dir"), str) or not item["output_dir"]:
            raise BuildFunctionError(f"job {index} needs an explicit output_dir")
        candidate = item.get("candidate_module")
        if candidate is not None and (not isinstance(candidate, str) or not candidate):
            raise BuildFunctionError(f"job {index} candidate_module must be a path or null")
        candidate_path = strict_file(base / candidate if candidate and not Path(candidate).is_absolute()
                                     else candidate, f"job {index} candidate module") if candidate else None
        raw_output = Path(item["output_dir"])
        target_output = output_path(raw_output if raw_output.is_absolute() else base / raw_output,
                                    f"job {index} output directory")
        resolved.append({"module": item["module"], "candidate_module": candidate_path,
                         "output_dir": target_output})
    return resolved


def validate_jobs(jobs: list[dict], repo: Path, common_inputs: list[Path]) -> list[dict]:
    outputs = []
    for job in jobs:
        name = job["module"]
        if not re.fullmatch(r"[A-Za-z0-9_.-]+", name):
            raise BuildFunctionError(f"unsafe module name: {name!r}")
        directory = job["output_dir"]
        inputs = [*common_inputs]
        if job["candidate_module"] is not None:
            inputs.append(job["candidate_module"])
        validate_external_output(directory, repo, inputs, f"output for {name}")
        for previous_name, previous in outputs:
            if paths_overlap(directory, previous):
                raise BuildFunctionError(
                    f"job output directories overlap: {previous_name}={previous} and {name}={directory}")
        outputs.append((name, directory))
    return jobs


def run_job(job: dict, retail: Path, config: Path, no_cache: bool, repo: Path,
            daemon_socket: Path | None = None) -> dict:
    started = time.perf_counter()
    output = job["output_dir"]
    output.mkdir(parents=True, exist_ok=True)
    local_output = output / "local-build"
    selection_output = output / "selection"
    report_path = local_output / "report.json"
    result = {
        "schema": "single-function-build-result-v1",
        "created_utc": datetime.now(timezone.utc).isoformat(),
        "module": job["module"],
        "candidate_module": str(job["candidate_module"]) if job["candidate_module"] else None,
        "retail_sha256": sha256_file(retail),
        "config_sha256": sha256_file(config),
        "output_dir": str(output),
        "apis": {},
        "elapsed_seconds": {},
        "behavior_status": "comparison-only",
    }
    result["local_report"] = str(report_path)
    compile_start = time.perf_counter()
    try:
        if daemon_socket is not None:
            daemon_result = daemon_build(daemon_socket, job, local_output, no_cache)
            local_report = {
                "cache": daemon_result.get("cache"),
                "timings_seconds": daemon_result.get("timings_seconds", {}),
                "daemon": daemon_result,
            }
        else:
            local_report = compare_module_build.compile_and_compare(
                retail, config, None, job["module"], job["candidate_module"],
                local_output, use_cache=not no_cache)
        compile_error = None
    except (Exception, SystemExit) as exc:
        local_report = None
        compile_error = str(exc) or type(exc).__name__
    compile_elapsed = time.perf_counter() - compile_start
    result["apis"]["compile_and_compare"] = (
        "local-build-daemon:build" if daemon_socket is not None
        else "compare_module_build.compile_and_compare")
    result["elapsed_seconds"]["compile_and_compare"] = round(compile_elapsed, 6)
    result["compile_error"] = compile_error
    if local_report is not None and report_path.is_file():
        result["local_report_sha256"] = sha256_file(report_path)
        result["local_cache"] = local_report.get("cache")
        result["compiler_elapsed_seconds"] = local_report.get("timings_seconds", {}).get("total")
        if local_report.get("daemon") is not None:
            result["daemon_build"] = local_report["daemon"]

    if local_report is None:
        result["status"] = "local_compile_failed"
        result["selection_status"] = "not_run"
    else:
        try:
            preflight_result = prepare_module_selection.preflight_single_report(
                repo, config, retail, report_path, selection_output, compare_module_build)
            preflight_elapsed = preflight_result["preflight_report"]["elapsed_seconds"]["total"]
            result["apis"]["strict_preflight"] = "prepare_module_selection.preflight_single_report"
            result["elapsed_seconds"]["strict_preflight"] = round(preflight_elapsed, 6)
            result["selection_dir"] = str(selection_output)
            result["selection_proposal"] = {
                "path": preflight_result["proposal_path"],
                "sha256": preflight_result["proposal_sha256"],
            }
            result["preflight_report"] = {
                "path": preflight_result["report_path"],
                "sha256": preflight_result["report_sha256"],
            }
            result["selection_status"] = preflight_result["status"]
            result["status"] = ("passed" if preflight_result["exit_code"] == 0
                                else "strict_preflight_rejected")
        except (BuildFunctionError, OSError, ValueError, KeyError, TypeError) as exc:
            result["status"] = "preflight_setup_failed"
            result["selection_status"] = "not_run"
            result["preflight_error"] = str(exc)
    result["elapsed_seconds"]["total"] = round(time.perf_counter() - started, 6)
    summary_path = output / "summary.json"
    write_json(summary_path, result)
    result["summary"] = {"path": str(summary_path), "sha256": sha256_file(summary_path)}
    return result


def parser_for_cli() -> argparse.ArgumentParser:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--retail", required=True, type=Path, help="pinned user-supplied retail ROM")
    parser.add_argument("--config", required=True, type=Path,
                        help="revision-specific selected manifest; never edited")
    group = parser.add_mutually_exclusive_group(required=True)
    group.add_argument("--module", help="one existing selected code module")
    group.add_argument("--jobs-file", type=Path,
                       help=f"explicit {JOBS_SCHEMA} batch description")
    parser.add_argument("--candidate-module", type=Path,
                        help="optional C candidate overrides for one selected module")
    parser.add_argument("--output-dir", type=Path,
                        help="new external evidence directory (single-module mode)")
    parser.add_argument("--jobs", type=int, default=DEFAULT_JOBS,
                        help=f"bounded batch workers, 1..{MAX_JOBS} (default {DEFAULT_JOBS})")
    parser.add_argument("--daemon-socket", type=Path,
                        help="optional settled local daemon Unix socket; direct mode is default")
    parser.add_argument("--no-cache", action="store_true",
                        help="disable local compilation and support-object caches")
    return parser


def parse_jobs(args, retail: Path, config: Path, repo: Path,
               daemon_socket: Path | None = None) -> list[dict]:
    common_inputs = [retail, config]
    if daemon_socket is None and args.daemon_socket:
        daemon_socket = validate_daemon_socket(args.daemon_socket)
    if daemon_socket is not None:
        common_inputs.append(daemon_socket)
    if args.jobs_file is None:
        if not args.module or args.output_dir is None:
            raise BuildFunctionError("single-module mode requires --module and --output-dir")
        if args.jobs != DEFAULT_JOBS:
            raise BuildFunctionError("--jobs applies only with --jobs-file")
        candidate = strict_file(args.candidate_module, "candidate module") if args.candidate_module else None
        output = output_path(args.output_dir, "output directory")
        return validate_jobs([{"module": args.module, "candidate_module": candidate,
                               "output_dir": output}], repo, common_inputs)
    if args.module or args.candidate_module or args.output_dir:
        raise BuildFunctionError("--jobs-file cannot be combined with single-module fields")
    if not 1 <= args.jobs <= MAX_JOBS:
        raise BuildFunctionError(f"--jobs must be between 1 and {MAX_JOBS}")
    jobs_file = strict_file(args.jobs_file, "jobs file")
    if daemon_socket is not None and args.jobs > 2:
        raise BuildFunctionError("the local daemon accepts at most 2 simultaneous builds; use --jobs 1 or 2")
    jobs = load_jobs_file(jobs_file)
    return validate_jobs(jobs, repo, [*common_inputs, jobs_file])


def run_jobs(jobs: list[dict], retail: Path, config: Path, no_cache: bool,
             repo: Path, workers: int, daemon_socket: Path | None = None) -> list[dict]:
    if len(jobs) == 1:
        try:
            return [run_job(jobs[0], retail, config, no_cache, repo, daemon_socket)]
        except Exception as exc:
            return [{"module": jobs[0]["module"], "status": "worker_error",
                     "output_dir": str(jobs[0]["output_dir"]), "error": str(exc)}]
    results = []
    with ThreadPoolExecutor(max_workers=workers, thread_name_prefix="function-build") as pool:
        futures = {pool.submit(run_job, job, retail, config, no_cache, repo,
                               daemon_socket): job
                   for job in jobs}
        for future in as_completed(futures):
            job = futures[future]
            try:
                results.append(future.result())
            except Exception as exc:  # retain other independent jobs' results
                results.append({"module": job["module"], "status": "worker_error",
                                "output_dir": str(job["output_dir"]), "error": str(exc)})
    results.sort(key=lambda row: (row["module"], row.get("candidate_module") or ""))
    return results


def main(argv=None) -> int:
    parser = parser_for_cli()
    args = parser.parse_args(argv)
    try:
        repo = ROOT.resolve(strict=True)
        retail = strict_file(args.retail, "retail ROM")
        config = strict_file(args.config, "manifest")
        daemon_socket = validate_daemon_socket(args.daemon_socket) if args.daemon_socket else None
        jobs = parse_jobs(args, retail, config, repo, daemon_socket)
    except BuildFunctionError as exc:
        parser.error(str(exc))

    all_results = run_jobs(jobs, retail, config, args.no_cache, repo,
                           min(args.jobs, len(jobs)),
                           daemon_socket)
    response = {"schema": "single-function-build-summary-v1",
                "status": ("passed" if all(row.get("status") == "passed" for row in all_results)
                           else "failed"),
                "jobs": len(all_results), "workers": min(args.jobs, len(all_results)),
                "behavior_status": "comparison-only", "results": all_results}
    print(json.dumps(response, sort_keys=True))
    return 0 if response["status"] == "passed" else 2


if __name__ == "__main__":
    raise SystemExit(main())
