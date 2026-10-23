#!/usr/bin/env python3
"""Prepare a hash-pinned C module selection proposal from local build reports.

This is a read-only preflight. It never edits a manifest or builds a ROM.
"""
from __future__ import annotations

import argparse
import hashlib
import importlib.util
import json
import re
import subprocess
import sys
import tempfile
import time
from pathlib import Path


RETAIL_SHA256 = "43fc8204c6dceee58828aebc7af0c72eb807e99f35ad641c8bb0a4fa8b6edc19"
PIN_SCHEMA = "module-compile-input-pins-v1"
NATIVE_COMPILE_INPUT_SCHEMA = "local-compile-inputs-v1"
INCLUDE_RE = re.compile(r"^\s*#\s*include\s*([<\"])([^>\"]+)[>\"]")
INCLUDE_DIRECTIVE_RE = re.compile(r"^\s*#\s*include\b")
BRANCH_RE = re.compile(
    r"\b(?:b(?:eq|ne|cs|cc|mi|pl|vs|vc|hi|ls|ge|lt|gt|le|hs|lo)|b)"
    r"(?:\.n)?\s+(?:0x)?([0-9a-fA-F]+)\b",
    re.IGNORECASE,
)
POLICY_NAMES = {
    "agbcc-unreferenced-switch-pointer-v1",
    "agbcc-unreferenced-symbol-pointer-v1",
    "agbcc-unreferenced-pointer-objects-v1",
}
ASM_ONLY_FIELDS = {
    "instructions_bytes", "literal_bytes", "dispatch_table_bytes", "padding_bytes",
    "inline_assembly_bytes", "assembly_instruction_bytes", "assembly_ratio",
    "components", "component", "mix", "mixed_components",
}
REPORT_CONFIG_KEYS = {
    "kind", "compiler_flags", "external_symbols", "external_exclude_symbols",
    "trailing_alignment_bytes", "functions", "linker_veneer_policy",
    "compiler_data_policy",
}


class PreflightError(ValueError):
    """An input failed a preflight gate."""


def require(condition: bool, message: str) -> None:
    if not condition:
        raise PreflightError(message)


def canonical(value) -> str:
    return json.dumps(value, sort_keys=True, separators=(",", ":"), ensure_ascii=True)


def sha256_bytes(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def sha256_file(path: Path) -> str:
    digest = hashlib.sha256()
    with path.open("rb") as stream:
        for chunk in iter(lambda: stream.read(1024 * 1024), b""):
            digest.update(chunk)
    return digest.hexdigest()


def write_json(path: Path, value) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(json.dumps(value, sort_keys=True, indent=2, ensure_ascii=True) + "\n")


def load_json(path: Path):
    try:
        value = json.loads(path.read_text())
    except Exception as exc:
        raise PreflightError(f"invalid JSON at {path}: {exc}") from exc
    return value


def resolve_path(value, repo: Path, label: str) -> Path:
    require(isinstance(value, str) and value, f"{label}: path is missing")
    path = Path(value).expanduser()
    if not path.is_absolute():
        path = repo / path
    try:
        return path.resolve(strict=True)
    except OSError as exc:
        raise PreflightError(f"{label}: file does not exist: {path}") from exc


def repo_relative(path: Path, repo: Path, label: str) -> str:
    try:
        return path.resolve(strict=True).relative_to(repo.resolve(strict=True)).as_posix()
    except ValueError as exc:
        raise PreflightError(f"{label}: file is outside the repository root") from exc


def manifest_module(manifest: dict, name: str) -> dict:
    matches = [m for m in manifest.get("modules", []) if m.get("name") == name]
    require(len(matches) == 1,
            f"manifest must contain exactly one module named {name}; found {len(matches)}")
    return matches[0]


def json_pointer(value, pointer: str):
    require(pointer == "" or pointer.startswith("/"), "pin basis has an invalid JSON pointer")
    current = value
    for raw in pointer.split("/")[1:]:
        key = raw.replace("~1", "/").replace("~0", "~")
        if isinstance(current, list):
            current = current[int(key)]
        elif isinstance(current, dict):
            current = current[key]
        else:
            raise KeyError(pointer)
    return current


def validate_basis(record: dict, expected, repo: Path, cache: dict, label: str) -> None:
    basis = record.get("basis")
    require(isinstance(basis, dict), f"{label}: compile-time pin basis is missing")
    path = resolve_path(basis.get("path"), repo, f"{label} basis")
    if str(path) not in cache:
        cache[str(path)] = sha256_file(path)
    actual_hash = cache[str(path)]
    require(actual_hash == basis.get("sha256"), f"{label}: pin-basis file hash changed")
    try:
        if str(path) not in cache.get("json", {}):
            cache.setdefault("json", {})[str(path)] = load_json(path)
        pinned_value = json_pointer(cache["json"][str(path)], basis.get("json_pointer", ""))
    except Exception as exc:
        raise PreflightError(f"{label}: pin-basis JSON pointer is invalid: {exc}") from exc
    require(pinned_value == expected, f"{label}: compile-time pin basis disagrees with pinned value")


def discover_local_headers(source: Path, repo: Path) -> list[Path]:
    """Return the complete quoted-include closure; reject opaque include forms."""
    pending = [source.resolve(strict=True)]
    seen: set[Path] = set()
    result: set[Path] = set()
    while pending:
        current = pending.pop()
        if current in seen:
            continue
        seen.add(current)
        try:
            lines = current.read_text().splitlines()
        except (OSError, UnicodeError) as exc:
            raise PreflightError(f"cannot read source dependency {current}: {exc}") from exc
        for line in lines:
            match = INCLUDE_RE.match(line)
            if not match:
                if INCLUDE_DIRECTIVE_RE.match(line):
                    raise PreflightError(
                        f"{current}: non-literal include provenance is unsupported by this pilot")
                continue
            delimiter, name = match.groups()
            if delimiter != '"':
                raise PreflightError(f"{current}: non-local include form is unsupported")
            candidates = [current.parent / name, repo / name]
            found = next((p.resolve() for p in candidates if p.is_file()), None)
            require(found is not None, f"{current}: included header {name!r} cannot be resolved")
            repo_relative(found, repo, f"included header {name}")
            result.add(found)
            pending.append(found)
    result.discard(source.resolve(strict=True))
    return sorted(result, key=lambda p: p.as_posix())


def validate_file_pin(record: dict, expected_path: Path, repo: Path, label: str) -> tuple[str, str]:
    require(isinstance(record, dict), f"{label}: file pin is missing")
    path = resolve_path(record.get("path"), repo, label)
    require(path == expected_path.resolve(strict=True), f"{label}: pinned path differs from report path")
    digest = sha256_file(path)
    require(digest == record.get("sha256"), f"{label}: pinned SHA-256 mismatch")
    return str(path), digest


def validate_pin_record(report_path: Path, report: dict, segment: dict, config: dict,
                        pin: dict, repo: Path) -> dict:
    require(isinstance(pin, dict), "compile-time module pin is missing")
    require(sha256_file(report_path) == pin.get("report_sha256"),
            "compile-time report SHA-256 pin is missing or stale")

    source = resolve_path(segment.get("source"), repo, "report source")
    source_rel = repo_relative(source, repo, "report source")
    source_record = pin.get("source")
    require(isinstance(source_record, dict), "compile-time source pin is missing")
    require(source_record.get("path") == source_rel, "compile-time source path differs from report")
    source_sha = sha256_file(source)
    require(source_sha == segment.get("source_sha256") == source_record.get("sha256"),
            "stale source hash or compile-time source pin")
    basis_cache: dict = {}
    validate_basis(source_record, source_sha, repo, basis_cache, "source")

    found_headers = discover_local_headers(source, repo)
    header_records = pin.get("headers")
    require(isinstance(header_records, list), "compile-time header dependency pins are missing")
    pinned_header_paths = []
    header_evidence = []
    for record in header_records:
        require(isinstance(record, dict), "malformed header pin")
        path = resolve_path(record.get("path"), repo, "header pin")
        rel = repo_relative(path, repo, "header pin")
        header_sha = sha256_file(path)
        require(header_sha == record.get("sha256"), f"changed compile-time header: {rel}")
        validate_basis(record, header_sha, repo, basis_cache, f"header {rel}")
        pinned_header_paths.append(path)
        header_evidence.append({"path": rel, "sha256": header_sha})
    require(found_headers == sorted(pinned_header_paths, key=lambda p: p.as_posix()),
            "compile-time header pins do not equal the discovered local include closure")

    candidate_path = resolve_path(segment.get("candidate_module_json"), repo,
                                  "candidate module configuration")
    candidate_path_text, candidate_sha = validate_file_pin(
        pin.get("candidate_module_json"), candidate_path, repo, "candidate module JSON")
    candidate = load_json(candidate_path)
    for key in ("kind", "compiler_flags", "external_symbols",
                "external_exclude_symbols", "trailing_alignment_bytes", "functions",
                "linker_veneer_policy"):
        require(canonical(candidate.get(key)) == canonical(config.get(key)),
                f"compile-time candidate configuration differs from report: {key}")
    candidate_source = candidate.get("source")
    candidate_source_path = resolve_path(candidate_source, repo, "candidate source")
    require(candidate_source_path == source, "candidate JSON source path differs from report source")
    policy = candidate.get("compiler_data_policy")
    policy = None if policy is None else policy
    norm = segment.get("compiler_data_normalization")
    if policy is None:
        require(norm is None, "compiler-data normalization exists without a pinned policy")
    else:
        name = policy if isinstance(policy, str) else policy.get("name") if isinstance(policy, dict) else None
        require(name in POLICY_NAMES, f"unsupported compiler-data policy: {name!r}")
        require(isinstance(norm, dict) and norm.get("policy") == name,
                "compiler-data policy/normalization metadata mismatch")
        if isinstance(policy, dict):
            require(name == "agbcc-unreferenced-pointer-objects-v1",
                    "object inventory metadata requires the declared object policy")
            require(set(policy) == {"name", "input_assembly_sha256", "objects"},
                    "object policy contains unsupported or missing metadata fields")
            require(isinstance(policy["input_assembly_sha256"], str)
                    and re.fullmatch(r"[0-9a-fA-F]{64}", policy["input_assembly_sha256"]),
                    "object policy input assembly hash is invalid")
            objects = policy["objects"]
            require(isinstance(objects, list) and 0 < len(objects) <= 32,
                    "object policy inventory must contain 1..32 objects")
            require(all(isinstance(obj, dict) and set(obj) == {"label", "target"}
                        and isinstance(obj.get("label"), str) and obj["label"]
                        and isinstance(obj.get("target"), str) and obj["target"]
                        for obj in objects),
                    "object policy inventory contains an unsupported object record")
            require(len({obj["label"] for obj in objects}) == len(objects),
                    "object policy inventory has duplicate labels")
            for field in ("input_assembly_sha256", "objects"):
                require(norm.get(field) == policy[field],
                        f"compiler-data metadata differs from pinned policy: {field}")
        else:
            require(name != "agbcc-unreferenced-pointer-objects-v1",
                    "the pointer-object compiler-data policy requires its hash-bound inventory")

    toolchain = report.get("toolchain")
    require(isinstance(toolchain, dict) and toolchain,
            "report toolchain identity is missing")
    require(canonical(pin.get("toolchain")) == canonical(toolchain),
            "compile-time toolchain pin differs from report")
    require(pin.get("toolchain_sha256") == sha256_bytes(canonical(toolchain).encode()),
            "compile-time toolchain hash is missing or stale")
    effective_config = {
        "kind": config.get("kind"),
        "compiler_flags": config.get("compiler_flags"),
        "external_symbols": config.get("external_symbols"),
        "external_exclude_symbols": config.get("external_exclude_symbols"),
        "trailing_alignment_bytes": config.get("trailing_alignment_bytes"),
        "functions": config.get("functions"),
        "compiler_data_policy": policy,
    }
    if "linker_veneer_policy" in config:
        effective_config["linker_veneer_policy"] = config["linker_veneer_policy"]
    require(canonical(pin.get("effective_configuration")) == canonical(effective_config),
            "compile-time effective configuration pin differs from report/input JSON")

    binary_path = resolve_path(segment.get("binary"), repo, "report binary")
    binary_record = pin.get("binary")
    binary_path_text, binary_sha = validate_file_pin(binary_record, binary_path, repo, "generated binary")
    require(binary_sha == segment.get("binary_sha256"), "report generated binary SHA-256 mismatch")

    elf_path = resolve_path(segment.get("elf"), repo, "report ELF")
    elf_path_text, elf_sha = validate_file_pin(pin.get("elf"), elf_path, repo, "linked ELF")
    disassembly_path = resolve_path(segment.get("disassembly"), repo, "report disassembly")
    disassembly_path_text, disassembly_sha = validate_file_pin(
        pin.get("disassembly"), disassembly_path, repo, "linked disassembly")

    link_evidence = []
    link_records = pin.get("link_dependencies")
    require(isinstance(link_records, list), "link dependency pin list is missing")
    for record in link_records:
        path = resolve_path(record.get("path"), repo, "link dependency")
        rel = repo_relative(path, repo, "link dependency")
        digest = sha256_file(path)
        require(digest == record.get("sha256"), f"changed link dependency: {rel}")
        validate_basis(record, digest, repo, basis_cache, f"link dependency {rel}")
        link_evidence.append({"path": rel, "sha256": digest})
    if config.get("external_symbols") is True:
        require(bool(link_records), "external-symbol link has no pinned alias/dependency input")

    return {
        "method": "explicit-legacy-pins-v1",
        "report_sha256": pin["report_sha256"],
        "source": {"path": source_rel, "sha256": source_sha},
        "headers": header_evidence,
        "candidate_module_json": {"path": candidate_path_text, "sha256": candidate_sha},
        "binary": {"path": binary_path_text, "sha256": binary_sha},
        "elf": {"path": elf_path_text, "sha256": elf_sha},
        "disassembly": {"path": disassembly_path_text, "sha256": disassembly_sha},
        "link_dependencies": sorted(link_evidence, key=lambda x: x["path"]),
        "toolchain_sha256": pin["toolchain_sha256"],
        "effective_configuration_sha256": sha256_bytes(canonical(effective_config).encode()),
        "compiler_data_policy": policy,
        "compiler_data_normalization_sha256": (
            sha256_bytes(canonical(norm).encode()) if norm is not None else None),
    }


def path_list(value, repo: Path, label: str) -> list[Path]:
    require(isinstance(value, list), f"{label}: expected a path list")
    paths = [resolve_path(item, repo, label) for item in value]
    require(len(paths) == len(set(paths)), f"{label}: duplicate paths")
    return sorted(paths, key=lambda item: item.as_posix())


def validate_native_compile_inputs(report_path: Path, report: dict, segment: dict,
                                   config: dict, baseline_module: dict,
                                   baseline: dict, repo: Path,
                                   compare_api, baseline_path: Path | None = None) -> dict:
    """Verify compiler-emitted provenance against files and current dependencies."""
    native = report.get("compile_inputs")
    require(isinstance(native, dict), "native compile_inputs must be an object")
    require(native.get("schema") == NATIVE_COMPILE_INPUT_SCHEMA,
            f"native compile_inputs schema must be {NATIVE_COMPILE_INPUT_SCHEMA}")
    require(native.get("capture") == "before-and-after-compilation",
            "native compile_inputs must capture inputs before and after compilation")

    toolchain = report.get("toolchain")
    require(isinstance(toolchain, dict) and toolchain,
            "report toolchain identity is missing")
    toolchain_sha = sha256_bytes(canonical(toolchain).encode())
    require(native.get("toolchain_sha256") == toolchain_sha,
            "native compile_inputs toolchain hash differs from canonical report toolchain")

    source = resolve_path(segment.get("source"), repo, "report source")
    source_sha = sha256_file(source)
    require(source_sha == segment.get("source_sha256"),
            "native compile source hash differs from report segment")
    require(source.is_relative_to(repo.resolve(strict=True)),
            "native compile source must be inside repository root")

    module_name = (report.get("baseline_module") or {}).get("name")
    effective = native.get("effective_module")
    require(isinstance(effective, dict), "native effective_module must be a complete module object")
    require(effective.get("name") == module_name,
            "native effective module name differs from report baseline")
    require(effective.get("offset") == baseline_module.get("offset")
            and effective.get("size") == baseline_module.get("size"),
            "native effective module span differs from frozen baseline")
    effective_source = resolve_path(effective.get("source"), repo, "native effective source")
    require(effective_source == source,
            "native effective source differs from report segment source")

    # Reconstruct the resolved source configuration using the same candidate
    # override routine as the local compiler. This checks selected-C baselines
    # and ASM-to-C replacements without inventing pins from present-day files.
    try:
        module = dict(baseline_module)
        candidate_raw = segment.get("candidate_module_json")
        candidate_path = (resolve_path(candidate_raw, repo, "candidate module JSON")
                          if candidate_raw is not None else None)
        expected_module, _ = compare_api.apply_candidate_overrides(module, candidate_path)
    except Exception as exc:
        raise PreflightError(f"cannot reconstruct effective module configuration: {exc}") from exc
    if expected_module.get("functions") is None:
        expected_module["functions"] = [{"name": module_name,
                                         "offset": expected_module.get("offset"),
                                         "size": expected_module.get("size")}]
    expected_source = resolve_path(expected_module.get("source"), repo,
                                   "resolved module source")
    expected_module["source"] = str(expected_source)
    require(expected_source == source,
            "candidate/source configuration differs from report source")
    effective_normalized = dict(effective)
    effective_normalized["source"] = str(effective_source)
    require(canonical(effective_normalized) == canonical(expected_module),
            "native effective_module differs from selected config plus candidate overrides")

    config = report.get("module_configuration")
    require(isinstance(config, dict), "report module_configuration is missing")
    resolved_defaults = {
        "compiler_flags": ["-O0", "-mthumb-interwork"],
        "external_symbols": effective.get("kind") in {"c", "mixed"},
        "external_exclude_symbols": [],
        "trailing_alignment_bytes": 0,
    }
    for key, value in config.items():
        effective_value = effective.get(key, resolved_defaults.get(key))
        require(canonical(effective_value) == canonical(value),
                f"native effective module differs from report configuration: {key}")
    require(config.get("kind") == "c",
            "only ordinary pure C module reports are supported")
    require("linker_veneer_policy" not in config,
            "linker veneer/relocation policies are outside this preflight pilot")

    files = native.get("files")
    require(isinstance(files, list), "native compile_inputs.files must be a list")
    allowed_roles = {"source", "header", "link", "build_tool", "toolchain", "config", "candidate"}
    role_paths: dict[str, list[Path]] = {role: [] for role in allowed_roles}
    file_evidence = []
    for index, record in enumerate(files):
        require(isinstance(record, dict)
                and set(record) == {"role", "path", "sha256"},
                f"native compile file record {index} is malformed")
        role = record.get("role")
        require(role in allowed_roles, f"native compile file has unsupported role: {role!r}")
        raw_path = record.get("path")
        require(isinstance(raw_path, str) and Path(raw_path).expanduser().is_absolute(),
                f"native {role} path must be absolute")
        path = resolve_path(raw_path, repo, f"native {role}")
        # The local compiler memoizes tool digests only inside this process,
        # keyed by file identity plus stat change detection. Reuse that trusted
        # digest for toolchain executables; every source/header/config/artifact
        # remains freshly content-hashed here.
        tool_hasher = getattr(compare_api, "tool_file_sha", None)
        actual = (tool_hasher(path) if role == "toolchain" and callable(tool_hasher)
                  else sha256_file(path))
        require(record.get("sha256") == actual,
                f"native {role} input hash changed: {path}")
        role_paths[role].append(path)
        file_evidence.append({"role": role, "path": str(path), "sha256": actual})

    for role in allowed_roles:
        require(len(role_paths[role]) == len(set(role_paths[role])),
                f"native {role} input list contains duplicates")
    require(role_paths["source"] == [source],
            "native source-role inputs do not identify exactly the report source")
    require(len(role_paths["config"]) == 1
            and sha256_file(role_paths["config"][0]) == report.get("manifest_sha256"),
            "native config-role input does not match the report manifest hash")
    if baseline_path is not None:
        require(role_paths["config"] == [baseline_path.resolve(strict=True)],
                "native config-role path differs from the supplied baseline manifest")
    build_tools = {(repo / "tools/compare_module_build.py").resolve(strict=True),
                   (repo / "tools/build_rom.py").resolve(strict=True)}
    require(set(role_paths["build_tool"]) == build_tools,
            "native build_tool role must pin compare_module_build.py and build_rom.py")
    require(bool(role_paths["toolchain"]), "native toolchain files are missing")
    toolchain_entries = toolchain.get("tools")
    require(isinstance(toolchain_entries, dict) and bool(toolchain_entries)
            and all(isinstance(item, dict) and isinstance(item.get("path"), str)
                    for item in toolchain_entries.values()),
            "report toolchain paths are malformed")
    reported_tool_paths = {
        Path(item["path"]).expanduser().resolve(strict=True)
        for item in toolchain_entries.values()
    }
    require(set(role_paths["toolchain"]) == reported_tool_paths,
            "native toolchain-role files differ from report tool paths")
    expected_link_paths = {(repo / "config/symbols.ld").resolve(strict=True)}
    if effective.get("external_symbols", effective.get("kind") in {"c", "mixed"}):
        expected_link_paths.add((repo / "asm/external_thumb_symbols.s").resolve(strict=True))
    require(set(role_paths["link"]) == expected_link_paths,
            "native link-role files differ from the declared local link inputs")

    candidate_raw = segment.get("candidate_module_json")
    if candidate_raw is None:
        require(not role_paths["candidate"],
                "native candidate-role input exists without a candidate module")
        candidate_evidence = None
    else:
        candidate = resolve_path(candidate_raw, repo, "candidate module JSON")
        require(role_paths["candidate"] == [candidate],
                "native candidate-role input differs from report candidate module")
        candidate_evidence = next(item for item in file_evidence
                                  if item["role"] == "candidate")

    link_evidence = [item for item in file_evidence if item["role"] == "link"]
    dependency_raw = native.get("dependency_paths")
    dependencies = path_list(dependency_raw, repo, "native dependency_paths")
    require(source in dependencies,
            "native dependency closure omits the compiled source")
    try:
        discover = getattr(compare_api, "discover_c_dependencies", None)
        require(callable(discover),
                "native compile provenance requires compare_module_build.discover_c_dependencies")
        discovered = discover(effective, source)
        discovered_paths = sorted({Path(item).expanduser().resolve(strict=True)
                                   for item in discovered}, key=lambda item: item.as_posix())
    except Exception as exc:
        raise PreflightError(f"cannot recompute compiler dependency closure: {exc}") from exc
    require(dependencies == discovered_paths,
            "native dependency_paths differ from current clang -M closure")
    expected_headers = sorted((set(discovered_paths) - {source}), key=lambda p: p.as_posix())
    require(sorted(role_paths["header"], key=lambda path: path.as_posix()) == expected_headers,
            "native header-role files differ from actual compiler dependency closure")

    artifacts = native.get("artifacts")
    expected_artifact_names = {"preprocessed", "compiler_assembly", "binary", "elf", "disassembly"}
    require(isinstance(artifacts, dict) and set(artifacts) == expected_artifact_names,
            "native artifacts must contain exactly preprocessed, compiler_assembly, binary, elf, disassembly")
    artifact_evidence = {}
    for name in sorted(expected_artifact_names):
        item = artifacts[name]
        require(isinstance(item, dict) and set(item) == {"path", "sha256"},
                f"native artifact {name} record is malformed")
        artifact = resolve_path(item.get("path"), repo, f"native artifact {name}")
        actual = sha256_file(artifact)
        require(item.get("sha256") == actual,
                f"native artifact {name} hash changed")
        artifact_evidence[name] = {"path": str(artifact), "sha256": actual}

    for artifact_name, segment_key, hash_key in (
            ("binary", "binary", "binary_sha256"),
            ("elf", "elf", None),
            ("disassembly", "disassembly", None)):
        segment_path = resolve_path(segment.get(segment_key), repo,
                                    f"report {segment_key}")
        require(artifact_evidence[artifact_name]["path"] == str(segment_path),
                f"native {artifact_name} artifact path differs from report segment")
        if hash_key:
            require(artifact_evidence[artifact_name]["sha256"] == segment.get(hash_key),
                    f"native {artifact_name} artifact hash differs from report segment")

    return {
        "method": "native-compile-inputs-v1",
        "report_sha256": sha256_file(report_path),
        "source": {"path": repo_relative(source, repo, "native report source"),
                   "absolute_path": str(source), "sha256": source_sha},
        "headers": [{"path": str(path), "sha256": sha256_file(path)}
                    for path in expected_headers],
        "candidate_module_json": candidate_evidence,
        "binary": artifact_evidence["binary"],
        "elf": artifact_evidence["elf"],
        "disassembly": artifact_evidence["disassembly"],
        "preprocessed": artifact_evidence["preprocessed"],
        "compiler_assembly": artifact_evidence["compiler_assembly"],
        "link_dependencies": sorted(link_evidence, key=lambda item: item["path"]),
        "toolchain_files": [item for item in file_evidence if item["role"] == "toolchain"],
        "config": next(item for item in file_evidence if item["role"] == "config"),
        "toolchain_sha256": toolchain_sha,
        "effective_configuration_sha256": sha256_bytes(canonical(effective).encode()),
        "dependency_paths": [str(path) for path in dependencies],
        "compiler_data_policy": effective.get("compiler_data_policy"),
        "compiler_data_normalization_sha256": (
            sha256_bytes(canonical(segment["compiler_data_normalization"]).encode())
            if segment.get("compiler_data_normalization") is not None else None),
    }
def validate_proposal_module(module: dict) -> None:
    forbidden = sorted(ASM_ONLY_FIELDS.intersection(module))
    require(not forbidden, f"proposal retains ASM/mixed-only fields: {forbidden}")
    require(module.get("kind") == "c", "proposal module kind must be c")
    require(type(module.get("offset")) is int and type(module.get("size")) is int
            and module["offset"] >= 0 and module["size"] > 0,
            "proposal offset/size is invalid")
    require(type(module.get("trailing_alignment_bytes")) is int
            and module["trailing_alignment_bytes"] in (0, 2),
            "proposal trailing alignment is outside the supported {0,2} set")
    functions = module.get("functions")
    require(isinstance(functions, list) and len(functions) == 1,
            "proposal must have exactly one function")
    fn = functions[0]
    require(fn.get("offset") == module.get("offset"),
            "unsupported multi-entry/non-start function layout")
    require(fn.get("size") == module.get("size"),
            "function size must equal generated module size")
    require(fn.get("name") and module.get("name"), "module/function names are required")
    policy = module.get("match_policy", "exact")
    diffs = module.get("expected_differences", [])
    require(policy in {"exact", "allow-differences"}, f"unsupported match policy: {policy}")
    require((policy == "exact" and not diffs) or (policy == "allow-differences" and bool(diffs)),
            "match policy and expected_differences disagree")
    begin, end = module["offset"], module["offset"] + module["size"]
    seen = set()
    for diff in diffs:
        require(isinstance(diff, dict), "difference record must be an object")
        off = diff.get("rom_offset")
        require(type(off) is int and begin <= off < end,
                "difference lies outside generated module span (retained-tail difference rejected)")
        for key in ("reference_byte", "generated_byte"):
            require(type(diff.get(key)) is int and 0 <= diff[key] <= 255,
                    f"invalid or missing {key} in difference")
        require(off not in seen, f"duplicate difference offset {off}")
        seen.add(off)
    policy_data = module.get("compiler_data_policy")
    if policy_data is not None:
        name = policy_data if isinstance(policy_data, str) else policy_data.get("name") if isinstance(policy_data, dict) else None
        require(name in POLICY_NAMES, f"unsupported compiler-data policy: {name!r}")


def selected_differences(binary: bytes, retail_span: bytes, offset: int) -> list[dict]:
    return [
        {"rom_offset": offset + i, "reference_byte": ref, "generated_byte": gen}
        for i, (gen, ref) in enumerate(zip(binary, retail_span)) if gen != ref
    ]


def validate_selected_against_proposal(current: dict, proposed: dict) -> None:
    validate_proposal_module(proposed)
    keys = ("kind", "source", "offset", "size", "compiler_flags", "external_symbols",
            "external_exclude_symbols", "trailing_alignment_bytes", "functions",
            "compiler_data_policy", "linker_veneer_policy", "match_policy",
            "expected_differences")
    for key in keys:
        if key == "expected_differences":
            before, after = current.get(key, []), proposed.get(key, [])
        elif key == "match_policy":
            before, after = current.get(key, "exact"), proposed.get(key, "exact")
        elif key in ("trailing_alignment_bytes", "compiler_data_policy", "linker_veneer_policy"):
            before, after = current.get(key, 0 if key == "trailing_alignment_bytes" else None), proposed.get(key)
        else:
            before, after = current.get(key), proposed.get(key)
        require(canonical(before) == canonical(after),
                f"current selected module field {key} differs from generated proposal")
    require(current.get("size") == proposed["size"],
            "selected size is stale (original ASM size retained)")


def read_elf_binary(elf: Path, objcopy: Path) -> bytes:
    with tempfile.TemporaryDirectory(prefix="module-preflight-objcopy-") as directory:
        output = Path(directory) / "linked.bin"
        try:
            proc = subprocess.run([str(objcopy), "-O", "binary", str(elf), str(output)],
                                  check=False, capture_output=True, text=True, timeout=15)
        except (OSError, subprocess.TimeoutExpired) as exc:
            raise PreflightError(f"objcopy failed while reading linked ELF: {exc}") from exc
        require(proc.returncode == 0 and output.is_file(),
                f"objcopy failed while reading linked ELF: {proc.stderr.strip()}")
        return output.read_bytes()


def validate_terminal_alignment(binary: bytes, raw_elf: bytes, trim: int,
                                generated_size: int, text_size: int,
                                function_size: int) -> dict:
    require(trim in (0, 2), f"unsupported terminal alignment trim {trim}; supported values are 0 or 2")
    require(len(binary) == generated_size, "generated binary length differs from report")
    require(text_size == generated_size + trim,
            "ELF .text size does not equal generated bytes plus declared terminal trim")
    if trim:
        require(len(raw_elf) == generated_size + trim,
                "objcopy ELF bytes do not equal generated bytes plus declared trim")
        require(raw_elf[:generated_size] == binary,
                "ELF .text prefix differs from generated binary")
        require(raw_elf[generated_size:] == bytes.fromhex("c046"),
                "declared two-byte trim is not the proven terminal Thumb NOP C046")
        require(function_size in (generated_size, generated_size + trim),
                "linked function symbol size does not bound the generated span/terminal NOP")
    else:
        require(raw_elf == binary, "untrimmed ELF bytes differ from generated binary")
        require(function_size == generated_size,
                "untrimmed linked function symbol size differs from generated binary")
    return {"trim_bytes": trim, "generated_bytes": generated_size,
            "elf_text_bytes": text_size,
            "terminal_bytes": raw_elf[generated_size:].hex() if trim else ""}


def linked_function_size(elf: Path, readelf: Path, function_name: str,
                         expected_thumb_address: int) -> int:
    try:
        proc = subprocess.run([str(readelf), "-sW", str(elf)], check=False,
                              capture_output=True, text=True, timeout=15)
    except (OSError, subprocess.TimeoutExpired) as exc:
        raise PreflightError(f"readelf failed while checking function symbol: {exc}") from exc
    require(proc.returncode == 0, f"readelf failed: {proc.stderr.strip()}")
    matches = []
    for line in proc.stdout.splitlines():
        fields = line.split()
        if len(fields) >= 8 and fields[3] == "FUNC" and fields[-1] == function_name:
            try:
                matches.append((int(fields[1], 16), int(fields[2], 10)))
            except ValueError:
                continue
    require(len(matches) == 1, f"linked ELF must contain one {function_name} function symbol")
    address, size = matches[0]
    require(address == expected_thumb_address,
            f"linked function entry differs from pinned Thumb address: {address:#x}")
    return size


def normalize_objdump_binary_header(text: str) -> list[str]:
    """Ignore only objdump's input-path banner for a bounded raw binary."""
    lines = text.splitlines(keepends=True)
    for index, line in enumerate(lines):
        body = line.rstrip("\r\n")
        if not body.strip():
            continue
        if not re.fullmatch(r".*:\s+file format binary\s*", body):
            raise PreflightError("bounded binary disassembly has no objdump binary-format banner")
        ending = line[len(body):]
        lines[index] = "<binary-input>: file format binary" + ending
        return lines
    raise PreflightError("bounded binary disassembly is empty")


def verify_reference_artifacts(segment: dict, report: dict, retail: bytes,
                               offset: int, span: int, repo: Path,
                               native_report: bool) -> dict | None:
    reference_raw = segment.get("reference_binary")
    disassembly_raw = segment.get("reference_disassembly")
    if not native_report and reference_raw is None and disassembly_raw is None:
        return None
    require(reference_raw is not None and disassembly_raw is not None,
            "bounded reference binary and disassembly must be supplied together")
    reference_path = resolve_path(reference_raw, repo, "bounded reference binary")
    reference = reference_path.read_bytes()
    require(reference == retail[offset:offset + span],
            "bounded reference binary differs from the pinned retail module span")
    disassembly_path = resolve_path(disassembly_raw, repo, "bounded reference disassembly")
    toolchain = report.get("toolchain") or {}
    objdump_record = (toolchain.get("tools") or {}).get("objdump")
    require(isinstance(objdump_record, dict) and isinstance(objdump_record.get("path"), str),
            "report has no objdump tool path for bounded reference validation")
    # C output in this pilot uses the Thumb mode. The segment carries the
    # configured address; its offset is independently checked by validate_report.
    gba = segment.get("gba_address")
    require(type(gba) is int and gba >= offset,
            "bounded reference segment has an invalid GBA address")
    command = [objdump_record["path"], "-D", "-b", "binary", "-m", "arm",
               f"--adjust-vma={gba}"]
    if gba & 1 == 0:  # C output in this pilot is an ordinary Thumb entry.
        command += ["-M", "force-thumb"]
    command.append(str(reference_path))
    try:
        rendered = subprocess.check_output(command, text=True, timeout=20)
    except (OSError, subprocess.CalledProcessError, subprocess.TimeoutExpired) as exc:
        raise PreflightError(f"cannot validate bounded reference disassembly: {exc}") from exc
    stored_disassembly = disassembly_path.read_text()
    require(normalize_objdump_binary_header(stored_disassembly)
            == normalize_objdump_binary_header(rendered),
            "bounded reference disassembly differs from the pinned retail span")
    return {
        "reference_binary": {"path": str(reference_path), "sha256": sha256_file(reference_path),
                             "bytes": len(reference)},
        "reference_disassembly": {"path": str(disassembly_path),
                                  "sha256": sha256_file(disassembly_path),
                                  "redecoded_from_reference_span": True},
    }


def validate_report(report_path: Path, report: dict, index_name: str, baseline: dict,
                    baseline_sha: str, repo: Path, retail: bytes, pin: dict | None,
                    elf_guard, layout_guard, objcopy: Path, readelf: Path,
                    retail_sha_expected: str = RETAIL_SHA256,
                    compare_api=None, baseline_path: Path | None = None) -> tuple[dict, dict]:
    require(report.get("schema") == "local-module-build-v1", "unsupported report schema")
    require(report.get("retail_sha256") == retail_sha_expected,
            "report retail revision is not pinned")
    require(sha256_bytes(retail) == retail_sha_expected,
            "retail file SHA-256 does not match pinned revision")
    require(report.get("manifest_sha256") == baseline_sha,
            "report baseline manifest hash mismatch")
    base = report.get("baseline_module") or {}
    name = base.get("name")
    require(name == index_name, "report-index module name differs from report baseline module")
    bm = manifest_module(baseline, name)
    require(bm.get("kind") in {"assembly", "c"},
            f"{name}: baseline must be selected assembly or C")
    offset, span = bm.get("offset"), bm.get("size")
    require(type(offset) is int and type(span) is int and span > 0,
            f"{name}: baseline module span is invalid")
    require(base.get("rom_offset") == offset and base.get("reference_size") == span,
            f"{name}: report/baseline entry or envelope differs")
    config = report.get("module_configuration") or {}
    unknown_config = sorted(set(config) - REPORT_CONFIG_KEYS)
    if unknown_config:
        raise PreflightError(f"{name}: unsupported report configuration fields {unknown_config}")
    require(config.get("kind") == "c", f"{name}: only pure C is supported")
    production_layout = dict(config)
    production_layout.update({
        "name": name,
        "source": (report.get("segments") or [{}])[0].get("source"),
        "offset": offset,
        "size": span,
    })
    layout_guard(production_layout, baseline)
    functions = config.get("functions")
    require(isinstance(functions, list) and len(functions) == 1,
            f"{name}: multi-entry modules are unsupported")
    fn = functions[0]
    require(isinstance(fn, dict) and fn.get("offset") == offset and fn.get("size") == span,
            f"{name}: function must be the ordinary single entry at the frozen module start")
    require(isinstance(fn.get("name"), str) and fn["name"], f"{name}: function name is missing")
    require(isinstance(config.get("compiler_flags"), list) and config["compiler_flags"],
            f"{name}: compiler flags are missing")
    require(type(config.get("external_symbols")) is bool,
            f"{name}: external_symbols must be explicit")
    require(isinstance(config.get("external_exclude_symbols"), list),
            f"{name}: external_exclude_symbols must be explicit")
    trim = config.get("trailing_alignment_bytes")
    require(type(trim) is int and trim in (0, 2),
            f"{name}: unsupported or missing trailing_alignment_bytes")
    segments = report.get("segments")
    require(isinstance(segments, list) and len(segments) == 1,
            f"{name}: exactly one linked output segment is required")
    segment = segments[0]
    require(segment.get("fits") is True, f"{name}: output does not fit its frozen module span")
    generated = segment.get("generated_size")
    require(type(generated) is int and generated > 0, f"{name}: generated size is invalid")
    require(generated <= span, f"{name}: output exceeds baseline span ({generated}>{span})")
    require(segment.get("rom_offset") == offset and segment.get("reference_size") == span,
            f"{name}: segment offset/envelope differs from baseline")
    rom_base = baseline.get("rom_base")
    require(type(rom_base) is int and segment.get("gba_address") == rom_base + offset,
            f"{name}: segment GBA address does not match baseline ROM base")
    if "compile_inputs" in report:
        require(compare_api is not None,
                "native compile_inputs requires the production compare_module_build API")
        pin_evidence = validate_native_compile_inputs(
            report_path, report, segment, config, bm, baseline, repo, compare_api,
            baseline_path=baseline_path)
    else:
        require(pin is not None,
                "legacy local build report requires explicit historical compile-input pins")
        pin_evidence = validate_pin_record(report_path, report, segment, config, pin, repo)
    binary_path = Path(pin_evidence["binary"]["path"])
    binary = binary_path.read_bytes()
    require(len(binary) == generated, f"{name}: binary length differs from report generated_size")
    entry_validation = segment.get("entry_validation") or {}
    entries = segment.get("functions") or []
    require(entry_validation.get("passed") is True and entry_validation.get("checked_entries") == 1,
            f"{name}: report did not validate exactly one entry")
    require(len(entries) == 1 and entries[0].get("mode") == "thumb",
            f"{name}: only one Thumb entry is supported")
    entry = entries[0]
    require(entry.get("rom_offset") == offset and entry.get("gba_address") == rom_base + offset
            and entry.get("thumb_entry_address") == ((rom_base + offset) | 1),
            f"{name}: Thumb entry metadata is inconsistent")
    require(entry.get("name") == fn["name"], f"{name}: entry and function names disagree")

    elf_path = Path(pin_evidence["elf"]["path"])
    sections = elf_guard(elf_path)
    text_sections = [s for s in sections if s.get("name") == ".text"]
    require(len(text_sections) == 1, f"{name}: linked ELF must have exactly one .text section")
    reported_elf = segment.get("elf_section_validation") or {}
    require(reported_elf.get("passed") is True
            and canonical(reported_elf.get("sections", [])) == canonical(sections),
            f"{name}: report ELF section list differs from current independent ELF guard")
    if trim:
        expected_address = (rom_base + offset) | 1
        function_size = linked_function_size(elf_path, readelf, fn["name"], expected_address)
        raw_elf = read_elf_binary(elf_path, objcopy)
    else:
        function_size = generated
        raw_elf = binary
    trim_evidence = validate_terminal_alignment(
        binary, raw_elf, trim, generated, text_sections[0].get("size"), function_size)
    if trim:
        disassembly = Path(pin_evidence["disassembly"]["path"]).read_text()
        trimmed_address = rom_base + offset + generated
        for target in BRANCH_RE.findall(disassembly):
            require(int(target, 16) != trimmed_address,
                    f"{name}: branch targets the removed terminal alignment NOP")

    original = retail[offset:offset + span]
    require(len(original) == span, f"{name}: baseline span extends past retail image")
    reference_evidence = verify_reference_artifacts(
        segment, report, retail, offset, span, repo, "compile_inputs" in report)
    diffs = selected_differences(binary, original[:generated], offset)
    proposal = {
        "name": name,
        "source": pin_evidence["source"]["path"],
        "kind": "c",
        "compiler_flags": list(config["compiler_flags"]),
        "external_symbols": config["external_symbols"],
        "external_exclude_symbols": list(config["external_exclude_symbols"]),
        "trailing_alignment_bytes": trim,
        "offset": offset,
        "size": generated,
        "functions": [{"name": fn["name"], "offset": offset, "size": generated}],
        "match_policy": "allow-differences" if diffs else "exact",
    }
    if pin_evidence["compiler_data_policy"] is not None:
        proposal["compiler_data_policy"] = pin_evidence["compiler_data_policy"]
    if config.get("linker_veneer_policy") is not None:
        proposal["linker_veneer_policy"] = config["linker_veneer_policy"]
    if diffs:
        proposal["expected_differences"] = diffs
    validate_proposal_module(proposal)
    evidence = {
        "module": name,
        "report": str(report_path.resolve()),
        "baseline_span": {"offset": offset, "bytes": span},
        "generated_bytes": generated,
        "trim": trim_evidence,
        "retained_original_suffix_bytes": span - generated,
        "retail_prefix_difference_count": len(diffs),
        "match_policy": proposal["match_policy"],
        "entry": entry,
        "elf_section_guard": sections,
        "compile_provenance": pin_evidence,
        "bounded_reference": reference_evidence,
    }
    return proposal, evidence


def load_report_records(index_path: Path | None, report_paths: list[Path]) -> tuple[list[tuple[str, Path]], str | None]:
    if index_path is not None:
        index = load_json(index_path)
        require(isinstance(index, list), "report index must be a JSON list of {module, report}")
        records = []
        for row in index:
            require(isinstance(row, dict) and isinstance(row.get("module"), str),
                    "report index row is malformed")
            records.append((row["module"], Path(row.get("report", ""))))
        return records, sha256_file(index_path)
    require(bool(report_paths), "at least one --report or --report-index is required")
    records = []
    for path in report_paths:
        records.append(("", path))
    return records, None


def load_production_validators(repo: Path):
    helper_path = repo / "tools/compare_module_build.py"
    spec = importlib.util.spec_from_file_location("compare_module_build_preflight", helper_path)
    require(spec is not None and spec.loader is not None, "cannot load shared ELF validator")
    helper = importlib.util.module_from_spec(spec)
    sys.modules[spec.name] = helper
    spec.loader.exec_module(helper)
    return helper.validate_elf_load_sections, helper.validate_module_layout, helper


def classify_batch(proposal_count: int, unsupported_count: int,
                   fail_on_unsupported: bool) -> str:
    if proposal_count == 0:
        return "rejected_no_supported_modules"
    if fail_on_unsupported and unsupported_count:
        return "rejected_due_to_unsupported_inputs"
    if unsupported_count:
        return "passed_with_unsupported_inputs"
    return "passed"


def preflight_single_report(repo_root: Path, baseline_path: Path, retail_path: Path,
                            report_path: Path, output_dir: Path, compare_api,
                            current_manifest_path: Path | None = None) -> dict:
    """Run the strict one-method proposal path without a second Python process."""
    started = time.perf_counter()
    repo = repo_root.expanduser().resolve(strict=True)
    baseline_file = baseline_path.expanduser().resolve(strict=True)
    retail_file = retail_path.expanduser().resolve(strict=True)
    report_file = report_path.expanduser().resolve(strict=True)
    output = output_dir.expanduser().resolve()
    require(not output.is_relative_to(repo) and not repo.is_relative_to(output),
            "output directory must be outside and not contain the repository")
    require(not any(output.iterdir()) if output.is_dir() else True,
            "output directory must be new or empty")
    output.mkdir(parents=True, exist_ok=True)

    stages = {}
    tick = time.perf_counter()
    report = load_json(report_file)
    base_name = (report.get("baseline_module") or {}).get("name")
    require(isinstance(base_name, str) and base_name,
            "local report does not identify its baseline module")
    baseline, baseline_sha = compare_api.load_local_manifest(baseline_file, base_name)
    retail = retail_file.read_bytes()
    current = None
    current_sha = None
    if current_manifest_path is not None:
        current_file = current_manifest_path.expanduser().resolve(strict=True)
        current, current_sha = compare_api.load_local_manifest(current_file, base_name)
    stages["input_load_and_identity"] = round(time.perf_counter() - tick, 6)

    proposals, evidence, unsupported = [], [], []
    tick = time.perf_counter()
    try:
        proposal, proof = validate_report(
            report_file, report, base_name, baseline, baseline_sha, repo, retail,
            None, compare_api.validate_elf_load_sections,
            compare_api.validate_module_layout,
            Path(report["toolchain"]["tools"]["objcopy"]["path"]).resolve(strict=True),
            Path(report["toolchain"]["tools"]["readelf"]["path"]).resolve(strict=True),
            retail_sha_expected=RETAIL_SHA256, compare_api=compare_api,
            baseline_path=baseline_file)
        if current is not None:
            selected = manifest_module(current, base_name)
            validate_selected_against_proposal(selected, proposal)
            proof["current_selected_comparison"] = (
                "all supported proposal fields match current selected module")
        proposals.append(proposal)
        proof["validation_elapsed_seconds"] = round(time.perf_counter() - tick, 6)
        evidence.append(proof)
    except (OSError, KeyError, TypeError, ValueError) as exc:
        unsupported.append({"module": base_name, "report": str(report_file),
                            "reason": str(exc)})
    stages["report_validation_and_proposal"] = round(time.perf_counter() - tick, 6)

    status = classify_batch(len(proposals), len(unsupported), True)
    proposal_doc = {
        "schema": "local-selection-proposal-v2",
        "batch_status": status,
        "complete_batch": bool(proposals) and not unsupported,
        "baseline_manifest_sha256": baseline_sha,
        "retail_sha256": sha256_bytes(retail),
        "modules": proposals,
    }
    write_json(output / "selection-proposal.json", proposal_doc)
    report_doc = {
        "schema": "module-selection-preflight-report-v2",
        "status": status,
        "baseline_manifest_sha256": baseline_sha,
        "retail_sha256": sha256_bytes(retail),
        "report_index_sha256": None,
        "compile_input_pins_sha256": None,
        "compile_input_provenance_modes": {
            "native": sum(item["compile_provenance"].get("method") == "native-compile-inputs-v1"
                           for item in evidence),
            "explicit_legacy_pins": 0,
        },
        "current_manifest_sha256": current_sha,
        "modules": evidence,
        "unsupported": unsupported,
        "totals": {
            "indexed_reports": 1,
            "accepted_modules": len(proposals),
            "accepted_generated_bytes": sum(item["size"] for item in proposals),
            "accepted_declared_terminal_trim_bytes": sum(
                item["trailing_alignment_bytes"] for item in proposals),
            "unsupported_reports": len(unsupported),
            "retail_prefix_difference_records": sum(
                len(item.get("expected_differences", [])) for item in proposals),
        },
        "elapsed_seconds": {
            **stages, "total": round(time.perf_counter() - started, 6),
        },
        "limits": [
            "Strict one-method preflight; unsupported input rejects the proposal.",
            "Only ordinary pure-C single-entry Thumb modules are supported.",
            "Compilation and comparison do not prove behavior or replace batch/full-ROM integration.",
            "Native inputs use captured hashes and the current compiler dependency closure.",
        ],
    }
    write_json(output / "preflight-report.json", report_doc)
    return {"status": status, "exit_code": 0 if status == "passed" else 2,
            "proposal_path": str(output / "selection-proposal.json"),
            "report_path": str(output / "preflight-report.json"),
            "proposal_sha256": sha256_file(output / "selection-proposal.json"),
            "report_sha256": sha256_file(output / "preflight-report.json"),
            "preflight_report": report_doc}


def main(argv=None) -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--repo-root", required=True, type=Path)
    parser.add_argument("--baseline-manifest", required=True, type=Path)
    parser.add_argument("--retail-rom", required=True, type=Path)
    group = parser.add_mutually_exclusive_group(required=True)
    group.add_argument("--report-index", type=Path,
                       help="JSON list with module and report paths")
    group.add_argument("--report", action="append", type=Path,
                       help="local-module-build-v1 report; repeat per module")
    parser.add_argument("--compile-input-pins", type=Path,
                        help="explicit historical pins required only for legacy reports")
    parser.add_argument("--current-manifest", type=Path)
    parser.add_argument("--objcopy", required=True, type=Path)
    parser.add_argument("--readelf", required=True, type=Path)
    parser.add_argument("--output-dir", required=True, type=Path)
    parser.add_argument("--fail-on-unsupported", action="store_true",
                        help="return a failing exit status if any indexed report is explicitly unsupported")
    args = parser.parse_args(argv)

    started = time.perf_counter()
    stages = {}
    tick = time.perf_counter()
    repo = args.repo_root.expanduser().resolve(strict=True)
    baseline_path = args.baseline_manifest.expanduser().resolve(strict=True)
    retail_path = args.retail_rom.expanduser().resolve(strict=True)
    pins_path = args.compile_input_pins.expanduser().resolve(strict=True) if args.compile_input_pins else None
    current_path = args.current_manifest.expanduser().resolve(strict=True) if args.current_manifest else None
    objcopy = args.objcopy.expanduser().resolve(strict=True)
    readelf = args.readelf.expanduser().resolve(strict=True)
    output = args.output_dir.expanduser().resolve()
    require(not output.is_relative_to(repo), "output directory must be outside the repository")
    output.mkdir(parents=True, exist_ok=True)
    retail = retail_path.read_bytes()
    retail_sha = sha256_bytes(retail)
    require(retail_sha == RETAIL_SHA256, "retail ROM does not match the configured US revision")
    pins_sha = None
    pin_modules = {}
    if pins_path is not None:
        pins_raw = pins_path.read_bytes()
        pins_sha = sha256_bytes(pins_raw)
        pins_doc = json.loads(pins_raw)
        require(pins_doc.get("schema") == PIN_SCHEMA, f"compile input pins schema must be {PIN_SCHEMA}")
        pin_modules = pins_doc.get("modules")
        require(isinstance(pin_modules, dict), "compile input pins must contain a module-name mapping")
    elf_guard, layout_guard, compare_api = load_production_validators(repo)
    stages["input_load_and_identity"] = round(time.perf_counter() - tick, 6)

    tick = time.perf_counter()
    index_path = args.report_index.expanduser().resolve(strict=True) if args.report_index else None
    report_paths = [p.expanduser().resolve(strict=True) for p in (args.report or [])]
    records, index_sha = load_report_records(index_path, report_paths)
    proposals, evidence, unsupported = [], [], []
    baseline_sha = None
    current_sha = None
    seen_names, ranges = set(), []
    for indexed_name, raw_path in records:
        report_path = raw_path.expanduser().resolve(strict=True) if raw_path.is_absolute() else (index_path.parent / raw_path).resolve(strict=True)
        report = load_json(report_path)
        base = report.get("baseline_module") or {}
        name = base.get("name")
        if not indexed_name:
            indexed_name = name
        require(isinstance(name, str) and indexed_name == name,
                "report-index module name differs from report baseline module")
        require(name not in seen_names, f"duplicate report-index module {name}")
        seen_names.add(name)
        baseline, module_manifest_sha = compare_api.load_local_manifest(baseline_path, name)
        if baseline_sha is None:
            baseline_sha = module_manifest_sha
        require(module_manifest_sha == baseline_sha,
                "baseline manifest changed while loading compact module records")
        if current_path is not None:
            current, module_current_sha = compare_api.load_local_manifest(current_path, name)
            if current_sha is None:
                current_sha = module_current_sha
            require(module_current_sha == current_sha,
                    "current manifest changed while loading compact module records")
        segments = report.get("segments")
        if isinstance(segments, list) and len(segments) == 1 and segments[0].get("fits") is not True:
            unsupported.append({"module": name, "report": str(report_path),
                                "reason": "local report says output does not fit the frozen span"})
            continue
        module_start = time.perf_counter()
        try:
            proposal, proof = validate_report(
                report_path, report, indexed_name, baseline, baseline_sha, repo, retail,
                pin_modules.get(name), elf_guard, layout_guard, objcopy, readelf,
                compare_api=compare_api, baseline_path=baseline_path)
            if current_path is not None:
                selected = manifest_module(current, name)
                validate_selected_against_proposal(selected, proposal)
                proof["current_selected_comparison"] = "all supported proposal fields match current selected module"
            start, end = proposal["offset"], proposal["offset"] + proposal["size"]
            require(all(end <= a or start >= b for a, b in ranges),
                    f"{name}: proposed spans overlap another accepted module")
            ranges.append((start, end))
            proof["validation_elapsed_seconds"] = round(time.perf_counter() - module_start, 6)
            proposals.append(proposal)
            evidence.append(proof)
        except (OSError, KeyError, TypeError, ValueError) as exc:
            unsupported.append({"module": name, "report": str(report_path), "reason": str(exc)})
    stages["report_validation_and_proposal"] = round(time.perf_counter() - tick, 6)

    proposals.sort(key=lambda m: (m["offset"], m["name"]))
    evidence.sort(key=lambda e: (e["baseline_span"]["offset"], e["module"]))
    unsupported.sort(key=lambda e: (e["module"], e["reason"]))
    report_status = classify_batch(len(proposals), len(unsupported), args.fail_on_unsupported)
    proposal_doc = {
        "schema": "local-selection-proposal-v2",
        "batch_status": report_status,
        "complete_batch": bool(proposals) and not unsupported,
        "baseline_manifest_sha256": baseline_sha,
        "retail_sha256": retail_sha,
        "modules": proposals,
    }
    write_start = time.perf_counter()
    write_json(output / "selection-proposal.json", proposal_doc)
    stages["proposal_write"] = round(time.perf_counter() - write_start, 6)
    report_doc = {
        "schema": "module-selection-preflight-report-v2",
        "status": report_status,
        "baseline_manifest_sha256": baseline_sha,
        "retail_sha256": retail_sha,
        "report_index_sha256": index_sha,
        "compile_input_pins_sha256": pins_sha,
        "compile_input_provenance_modes": {
            "native": sum(row["compile_provenance"].get("method") == "native-compile-inputs-v1"
                           for row in evidence),
            "explicit_legacy_pins": sum(row["compile_provenance"].get("method") == "explicit-legacy-pins-v1"
                                         for row in evidence),
        },
        "current_manifest_sha256": current_sha,
        "modules": evidence,
        "unsupported": unsupported,
        "totals": {
            "indexed_reports": len(records),
            "accepted_modules": len(proposals),
            "accepted_generated_bytes": sum(m["size"] for m in proposals),
            "accepted_declared_terminal_trim_bytes": sum(m["trailing_alignment_bytes"] for m in proposals),
            "unsupported_reports": len(unsupported),
            "retail_prefix_difference_records": sum(len(m.get("expected_differences", [])) for m in proposals),
        },
        "elapsed_seconds": {
            **stages,
            "total": round(time.perf_counter() - started, 6),
        },
        "limits": [
            "Read-only proposal generation; no manifest is edited and no compilation/full ROM build is run.",
            "Only ordinary pure-C modules with one Thumb entry at the baseline start are supported.",
            "Supported terminal alignment is 0 or an independently verified two-byte terminal C046 NOP.",
            "Compiler-data policies are metadata-preserved only for the three explicitly recognized policies and require matching normalization evidence.",
            "Native local-compile-inputs-v1 reports verify captured source/config/candidate/toolchain/build/link inputs, current clang -M dependency closure, effective module configuration, and generated artifact hashes.",
            "Legacy reports require explicit historical compile-input pins; current file hashes alone are not treated as compile-time provenance.",
            "A supported subset can be emitted with unsupported reports listed; whole-batch acceptance requires --fail-on-unsupported and zero unsupported reports.",
            "The proposal carries batch_status and complete_batch so a supported subset cannot be mistaken for a fully accepted input batch.",
        ],
    }
    write_json(output / "preflight-report.json", report_doc)
    print(json.dumps({"status": report_doc["status"], "accepted": len(proposals),
                      "unsupported": len(unsupported), "generated_bytes": report_doc["totals"]["accepted_generated_bytes"],
                      "proposal_sha256": sha256_file(output / "selection-proposal.json"),
                      "report_sha256": sha256_file(output / "preflight-report.json")}, sort_keys=True))
    return 2 if (not proposals or (args.fail_on_unsupported and unsupported)) else 0


if __name__ == "__main__":
    try:
        raise SystemExit(main())
    except PreflightError as exc:
        print(f"preflight rejected: {exc}", file=sys.stderr)
        raise SystemExit(2)
