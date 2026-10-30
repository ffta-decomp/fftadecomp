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


def verify_build(config, index, expected, build_dir, jobs=2, function_targets=None):
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
            if len(data) != target['original_bytes'] or actual != target['sha256']:
                raise ValueError(f"{module['name']}: generated {len(data)} bytes, SHA-256 {actual}; "
                                 f"expected {target['original_bytes']} bytes, SHA-256 {target['sha256']}")
            if function_targets is not None:
                verify_function_ranges(data, function_targets[module['name']])
            if entries < 1:
                raise ValueError(module['name'] + ': no linked function entry')
            return {'name': module['name'], 'rom_offset': module['offset'],
                    'original_bytes': len(data), 'sha256': actual}
        rows, failures = [], []
        with ThreadPoolExecutor(max_workers=jobs) as pool:
            futures = {pool.submit(compile_one, module): module['name'] for module in config['modules']}
            for future in as_completed(futures):
                try:
                    rows.append(future.result())
                except (Exception, SystemExit) as error:
                    failures.append({'module': futures[future], 'error': str(error)})
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


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--jobs', type=int, choices=range(1, 5), default=2)
    parser.add_argument('--build-dir', type=Path, default=ROOT / 'build')
    args = parser.parse_args()
    config = json.loads((ROOT / 'config/completed-build.json').read_text())
    index = json.loads((ROOT / 'src/completed-index.json').read_text())
    expected = json.loads((ROOT / 'data/completed-module-hashes.json').read_text())
    functions = load_function_targets(config, expected, (ROOT / 'data/completed-function-hashes.csv').read_bytes())
    result = verify_build(config, index, expected, args.build_dir, args.jobs, functions)
    result['function_ranges'] = sum(len(rows) for rows in functions.values())
    print(json.dumps(result, indent=2))


if __name__ == '__main__':
    main()
