#!/usr/bin/env python3
"""Compile one selected GBA code module and compare it with its retail span."""

from __future__ import annotations

import argparse
import hashlib
import json
import os
import platform
import re
import shlex
import shutil
import sqlite3
import subprocess
import sys
import tempfile
import threading
import time
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
RESULT_CACHE_ROOT = ROOT / "build/local-comparison-cache"
TOOL_CACHE_ROOT = ROOT / "build/local-tool-cache"
MANIFEST_CACHE_ROOT = ROOT / "build/local-manifest-index"
sys.path.insert(0, str(ROOT / "tools"))
import build_rom  # noqa: E402
LOADED_TOOL_HASHES = {
    str(Path(path).resolve()): hashlib.sha256(Path(path).read_bytes()).hexdigest()
    for path in (__file__, build_rom.__file__)
}
_TOOLCHAIN_MEMORY = None
_TOOLCHAIN_LOCK = threading.RLock()
_CLANG_DRIVER = None
_TOOL_DIGESTS = {}


def file_stamp(path):
    """Change detection for session memoization, never a persisted content pin."""
    try:
        item = Path(path).stat()
        return (item.st_dev, item.st_ino, item.st_size, item.st_mtime_ns, item.st_ctime_ns)
    except (OSError, TypeError):
        return None


def tool_file_sha(path: Path) -> str:
    """Reuse a binary digest only within this process and unchanged file identity."""
    path = path.resolve()
    with _TOOLCHAIN_LOCK:
        before = file_stamp(path)
        cached = _TOOL_DIGESTS.get(str(path))
        if cached is not None and cached[0] == before:
            return cached[1]
        digest = sha256_file(path)
        if before != file_stamp(path):
            raise ValueError(f"toolchain executable changed while hashing: {path}")
        _TOOL_DIGESTS[str(path)] = (before, digest)
        return digest


def vendor_git_state():
    directory = ROOT / "vendor/agbcc/.git"
    if directory.is_file():
        text = directory.read_text().strip()
        if not text.startswith("gitdir: "):
            return text
        directory = (directory.parent / text[8:]).resolve()
    head = directory / "HEAD"
    text = head.read_text() if head.is_file() else "missing"
    ref = directory / text.strip()[5:] if text.startswith("ref: ") else head
    return (text, file_stamp(ref), file_stamp(directory / "packed-refs"))


CODE_KINDS = {"c", "mixed", "assembly"}
ELF_SECTION_HEADER = re.compile(
    r"^\s*(\d+)\s+(\S+)\s+([0-9a-fA-F]+)\s+"
    r"([0-9a-fA-F]+)\s+([0-9a-fA-F]+)\s+([0-9a-fA-F]+)\s+(\S+)"
)
ALLOWED_OVERRIDES = {
    "source", "kind", "functions", "compiler_flags",
    "external_symbols", "external_exclude_symbols", "trailing_alignment_bytes", "linker_veneer_policy",
    "compiler_data_policy",
}


def sha256_bytes(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def sha256_file(path: Path) -> str:
    digest = hashlib.sha256()
    with path.open("rb") as stream:
        for chunk in iter(lambda: stream.read(1024 * 1024), b""):
            digest.update(chunk)
    return digest.hexdigest()


def _exception_record(error: BaseException) -> dict:
    """Return bounded, JSON-safe details without assuming subprocess output exists."""
    record = {"type": type(error).__name__, "message": str(error)[:8192]}
    for field in ("returncode", "cmd", "stdout", "stderr"):
        value = getattr(error, field, None)
        if value is None:
            continue
        if isinstance(value, bytes):
            value = value.decode("utf-8", errors="replace")
        if field == "cmd" and isinstance(value, (tuple, list)):
            value = [str(part) for part in value]
        elif not isinstance(value, (int, str, list)):
            value = str(value)
        if isinstance(value, str):
            value = value[:65536]
        elif isinstance(value, list):
            value = [str(part)[:4096] for part in value[:256]]
        record[field] = value
    return record


def _compile_substage(error: BaseException, context: dict) -> str | None:
    if context.get("stage") != "compile_module":
        return None
    timings = context.get("compile_stage_timings", {})
    last_timed_stage = next(reversed(timings), None) if timings else None
    command = getattr(error, "cmd", None)
    if isinstance(command, (tuple, list)) and command:
        executable = Path(str(command[0])).name
        if executable == "agbcc":
            return "agbcc"
        if "clang" in executable:
            return "preprocessing"
        if executable == "arm-none-eabi-as":
            return last_timed_stage or "assembly"
        if executable == "arm-none-eabi-ld":
            return last_timed_stage or "linking"
        if executable == "arm-none-eabi-objcopy":
            return last_timed_stage or "binary_extraction"
    return last_timed_stage


def _write_failure_diagnostics(work: Path, output_dir: Path, module: dict,
                               context: dict, error: BaseException) -> None:
    """Copy surviving compiler products before the temporary workspace is removed."""
    stem = module["name"]
    artifact_names = (
        stem + ".i", stem + ".s", stem + ".compiler-original.s",
        stem + ".o", stem + "_external.o", stem + ".elf", stem + ".bin",
        stem + ".compiler-data.json",
    )
    artifact_dir = output_dir / "failure-artifacts"
    artifacts = {}
    copy_errors = []
    for name in artifact_names:
        source = work / name
        if not source.is_file():
            continue
        try:
            artifact_dir.mkdir(parents=True, exist_ok=True)
            destination = artifact_dir / name
            shutil.copyfile(source, destination)
            artifacts[name] = {
                "path": str(destination),
                "size_bytes": destination.stat().st_size,
                "sha256": sha256_file(destination),
            }
        except OSError as copy_error:
            copy_errors.append({"artifact": name, "error": str(copy_error)[:4096]})

    report = {
        "schema": "local-module-build-failure-v1",
        "status": "failed",
        "module": stem,
        "stage": context.get("stage", "unknown"),
        "compile_substage": _compile_substage(error, context),
        "error": _exception_record(error),
        "compile_stage_timings_seconds": context.get("compile_stage_timings", {}),
        "artifacts": artifacts,
        "artifact_copy_errors": copy_errors,
        "inputs": {
            "retail_sha256": context.get("retail_sha256"),
            "manifest_sha256": context.get("manifest_sha256"),
            "source": context.get("source"),
            "source_sha256": context.get("source_sha256"),
            "candidate_module_json": context.get("candidate_module_json"),
            "candidate_module_sha256": context.get("candidate_module_sha256"),
            "compile_inputs": context.get("compile_inputs", []),
            "toolchain_sha256": context.get("toolchain_sha256"),
        },
        "cache": {
            "key": context.get("cache_key"),
            "enabled": bool(context.get("cache_enabled")),
            "failure_published": False,
        },
    }
    path = output_dir / "failure.json"
    build_rom.atomic_write(path, (json.dumps(report, indent=2) + "\n").encode())


class _FailurePreservingTemporaryDirectory:
    """Keep diagnostic evidence if a local compile/validation stage raises."""

    def __init__(self, *, prefix: str, directory: Path, output_dir: Path,
                 module: dict, context: dict):
        self._temporary = tempfile.TemporaryDirectory(prefix=prefix, dir=directory)
        self._output_dir = output_dir
        self._module = module
        self._context = context
        self._path = None

    def __enter__(self):
        self._path = Path(self._temporary.__enter__())
        return str(self._path)

    def __exit__(self, exc_type, exc, traceback):
        if exc is not None:
            try:
                _write_failure_diagnostics(self._path, self._output_dir,
                                           self._module, self._context, exc)
            except Exception as diagnostic_error:
                # Preserve the original compile/validation exception. If even the
                # structured record cannot be written, leave a minimal sidecar.
                fallback = self._output_dir / "failure-diagnostics-error.txt"
                try:
                    fallback.write_text(f"{type(diagnostic_error).__name__}: "
                                        f"{diagnostic_error}\n", encoding="utf-8")
                except OSError:
                    pass
        return self._temporary.__exit__(exc_type, exc, traceback)


def canonical(value) -> str:
    return json.dumps(value, sort_keys=True, separators=(",", ":"))


def load_local_manifest(path: Path, module_name: str | None = None) -> tuple[dict, str]:
    """Read one module and overlapping spans without reparsing the full ledger.

    The source manifest is always content-hashed. Its immutable SQLite index is
    built once and published atomically; no ROM, disassembly or assets enter it.
    """
    raw = path.read_bytes()
    digest = sha256_bytes(raw)
    MANIFEST_CACHE_ROOT.mkdir(parents=True, exist_ok=True)
    entry = MANIFEST_CACHE_ROOT / digest
    valid = False
    try:
        receipt = json.loads((entry / "receipt.json").read_text())
        valid = (receipt["source_sha256"] == digest
                 and sha256_file(entry / "index.sqlite3") == receipt["index_sha256"])
    except (OSError, ValueError, KeyError, TypeError):
        pass
    if not valid:
        # A corrupt published index is rejected; never mix its rows with fresh
        # source data or replace a directory another parallel reader is using.
        if entry.exists():
            raise ValueError("local manifest index is corrupt; remove this inactive cache entry")
        source = json.loads(raw)
        with tempfile.TemporaryDirectory(prefix="index-", dir=MANIFEST_CACHE_ROOT) as temporary:
            staged = Path(temporary) / "entry"
            staged.mkdir()
            database = staged / "index.sqlite3"
            with sqlite3.connect(database) as connection:
                connection.execute("CREATE TABLE modules(name TEXT, start INTEGER, end INTEGER, body TEXT)")
                connection.executemany("INSERT INTO modules VALUES(?,?,?,?)", (
                    (m["name"], m["offset"], m["offset"] + m["size"], canonical(m))
                    for m in source["modules"]))
                connection.execute("CREATE INDEX module_name ON modules(name)")
                connection.execute("CREATE INDEX module_start ON modules(start)")
                connection.execute("CREATE TABLE metadata(body TEXT)")
                connection.execute("INSERT INTO metadata VALUES(?)", (canonical(
                    {k: v for k, v in source.items() if k != "modules"}),))
            (staged / "receipt.json").write_text(canonical({
                "source_sha256": digest, "index_sha256": sha256_file(database)}))
            try:
                staged.rename(entry)
            except OSError:
                if not entry.is_dir():
                    raise
    database = (entry / "index.sqlite3").resolve()
    with sqlite3.connect(database.as_uri() + "?mode=ro&immutable=1", uri=True) as connection:
        manifest = json.loads(connection.execute("SELECT body FROM metadata").fetchone()[0])
        if module_name is None:
            manifest["modules"] = []
            return manifest, digest
        rows = connection.execute("SELECT start,end,body FROM modules WHERE name=?", (module_name,)).fetchall()
        if len(rows) != 1:
            raise ValueError(f"expected exactly one selected module named {module_name!r}")
        start, end, body = rows[0]
        overlaps = connection.execute(
            "SELECT name,start,end FROM modules WHERE start<? AND end>? AND name!=?",
            (end, start, module_name)).fetchall()
    manifest["modules"] = [json.loads(body), *[
        {"name": name, "offset": begin, "size": finish - begin}
        for name, begin, finish in overlaps]]
    return manifest, digest


def discover_c_dependencies(module: dict, source: Path) -> list[Path]:
    """Use the production preprocessor, including conditional/macro includes."""
    command = build_rom.c_preprocessor_command(module, source)
    dependencies = subprocess.check_output(
        [*command, "-M", "-MT", "module"], text=True)
    # clang emits Make escaping, including backslash-newline continuation and
    # doubled dollar signs. There is one explicit target, independent of paths.
    prefix = "module:"
    if not dependencies.startswith(prefix):
        raise ValueError("unexpected preprocessor dependency target")
    words = shlex.split(dependencies[len(prefix):].replace("\\\n", ""), posix=True)
    paths = sorted({Path(word.replace("$$", "$")).resolve() for word in words}, key=str)
    if source.resolve() not in paths or any(not path.is_file() for path in paths):
        raise ValueError("preprocessor dependency set is missing a compile input")
    return paths


def snapshot_compile_inputs(module: dict, source: Path, config_path: Path,
                            candidate_path: Path | None, toolchain: dict) -> tuple[list[dict], list[Path]]:
    """Capture real dependencies before compiling, never reconstruct old pins."""
    paths: dict[Path, str] = {}
    dependencies = discover_c_dependencies(module, source) if module["kind"] in {"c", "mixed"} else [source]
    for path in dependencies:
        paths[path] = "source" if path == source else "header"
    paths[config_path] = "config"
    if candidate_path:
        paths[candidate_path.resolve()] = "candidate"
    for path in (Path(__file__), Path(build_rom.__file__)):
        paths[path.resolve()] = "build_tool"
    paths[(ROOT / "config/symbols.ld").resolve()] = "link"
    if module.get("external_symbols", module["kind"] in {"c", "mixed"}):
        paths[(ROOT / "asm/external_thumb_symbols.s").resolve()] = "link"
    for item in toolchain["tools"].values():
        paths[Path(item["path"]).resolve()] = "toolchain"
    records = [{"path": str(path), "role": role,
                "sha256": tool_file_sha(path) if role == "toolchain" else sha256_file(path)}
               for path, role in sorted(paths.items(), key=lambda item: str(item[0]))]
    for record in records:
        if record["role"] == "build_tool" and record["sha256"] != LOADED_TOOL_HASHES[record["path"]]:
            raise ValueError("build tool changed after import; restart this build process")
    return records, dependencies


def verify_compile_inputs(records: list[dict]) -> None:
    for item in records:
        path = Path(item["path"])
        digest = tool_file_sha(path) if item["role"] == "toolchain" else sha256_file(path)
        if digest != item["sha256"]:
            raise ValueError(f"compile input changed during build: {path}")


def local_cache_allowed(module: dict, source: Path, dependencies: list[Path]) -> bool:
    # C includes are resolved by clang. Assembler/linker includes need a separate
    # dependency resolver; remain uncached instead of guessing their closure.
    if module["kind"] != "c":
        return False
    inputs = [ROOT / "config/symbols.ld", *dependencies]
    if module.get("external_symbols", module["kind"] in {"c", "mixed"}):
        inputs.append(ROOT / "asm/external_thumb_symbols.s")
    if any(re.search(r"(?mi)\.(?:include|incbin)\b|\b(?:asm|__asm__|__asm)\b",
                     path.read_text(errors="replace")) for path in inputs):
        return False
    return not re.search(r"\b(?:INCLUDE|INPUT|GROUP|STARTUP|SEARCH_DIR)\b",
                         (ROOT / "config/symbols.ld").read_text())


def restore_local_cache(cache: Path, key: str, output: Path, inputs: list[dict],
                        total_start: float) -> dict | None:
    entry = cache / key
    try:
        receipt = json.loads((entry / "receipt.json").read_text())
        if receipt["key"] != key:
            return None
        for name, digest in receipt["files"].items():
            if Path(name).name != name or sha256_file(entry / name) != digest:
                return None
        cached = json.loads((entry / "report.json").read_text())
        verify_compile_inputs(inputs)
    except (OSError, ValueError, KeyError, TypeError):
        return None
    output.mkdir(parents=True, exist_ok=True)
    old_output = str(Path(cached["segments"][0]["binary"]).parent)

    def relocate(value):
        if isinstance(value, dict):
            return {k: relocate(v) for k, v in value.items()}
        if isinstance(value, list):
            return [relocate(v) for v in value]
        if isinstance(value, str) and value.startswith(old_output + "/"):
            return str(output) + value[len(old_output):]
        return value

    report = relocate(cached)
    for name in receipt["files"]:
        if name != "report.json":
            shutil.copyfile(entry / name, output / name)
    report["cache"] = {"hit": True, "key": key, "compiled_this_invocation": False,
                       "origin_report_sha256": receipt["files"]["report.json"]}
    report["original_timings_seconds"] = report["timings_seconds"]
    report["timings_seconds"] = {"total": round(time.perf_counter() - total_start, 6)}
    (output / "report.json").write_text(json.dumps(report, indent=2) + "\n")
    return report


def publish_local_cache(cache: Path, key: str, output: Path) -> None:
    cache.mkdir(parents=True, exist_ok=True)
    with tempfile.TemporaryDirectory(prefix="publish-", dir=cache) as temporary:
        staged = Path(temporary) / "entry"
        staged.mkdir()
        files = {}
        for path in output.iterdir():
            if path.is_file() and path.name != ".local-build.lock":
                shutil.copyfile(path, staged / path.name)
                files[path.name] = sha256_file(staged / path.name)
        (staged / "receipt.json").write_text(canonical({"key": key, "files": files}))
        try:
            staged.rename(cache / key)
        except OSError:
            # Another independent method build may have published this same key.
            # Leave its immutable entry intact; corrupt entries are cache misses.
            if not (cache / key).is_dir():
                raise


def validate_revision(retail: Path, config: dict) -> bytes:
    if not retail.is_file():
        raise ValueError(f"retail input does not exist: {retail}")
    data = retail.read_bytes()
    if len(data) != config.get("size") or sha256_bytes(data) != config.get("sha256"):
        raise ValueError("retail input revision mismatch; refusing local compile")
    return data


def find_module(config: dict, name: str) -> dict:
    modules = [module for module in config.get("modules", []) if module.get("name") == name]
    if len(modules) != 1:
        raise ValueError(f"expected exactly one selected module named {name!r}")
    return dict(modules[0])


def validate_module_layout(module: dict, config: dict) -> None:
    name = module.get("name", "<unnamed>")
    if module.get("kind") not in CODE_KINDS:
        raise ValueError(f"{name}: local compiler accepts only selected C/mixed/assembly modules")
    if not isinstance(module.get("source"), str) or not module["source"]:
        raise ValueError(f"{name}: source path is required")
    offset, size = module.get("offset"), module.get("size")
    if type(offset) is not int or type(size) is not int or offset < 0 or size < 1:
        raise ValueError(f"{name}: invalid module span")
    if offset + size > config.get("size", 0):
        raise ValueError(f"{name}: module span exceeds the configured ROM")
    functions = module.get("functions")
    if functions is None:
        functions = [{"name": name, "offset": offset, "size": size}]
        module["functions"] = functions
    if not isinstance(functions, list) or not functions:
        raise ValueError(f"{name}: at least one declared function/entry is required")
    seen = set()
    for function in functions:
        if not isinstance(function, dict) or not isinstance(function.get("name"), str):
            raise ValueError(f"{name}: malformed function entry")
        entry_name = function["name"]
        if entry_name in seen:
            raise ValueError(f"{name}: duplicate function entry {entry_name}")
        seen.add(entry_name)
        function_offset, function_size = function.get("offset"), function.get("size")
        if type(function_offset) is not int or type(function_size) is not int or function_size < 1:
            raise ValueError(f"{name}: invalid span for entry {entry_name}")
        if function_offset < offset or function_offset + function_size > offset + size:
            raise ValueError(f"{name}: entry {entry_name} exceeds the selected module span")
    if not re.fullmatch(r"[A-Za-z0-9_.-]+", name):
        raise ValueError(f"unsafe module name: {name!r}")


def apply_candidate_overrides(module: dict, candidate_path: Path | None,
                              capture: dict | None = None) -> tuple[dict, str | None]:
    if candidate_path is None:
        return module, None
    if not candidate_path.is_file():
        raise ValueError(f"candidate module JSON does not exist: {candidate_path}")
    candidate_raw = candidate_path.read_bytes()
    candidate = json.loads(candidate_raw)
    if capture is not None:
        capture["sha256"] = sha256_bytes(candidate_raw)
    if not isinstance(candidate, dict):
        raise ValueError("candidate module JSON must be an object")
    unknown = sorted(set(candidate) - ALLOWED_OVERRIDES)
    if unknown:
        raise ValueError(f"candidate may override only {sorted(ALLOWED_OVERRIDES)}; found {unknown}")
    if "source" in candidate:
        source_path = Path(candidate["source"]).expanduser()
        if not source_path.is_absolute():
            source_path = ROOT / source_path
        source_path = source_path.resolve()
        if not source_path.is_file():
            raise ValueError(f"candidate source does not exist: {source_path}")
        module["source"] = str(source_path)
    original_kind = module["kind"]
    for key in ("kind", "functions", "compiler_flags", "external_symbols",
                "external_exclude_symbols", "trailing_alignment_bytes", "linker_veneer_policy",
                "compiler_data_policy"):
        if key in candidate:
            module[key] = candidate[key]
    if original_kind == "assembly" and module["kind"] in {"c", "mixed"}:
        # These metadata defaults follow build_rom's C module behavior rather
        # than inheriting assembly-only settings from the selected module.
        if "external_symbols" not in candidate:
            module["external_symbols"] = True
        if "external_exclude_symbols" not in candidate:
            module["external_exclude_symbols"] = []
        if "trailing_alignment_bytes" not in candidate:
            module["trailing_alignment_bytes"] = 0
    if type(module.get("external_symbols", module["kind"] in {"c", "mixed"})) is not bool:
        raise ValueError("external_symbols must be a boolean")
    exclusions = module.get("external_exclude_symbols", [])
    if (not isinstance(exclusions, list) or
            any(not isinstance(symbol, str) or not symbol.isidentifier() for symbol in exclusions)):
        raise ValueError("external_exclude_symbols must be a list of valid identifiers")
    alignment = module.get("trailing_alignment_bytes", 0)
    if type(alignment) is not int or alignment < 0:
        raise ValueError("trailing_alignment_bytes must be a non-negative integer")
    return module, sha256_file(Path(module["source"]).resolve())


def diff_bytes(reference: bytes, generated: bytes, rom_offset: int, rom_base: int) -> dict:
    common = min(len(reference), len(generated))
    differences = []
    for index in range(max(len(reference), len(generated))):
        reference_byte = reference[index] if index < len(reference) else None
        generated_byte = generated[index] if index < len(generated) else None
        if reference_byte != generated_byte:
            differences.append({
                "rom_offset": rom_offset + index,
                "gba_address": rom_base + rom_offset + index,
                "reference_byte": reference_byte,
                "generated_byte": generated_byte,
            })
    matched = sum(reference[index] == generated[index] for index in range(common))
    return {
        "reference_size": len(reference),
        "generated_size": len(generated),
        "common_compared_bytes": common,
        "matching_bytes": matched,
        "differing_bytes_in_common_span": sum(
            reference[index] != generated[index] for index in range(common)),
        "missing_generated_bytes": max(0, len(reference) - len(generated)),
        "overflow_bytes": max(0, len(generated) - len(reference)),
        "differences": differences,
    }


def source_mode(source: Path, kind: str) -> str:
    if kind in {"c", "mixed"}:
        return "thumb"
    text = source.read_text(errors="replace")
    has_thumb = bool(re.search(r"(?m)^\s*\.thumb(?:\s|$)", text)) or ".thumb_func" in text
    has_arm = bool(re.search(r"(?m)^\s*\.arm(?:\s|$)", text))
    if has_thumb and not has_arm:
        return "thumb"
    if has_arm and not has_thumb:
        return "arm"
    return "mixed-or-unspecified"


def entry_records(module: dict, source: Path, rom_base: int) -> list[dict]:
    mode = source_mode(source, module["kind"])
    entries = []
    for function in module["functions"]:
        if function["name"].startswith("Compiler"):
            continue
        address = rom_base + function["offset"]
        entries.append({
            "name": function["name"],
            "rom_offset": function["offset"],
            "gba_address": address,
            "mode": mode,
            "thumb_entry_address": (address | 1) if mode == "thumb" else None,
        })
    return entries


def toolchain_versions() -> dict:
    # One daemon/batch invocation reuses version queries while executable,
    # developer-selection and vendor-ref metadata stay unchanged. Real file
    # content hashes are still captured and verified for every compile report.
    with _TOOLCHAIN_LOCK:
        return _toolchain_versions()


def _toolchain_versions() -> dict:
    global _TOOLCHAIN_MEMORY, _CLANG_DRIVER
    executables = (
        ("agbcc", ROOT / "build/toolchain/agbcc"),
        ("clang", shutil.which("clang")),
        ("assembler", shutil.which("arm-none-eabi-as")),
        ("linker", shutil.which("arm-none-eabi-ld")),
        ("objcopy", shutil.which("arm-none-eabi-objcopy")),
        ("objdump", shutil.which("arm-none-eabi-objdump")),
        ("readelf", shutil.which("arm-none-eabi-readelf")),
        ("nm", shutil.which("arm-none-eabi-nm")),
    )
    environment = {key: os.environ.get(key)
                   for key in ("DEVELOPER_DIR", "SDKROOT", "TOOLCHAINS")}
    selection = (canonical(environment), file_stamp("/var/db/xcode_select_link"),
                 str(Path("/var/db/xcode_select_link").resolve()))
    if sys.platform == "darwin":
        if _CLANG_DRIVER is None or _CLANG_DRIVER[0] != selection:
            driver = subprocess.check_output(["xcrun", "--find", "clang"], text=True).strip()
            _CLANG_DRIVER = (selection, driver)
        executables += (("clang_driver", _CLANG_DRIVER[1]),)
    stamp = (tuple((name, str(path), file_stamp(path)) for name, path in executables),
             selection, vendor_git_state(), str(TOOL_CACHE_ROOT))
    if _TOOLCHAIN_MEMORY is not None and _TOOLCHAIN_MEMORY[0] == stamp:
        return _TOOLCHAIN_MEMORY[1]
    identities = {}
    for name, executable in executables:
        if executable is None or not Path(executable).exists():
            raise ValueError(f"required tool is missing: {name}")
        identities[name] = {"path": str(executable), "sha256": tool_file_sha(Path(executable))}
    try:
        revision = subprocess.check_output(
            ["git", "-C", str(ROOT / "vendor/agbcc"), "rev-parse", "HEAD"],
            text=True, stderr=subprocess.DEVNULL).strip()
    except subprocess.CalledProcessError:
        revision = "unknown"
    # Apple's /usr/bin/clang can dispatch to a selected developer toolchain;
    # query that one version on each invocation, not just the launcher hash.
    clang_version = build_rom.version_line([identities["clang"]["path"], "--version"])
    identity = {"executables": identities, "agbcc_revision": revision,
                "clang_version": clang_version, "environment": environment,
                "python": sys.version, "platform": platform.platform()}
    key = sha256_bytes(canonical(identity).encode())
    cache_path = TOOL_CACHE_ROOT / "versions" / (key + ".json")
    try:
        cached = json.loads(cache_path.read_text())
        if (cached["identity"] == identity
                and sha256_bytes(canonical(cached["value"]).encode()) == cached["sha256"]):
            _TOOLCHAIN_MEMORY = (stamp, cached["value"])
            return cached["value"]
    except (OSError, ValueError, KeyError, TypeError):
        pass
    tools = {}
    for name, executable in executables:
        if executable is None or not Path(executable).exists():
            raise ValueError(f"required tool is missing: {name}")
        executable = str(executable)
        if name == "agbcc":
            version = build_rom.version_line([executable, "--version"])
        else:
            version = clang_version if name in {"clang", "clang_driver"} else build_rom.version_line([executable, "--version"])
        tools[name] = {"path": executable, "version": version,
                       "revision": revision if name == "agbcc" else None}
    value = {"tools": tools, "python": sys.version.splitlines()[0], "platform": platform.platform()}
    cache_path.parent.mkdir(parents=True, exist_ok=True)
    build_rom.atomic_write(cache_path, canonical({"identity": identity, "value": value,
                                                 "sha256": sha256_bytes(canonical(value).encode())}).encode())
    _TOOLCHAIN_MEMORY = (stamp, value)
    return value


# Both build paths must reject allocated bytes omitted by .text extraction.
parse_elf_sections = build_rom.parse_elf_sections
validate_elf_load_sections = build_rom.validate_elf_load_sections


def compile_and_compare(retail_path: Path, config_path: Path, config: dict, module_name: str,
                        candidate_path: Path | None, output_dir: Path, *,
                        use_cache: bool = True) -> dict:
    output = output_dir.resolve()
    if output == ROOT or output.is_relative_to(ROOT):
        raise ValueError("--output-dir must be outside the source tree")
    if any(path.resolve().is_relative_to(output) for path in (retail_path, config_path)):
        raise ValueError("output directory must not contain the retail/config input")
    if output.exists() and any(output.iterdir()):
        raise ValueError("--output-dir must be new or empty; refusing to overwrite prior evidence")
    output.mkdir(parents=True, exist_ok=True)
    lock = output / ".local-build.lock"
    descriptor = os.open(lock, os.O_CREAT | os.O_EXCL | os.O_WRONLY, 0o600)
    os.close(descriptor)
    try:
        return _compile_and_compare(retail_path, config_path, config, module_name,
                                    candidate_path, output, use_cache=use_cache)
    finally:
        lock.unlink()


def _compile_and_compare(retail_path: Path, config_path: Path, config: dict, module_name: str,
                         candidate_path: Path | None, output_dir: Path, *,
                         use_cache: bool = True) -> dict:
    retail_path = retail_path.resolve()
    config_path = config_path.resolve()
    output_dir = output_dir.resolve()
    if output_dir == ROOT or output_dir.is_relative_to(ROOT):
        raise ValueError("--output-dir must be outside the source tree")
    if output_dir == retail_path or output_dir == config_path or retail_path.is_relative_to(output_dir):
        raise ValueError("output directory must not contain or replace the retail/config input")
    if output_dir.exists() and any(p.name != ".local-build.lock" for p in output_dir.iterdir()):
        raise ValueError("--output-dir must be new or empty; refusing to overwrite prior evidence")

    total_start = time.perf_counter()
    manifest, manifest_sha = load_local_manifest(config_path, module_name)
    retail = validate_revision(retail_path, manifest)
    retail_sha = sha256_bytes(retail)
    module = find_module(manifest, module_name)
    original_module = dict(module)
    validate_module_layout(module, manifest)
    candidate_capture = {}
    module, candidate_source_sha = apply_candidate_overrides(module, candidate_path, candidate_capture)
    validate_module_layout(module, manifest)
    source_path = Path(module["source"]).expanduser()
    if not source_path.is_absolute():
        source_path = ROOT / source_path
    source_path = source_path.resolve()
    if not source_path.is_file():
        raise ValueError(f"source does not exist: {source_path}")
    source_sha = candidate_source_sha or sha256_file(source_path)
    module["source"] = str(source_path)

    selected = manifest["modules"]
    start = module["offset"]
    end = start + module["size"]
    for other in selected:
        if other["name"] == module_name:
            continue
        other_start = other.get("offset", 0)
        other_end = other_start + other.get("size", 0)
        if start < other_end and other_start < end:
            raise ValueError(f"{module_name}: selected span overlaps {other['name']}")
    reference = retail[start:end]
    if len(reference) != module["size"]:
        raise ValueError(f"{module_name}: selected reference span is truncated")

    provenance_start = time.perf_counter()
    toolchain = toolchain_versions()
    compile_inputs, dependencies = snapshot_compile_inputs(
        module, source_path, config_path, candidate_path, toolchain)
    captured = {record["role"]: record["sha256"] for record in compile_inputs
                if record["role"] in {"source", "config", "candidate"}}
    if captured.get("source") != source_sha or captured.get("config") != manifest_sha:
        raise ValueError("source/config changed between parsing and compile input capture")
    if candidate_path and captured.get("candidate") != candidate_capture["sha256"]:
        raise ValueError("candidate configuration changed between parsing and input capture")
    cache_key = sha256_bytes(canonical({
        "schema": "local-comparison-cache-v1", "module": module,
        "inputs": compile_inputs, "toolchain": toolchain,
        "rom_base": manifest["rom_base"], "retail_sha256": retail_sha,
    }).encode())
    cache = RESULT_CACHE_ROOT
    cache_enabled = use_cache and local_cache_allowed(module, source_path, dependencies)
    if cache_enabled:
        reused = restore_local_cache(cache, cache_key, output_dir, compile_inputs, total_start)
        if reused is not None:
            return reused
    provenance_seconds = time.perf_counter() - provenance_start

    output_dir.mkdir(parents=True, exist_ok=True)
    (ROOT / "build/local-modules").mkdir(parents=True, exist_ok=True)
    compile_start = time.perf_counter()
    failure_context = {
        "stage": "compile_module",
        "compile_stage_timings": {},
        "retail_sha256": retail_sha,
        "manifest_sha256": manifest_sha,
        "source": str(source_path),
        "source_sha256": source_sha,
        "candidate_module_json": str(candidate_path.resolve()) if candidate_path else None,
        "candidate_module_sha256": candidate_capture.get("sha256"),
        "compile_inputs": compile_inputs,
        "toolchain_sha256": sha256_bytes(canonical(toolchain).encode()),
        "cache_key": cache_key,
        "cache_enabled": cache_enabled,
    }
    with _FailurePreservingTemporaryDirectory(
            prefix=f"{module_name}-", directory=ROOT / "build/local-modules",
            output_dir=output_dir, module=module, context=failure_context) as temp:
        work = Path(temp)
        # compile_module resolves relative source paths against ROOT; absolute source paths
        # remain absolute and allow isolated candidate files without copying them into Git.
        compile_stages = {}
        failure_context["compile_stage_timings"] = compile_stages
        generated = build_rom.compile_module(
            module, work, manifest["rom_base"], None, retail,
            tool_cache_dir=TOOL_CACHE_ROOT if use_cache else None,
            stage_timings=compile_stages)
        compile_seconds = time.perf_counter() - compile_start

        elf = work / (module["name"] + ".elf")
        failure_context["stage"] = "ELF load-section validation"
        checked_sections = validate_elf_load_sections(elf)

        entry_start = time.perf_counter()
        failure_context["stage"] = "linked function-entry validation"
        entries_checked = build_rom.check_linked_function_entries(module, work, manifest["rom_base"])
        entry_seconds = time.perf_counter() - entry_start

        binary = work / (module["name"] + ".bin")
        disassembly_start = time.perf_counter()
        failure_context["stage"] = "linked disassembly and symbols"
        disassembly = subprocess.check_output(
            [shutil.which("arm-none-eabi-objdump"), "-d", "-r", "--wide", str(elf)], text=True)
        symbols = subprocess.check_output(
            [shutil.which("arm-none-eabi-nm"), "-n", str(elf)], text=True)
        disassembly_seconds = time.perf_counter() - disassembly_start
        diff_start = time.perf_counter()
        diff = diff_bytes(reference, generated, start, manifest["rom_base"])
        diff_seconds = time.perf_counter() - diff_start

        stem = module["name"]
        output_elf = output_dir / f"{stem}.elf"
        output_binary = output_dir / f"{stem}.bin"
        output_disassembly = output_dir / f"{stem}.disassembly.txt"
        output_symbols = output_dir / f"{stem}.symbols.txt"
        output_diff = output_dir / f"{stem}.diff.json"
        output_reference = output_dir / f"{stem}.reference.bin"
        output_reference_disassembly = output_dir / f"{stem}.reference.disassembly.txt"
        failure_context["stage"] = "artifact publication and input revalidation"
        shutil.copyfile(elf, output_elf)
        # compile_module returns the declared, alignment-trimmed module span;
        # its intermediate .bin may still contain linker alignment bytes.
        output_binary.write_bytes(generated)
        output_disassembly.write_text(disassembly)
        output_symbols.write_text(symbols)
        output_diff.write_text(json.dumps(diff, indent=2) + "\n")
        output_reference.write_bytes(reference)
        failure_context["stage"] = "reference disassembly"
        reference_command = [shutil.which("arm-none-eabi-objdump"), "-D", "-b", "binary",
                             "-m", "arm", f"--adjust-vma={manifest['rom_base'] + start}"]
        if source_mode(source_path, module["kind"]) == "thumb":
            reference_command += ["-M", "force-thumb"]
        output_reference_disassembly.write_text(subprocess.check_output(
            [*reference_command, str(output_reference)], text=True))
        artifacts = {}
        for label, path in (("binary", output_binary), ("elf", output_elf),
                            ("disassembly", output_disassembly)):
            artifacts[label] = {"path": str(path), "sha256": sha256_file(path)}
        for label, suffix in (("preprocessed", ".i"), ("compiler_assembly", ".s")):
            path = work / (stem + suffix)
            if module["kind"] in {"c", "mixed"} and path.is_file():
                destination = output_dir / (stem + suffix)
                shutil.copyfile(path, destination)
                artifacts[label] = {"path": str(destination), "sha256": sha256_file(destination)}
        failure_context["stage"] = "compile-input revalidation"
        verify_compile_inputs(compile_inputs)
        if (module["kind"] in {"c", "mixed"}
                and discover_c_dependencies(module, source_path) != dependencies):
            raise ValueError("preprocessor dependency closure changed during build")
        fits = len(generated) <= module["size"]
        entries = entry_records(module, source_path, manifest["rom_base"])
        segment = {
            "module": module_name,
            "rom_offset": start,
            "gba_address": manifest["rom_base"] + start,
            "reference_size": module["size"],
            "generated_size": len(generated),
            "binary": str(output_binary),
            "binary_sha256": sha256_bytes(generated),
            "fits": fits,
            "functions": entries,
            "entry_validation": {"passed": True, "checked_entries": entries_checked},
            "elf_section_validation": {
                "passed": True,
                "policy": "nonempty allocated/load sections outside .text are unsupported",
                "sections": checked_sections,
            },
            "compiler_data_normalization": (
                json.loads((work / (module_name + ".compiler-data.json")).read_text())
                if module.get("compiler_data_policy") else None),
            "linker_veneers": build_rom.verified_linker_veneers(module, work, manifest["rom_base"]),
            "source": str(source_path),
            "source_sha256": source_sha,
            "candidate_module_json": str(candidate_path.resolve()) if candidate_path else None,
            "elf": str(output_elf),
            "disassembly": str(output_disassembly),
            "symbols": str(output_symbols),
            "diff": str(output_diff),
            "diff_sha256": sha256_file(output_diff),
            "reference_binary": str(output_reference),
            "reference_disassembly": str(output_reference_disassembly),
            "matching_bytes": diff["matching_bytes"],
            "differing_bytes": diff["differing_bytes_in_common_span"],
            "overflow_bytes": diff["overflow_bytes"],
            "missing_generated_bytes": diff["missing_generated_bytes"],
            "unmatched_retail_bytes": max(0, module["size"] - diff["matching_bytes"]),
            "compiled_module_only": True,
            "neighbor_bytes_overlaid": False,
        }
        report = {
            "schema": "local-module-build-v1",
            "retail_sha256": retail_sha,
            "manifest_sha256": manifest_sha,
            "baseline_module": {"name": original_module["name"], "kind": original_module["kind"],
                                "rom_offset": start, "reference_size": module["size"]},
            "module_configuration": {
                "kind": module["kind"],
                "compiler_flags": (module.get("compiler_flags", ["-O0", "-mthumb-interwork"])
                                   if module["kind"] in {"c", "mixed"} else None),
                "external_symbols": module.get("external_symbols", module["kind"] in {"c", "mixed"}),
                "external_exclude_symbols": module.get("external_exclude_symbols", []),
                "trailing_alignment_bytes": module.get("trailing_alignment_bytes", 0),
                "functions": module["functions"],
                **({"linker_veneer_policy": module["linker_veneer_policy"]}
                   if "linker_veneer_policy" in module else {}),
                **({"compiler_data_policy": module["compiler_data_policy"]}
                   if "compiler_data_policy" in module else {}),
            },
            "segments": [segment],
            "toolchain": toolchain,
            "compile_inputs": {
                "schema": "local-compile-inputs-v1",
                "capture": "before-and-after-compilation",
                "files": compile_inputs,
                "effective_module": module,
                "dependency_paths": [str(path) for path in dependencies],
                "artifacts": artifacts,
                "toolchain_sha256": sha256_bytes(canonical(toolchain).encode()),
            },
            "cache": {"hit": False, "key": cache_key, "enabled": cache_enabled,
                      "compiled_this_invocation": True},
            "timings_seconds": {
                "input_provenance": round(provenance_seconds, 6),
                "compile_and_link": round(compile_seconds, 6),
                "compile_stages": compile_stages,
                "entry_validation": round(entry_seconds, 6),
                "disassembly_and_symbols": round(disassembly_seconds, 6),
                "byte_comparison": round(diff_seconds, 6),
                "total": round(time.perf_counter() - total_start, 6),
            },
            "scope_limits": [
                "Only this module was compiled; external selected dependencies were not rebuilt.",
                "This report is not a full ROM build or runtime behavior validation.",
                "fits=false means generated bytes exceed the declared span; no neighbor bytes were overlaid.",
                "A shorter generated span leaves remaining retail bytes outside the local binary unchanged.",
            ],
        }
        failure_context["stage"] = "success report publication"
        output_report = output_dir / "report.json"
        output_report.write_text(json.dumps(report, indent=2) + "\n")
    if cache_enabled:
        publish_local_cache(cache, cache_key, output_dir)
    return report


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--retail", required=True, type=Path, help="pinned user-supplied retail ROM")
    parser.add_argument("--config", required=True, type=Path, help="revision-specific selected manifest")
    parser.add_argument("--module", required=True, help="name of one existing selected module")
    parser.add_argument("--candidate-module", type=Path,
                        help="optional JSON object overriding existing code-module build metadata")
    parser.add_argument("--output-dir", required=True, type=Path,
                        help="new or empty directory outside the source tree")
    parser.add_argument("--no-cache", action="store_true",
                        help="compile again without local result or tool-object reuse")
    args = parser.parse_args()
    try:
        report = compile_and_compare(args.retail, args.config, None, args.module,
                                     args.candidate_module, args.output_dir, use_cache=not args.no_cache)
    except (OSError, ValueError, json.JSONDecodeError, subprocess.CalledProcessError,
            SystemExit) as error:
        print(f"local module build failed: {error}", file=sys.stderr)
        failure_report = args.output_dir.resolve() / "failure.json"
        if failure_report.is_file():
            print(f"failure diagnostics: {failure_report}", file=sys.stderr)
        return 2
    segment = report["segments"][0]
    print(f"{args.module}: {segment['matching_bytes']}/{segment['reference_size']} bytes match; "
          f"generated={segment['generated_size']} fits={segment['fits']} report="
          f"{Path(args.output_dir).resolve() / 'report.json'}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
