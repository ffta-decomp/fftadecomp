"""Refresh public image accounting from registered, pinned integration receipts.

This reader never builds code, examines C, changes the ledger or writes config.
Additions and image-bound nonexact C/mixed replacements are supported. A newer invalid packet is
an error, rather than permission to silently continue publishing an old image.
"""
from __future__ import annotations

import copy
import datetime as dt
import hashlib
import json
from pathlib import Path
import re
import subprocess

ROOT = Path(__file__).resolve().parents[1]
RESIDUAL_GROUP = 'earlier-and-shared-routines'
IMAGE_SCHEMA = 'whole-exact-production-identity-v1'


def require(condition, message):
    if not condition:
        raise ValueError('public baseline refresh: ' + message)


def digest(raw):
    return hashlib.sha256(raw).hexdigest()


def pinned(pin):
    require(isinstance(pin, dict) and isinstance(pin.get('path'), str), 'missing evidence pin')
    raw = Path(pin['path']).read_bytes()
    require(digest(raw) == pin.get('sha256'), 'evidence hash changed: ' + pin['path'])
    return raw


def json_pin(pin):
    return json.loads(pinned(pin))


def hash_value(value):
    return isinstance(value, str) and re.fullmatch('[0-9a-f]{64}', value) is not None


def natural(value, label):
    require(type(value) is int and value >= 0, 'invalid ' + label)
    return value


def git(repo, *args, check=True):
    result = subprocess.run(['git', '-C', str(repo), *args], capture_output=True, check=False)
    if check:
        require(result.returncode == 0, 'Git verification failed: ' + ' '.join(args[:2]))
    return result


def ancestor(repo, older, newer):
    result = git(repo, 'merge-base', '--is-ancestor', older, newer, check=False)
    require(result.returncode in (0, 1), 'cannot verify Git ancestry')
    return result.returncode == 0


def _packets(ledger, repo):
    """Read only registered commit evidence, never discover private directories."""
    packets = []
    for row in ledger.db.execute('SELECT sha,payload FROM commits ORDER BY recorded_at'):
        sha, payload = row
        commit = json.loads(payload)
        require(commit.get('sha') == sha, 'registered commit identity differs')
        require(re.fullmatch('[0-9a-f]{40}', sha) is not None, 'invalid commit identity')
        # Off-branch milestones cannot replace this checkout's baseline.
        if not ancestor(repo, sha, 'HEAD'):
            continue
        documents = []
        for pin in commit.get('evidence', []):
            if Path(pin['path']).suffix == '.json':
                documents.append((pin, json_pin(pin)))
        images = [(pin, doc) for pin, doc in documents if isinstance(doc, dict) and doc.get('schema') == IMAGE_SCHEMA]
        image_named = [doc for pin, doc in documents if Path(pin['path']).name == 'actual-image-identity.json']
        require(not image_named or images, 'unsupported actual-image receipt schema')
        if not images:
            continue
        require(len(images) == 1, 'ambiguous actual-image evidence')
        pin, image = images[0]
        receipts = [doc for _, doc in documents if isinstance(doc, dict) and doc.get('commit') == sha
                    and doc.get('actual_image_gate_sha256') == pin['sha256']]
        packets.append({'commit': commit, 'image': image, 'image_pin': pin,
                        'receipt': receipts[0] if len(receipts) == 1 else None})
    return packets


def _members(manifest, report, baseline, assignments, replacements=()):
    groups = {g['public_submodule_id']: g for g in baseline['groups']}
    old = {m['module']: m for m in baseline['modules_private']}
    reports = {m['name']: m for m in report['modules']}
    require(len(reports) == len(report['modules']), 'duplicate build modules')
    selected = [m for m in manifest['modules'] if m['kind'] in ('c', 'mixed')]
    require(len({m['name'] for m in selected}) == len(selected), 'duplicate manifest modules')
    require(set(old) <= {m['name'] for m in selected}, 'non-additive removal or kind change')
    rows = []
    for module in selected:
        name = module['name']
        built = reports.get(name)
        require(built is not None, 'missing build module: ' + name)
        offset = natural(module['offset'], 'module offset')
        size = natural(module['size'], 'module size')
        require(size > 0, 'empty module: ' + name)
        require((built['kind'], built['rom_offset'], built['size']) ==
                (module['kind'], offset, size), 'manifest/build range differs: ' + name)
        require(built.get('differing_bytes', []) == module.get('expected_differences', []),
                'manifest expected differences disagree: ' + name)
        require(type(built['exact_binary_match']) is bool and hash_value(built['sha256']),
                'unknown module identity: ' + name)
        if built['exact_binary_match']:
            require(not built.get('differing_bytes') and built.get('matching_bytes') == size,
                    'incomplete exact module: ' + name)
        previous = old.get(name)
        if previous:
            require(name in replacements or
                    (previous['kind'], previous['rom_offset'], previous['size'],
                     previous['source'], previous['binary_sha256'], previous['module_exact']) ==
                    (module['kind'], offset, size, module['source'], built['sha256'],
                     built['exact_binary_match']), 'non-additive existing module change: ' + name)
            group = previous['public_submodule_id']
            basis = previous['membership_basis']
        else:
            assignment = assignments.get(name)
            if assignment:
                require(assignment.get('source') == module['source'], 'membership source differs: ' + name)
                group = assignment['public_submodule_id']
                basis = 'explicit-pinned-module-membership'
            else:
                matches = [r['public_submodule_id'] for r in baseline.get('source_prefix_rules', [])
                           if module['source'].startswith(r['source_prefix'])]
                require(len(matches) <= 1, 'ambiguous source membership: ' + name)
                group = matches[0] if matches else RESIDUAL_GROUP
                basis = 'inherited-source-prefix-rule' if matches else 'unclassified-integrated-module'
        require(group in groups, 'unknown public subgroup: ' + str(group))
        functions = []
        for f in built['functions']:
            if f['name'].startswith('Compiler'):
                continue
            start = natural(f['rom_offset'], 'entry offset')
            length = natural(f['size'], 'entry size')
            require(offset <= start <= start + length <= offset + size, 'entry outside module: ' + name)
            require(type(f['exact_binary_match']) is bool and hash_value(f['sha256']),
                    'unknown entry accounting: ' + name)
            functions.append({'name': f['name'], 'rom_offset': start, 'size': length,
                              'end_exclusive': start + length, 'exact_binary_match': f['exact_binary_match'],
                              'binary_sha256': f['sha256']})
        pure = module['kind'] == 'c'
        row = {'module': name, 'source': module['source'], 'kind': module['kind'],
               'public_submodule_id': group, 'public_system': groups[group]['system'],
               'membership_basis': basis, 'rom_offset': offset, 'size': size,
               'end_exclusive': offset + size, 'binary_sha256': built['sha256'],
               'module_exact': built['exact_binary_match'],
               'pure_c_exact_span_eligible': pure and built['exact_binary_match'],
               'compiled_named_entry_count': len(functions),
               'exact_compiled_named_entry_count': sum(f['exact_binary_match'] for f in functions) if pure else 0,
               'exact_compiled_named_body_bytes': sum(f['size'] for f in functions if f['exact_binary_match']) if pure else 0,
               'functions': functions, 'compiler_placeholder_count': len(built['functions']) - len(functions),
               'module_span_limit': 'Module/entry accounting does not establish whole original-function completion.'}
        if basis == 'unclassified-integrated-module':
            row['responsibility_status'] = 'unresolved-subgroup-accounting-remainder'
        rows.append(row)
    spans = sorted((m['rom_offset'], m['end_exclusive']) for m in rows)
    require(all(a[1] <= b[0] for a, b in zip(spans, spans[1:])), 'overlapping public module ranges')
    return rows


def _account(rows):
    pure = [m for m in rows if m['kind'] == 'c']
    mixed = [m for m in rows if m['kind'] == 'mixed']
    return {'selected_c_modules': len(pure), 'pure_c_bytes': sum(m['size'] for m in pure),
            'exact_c_bytes': sum(m['size'] for m in pure if m['module_exact']),
            'nonmatching_c_bytes': sum(m['size'] for m in pure if not m['module_exact']),
            'compiled_c_entries': sum(m['compiled_named_entry_count'] for m in pure),
            'mixed_bytes': sum(m['size'] for m in mixed), 'mixed_modules': len(mixed),
            'mixed_entries': sum(m['compiled_named_entry_count'] for m in mixed)}


def _reconcile(baseline, rows, report):
    groups = copy.deepcopy(baseline['groups'])
    require(len({g['public_submodule_id'] for g in groups}) == len(groups), 'duplicate baseline group')
    for group in groups:
        members = [m for m in rows if m['public_submodule_id'] == group['public_submodule_id']]
        group['actual'] = _account(members)
        group['module_names'] = [m['module'] for m in members]
        group['exact_c_module_count'] = sum(m['pure_c_exact_span_eligible'] for m in members)
        group['exact_compiled_c_entry_count'] = sum(m['exact_compiled_named_entry_count'] for m in members)
        group['exact_compiled_c_body_bytes'] = sum(m['exact_compiled_named_body_bytes'] for m in members)
        if 'published' in group:
            group['delta'] = {k: v - group['published'][k] for k, v in group['actual'].items()}
            group['all_published_fields_match'] = not any(group['delta'].values())
    total = _account(rows)
    require(total['pure_c_bytes'] == report['recovered_c_bytes'] + report['nonmatching_c_bytes'],
            'build pure-C total differs')
    require(total['exact_c_bytes'] == report['recovered_c_bytes'], 'build exact-C total differs')
    require(total['mixed_bytes'] == report['mixed_c_span_bytes'], 'build mixed total differs')
    require(total['compiled_c_entries'] == report['recovered_c_functions'] + report['nonmatching_c_functions'],
            'build C entry total differs')
    require(total['mixed_entries'] == report['mixed_c_functions'], 'build mixed entry total differs')
    totals = {'c_modules': total['selected_c_modules'], 'mixed_modules': total['mixed_modules'],
              'pure_c_bytes': total['pure_c_bytes'], 'exact_c_module_span_bytes': total['exact_c_bytes'],
              'exact_c_modules': sum(m['pure_c_exact_span_eligible'] for m in rows),
              'compiled_c_entries': total['compiled_c_entries'],
              'exact_compiled_c_entries': sum(m['exact_compiled_named_entry_count'] for m in rows),
              'exact_compiled_c_body_bytes': sum(m['exact_compiled_named_body_bytes'] for m in rows),
              'mixed_bytes': total['mixed_bytes'], 'mixed_named_entries': total['mixed_entries'],
              'public_groups_reconciled': len(groups)}
    return groups, totals


def _replacement(method, module, previous, previous_built, image, ledger, repo):
    """Bind an old nonexact identity to pinned production metadata, without reading code."""
    name = module['name']
    require(previous['module_exact'] is False and previous_built['exact_binary_match'] is False,
            'already exact module replacement: ' + name)
    require((previous_built['kind'], previous_built['rom_offset'], previous_built['size'],
             previous_built['sha256']) ==
            (previous['kind'], previous['rom_offset'], previous['size'], previous['binary_sha256']),
            'previous replacement identity differs: ' + name)
    require(module['kind'] == previous['kind'], 'replacement kind differs: ' + name)
    require(module['offset'] == previous['rom_offset'], 'replacement offset shifted: ' + name)
    require(module['size'] >= previous['size'], 'replacement shrinks selected span: ' + name)
    require(method.get('prior_selected_kind') == previous['kind'] and
            method.get('prior_selected_bytes') == previous['size'], 'prior selected receipt differs: ' + name)
    require(method.get('source') == module['source'] and method.get('kind') == module['kind']
            and hash_value(method.get('source_sha256')), 'replacement source binding differs: ' + name)
    source = Path(module['source'])
    require(not source.is_absolute() and '..' not in source.parts, 'invalid replacement source: ' + name)
    source = (repo / source).resolve()
    task = ledger.db.execute('SELECT module,original_bytes,spec FROM tasks WHERE id=?',
                             (method['task_id'],)).fetchone()
    require(task is not None, 'replacement task is not registered: ' + name)
    spec = json.loads(task[2])
    require((task[0], task[1], spec.get('rom_offset'), spec.get('original_span_bytes')) ==
            (name, module['size'], module['offset'], module['size']), 'replacement task range differs: ' + name)
    original_sha = spec.get('original_reference_span_sha256')
    require(original_sha is None or original_sha == method['full_binary_sha256'],
            'replacement task retail identity differs: ' + name)
    pin = method.get('production_report')
    require(isinstance(pin, dict) and Path(pin.get('path', '')).suffix == '.json',
            'replacement native report missing: ' + name)
    native = json_pin(pin)
    require(native.get('schema') == 'local-module-build-v1' and
            native.get('retail_sha256') == image['reference_sha256'] and
            native.get('manifest_sha256') == image['manifest_sha256'], 'replacement native identity differs: ' + name)
    native_module = native.get('baseline_module', {})
    require((native_module.get('name'), native_module.get('kind'), native_module.get('rom_offset'),
             native_module.get('reference_size')) ==
            (name, module['kind'], module['offset'], module['size']), 'replacement native module differs: ' + name)
    segments = native.get('segments', [])
    require(len(segments) == 1, 'replacement native segment count differs: ' + name)
    segment = segments[0]
    require((segment.get('module'), segment.get('rom_offset'), segment.get('reference_size'),
             segment.get('generated_size'), segment.get('binary_sha256'), segment.get('matching_bytes')) ==
            (name, module['offset'], module['size'], module['size'], method['full_binary_sha256'], module['size']),
            'replacement native range/binary differs: ' + name)
    require(all(segment.get(key) == 0 for key in ('differing_bytes', 'overflow_bytes',
                    'missing_generated_bytes', 'unmatched_retail_bytes')) and segment.get('fits') is True
            and segment.get('neighbor_bytes_overlaid') is False and not segment.get('linker_veneers')
            and segment.get('entry_validation', {}).get('passed') is True
            and segment.get('elf_section_validation', {}).get('passed') is True,
            'replacement native exact gate incomplete: ' + name)
    entries = segment.get('functions', [])
    require(any(f.get('rom_offset') == module['offset'] and
                f.get('gba_address') == 0x08000000 + module['offset'] and
                ((f.get('mode') == 'thumb' and f.get('thumb_entry_address') == 0x08000001 + module['offset'])
                 or f.get('mode') == 'arm') for f in entries), 'replacement native entry differs: ' + name)
    inputs = native.get('compile_inputs', {})
    require(inputs.get('schema') == 'local-compile-inputs-v1' and
            inputs.get('capture') == 'before-and-after-compilation', 'replacement compile provenance missing: ' + name)
    effective = copy.deepcopy(module); effective['source'] = str(source)
    require(inputs.get('effective_module') == effective, 'replacement native configuration differs: ' + name)
    source_pins = [p for p in inputs.get('files', []) if p.get('role') == 'source']
    require(len(source_pins) == 1 and Path(source_pins[0]['path']).resolve() == source and
            Path(segment.get('source', '')).resolve() == source and
            source_pins[0].get('sha256') == segment.get('source_sha256') == method['source_sha256'],
            'replacement native source hash differs: ' + name)
    config_pins = [p for p in inputs.get('files', []) if p.get('role') == 'config']
    require(len(config_pins) == 1 and config_pins[0].get('sha256') == image['manifest_sha256'],
            'replacement native manifest pin differs: ' + name)
    toolchain = native.get('toolchain')
    require(isinstance(toolchain, dict) and bool(toolchain) and inputs.get('toolchain_sha256') ==
            digest(json.dumps(toolchain, sort_keys=True, separators=(',', ':')).encode()),
            'replacement native toolchain identity differs: ' + name)
    require(inputs.get('artifacts', {}).get('binary', {}).get('sha256') == method['full_binary_sha256'],
            'replacement native artifact identity differs: ' + name)


def _apply(packet, baseline, repo, manifest_path, assignments, ledger):
    commit = packet['commit']; image = packet['image']; receipt = packet['receipt']
    sha = commit['sha']
    require(receipt is not None, 'commit receipt does not bind actual image: ' + sha)
    require(image.get('passed') is True and image.get('full_image_equal_to_prevalidated_expected') is True
            and image.get('outside_owned_envelopes') == 0, 'actual-image gate not passed: ' + sha)
    require(image.get('reference_sha256') == baseline['retail_sha256'], 'retail revision differs')
    require(image.get('baseline_output_sha256') == baseline['baseline_rom_sha256'], 'image chain differs')
    previous_commit = baseline['integrated_commit']
    require(ancestor(repo, previous_commit, image['baseline_commit'])
            and ancestor(repo, image['baseline_commit'], sha), 'integration ancestry differs')
    directory = Path(packet['image_pin']['path']).parent
    manifest_pin = {'path': str(directory / 'prepared-manifest.json'), 'sha256': image['manifest_sha256']}
    build_pin = {'path': str(directory / 'full-build-report.json'), 'sha256': image['build_report_sha256']}
    manifest_raw = pinned(manifest_pin)
    require(git(repo, 'show', sha + ':' + manifest_path).stdout == manifest_raw,
            'prepared manifest differs from committed manifest')
    manifest = json.loads(manifest_raw); report = json_pin(build_pin)
    require(manifest['sha256'] == baseline['retail_sha256'] == report['input_sha256'], 'build revision differs')
    require(report['output_sha256'] == image['output_sha256'] and hash_value(report['output_sha256']),
            'actual-image/build output differs')
    methods = image['methods']
    require(len({m['module'] for m in methods}) == len(methods), 'duplicate integrated method')
    require(len({m['task_id'] for m in methods}) == len(methods), 'duplicate integrated task')
    require(len(commit['tasks']) == len(methods) and
            {m['task_id'] for m in methods} == set(commit['tasks']), 'registered tasks differ from actual image')
    require(receipt['methods'] == len(methods) and receipt['whole_exact_bytes'] ==
            sum(m['full_original_bytes'] for m in methods), 'commit accounting differs')
    selected = {m['name']: m for m in manifest['modules']}
    built = {m['name']: m for m in report['modules']}
    require(len(selected) == len(manifest['modules']), 'duplicate manifest modules')
    previous_manifest = json_pin(baseline['input_pins']['manifest'])
    previous_selected = {m['name']: m for m in previous_manifest['modules']}
    previous_built = {m['name']: m for m in json_pin(baseline['input_pins']['build_report'])['modules']}
    old = {m['module']: m for m in baseline['modules_private']}
    old_names = set(old); method_names = {m['module'] for m in methods}
    require(set(previous_selected) <= set(selected), 'unlisted manifest removal')
    require((set(selected) - set(previous_selected)) <= method_names, 'unlisted manifest addition')
    for name, previous in previous_selected.items():
        require(name in method_names or previous == selected[name], 'unlisted existing module change: ' + name)
    for method in methods:
        name = method['module']; module = selected[name]; result = built[name]
        require(method.get('full_range_exact') is True and result['exact_binary_match'] is True,
                'method not complete exact: ' + name)
        require((method['rom_offset'], method['full_original_bytes'], method['full_binary_sha256']) ==
                (module['offset'], module['size'], result['sha256']), 'method range/binary differs: ' + name)
        accounting = method['accounting']
        components = (accounting.get('instruction_bytes'), accounting.get('literal_bytes'), accounting.get('alignment_bytes'))
        for value in components:
            natural(value, 'method component accounting')
        require(sum(components) == module['size'], 'incomplete method accounting: ' + name)
        require(components == (result['instructions_bytes'], result['literal_bytes'], result['padding_bytes']),
                'method/build component accounting differs: ' + name)
        require(module['kind'] in ('c', 'mixed'), 'integrated method is not C/mixed: ' + name)
        for other in manifest['modules']:
            if other['name'] != name:
                other_start = natural(other['offset'], 'other module offset')
                other_end = other_start + natural(other['size'], 'other module size')
                require(module['offset'] + module['size'] <= other_start or
                        other_end <= module['offset'], 'overlapping integrated module range: ' + name)
        if name in old:
            _replacement(method, module, old[name], previous_built[name], image, ledger, repo)
    additions = {m['name'] for m in manifest['modules'] if m['kind'] in ('c', 'mixed')} - old_names
    require(additions == method_names - old_names, 'manifest additions not exactly covered by image receipt')
    replacements = method_names & old_names
    if replacements:
        require(image.get('components') == {
            key: sum(m['accounting'][key] for m in methods)
            for key in ('instruction_bytes', 'literal_bytes', 'alignment_bytes')},
            'actual-image component accounting differs')
    rows = _members(manifest, report, baseline, assignments, replacements)
    groups, totals = _reconcile(baseline, rows, report)
    result = copy.deepcopy(baseline)
    result.update({'generated_utc': dt.datetime.now(dt.timezone.utc).isoformat(), 'integrated_commit': sha,
                   'baseline_rom_sha256': report['output_sha256'], 'modules_private': rows,
                   'groups': groups, 'totals': totals, 'unknowns': [], 'report_manifest_mismatches': [],
                   'task_baseline_overlap_private': [],
                   'task_baseline_overlap_status': 'Superseded by publisher live range-union accounting.'})
    result['input_pins'] = {**baseline['input_pins'], 'manifest': manifest_pin, 'build_report': build_pin,
                            'actual_image': packet['image_pin']}
    result['semantic_responsibility_unknowns'] = [
        *baseline.get('semantic_responsibility_unknowns', []),
        *[{'module': m['module'], 'source': m['source'], 'public_submodule_id': RESIDUAL_GROUP,
           'responsibility_status': m['responsibility_status'],
           'basis': 'Verified integrated accounting remainder; no semantic subgroup inferred.'}
          for m in rows if m['module'] in additions and m['membership_basis'] == 'unclassified-integrated-module']]
    result['refresh_provenance'] = {'policy': 'registered-whole-exact-image-replacements-v2',
                                    'replacement_modules': sorted(replacements),
                                    'commits': baseline.get('refresh_provenance', {}).get('commits', []) + [sha],
                                    'unresolved_membership_policy': 'Existing shared group is accounting remainder, not semantic classification.'}
    return result


def refresh(ledger, config):
    """Return a validated newer baseline object, or the pinned object unchanged.

    Required config: baseline and baseline_sha256. Optional: repo_root,
    manifest_path (default config/retail-us.json), baseline_membership={path,
    sha256} with explicit_module_mappings records keyed by module and containing
    source/public_submodule_id. Missing subgroup facts use only the existing
    shared accounting remainder, explicitly marked unresolved.
    """
    pin = {'path': config['baseline'], 'sha256': config['baseline_sha256']}
    baseline = json_pin(pin)
    require(baseline.get('schema') == 'baseline-public-group-map-v1', 'unsupported baseline schema')
    require(not baseline.get('unknowns') and not baseline.get('report_manifest_mismatches'), 'unresolved baseline accounting')
    # Bind the fallback to its actual manifest/report as well as the JSON pin.
    json_pin(baseline['input_pins']['manifest'])
    json_pin(baseline['input_pins']['build_report'])
    repo = Path(config.get('repo_root', ROOT))
    manifest_path = config.get('manifest_path', 'config/retail-us.json')
    require(not Path(manifest_path).is_absolute() and '..' not in Path(manifest_path).parts, 'invalid committed manifest path')
    packets = _packets(ledger, repo)
    if not packets:
        return baseline
    base_sha = baseline.get('integrated_commit')
    if base_sha is None:
        matches = [p for p in packets if p['image'].get('build_report_sha256') ==
                   baseline['input_pins']['build_report']['sha256'] and p['image'].get('manifest_sha256') ==
                   baseline['input_pins']['manifest']['sha256']]
        require(len(matches) == 1, 'cannot bind baseline to one registered integration commit')
        base_sha = matches[0]['commit']['sha']
    require(ancestor(repo, base_sha, 'HEAD'), 'baseline commit is not in this checkout history')
    newer = [p for p in packets if p['commit']['sha'] != base_sha and ancestor(repo, base_sha, p['commit']['sha'])]
    if not newer:
        return baseline
    # Registered timestamps can be backfilled; Git ancestry owns ordering.
    ordered = []
    while newer:
        earliest = [p for p in newer if all(p is q or ancestor(repo, p['commit']['sha'], q['commit']['sha']) for q in newer)]
        require(len(earliest) == 1, 'integration commits are not a single ancestry chain')
        ordered.append(earliest[0]); newer.remove(earliest[0])
    assignments = copy.deepcopy(baseline.get('explicit_module_mappings', {}))
    if config.get('baseline_membership'):
        assignments.update(json_pin(config['baseline_membership'])['explicit_module_mappings'])
    result = {**baseline, 'integrated_commit': base_sha}
    for packet in ordered:
        result = _apply(packet, result, repo, manifest_path, assignments, ledger)
    result['refresh_provenance']['previous_baseline'] = pin
    result['ledger_snapshot_event_seq'] = ledger.db.execute('SELECT max(seq) FROM events').fetchone()[0]
    result['totals']['ledger_tasks'] = ledger.db.execute('SELECT count(*) FROM tasks').fetchone()[0]
    return result
