#!/usr/bin/env python3
"""Build all selected source modules and verify recorded native hashes without a ROM."""
import argparse
import csv
import io
from concurrent.futures import ThreadPoolExecutor, as_completed
import hashlib
import json
from pathlib import Path
import re
import subprocess
import sys
import tempfile
import time

import build_rom

ROOT = Path(__file__).resolve().parents[1]
RETAIL_SHA256 = '43fc8204c6dceee58828aebc7af0c72eb807e99f35ad641c8bb0a4fa8b6edc19'


def sha256(data):
    return hashlib.sha256(data).hexdigest()


def set_hash(rows):
    canonical = json.dumps(rows, sort_keys=True, separators=(',', ':')).encode()
    return sha256(canonical)


def validate_inputs(config, index, expected, root=ROOT):
    """Reject stale selections, altered inputs, duplicate ranges or missing targets."""
    if (config.get('sha256') != RETAIL_SHA256 or index.get('retail_sha256') != RETAIL_SHA256
            or expected.get('retail_sha256') != RETAIL_SHA256
            or expected.get('schema') != 'completed-module-sha256-v1'):
        raise ValueError('Target identity or hash snapshot schema mismatch')
    modules = config.get('modules')
    indexed = index.get('modules')
    targets = expected.get('modules')
    if not all(isinstance(x, list) for x in (modules, indexed, targets)):
        raise ValueError('Missing selection, source index or target hashes')
    if set_hash(targets) != expected.get('module_set_sha256'):
        raise ValueError('Recorded target set checksum mismatch')
    selected, published, hashes = {}, {}, {}
    for row, dest in ((modules, selected), (indexed, published), (targets, hashes)):
        for item in row:
            if not isinstance(item, dict) or not re.fullmatch(r'[A-Za-z0-9_.-]+', item.get('name', '')):
                raise ValueError('Invalid module identity')
            if item['name'] in dest:
                raise ValueError('Duplicate module identity: ' + item['name'])
            dest[item['name']] = item
    if not selected or set(selected) != set(published) or set(selected) != set(hashes):
        raise ValueError('Selection, source index and target hashes must cover the same modules')
    last_end = 0
    for module in sorted(modules, key=lambda x: x.get('offset', -1)):
        name = module['name']; offset = module.get('offset'); size = module.get('size')
        if (module.get('kind') not in ('c', 'mixed') or module.get('match_policy', 'exact') != 'exact'
                or type(offset) is not int or type(size) is not int or size <= 0 or offset < last_end
                or offset + size > config.get('size', 0)):
            raise ValueError('Invalid or overlapping exact source span: ' + name)
        last_end = offset + size
        row = published[name]; target = hashes[name]
        if (module['offset'], module['size'], module['kind'], module['source']) != (
                row.get('rom_offset'), row.get('original_bytes'), row.get('kind'), row.get('source')):
            raise ValueError('Module/source index identity mismatch: ' + name)
        if (set(target) != {'name', 'rom_offset', 'original_bytes', 'sha256'}
                or (target['rom_offset'], target['original_bytes']) != (offset, size)
                or not isinstance(target['sha256'], str) or not re.fullmatch(r'[0-9a-f]{64}', target['sha256'])):
            raise ValueError('Invalid target hash identity: ' + name)
    paths = set()
    for item in index.get('files', []):
        if not isinstance(item, dict) or set(item) != {'path', 'sha256'} or item['path'] in paths:
            raise ValueError('Invalid or duplicate source index file')
        paths.add(item['path'])
        path = (root / item['path']).resolve()
        if not path.is_relative_to(root.resolve()) or not path.is_file() or sha256(path.read_bytes()) != item['sha256']:
            raise ValueError('Published source/header hash mismatch: ' + item['path'])
    if any(module['source'] not in paths for module in modules):
        raise ValueError('A selected source is not hash-pinned in the source index')
    return hashes


def load_function_targets(config, expected, raw):
    """Bind every selected function/data range to its recorded digest."""
    if sha256(raw) != expected.get('function_table_sha256'):
        raise ValueError('Function hash table checksum mismatch')
    reader = csv.DictReader(io.StringIO(raw.decode('utf-8'), newline=''))
    if reader.fieldnames != ['id', 'address', 'original_bytes', 'sha256', 'kind', 'module', 'name']:
        raise ValueError('Invalid function hash table columns')
    records = list(reader)
    if len(records) != expected.get('function_range_count'):
        raise ValueError('Function hash table count mismatch')
    by_key = {}
    for row in records:
        try:
            address = int(row['address'], 16)
            length = int(row['original_bytes'])
        except ValueError as error:
            raise ValueError('Invalid function address or length') from error
        offset = address - config['rom_base']
        identity = f'US-{offset:08X}-{length:06X}'
        if (offset < 0 or length <= 0 or row['id'] != identity
                or row['address'] != f'0x{address:08X}'
                or row['kind'] not in ('function', 'data')
                or not re.fullmatch(r'[0-9a-f]{64}', row['sha256'])):
            raise ValueError('Invalid function hash identity')
        key = (row['module'], offset, length, row['name'])
        if key in by_key:
            raise ValueError('Duplicate function hash range')
        by_key[key] = row
    result = {}
    for module in config['modules']:
        offset = module['offset']
        functions = module.get('functions') or [dict(name=module['name'], offset=offset, size=module['size'])]
        spans = []
        for item in sorted(functions, key=lambda x: x['offset']):
            start, size, name = item['offset'], item['size'], item['name']
            key = (module['name'], start, size, name)
            row = by_key.pop(key, None)
            if (start != offset or size <= 0 or start + size > module['offset'] + module['size']
                    or row is None or row['kind'] != ('data' if name.startswith('Compiler') else 'function')):
                raise ValueError('Missing or invalid selected function range: ' + module['name'])
            spans.append((start - module['offset'], size, row['sha256'], row['id']))
            offset = start + size
        if offset != module['offset'] + module['size']:
            raise ValueError('Function ranges do not cover module: ' + module['name'])
        result[module['name']] = spans
    if by_key:
        raise ValueError('Unselected function hash ranges')
    return result


def verify_function_ranges(data, spans):
    for offset, size, expected_hash, identity in spans:
        if sha256(data[offset:offset + size]) != expected_hash:
            raise ValueError(identity + ': function range SHA-256 mismatch')


class ModuleMismatch(ValueError):
    def __init__(self, message, functions):
        super().__init__(message)
        self.functions = functions


def verify_build(config, index, expected, build_dir, jobs=2, function_targets=None, outcomes=None):
    targets = validate_inputs(config, index, expected)
    build_rom.BUILD_ROOT = build_dir.resolve()
    workroot = build_rom.BUILD_ROOT / 'source-hash-validation'
    workroot.mkdir(parents=True, exist_ok=True)
    started = time.monotonic()
    with tempfile.TemporaryDirectory(prefix='run-', dir=workroot) as tmp:
        def compile_one(module):
            work = Path(tmp) / module['name']; work.mkdir()
            build_rom.validate_source_mix(module)
            # Source modules use no reference bytes. Their original bytes are
            # represented only by the separately recorded per-range digest.
            data = build_rom.compile_module(module, work, config['rom_base'], None, None)
            entries = build_rom.check_linked_function_entries(module, work, config['rom_base'])
            target = targets[module['name']]
            actual = sha256(data)
            function_results = []
            if function_targets is not None:
                definitions = sorted(module.get('functions') or [dict(name=module['name'], offset=module['offset'], size=module['size'])], key=lambda x: x['offset'])
                for definition, (offset, size, digest, identity) in zip(definitions, function_targets[module['name']]):
                    valid = offset + size <= len(data) and sha256(data[offset:offset + size]) == digest
                    function_results.append({'name': definition['name'], 'id': identity,
                                             'status': 'match' if valid else 'mismatch'})
            if (len(data) != target['original_bytes'] or actual != target['sha256']
                    or any(row['status'] != 'match' for row in function_results)):
                raise ModuleMismatch(f"{module['name']}: generated {len(data)} bytes, SHA-256 {actual}; "
                                     f"expected {target['original_bytes']} bytes, SHA-256 {target['sha256']}", function_results)
            if entries < 1:
                raise ValueError(module['name'] + ': no linked function entry')
            return {'name': module['name'], 'rom_offset': module['offset'],
                    'original_bytes': len(data), 'sha256': actual}, function_results
        rows, failures = [], []
        with ThreadPoolExecutor(max_workers=jobs) as pool:
            futures = {pool.submit(compile_one, module): module['name'] for module in config['modules']}
            for future in as_completed(futures):
                try:
                    row, function_results = future.result()
                    rows.append(row)
                    if outcomes is not None:
                        outcomes[row['name']] = {'status': 'match', 'functions': function_results}
                except (Exception, SystemExit) as error:
                    name = futures[future]
                    failures.append({'module': name, 'error': str(error)})
                    if outcomes is not None:
                        outcomes[name] = {'status': 'mismatch' if isinstance(error, ModuleMismatch) else 'build error',
                                          'error': str(error), 'functions': getattr(error, 'functions', [])}
                if (len(rows) + len(failures)) % 100 == 0:
                    print(f"Checked {len(rows) + len(failures)}/{len(futures)} modules", flush=True)
        if failures:
            raise ValueError(json.dumps({'failed_modules': failures}, sort_keys=True))
    rows.sort(key=lambda row: row['rom_offset'])
    actual_set = set_hash(rows)
    if actual_set != expected['module_set_sha256']:
        raise ValueError('Compiled module set checksum mismatch')
    return {'modules': len(rows), 'original_bytes': sum(row['original_bytes'] for row in rows),
            'module_set_sha256': actual_set, 'rom_verified': False,
            'scope': 'Selected source ranges only; unrecovered code and resources are not checked.',
            'elapsed_seconds': round(time.monotonic() - started, 2)}


def changed_files(base):
    result = subprocess.check_output(['git', 'diff', '--name-only', '--no-renames', '-z', base, 'HEAD', '--'], cwd=ROOT)
    return sorted(path.decode('utf-8', errors='replace') for path in result.split(b'\0') if path)


def load_build_selections(root=ROOT):
    """Include explicit incremental publications, without changing the frozen release."""
    def read(path):
        resolved = (root / path).resolve()
        if not resolved.is_relative_to(root.resolve()):
            raise ValueError('Selection path escapes repository')
        return resolved.read_bytes()

    config = json.loads(read('config/completed-build.json'))
    index = json.loads(read('src/completed-index.json'))
    expected = json.loads(read('data/completed-module-hashes.json'))
    selections = [(config, index, expected, read('data/completed-function-hashes.csv'))]
    registry = root / 'data/source-build-selections.json'
    if registry.exists():
        registered = json.loads(registry.read_text())
        if registered.get('schema') != 'source-build-selections-v1':
            raise ValueError('Unknown source build registry schema')
        for entry in registered['selections']:
            raw = read(entry['config'])
            proof = json.loads(read(entry['proof']))
            if (proof.get('schema') != 'source-build-selection-proof-v1'
                    or proof.get('config_sha256') != sha256(raw)):
                raise ValueError('Incremental build selection configuration hash mismatch')
            selections.append((json.loads(raw), proof['source_index'], proof['expected'],
                               proof['function_hash_csv'].encode('utf-8')))
    return merge_build_selections(selections, root)


def merge_build_selections(selections, root=ROOT):
    """Authenticate each selection, then reject collisions across publications."""
    merged = dict(selections[0][0], modules=[])
    index = {'retail_sha256': RETAIL_SHA256, 'modules': [], 'files': []}
    targets, functions, pins = [], {}, {}
    for config, source_index, expected, table in selections:
        validate_inputs(config, source_index, expected, root)
        ranges = load_function_targets(config, expected, table)
        if any(config.get(key) != merged.get(key) for key in ('rom_base', 'size', 'sha256')):
            raise ValueError('Build selections target different ROM identities')
        if functions.keys() & ranges.keys():
            raise ValueError('Duplicate module across build selections')
        functions.update(ranges)
        merged['modules'].extend(config['modules'])
        index['modules'].extend(source_index['modules'])
        targets.extend(expected['modules'])
        for pin in source_index['files']:
            previous = pins.setdefault(pin['path'], pin['sha256'])
            if previous != pin['sha256']:
                raise ValueError('Conflicting source input pins across build selections')
    targets.sort(key=lambda row: row['rom_offset'])
    index['files'] = [{'path': path, 'sha256': digest} for path, digest in sorted(pins.items())]
    expected = {'schema': 'completed-module-sha256-v1', 'retail_sha256': RETAIL_SHA256,
                'modules': targets, 'module_set_sha256': set_hash(targets)}
    validate_inputs(merged, index, expected, root)
    return merged, index, expected, functions


def require_changed_source_coverage(config, paths, root=ROOT):
    """A green build must not silently ignore newly published C files."""
    selected = {module['source'] for module in config['modules']}
    missing = [path for path in paths if path.startswith('src/') and path.endswith('.c')
               and (root / path).is_file() and path not in selected]
    if missing:
        raise ValueError('Changed C sources have no verified build selection: ' + ', '.join(missing))


def write_delta_summary(config, paths, outcomes, error, destination):
    """Report direct source changes, with unknown results distinct from mismatches."""
    def safe(value):
        return str(value).replace('&', '&amp;').replace('<', '&lt;').replace('|', '&#124;').replace('`', '&#96;').replace('\n', ' ')
    lines = ['## Source hash verification', '',
             'Whole selected build: ' + ('failed: ' + safe(error) if error else 'passed'), '',
             f"Selected coverage: {len(config['modules']):,} modules / "
             f"{sum(module['size'] for module in config['modules']):,} original bytes. "
             'Recorded native-range hashes are checked without a ROM; this is not full-ROM validation.', '',
             '### Changed files and directly associated selected functions', '',
             '| File | Function / range | Result |', '| --- | --- | --- |']
    modules_by_source = {}
    for module in config['modules']:
        modules_by_source.setdefault(module['source'], []).append(module)
    for path in paths:
        modules = modules_by_source.get(path, [])
        if not modules:
            if path.startswith('src/') and path.endswith('.c') and (ROOT / path).is_file():
                lines.append(f'| `{safe(path)}` | No selected source module | ERROR: no verified build coverage |')
            elif path.startswith('src/') and path.endswith('.c'):
                lines.append(f'| `{safe(path)}` | Deleted source | Not built |')
            else:
                lines.append(f'| `{safe(path)}` | Metadata, header or build tooling | See full-build and artifact checks |')
        for module in modules:
            result = outcomes.get(module['name'], {})
            by_id = {item['id']: item['status'] for item in result.get('functions', [])}
            for item in module.get('functions') or [dict(name=module['name'], offset=module['offset'], size=module['size'])]:
                ident = f"US-{item['offset']:08X}-{item['size']:06X}"
                status = by_id.get(ident, result.get('status', 'not built'))
                if status == 'match' and result.get('status') == 'mismatch':
                    status = 'range hash matches; module mismatch'
                lines.append(f"| `{safe(path)}` | `{safe(item['name'])}` ({ident}) | {status} |")
    if not paths:
        lines.append('| No changed files | — | — |')
    lines.extend(['', 'Headers, build configuration and other non-module files can affect multiple sources; the full selected set is rebuilt, but per-file dependency attribution is not inferred.', '', '### All failed modules', ''])
    failures = [(name, result) for name, result in sorted(outcomes.items()) if result['status'] != 'match']
    sources = {module['name']: module['source'] for module in config['modules']}
    if failures:
        for name, result in failures:
            lines.append(f"- `{safe(sources.get(name, 'unknown'))}` / `{safe(name)}`: {safe(result.get('error', result['status']))}")
            for item in result.get('functions', []):
                if item['status'] != 'match':
                    lines.append(f"  - `{safe(item['name'])}` ({item['id']}): {item['status']}")
    else:
        lines.append('None reported.' if not error else 'No module result available; see the error above.')
    with open(destination, 'a', encoding='utf-8') as output:
        output.write('\n'.join(lines) + '\n')


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--jobs', type=int, choices=range(1, 5), default=2)
    parser.add_argument('--build-dir', type=Path, default=ROOT / 'build')
    parser.add_argument('--base-ref', help='Report changed source files against this Git revision')
    parser.add_argument('--summary', type=Path, help='Append the delta report to this file')
    args = parser.parse_args()
    config = {'modules': []}
    paths = changed_files(args.base_ref) if args.base_ref else []
    outcomes, error = {}, None
    try:
        config, index, expected, functions = load_build_selections()
        require_changed_source_coverage(config, paths)
        result = verify_build(config, index, expected, args.build_dir, args.jobs, functions, outcomes)
        result['function_ranges'] = sum(len(rows) for rows in functions.values())
        print(json.dumps(result, indent=2))
    except (Exception, SystemExit) as exc:
        error = str(exc)
        print(error, file=sys.stderr)
    finally:
        if args.summary:
            write_delta_summary(config, paths, outcomes, error, args.summary)
    if error:
        raise SystemExit(1)


if __name__ == '__main__':
    main()
