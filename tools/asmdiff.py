#!/usr/bin/env python3
"""Read-only, displacement-aware ARM/Thumb diagnostics using pinned asm-differ.

Never compiles, edits a candidate/report, or submits matching credit.
"""
import argparse
from collections import Counter
from asm_alignment_details import details
import hashlib
import importlib.util
import json
from pathlib import Path
import re
import shutil
import subprocess
import sys
import tempfile

ROOT = Path(__file__).resolve().parents[1]
VENDOR = ROOT / "vendor/asm-differ/diff.py"
REG = re.compile(r"\b(?:r(?:1[0-5]|[0-9])|sl|fp|ip|sb)\b")
BARE_POOL_COMMENT = re.compile(
    r"^([ \t]*[0-9a-fA-F]+:[ \t]+[0-9a-fA-F]+(?:[ \t]+[0-9a-fA-F]+)*"
    r"[ \t]+ldr[ \t]+r(?:1[0-5]|[0-9]),[ \t]*\[pc,[^\]\r\n]*\]"
    r"[ \t]+[;@][ \t]*\()((?:0[xX])?[0-9a-fA-F]+)(\))([ \t]*)$",
    re.MULTILINE)


def sha(path):
    return hashlib.sha256(Path(path).read_bytes()).hexdigest()


def upstream():
    if not VENDOR.is_file():
        raise ValueError("Initialize vendor/asm-differ first; see docs/asm-diff.md")
    spec = importlib.util.spec_from_file_location("ffta_asm_differ", VENDOR)
    mod = importlib.util.module_from_spec(spec)
    sys.modules[spec.name] = mod
    spec.loader.exec_module(mod)
    return mod


def config(mod, algorithm="levenshtein", formatter=None):
    return mod.Config(
        arch=mod.ARM32_SETTINGS, diff_obj=False, file=None, ref_file=None,
        make=False, source_old_binutils=False, diff_section=".text", inlines=False,
        max_function_size_lines=100000, max_function_size_bytes=1000000,
        formatter=formatter or mod.JsonFormatter(arch_str="arm32"),
        diff_mode=mod.DiffMode.NORMAL, base_shift=0, skip_lines=0, compress=None,
        show_rodata_refs=False, show_branches=True, show_line_numbers=True,
        show_source=False, stop_at_ret=None, ignore_large_imms=False,
        ignore_addr_diffs=False, algorithm=algorithm, reg_categories={},
        diff_function_symbols=False)


def text_key(line):
    return re.sub(r"\s+", " ", line.normalized_original.strip())


def shifted_runs(pairs, minimum=4):
    """Only contiguous equal-text aligned runs, not semantic equivalence."""
    runs, current = [], []
    def flush():
        if len(current) >= minimum:
            a, b = current[0]
            runs.append({"reference_start": a.line_num, "current_start": b.line_num,
                         "reference_last": current[-1][0].line_num,
                         "current_last": current[-1][1].line_num,
                         "address_delta": b.line_num - a.line_num,
                         "aligned_lines": len(current)})
        current.clear()
    for a, b in pairs:
        same = (a is not None and b is not None and a.line_num is not None
                and b.line_num is not None and a.branch_target is None
                and b.branch_target is None and text_key(a) == text_key(b)
                and a.line_num != b.line_num and not a.mnemonic.startswith("."))
        if not same:
            flush()
            continue
        if current and b.line_num - a.line_num != current[0][1].line_num - current[0][0].line_num:
            flush()
        current.append((a, b))
    flush()
    return runs


def moved_candidates(left, right, pairs, minimum=4):
    """Unique exact-text windows outside the monotonic alignment are hints only.

    Keep registers/immediates/call targets: no mnemonic-only equivalence claim.
    Repeated sequences are deliberately excluded as ambiguous.
    """
    aligned = {(a.line_num, b.line_num) for a, b in pairs if a is not None and b is not None}
    def windows(lines):
        result = {}
        for i in range(len(lines) - minimum + 1):
            block = lines[i:i + minimum]
            if any(x.line_num is None or x.mnemonic.startswith((".", "<")) for x in block):
                continue
            key = tuple(text_key(x) for x in block)
            result.setdefault(key, []).append(i)
        return result
    a, b = windows(left), windows(right)
    hints = []
    last_a = last_b = -minimum
    for key, positions in a.items():
        if len(positions) != 1 or len(b.get(key, [])) != 1:
            continue
        i, j = positions[0], b[key][0]
        if (left[i].line_num, right[j].line_num) in aligned or (i < last_a + minimum and j < last_b + minimum):
            continue
        hints.append({"reference_start": left[i].line_num, "current_start": right[j].line_num,
                      "lines": minimum, "confidence": "unique_text_window_not_CFG_proof",
                      "instructions": list(key)})
        last_a, last_b = i, j
    return hints


def analyze_dumps(reference, current, algorithm="levenshtein"):
    mod = upstream()
    cfg = config(mod, algorithm)
    # Upstream splits the pool comment's first token after "(" and expects
    # whitespace before ")" (normally supplied by a symbol name). Raw GNU
    # binary disassembly has no symbol: retain the address, add only a separator.
    reference, ref_fixes = BARE_POOL_COMMENT.subn(r"\1\2 \3\4", reference)
    current, cur_fixes = BARE_POOL_COMMENT.subn(r"\1\2 \3\4", current)
    left, right = mod.process(reference, cfg), mod.process(current, cfg)
    for side, lines in (("reference", left), ("current", right)):
        errors = [line for line in lines if line.mnemonic == "ERROR"]
        if errors:
            raise ValueError(f"{side} disassembly has {len(errors)} parser errors: "
                             f"{errors[0].original}; no alignment published")
    if not left or not right:
        raise ValueError("No parsed instructions; unsupported or empty disassembly")
    pairs = mod.diff_lines(left, right, algorithm)
    # Upstream do_diff mutates branch operands for displacement-normalized
    # rendering. Detailed addresses and targets must retain the parsed input.
    difference_details = details(left, right, pairs)
    result = mod.do_diff(left, right, cfg)
    table = mod.align_diffs(result, result, cfg)
    rows = cfg.formatter.raw(table)
    counts = Counter()
    for a, b in pairs:
        if a is None:
            counts['inserted_lines'] += 1
        elif b is None:
            counts['deleted_lines'] += 1
        elif text_key(a) == text_key(b):
            counts['same_text_lines'] += 1
        elif REG.sub('<reg>', text_key(a)) == REG.sub('<reg>', text_key(b)):
            counts['register_only_text_differences'] += 1
        else:
            counts['other_aligned_differences'] += 1
    return {"diagnostic_line_counts": dict(counts),
            "parser_comment_normalizations": {"reference": ref_fixes, "current": cur_fixes},
            "shifted_runs": shifted_runs(pairs),
            "possible_moved_sequences": moved_candidates(left, right, pairs),
            "upstream_diff": rows, "difference_details": difference_details}, mod.PlainFormatter(column_width=85).table(table)


def load_segment(report_path, module=None):
    report_path = Path(report_path).resolve()
    report = json.loads(report_path.read_text())
    segments = report.get('segments', [])
    if module:
        segments = [s for s in segments if s.get('module') == module]
    if len(segments) != 1:
        raise ValueError("Select exactly one report segment with --module")
    segment = segments[0]
    paths = {}
    for key in ('binary', 'reference_binary'):
        p = Path(segment[key])
        if not p.is_absolute():
            p = report_path.parent / p
        p = p.resolve()
        if not p.is_file():
            raise ValueError(f"Missing frozen {key}: {p}")
        paths[key] = p
    if sha(paths['binary']) != segment.get('binary_sha256'):
        raise ValueError("Generated binary hash differs from frozen report")
    for key, sizekey in [('binary', 'generated_size'), ('reference_binary', 'reference_size')]:
        if paths[key].stat().st_size != segment.get(sizekey):
            raise ValueError(f"{key} size differs from report")
    if segment.get('reference_binary_sha256') and sha(paths['reference_binary']) != segment['reference_binary_sha256']:
        raise ValueError("Reference binary hash differs from report")
    modes = {f.get('mode') for f in segment.get('functions', [])}
    if len(modes) != 1 or not modes <= {'thumb', 'arm'}:
        raise ValueError("One explicit ARM/Thumb mode required; mixed-mode segments need separate analysis")
    return report, segment, paths, modes.pop()


def generated_extent(report, segment, paths, report_path, full_elf_text=False):
    """Check declared trimming against a pinned ELF, without repairing a report."""
    trim = report.get('module_configuration', {}).get('trailing_alignment_bytes', 0)
    if not trim and not full_elf_text:
        return None, None, None
    if type(trim) is not int or trim < 0:
        raise ValueError('Invalid declared terminal trim')
    artifact = report.get('compile_inputs', {}).get('artifacts', {}).get('elf', {})
    if not artifact.get('path') or not artifact.get('sha256') or not segment.get('elf'):
        raise ValueError('Pinned ELF required to check terminal trimming/full ELF text')
    def resolve(value):
        path = Path(value)
        return (path if path.is_absolute() else report_path.parent / path).resolve()
    elf = resolve(segment['elf'])
    if elf != resolve(artifact['path']) or sha(elf) != artifact['sha256']:
        raise ValueError('ELF differs from frozen report artifact')
    tools = report.get('toolchain', {}).get('tools', {})
    objcopy = tools.get('objcopy', {}).get('path') or shutil.which('arm-none-eabi-objcopy')
    readelf = tools.get('readelf', {}).get('path') or shutil.which('arm-none-eabi-readelf')
    if not objcopy or not readelf:
        raise ValueError('ARM objcopy/readelf required to check generated extent')
    with tempfile.TemporaryDirectory(prefix='asmdiff-extent-') as temp:
        binary = Path(temp) / 'text.bin'
        subprocess.run([str(objcopy), '-O', 'binary', '--only-section=.text', str(elf), str(binary)],
                       check=True, capture_output=True, timeout=30)
        raw = binary.read_bytes()
    symbols = subprocess.run([str(readelf), '-sW', str(elf)], check=True, capture_output=True,
                             text=True, timeout=30).stdout
    ranges = []
    for fn in segment.get('functions', []):
        rows = [line.split() for line in symbols.splitlines()
                if len(line.split()) >= 8 and line.split()[3] == 'FUNC'
                and line.split()[-1] == fn.get('name')]
        if len(rows) != 1:
            raise ValueError('One linked FUNC symbol required for each declared function')
        row = rows[0]
        address, size = int(row[1], 16), int(row[2])
        expected = fn.get('thumb_entry_address', fn.get('gba_address'))
        if expected is None or address != (int(expected, 0) if isinstance(expected, str) else expected):
            raise ValueError('ELF FUNC entry differs from frozen report')
        start = (address & ~1) - int(segment['gba_address'])
        if size <= 0 or start < 0 or start + size > len(raw):
            raise ValueError('ELF FUNC falls outside generated .text')
        ranges.append({'name': fn['name'], 'start': start, 'size': size, 'end': start + size})
    if not ranges:
        raise ValueError('Explicit linked FUNC symbols required to check generated extent')
    published = paths['binary'].read_bytes()
    if not raw.startswith(published):
        raise ValueError('Published generated binary is not a prefix of pinned ELF text')
    removed = raw[len(published):]
    verified_trim = (trim == 2 and removed == bytes.fromhex('c046')
                     and all(fn['end'] <= len(published) for fn in ranges))
    info = {'declared_trim_bytes': trim, 'reported_generated_bytes': len(published),
            'elf_text_bytes': len(raw), 'removed_bytes_hex': removed.hex(),
            'function_ranges': ranges, 'outside_FUNC_terminal_trim_verified': verified_trim,
            'view': 'full_elf_text' if full_elf_text else 'reported_binary',
            'report_unchanged': True}
    if trim and not verified_trim and not full_elf_text:
        raise ValueError('Declared terminal trim is not a verified outside-FUNC C046 suffix; '
                         'use --full-elf-text for diagnosis only; no alignment published')
    return raw if full_elf_text else None, info, {'path': str(elf), 'sha256': artifact['sha256']}


def run(report_path, output, module=None, algorithm="levenshtein", objdump=None,
        full_elf_text=False):
    report_path = Path(report_path).resolve()
    report, segment, paths, mode = load_segment(report_path, module)
    input_pins = {k: sha(v) for k, v in paths.items()}
    report_pin = sha(report_path)
    output = Path(output).resolve()
    if output.exists():
        raise ValueError("Output must be a new directory; never overwrite frozen evidence")
    raw, extent, elf_pin = generated_extent(report, segment, paths, report_path, full_elf_text)
    program = objdump or report.get('toolchain', {}).get('tools', {}).get('objdump', {}).get('path') or shutil.which('arm-none-eabi-objdump')
    if not program:
        raise ValueError("arm-none-eabi-objdump required")
    dumps = {}
    with tempfile.TemporaryDirectory(prefix='asmdiff-input-') as temp:
        for key, path in paths.items():
            if key == 'binary' and raw is not None:
                path = Path(temp) / 'generated.elf-text.bin'
                path.write_bytes(raw)
            command = [str(program), '-D', '-z', '-b', 'binary', '-m', 'arm', '-EL',
                       f"--adjust-vma={int(segment['gba_address'])}"]
            if mode == 'thumb':
                command += ['-M', 'force-thumb']
            dumps[key] = subprocess.run(command + [str(path)], check=True, capture_output=True,
                                        text=True, timeout=30).stdout
    result, plain = analyze_dumps(dumps['reference_binary'], dumps['binary'], algorithm)
    if sha(report_path) != report_pin or any(sha(paths[k]) != v for k, v in input_pins.items()):
        raise ValueError("Frozen input changed during diagnosis; no output published")
    if elf_pin and sha(elf_pin['path']) != elf_pin['sha256']:
        raise ValueError('Frozen ELF changed during diagnosis; no output published')
    result.update({"schema": "ffta-asm-alignment-v1", "diagnostic_only": True,
                   "acceptance": "Unchanged whole-byte gate only; alignment is not matching credit or semantic proof.",
                   "limitations": ["Linear alignment can be ambiguous in repeated blocks.",
                       "Moved sequences are text hints, not a control-flow equivalence proof.",
                       "Raw disassembly may interpret unreferenced data/jump tables as instructions.",
                       "Reference is the supplied frozen report artifact; no fresh retail authentication is implied."],
                   "algorithm": algorithm, "module": segment['module'], "mode": mode,
                   "report": str(report_path), "report_sha256": report_pin,
                   "inputs": {k: {"path": str(v), "sha256": input_pins[k]} for k, v in paths.items()},
                   "upstream": {"url": "https://github.com/simonlindholm/asm-differ",
                                "diff_py_sha256": sha(VENDOR)},
                   "generated_extent": extent, "elf_input": elf_pin,
                   "sizes": {"reference": segment['reference_size'],
                             "generated": len(raw) if raw is not None else segment['generated_size']}})
    if raw is not None:
        result['full_elf_text_sha256'] = hashlib.sha256(raw).hexdigest()
    output.mkdir(parents=True, exist_ok=False)
    (output/'alignment.json').write_text(json.dumps(result, indent=2) + '\n')
    (output/'alignment.txt').write_text(plain + '\n')
    for key, dump in dumps.items():
        (output/f'{key}.disassembly.txt').write_text(dump)
    if raw is not None:
        (output/'generated.elf-text.bin').write_bytes(raw)
    return result


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--build-report', required=True, type=Path)
    parser.add_argument('--output', required=True, type=Path)
    parser.add_argument('--module')
    parser.add_argument('--objdump')
    parser.add_argument('--full-elf-text', action='store_true',
                        help='Diagnose complete pinned ELF .text; never repair the report or credit a trim')
    parser.add_argument('--algorithm', choices=['levenshtein', 'difflib'], default='levenshtein')
    args = parser.parse_args()
    try:
        result = run(args.build_report, args.output, args.module, args.algorithm, args.objdump,
                     args.full_elf_text)
    except (ValueError, OSError, subprocess.SubprocessError) as error:
        parser.exit(2, f"asmdiff: {error}\n")
    print(json.dumps({"output": str(args.output), "sizes": result['sizes'],
                      "diagnostic_line_counts": result['diagnostic_line_counts'],
                      "shifted_runs": len(result['shifted_runs']),
                      "possible_moved_sequences": len(result['possible_moved_sequences']),
                      "diagnostic_only": True}, indent=2))


if __name__ == '__main__':
    main()
