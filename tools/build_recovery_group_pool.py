#!/usr/bin/env python3
"""Build a pinned, read-only one-hop qualification frontier, never ready tasks.

Only declared catalogue ranges and direct BLs with original address labels are
accepted. This is not a disassembler and does not infer ownership from proximity.
"""
import argparse
import hashlib
import json
from pathlib import Path
import re
import sqlite3
import time
from datetime import datetime, timezone


def number(value):
    if isinstance(value, int):
        return value
    text = str(value)
    return int(text, 16 if text.startswith('0x') or re.search('[a-fA-F]', text) or (len(text) == 8 and text.startswith('0')) else 10)


def pin(path):
    path = Path(path).resolve()
    return {'path': str(path), 'sha256': hashlib.sha256(path.read_bytes()).hexdigest()}


def overlaps(start, size, other, length):
    return start < other + length and other < start + size


def symbols(text):
    result = {}
    for name, address in re.findall(r'\.(?:thumb_set|set|equ)\s+(\w+)\s*,\s*(0x[\da-fA-F]+)', text):
        address = int(address, 16)
        if 0x08000000 <= address < 0x0a000000:
            result[name] = (address & ~1) - 0x08000000
    return result


def direct_edges(text, caller, size, symbol_table):
    """Only an explicit original-address label establishes the call site."""
    site = None
    for line in text.splitlines():
        label = re.match(r'\s*\.L_([\da-fA-F]{8}):', line)
        if label:
            site = int(label[1], 16) - 0x08000000
            continue
        call = re.match(r'\s*bl(?:\.w)?\s+([\w.]+)', line)
        if call and site is not None and caller <= site < caller + size:
            target = call[1]
            numeric = re.fullmatch(r'(?:RetailCall_|\.L_)([\da-fA-F]{8})', target)
            offset = ((int(numeric[1], 16) & ~1) - 0x08000000) if numeric else symbol_table.get(target)
            if offset is not None:
                yield {'caller': caller, 'site': site, 'target': offset}
        # Do not assign a later instruction to an earlier address label.
        if line.strip() and not line.lstrip().startswith(('/*', '*', '//', '@')):
            site = None


def build_pool(repo, catalog, manifest, db=None, exclusions=None, dispositions=None, group='battle', qualification_group=None):
    started = time.monotonic()
    explicit_qualification_group = qualification_group is not None
    qualification_group = qualification_group or group
    repo = Path(repo).resolve()
    cat = json.loads(Path(catalog).read_text())
    man = json.loads(Path(manifest).read_text())
    rows = cat['functions']
    seeds = [dict(x) for x in rows if x.get('group') == group]
    catalog_seed_count = len(seeds)
    ledger_seed_tasks = []
    ledger_seed_rejections = []
    by_offset = {}
    for row in rows:
        by_offset.setdefault(number(row['rom_offset']), []).append(row)
    modules = man['modules']
    native_ranges = []
    for module in modules:
        spans = {(number(module['offset']), number(module['size']))}
        spans.update((number(f['offset']), number(f['size'])) for f in module.get('functions', []) if 'size' in f)
        native_ranges.extend((start, size, module) for start, size in spans)
    syms = {}
    for m in modules:
        for f in m.get('functions', []):
            syms[f['name']] = number(f['offset'])
        syms[m['name']] = number(m['offset'])
    external = repo / 'asm/external_thumb_symbols.s'
    if external.exists():
        syms.update(symbols(external.read_text()))
    histories = []
    leases = []
    if db:
        connection = sqlite3.connect(Path(db).resolve().as_uri() + '?mode=ro', uri=True)
        try:
            connection.execute('BEGIN')
            for task, state, original_bytes, spec in connection.execute('SELECT id,state,original_bytes,spec FROM tasks'):
                spec = json.loads(spec)
                if spec.get('rom_offset') is not None:
                    histories.append((number(spec['rom_offset']), number(spec.get('original_span_bytes', original_bytes)), task, state))
                if explicit_qualification_group and (spec.get('group') == qualification_group or spec.get('work_group') == qualification_group):
                    ledger_seed_tasks.append((task, state, spec, original_bytes))
            if connection.execute("SELECT count(*) FROM sqlite_master WHERE name='work_leases'").fetchone()[0]:
                leases = list(connection.execute("SELECT rom_offset,size,actor,kind FROM work_leases WHERE state='active'"))
        finally:
            connection.close()
    seed_keys = {(number(x['rom_offset']), number(x['original_bytes'])) for x in seeds}
    ledger_added = 0
    ledger_seed_provenance = []
    for task, state, spec, original_bytes in ledger_seed_tasks:
        if spec.get('rom_offset') is None:
            ledger_seed_rejections.append({'task':task,'reason':'missing_native_offset'})
            continue
        off = number(spec['rom_offset'])
        size = number(spec.get('original_span_bytes', original_bytes))
        matches = [x for x in by_offset.get(off, []) if number(x['original_bytes']) == size]
        declared = [x for x in matches if x.get('entry_kind') == 'declared_function' or any(
            start == off and length == size and any(number(f['offset']) == off and number(f['size']) == size
            for f in module.get('functions', []) if 'size' in f) for start,length,module in native_ranges)]
        usable = [x for x in declared if any((repo / path).is_file() for path in x.get('asm_paths', []))]
        if not usable:
            ledger_seed_rejections.append({'task':task,'rom_offset':off,'size':size,'reason':'no_complete_catalog_function_with_original_asm'})
            continue
        ledger_seed_provenance.append({'task':task,'state':state,'rom_offset':off,'original_span_bytes':size,
                                       'group':spec.get('group'),'work_group':spec.get('work_group'),
                                       'source':pin(next(repo / path for path in usable[0]['asm_paths'] if (repo / path).is_file()))})
        if (off,size) not in seed_keys:
            added = dict(usable[0])
            added['seed_ledger_task'] = task
            seeds.append(added)
            seed_keys.add((off,size))
            ledger_added += 1
    sdk = json.loads(Path(exclusions).read_text()).get('entries', []) if exclusions else []
    closed = json.loads(Path(dispositions).read_text()).get('entries', []) if dispositions else []
    candidates = {}
    unresolved = []
    source_count = 0
    for seed in seeds:
        for relative in seed.get('asm_paths', []):
            path = repo / relative
            if not path.is_file():
                unresolved.append({'caller': seed['rom_offset'], 'reason': 'missing_seed_asm', 'path': str(path)})
                continue
            source_count += 1
            text = path.read_text()
            table = dict(syms)
            table.update(symbols(text))
            source_pin = pin(path)
            for edge in direct_edges(text, number(seed['rom_offset']), number(seed['original_bytes']), table):
                matches = by_offset.get(edge['target'], [])
                ranges = {(number(x['rom_offset']), number(x['original_bytes'])) for x in matches}
                if len(ranges) != 1:
                    unresolved.append(dict(edge, reason='target_not_unique_catalog_range', matches=len(matches)))
                    continue
                target = matches[0]
                off, size = next(iter(ranges))
                key = (off, size)
                proof = dict(source_pin, **edge)
                if key in candidates:
                    if proof not in candidates[key]['source_edges']:
                        candidates[key]['source_edges'].append(proof)
                    continue
                target_paths = [repo / x for x in target.get('asm_paths', []) if (repo / x).is_file()]
                matching_modules = [m for start, length, m in native_ranges if start == off and length == size]
                reasons = []
                declared_function = target.get('entry_kind') == 'declared_function' or any(
                    number(f['offset']) == off and number(f['size']) == size
                    for m in matching_modules for f in m.get('functions', []) if 'size' in f)
                if not declared_function:
                    reasons.append('whole_function_boundary_unproven')
                history = [{'task': t, 'state': s, 'rom_offset': o, 'size': n} for o,n,t,s in histories if overlaps(off,size,o,n)]
                if history:
                    reasons.append('historical_native_overlap')
                if any(m.get('kind') == 'c' and m.get('match_policy') == 'exact' for m in matching_modules):
                    reasons.append('selected_exact_c')
                if len(matching_modules) != 1:
                    reasons.append('nonunique_or_missing_current_manifest_range')
                if not target_paths:
                    reasons.append('missing_original_asm')
                target_pin = pin(target_paths[0]) if target_paths else None
                sdk_hits = [x.get('name') for x in sdk if overlaps(off,size,number(x['rom_offset']),number(x['original_span_bytes']))]
                if sdk_hits:
                    reasons.append('sdk_runtime_driver_overlap')
                bound = [x for x in closed if number(x['rom_offset']) == off and target_pin and x.get('source_sha256') == target_pin['sha256']]
                if bound:
                    reasons.append('source_hash_disposition')
                busy = [{'actor':a,'kind':k,'rom_offset':o,'size':n} for o,n,a,k in leases if o is not None and overlaps(off,size,o,n)]
                if busy:
                    reasons.append('live_work_lease_overlap')
                item = {'group': target.get('group','unclassified'), 'qualification_group': qualification_group,
                        'group_basis': 'direct_call_from_' + group, 'module': matching_modules[0]['name'] if len(matching_modules)==1 else target['name'],
                        'rom_offset': off, 'original_span_bytes': size, 'mode':target.get('mode'),
                        'boundary_kind':'whole_function' if declared_function else 'module_span_unproven',
                        'catalog_entry_kind':target.get('entry_kind'),
                        'source':target_pin, 'edge':proof,'source_edges':[proof], 'priority':size,
                        'eligibility':'excluded' if reasons else 'qualification_only', 'exclusion_reasons':reasons,
                        'historical_native':history,'sdk_exclusions':sdk_hits,'hash_dispositions':bound,'live_leases':busy,
                        'readiness':'unknown; source ABI/group/CFG qualification required; never automatic native-ready'}
                if bound and dispositions:
                    item['disposition'] = pin(dispositions)
                candidates[key] = item
    result = {'schema':'recovery-group-pool-v1','generated_at':datetime.now(timezone.utc).isoformat(),
              'group':group,'qualification_group':qualification_group,'manifest':pin(manifest),'catalog':pin(catalog),
              'inputs':{k:pin(v) for k,v in [('exclusions',exclusions),('dispositions',dispositions)] if v},
              'scope':'One hop from existing declared group ASM only; no inferred game ownership or ready tasks.',
              'candidates':sorted(candidates.values(),key=lambda x:(x['priority'],x['rom_offset'])),
              'unresolved_edges':unresolved, 'ledger_seed_rejections':ledger_seed_rejections,
              'ledger_seed_tasks_considered':len(ledger_seed_tasks),'ledger_seed_provenance':ledger_seed_provenance}
    reasons = {}
    for row in result['candidates']:
        for reason in row['exclusion_reasons']:
            reasons[reason] = reasons.get(reason,0)+1
    result['metrics'] = {'seed_catalog_rows':catalog_seed_count,'ledger_seed_rows_added':ledger_added,'seed_rows_total':len(seeds),'seed_asm_files_read':source_count,
                         'unique_direct_targets':len(candidates),'qualification_only':sum(x['eligibility']=='qualification_only' for x in candidates.values()),
                         'exclusion_reason_counts_nonexclusive':reasons,'unresolved_count':len(unresolved),'elapsed_seconds':time.monotonic()-started}
    return result


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--repo',type=Path,default=Path(__file__).resolve().parents[1])
    parser.add_argument('--catalog',type=Path,required=True)
    parser.add_argument('--manifest',type=Path,required=True)
    parser.add_argument('--db',type=Path)
    parser.add_argument('--exclusions',type=Path)
    parser.add_argument('--dispositions',type=Path)
    parser.add_argument('--group',default='battle')
    parser.add_argument('--qualification-group', help='Qualification campaign identity; defaults to --group')
    parser.add_argument('--output',type=Path,required=True)
    args=parser.parse_args()
    args.output.parent.mkdir(parents=True,exist_ok=True)
    # Freeze exactly the bytes read for this run, independently of live integration.
    manifest_bytes = args.manifest.read_bytes()
    manifest_sha = hashlib.sha256(manifest_bytes).hexdigest()
    snapshot = args.output.parent / ('manifest-' + manifest_sha + '.json')
    if snapshot.exists() and snapshot.read_bytes() != manifest_bytes:
        raise ValueError('immutable manifest snapshot collision')
    if not snapshot.exists():
        snapshot.write_bytes(manifest_bytes)
    result=build_pool(args.repo,args.catalog,snapshot,args.db,args.exclusions,args.dispositions,args.group,args.qualification_group)
    args.output.write_text(json.dumps(result,indent=2)+'\n')
    print(json.dumps(result['metrics'],sort_keys=True))


if __name__=='__main__':
    main()
