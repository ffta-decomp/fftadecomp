"""Allowlisted public recovery aggregates and unattended data-only publication."""
from __future__ import annotations

import fcntl
import datetime as dt
import hashlib
import json
import os
from pathlib import Path
import re
import subprocess
import tempfile

import recovery_workflow as wf

PUBLIC_FILES = ('data/workflow.json', 'data/progress.json', 'data/submodules.json')
STATES = ('ready', 'active', 'frozen', 'blocked')
LANES = ('main', 'worker2', 'worker3', 'sol_a', 'sol_b', 'sol_c', 'astra_handoff', 'other')
CLASSIFICATIONS = ('mapped', 'provisional', 'unmapped')


def identifier(value):
    if not isinstance(value, str) or not re.fullmatch(r'[a-z][a-z0-9-]{0,79}', value):
        raise ValueError('invalid public classification identifier')
    return value


def validate_mapping(mapping, catalog):
    if mapping['schema_version'] != 1:
        raise ValueError('unsupported classification schema')
    groups = {identifier(x['id']) for x in catalog['groups']}
    modules = {identifier(x['id']):identifier(x['system']) for x in catalog['submodules']}
    if len(modules) != len(catalog['submodules']):
        raise ValueError('duplicate public submodule')
    for rule in mapping['family_rules']:
        if modules.get(rule['public_submodule_id']) != rule['public_system']:
            raise ValueError('mapping no longer agrees with public catalog')
        if not rule['semantic_source_prefix'].startswith('src/') or '..' in Path(rule['semantic_source_prefix']).parts:
            raise ValueError('invalid mapping source prefix')
    if not set(mapping['provisional_systems'].values()) <= groups:
        raise ValueError('unknown provisional system')


def source_contract_attribution(spec):
    """Recognize declared provenance metadata without reading private sources."""
    def pinned(record):
        return (isinstance(record, dict)
                and isinstance(record.get('path'), str) and bool(record['path'].strip())
                and '\x00' not in record['path']
                and isinstance(record.get('sha256'), str)
                and re.fullmatch(r'[0-9a-fA-F]{64}', record['sha256']) is not None)
    evidence = spec.get('evidence_pins')
    return (spec.get('readiness') == 'source-contract-required'
            and pinned(spec.get('original_source'))
            and isinstance(evidence, list) and bool(evidence)
            and all(pinned(record) for record in evidence)
            and isinstance(spec.get('purpose'), str) and bool(spec['purpose'].strip()))


def classify(spec, mapping):
    family = str(spec.get('evidence_family', '')).rstrip('/')
    source = (spec.get('existing_semantic_source') or {}).get('path', '')
    try:
        source = Path(source).relative_to(wf.ROOT).as_posix() if Path(source).is_absolute() else source
    except ValueError:
        source = ''
    matches = [r for r in mapping['family_rules'] if
               (family == r['evidence_family_key'] or family.endswith('/'+r['evidence_family_key']))
               and source.startswith(r['semantic_source_prefix']) and '..' not in Path(source).parts]
    if len(matches) == 1:
        rule = matches[0]
        return rule['public_system'], rule['public_submodule_id'], 'mapped'
    if not matches and family.endswith('/asm-business-map-2026-10-19'):
        system = mapping['provisional_systems'].get(spec.get('system'))
        if system:
            return system, None, 'provisional'
    # A known family with mismatched sources or ambiguous rules stays closed.
    family_rules = [r for r in mapping['family_rules'] if
                    family == r['evidence_family_key'] or family.endswith('/'+r['evidence_family_key'])]
    if (not matches and not family_rules and isinstance(spec.get('system'), str)
            and source_contract_attribution(spec)):
        system = mapping['provisional_systems'].get(spec.get('system'))
        if system:
            return system, None, 'provisional'
    return 'unclassified', None, 'unmapped'


def mixed_completion_eligible(accounting):
    inline = accounting.get('inline_assembly_bytes', 0)
    total = accounting.get('instruction_bytes', accounting.get('instructions_bytes', 0))
    if type(inline) is not int or type(total) is not int or not 0 < inline < total:
        return False
    if inline * 10 < total:
        return True
    exception = accounting.get('assembly_ratio_exception') or {}
    components = {'low_level_engine':'system', 'system_kernel':'system',
                  'graphics':'graphics', 'audio':'audio'}
    return (isinstance(exception, dict) and exception.get('class') in components
            and accounting.get('component') == components[exception['class']]
            and isinstance(exception.get('reason'), str) and bool(exception['reason'].strip()))


def integrated_mixed_completion(baseline):
    """Use only pinned historical manifest accounting, never the live manifest."""
    modules = [x for x in baseline['modules_private'] if x.get('kind') == 'mixed']
    manifest = {}
    pin = baseline.get('input_pins', {}).get('manifest')
    if modules and pin:
        raw = Path(pin['path']).read_bytes()
        if hashlib.sha256(raw).hexdigest() != pin['sha256']:
            raise ValueError('mixed accounting manifest hash changed')
        manifest = {x['name']:x for x in json.loads(raw)['modules']}
    return [x for x in modules if x.get('module_exact') is True
            and mixed_completion_eligible(manifest.get(x.get('module'), x))]


def migration_attribution(records):
    """Summarize a source/range-bound prior-production audit without changing raw gates."""
    if not isinstance(records, dict) or records.get('schema_version') != 1:
        raise ValueError('unsupported migration-attribution proof')
    rows = records.get('rows')
    if not isinstance(rows, list): raise ValueError('migration-attribution rows are required')
    reports = records.get('reports', {})
    report_modules = {}
    if not isinstance(reports, dict): raise ValueError('report pins are required')
    if any(row.get('classification') != 'unknown' for row in rows):
        for side in ('before', 'after'):
            pin = reports.get(side)
            if not isinstance(pin, dict) or not isinstance(pin.get('path'), str) or not re.fullmatch(r'[0-9a-f]{64}', str(pin.get('sha256', ''))):
                raise ValueError('before/after production report pins are required')
            raw = Path(pin['path']).read_bytes()
            if hashlib.sha256(raw).hexdigest() != pin['sha256']:
                raise ValueError(f'{side} production report hash changed')
            doc = json.loads(raw)
            if doc.get('input_sha256') != records.get('retail_sha256'):
                raise ValueError('production report revision differs from attribution retail')
            report_modules[side] = {m['name']:m for m in doc.get('modules', [])}
    totals = {'registration': {'methods': 0, 'original_bytes': 0},
              'new_migration': {'methods': 0, 'original_bytes': 0},
              'unknown': {'methods': 0, 'original_bytes': 0}}
    seen = set()
    for row in rows:
        task = row.get('task_id'); start = row.get('rom_offset'); size = row.get('original_bytes')
        if not isinstance(task, str) or type(start) is not int or start < 0 or type(size) is not int or size <= 0:
            raise ValueError('invalid task/native-range attribution identity')
        identity = (start, size)
        if identity in seen: raise ValueError('duplicate native range in attribution proof')
        seen.add(identity)
        category = row.get('classification')
        if category not in totals: raise ValueError('invalid attribution classification')
        if category != 'unknown':
            required = ('candidate_source_sha256', 'candidate_binary_sha256')
            if any(not isinstance(row.get(key), str) or re.fullmatch(r'[0-9a-f]{64}', row[key]) is None for key in required):
                raise ValueError('attributed record lacks source/binary hash pins')
            build = row.get('candidate_build_pin')
            if not isinstance(build, dict) or not isinstance(build.get('path'), str) or not re.fullmatch(r'[0-9a-f]{64}', str(build.get('sha256', ''))):
                raise ValueError('attributed record lacks candidate build-report pin')
            build_raw = Path(build['path']).read_bytes()
            if hashlib.sha256(build_raw).hexdigest() != build['sha256']:
                raise ValueError('candidate build-report hash changed')
            build_doc = json.loads(build_raw)
            if build_doc.get('retail_sha256') != records.get('retail_sha256'):
                raise ValueError('candidate build uses a different retail revision')
            segment = next((x for x in build_doc.get('segments', []) if x.get('rom_offset') == start), None)
            source = row.get('candidate_source_pin')
            if not segment or (segment.get('reference_size') != size or segment.get('generated_size') != size
                    or segment.get('binary_sha256') != row['candidate_binary_sha256']
                    or segment.get('matching_bytes') != size or segment.get('differing_bytes') != 0
                    or segment.get('overflow_bytes') != 0):
                raise ValueError('candidate build does not prove the complete original envelope')
            if (not isinstance(source, dict) or not isinstance(source.get('path'), str)
                    or source.get('sha256') != row['candidate_source_sha256']
                    or segment.get('source_sha256') != row['candidate_source_sha256']):
                raise ValueError('attributed record lacks candidate source pin')
            if hashlib.sha256(Path(source['path']).read_bytes()).hexdigest() != row['candidate_source_sha256']:
                raise ValueError('candidate source hash changed')
            if row.get('report_before_credit') is not True or row.get('native_range_match') is not True:
                raise ValueError('attributed record lacks prior-time/native-range proof')
            try:
                credit_at = dt.datetime.fromisoformat(row['credit_at']).timestamp()
                before_at = dt.datetime.fromisoformat(row['before_report_at']).timestamp()
                after_at = dt.datetime.fromisoformat(row['after_report_at']).timestamp()
            except (KeyError, TypeError, ValueError) as error:
                raise ValueError('attributed record lacks report/credit chronology') from error
            if not before_at < credit_at <= after_at:
                raise ValueError('production snapshot chronology does not bracket the local credit')
            for side, at in (('before', before_at), ('after', after_at)):
                if abs(Path(reports[side]['path']).stat().st_mtime - at) > 2:
                    raise ValueError(f'{side} report time differs from its pinned filesystem observation')
            if row.get('before_report_sha256') != reports['before']['sha256'] or row.get('after_report_sha256') != reports['after']['sha256']:
                raise ValueError('row report hashes differ from the pinned production reports')
            before, after = row.get('before', {}), row.get('after', {})
            for side, module in (('before', before), ('after', after)):
                found = report_modules[side].get(module.get('module'))
                if (not found or found.get('rom_offset') != start or found.get('size') != module.get('size')
                        or found.get('kind') != module.get('kind') or found.get('sha256') != module.get('sha256')
                        or bool(found.get('exact_binary_match')) != bool(module.get('exact'))):
                    raise ValueError(f'{side} module does not match its pinned report/native range')
            if category == 'registration' and not (before.get('kind') == 'c' and before.get('exact') is True
                                                    and before.get('size') == size):
                raise ValueError('registration is not already whole-exact C in prior production')
            if category == 'new_migration' and not (after.get('kind') == 'c' and after.get('exact') is True
                                                     and after.get('size') == size
                                                     and after.get('sha256') == row['candidate_binary_sha256']
                                                     and segment.get('source_sha256') == row['candidate_source_sha256']
                                                     and (before.get('kind') == 'assembly' or before.get('exact') is False)):
                raise ValueError('new migration lacks exact before/after source transition')
        totals[category]['methods'] += 1
        totals[category]['original_bytes'] += size
    raw = records.get('raw_gates')
    if not isinstance(raw, dict): raise ValueError('raw gate totals are required')
    if sum(x['methods'] for x in totals.values()) != raw.get('local_exact_methods'):
        raise ValueError('attribution rows do not reconcile to raw local-exact methods')
    if sum(x['original_bytes'] for x in totals.values()) != raw.get('local_exact_original_bytes'):
        raise ValueError('attribution rows do not reconcile to raw local-exact bytes')
    window = raw.get('observed_seconds')
    new_bytes = totals['new_migration']['original_bytes']
    raw_bytes = raw['local_exact_original_bytes']
    return {'schema_version': 1, 'raw_gates_preserved': raw, 'attribution': totals,
            'rates': {'window_seconds': window,
                      'raw_local_exact_B_per_hour': raw_bytes * 3600 / window if type(window) in (int, float) and window > 0 else None,
                      'new_migration_original_bytes': new_bytes,
                      'new_migration_B_per_hour': new_bytes * 3600 / window if type(window) in (int, float) and window > 0 else None,
                      'unknown_original_bytes': totals['unknown']['original_bytes']},
            'scope': 'New-migration attribution is separate from raw gates. Only source/hash/native-range-bound transitions from a prior production snapshot count; unknown is retained, not subtracted or promoted.'}


def public_snapshot(ledger, catalog, mapping, baseline=None, migration_audit=None):
    validate_mapping(mapping, catalog)
    ledger.db.execute('BEGIN')
    try:
        stats = ledger.stats()
        tasks = ledger.tasks()
        credits = [dict(x) for x in ledger.db.execute(
            'SELECT task_id,module,gate,actor,at,binary_sha256,original_bytes,generated_bytes,payload FROM credits WHERE revoked=0 AND at<=?',
            (stats['as_of'],))]
        ledger.db.commit()
    except BaseException:
        ledger.db.rollback(); raise
    # Private accounting is consumed locally; never copy payloads to public JSON.
    mixed_identities = set(); eligible_mixed_identities = set()
    for credit in credits:
        accounting = json.loads(credit.pop('payload')).get('accounting', {})
        if accounting.get('inline_assembly_bytes', 0) or accounting.get('kind', accounting.get('source_kind')) == 'mixed':
            identity = (credit['task_id'], credit['binary_sha256'])
            mixed_identities.add(identity)
            if mixed_completion_eligible(accounting): eligible_mixed_identities.add(identity)
    for credit in credits:
        identity = (credit['task_id'], credit['binary_sha256'])
        credit['mixed'] = identity in mixed_identities
        credit['completion_eligible'] = identity not in mixed_identities or identity in eligible_mixed_identities
    delivery = credits + [{**x, 'gate':'integrated_exact'} for x in credits if x['gate']=='integrated' and any(
        y['gate']=='peer_exact' and y['module']==x['module'] and y['binary_sha256']==x['binary_sha256'] for y in credits)]
    classified = {x['id']:classify(x['spec'], mapping) for x in tasks}

    def metric(rows):
        return {'functions':len(rows), 'original_bytes':sum(x['original_bytes'] for x in rows),
                'generated_bytes':sum(x['generated_bytes'] for x in rows)}

    def summary(selected, delivered=None):
        ids = {x['id'] for x in selected}
        rows = [x for x in (delivery if delivered is None else delivered) if x['task_id'] in ids]
        gates = {}
        for gate in wf.DELIVERY_GATES:
            retained = [x for x in rows if x['gate']==gate]
            since_epoch = [x for x in retained if x['at']>=stats['epoch']]
            gates[gate] = {'retained':metric(retained), 'since_epoch':metric(since_epoch),
                          'cumulative_original_B_per_hour':sum(x['original_bytes'] for x in since_epoch)*3600/stats['elapsed_seconds']}
            for name, window in stats['throughput']['windows'].items():
                current = metric([x for x in since_epoch if window['start_inclusive']<=x['at']<window['end_exclusive']])
                current['original_B_per_hour'] = current['original_bytes']*3600/window['observed_seconds'] if window['observed_seconds'] else None
                gates[gate][name] = current
        return {'tasks':len(selected), 'original_backlog_span_bytes':sum(x['original_bytes'] for x in selected),
                'states':{s:sum(x['state']==s for x in selected) for s in STATES},
                'classification':{s:sum(classified[x['id']][2]==s for x in selected) for s in CLASSIFICATIONS}, 'gates':gates}

    groups = [x['id'] for x in catalog['groups']] + ['unclassified']
    submodules = [{'id':x['id'], 'system':x['system'], **summary([t for t in tasks if classified[t['id']][1]==x['id']])}
                  for x in catalog['submodules']]
    unassigned = [{'system':system, **summary([t for t in tasks if classified[t['id']][0]==system and classified[t['id']][1] is None])}
                  for system in groups]
    systems = [{'id':system, **summary([t for t in tasks if classified[t['id']][0]==system])} for system in groups]
    # Only numeric/enum fields cross the boundary. No event, task, spec or evidence dictionaries are copied.
    rounds = {}
    windows = {}
    for name, window in stats['throughput']['windows'].items():
        windows[name] = {key:window[key] for key in ('timezone','basis','start_inclusive','end_exclusive',
            'start_inclusive_local','end_exclusive_local','display','observed_seconds','partial','partial_reason')}
        rounds[name] = {key:window['rounds'][key] for key in ('rounds','completed_decision_intervals','median_seconds','p90_seconds',
                                                           'initial_preparations','first_round_methods','first_round_exact')}
    actors = []
    def implementer(credit):
        if credit['gate'].startswith('local_'):
            return credit['actor'] if credit['actor'] in LANES else 'other'
        candidates = {x['actor'] for x in credits if x['module']==credit['module']
                      and x['binary_sha256']==credit['binary_sha256'] and x['gate'].startswith('local_')}
        actor = next(iter(candidates)) if len(candidates)==1 else 'other'
        return actor if actor in LANES else 'other'
    for actor in LANES:
        credited = [x for x in delivery if implementer(x)==actor]
        # Delivery belongs to the local implementer, independent of current task ownership.
        actors.append({'id':actor, 'active_tasks':sum((t['actor'] if t['actor'] in LANES else 'other')==actor and t['state']=='active' for t in tasks),
                       'delivery':summary(tasks, credited)['gates']})
    current_window = stats['throughput']['current_incomplete_hour']
    current_hour = {key:current_window[key] for key in ('timezone','basis','start_inclusive','observed_until_inclusive',
        'start_inclusive_local','observed_until_inclusive_local','display','observed_seconds','partial','comparison_eligible')}
    data = {'schema_version':1, 'as_of':stats['as_of'], 'epoch':stats['epoch'], 'elapsed_seconds':stats['elapsed_seconds'],
            'integrated_snapshot_revision':catalog['snapshot_revision'],
            'mapping_sha256':hashlib.sha256(wf.encode(mapping).encode()).hexdigest(),
            'windows':windows, 'current_incomplete_hour':current_hour, 'totals':summary(tasks), 'systems':systems, 'submodules':submodules,
            'unassigned_submodules':unassigned, 'actors':actors, 'rounds':rounds,
            'recording_gaps':{key:len(stats['throughput'][key]) for key in
                              ('pending_peer_exact','pending_integration_exact','exact_rounds_without_local_credit')},
            'limitations':['Registered ledger credits only; missing historical receipts are not inferred.',
                'Local, peer and integrated gates are separate and must not be added together.',
                'Exact gate rates include C/mixed results. Completed ASM migration includes whole-exact C and eligible mixed; pure-C and mixed spans remain separate. Ordinary mixed needs less than 10% inline instruction bytes; documented low-level exceptions remain lower priority.',
                'Integrated_exact is a subset of integrated, dated at integration.',
                'Original envelopes include constants and alignment; task spans are not remaining executable bytes.',
                'Live activity does not change the separately dated verified ROM snapshot.',
                'Family mapping is accounting attribution, not new semantic acceptance; provisional system labels remain provisional.',
                'Rates include preparation, failures and handoffs. Partial windows and distinct cohorts are not causal speedup evidence.']}
    if migration_audit is not None:
        # This is a separate attribution account; raw gate aggregates above remain unchanged.
        data['migration_attribution'] = migration_attribution(migration_audit)
    if sum(x['tasks'] for x in submodules+unassigned) != data['totals']['tasks']:
        raise ValueError('classification partition does not reconcile')
    for gate in wf.DELIVERY_GATES:
        for period in ('retained','since_epoch','last_hour','previous_hour'):
            for key in ('functions','original_bytes','generated_bytes'):
                if sum(x['gates'][gate][period][key] for x in submodules+unassigned) != data['totals']['gates'][gate][period][key]:
                    raise ValueError('submodule delivery totals do not reconcile')
    if baseline is not None:
        data['dashboard'] = unified_dashboard(data, tasks, credits, classified, catalog, baseline, stats)
    check_public(data)
    return data


def interval_bytes(ranges):
    end = -1; total = 0
    for start, stop in sorted(ranges):
        if stop < start or start < 0:raise ValueError('invalid accounting range')
        total += max(0, stop-max(start,end));end=max(end,stop)
    return total


def merged_ranges(ranges):
    result = []
    for start, end in sorted(ranges):
        if type(start) is not int or type(end) is not int or start < 0 or end <= start:
            raise ValueError('invalid original ASM range')
        if result and start <= result[-1][1]:
            result[-1][1] = max(end, result[-1][1])
        else:
            result.append([start, end])
    return result


def intersection_bytes(left, right):
    left, right = merged_ranges(left), merged_ranges(right)
    i = j = total = 0
    while i < len(left) and j < len(right):
        a, b = left[i], right[j]
        total += max(0, min(a[1], b[1]) - max(a[0], b[0]))
        if a[1] <= b[1]: i += 1
        else: j += 1
    return total


def asm_match_progress(baseline, available, integrated):
    inventory = baseline.get('original_asm_inventory')
    if inventory is None:
        return {'status':'unknown', 'basis':'original_asm_spans', 'percent':None}
    if inventory['retail_sha256'] != baseline['retail_sha256']:
        raise ValueError('ASM inventory revision differs from baseline')
    ranges = merged_ranges(inventory['ranges'])
    denominator = interval_bytes(ranges)
    if not denominator or denominator != inventory['total_asm_bytes']:
        raise ValueError('ASM denominator does not reconcile')
    matched = intersection_bytes(available, ranges)
    return {'status':'known_catalogue', 'basis':'original_asm_spans',
            'numerator_basis':'deduplicated_original_asm_ranges_rewritten_as_whole_exact_c_or_eligible_mixed',
            'completion_policy':'c-or-eligible-mixed-r72',
            'rewritten_original_asm_bytes':matched, 'known_original_asm_bytes':denominator,
            'integrated_original_asm_bytes':intersection_bytes(integrated,ranges),
            'denominator_id':hashlib.sha256(json.dumps([inventory['retail_sha256'],ranges],separators=(',',':')).encode()).hexdigest(),
            'total_asm_bytes':denominator, 'matched_asm_bytes':matched,
            'integrated_matched_asm_bytes':intersection_bytes(integrated,ranges),
            'exact_bytes_outside_catalogue':interval_bytes(available)-matched,
            'percent':100*matched/denominator,
            'scope':'Known original ASM function/module spans, including internal literals and alignment; excludes resource ranges. Already migrated code remains in the denominator. Unclassified code is not yet in this catalogue.'}


def daily_progress(tasks, credits, baseline, stats, current):
    """Reconstruct dated ledger coverage, without backdating today's ROM baseline."""
    zone = dt.timezone(dt.timedelta(hours=8))
    cutoff = dt.datetime.fromisoformat(stats['as_of'])
    index = {task['id']: task for task in tasks}
    inventory = baseline.get('original_asm_inventory', {})
    catalogue = inventory.get('ranges', [])
    denominator = current.get('known_original_asm_bytes')
    events = []
    unlocated = 0
    for credit in credits:
        if credit['gate'] not in ('local_exact', 'integrated') or not credit['completion_eligible']:
            continue
        if credit['gate'] == 'integrated' and not any(
                other['gate'] == 'peer_exact' and other['module'] == credit['module']
                and other['binary_sha256'] == credit['binary_sha256'] for other in credits):
            continue
        start = index[credit['task_id']]['spec'].get('rom_offset')
        if type(start) is not int or start < 0:
            unlocated += 1
            continue
        at = dt.datetime.fromisoformat(credit['at'])
        if at <= cutoff:
            events.append((at, credit, (start, start + credit['original_bytes'])))
    today = cutoff.astimezone(zone).date()
    first = min([today, dt.datetime.fromisoformat(stats['epoch']).astimezone(zone).date(),
                 *[at.astimezone(zone).date() for at, _, _ in events]])
    by_day = {}
    for at, credit, span in sorted(events, key=lambda event: event[0]):
        by_day.setdefault(at.astimezone(zone).date(), []).append((credit, span))
    pools = {'local_exact': [], 'integrated': []}
    rows = []
    day = first
    while day <= today:
        row = {'date': day.isoformat(), 'partial': day == today,
               'new_exact_methods': 0, 'new_exact_asm_bytes': 0,
               'new_pure_c_asm_bytes': 0, 'new_eligible_mixed_asm_bytes': 0,
               'new_integrated_asm_bytes': 0}
        for credit, span in by_day.get(day, []):
            pool = pools[credit['gate']]
            before = intersection_bytes(pool, catalogue)
            pool.append(span)
            added = intersection_bytes(pool, catalogue) - before
            if credit['gate'] == 'local_exact':
                row['new_exact_methods'] += int(added > 0)
                row['new_exact_asm_bytes'] += added
                row['new_eligible_mixed_asm_bytes' if credit['mixed'] else 'new_pure_c_asm_bytes'] += added
            else:
                row['new_integrated_asm_bytes'] += added
        row['cumulative_registered_exact_asm_bytes'] = intersection_bytes(pools['local_exact'], catalogue)
        row['cumulative_registered_integrated_asm_bytes'] = intersection_bytes(pools['integrated'], catalogue)
        row['registered_percent'] = (100 * row['cumulative_registered_exact_asm_bytes'] / denominator
                                     if denominator else None)
        rows.append(row)
        day += dt.timedelta(days=1)
    registered = intersection_bytes(pools['local_exact'], catalogue)
    return {'schema_version': 1, 'timezone': 'Asia/Shanghai', 'as_of': stats['as_of'],
            'denominator_id': current.get('denominator_id'), 'known_original_asm_bytes': denominator,
            'current_exact_asm_bytes_without_local_date': (
                current['rewritten_original_asm_bytes'] - registered if denominator else None),
            'unlocated_records': unlocated, 'days': rows,
            'scope': 'Calendar days in Asia/Shanghai, using original credit occurrence times and currently unrevoked receipts. Range unions deduplicate overlaps within each gate. Cumulative curves cover dated ledger receipts only; the current ROM baseline is never backdated. Missing historical receipts are unknown, not zero recovery. Integration is a separate gate and must not be added to local exact. Current day is partial; no projection. Eligible mixed and pure C remain separate.'}


def unified_dashboard(snapshot, tasks, credits, classified, catalog, baseline, stats):
    """One row model drives the overview, system totals and submodule display."""
    if baseline.get('unknowns') or baseline.get('report_manifest_mismatches'):
        raise ValueError('integrated baseline has unresolved accounting')
    groups = {x['public_submodule_id']:x for x in baseline['groups']}
    if set(groups) != {x['id'] for x in catalog['submodules']}:
        raise ValueError('baseline and public submodule identities differ')
    exact = [(x['rom_offset'],x['end_exclusive']) for x in baseline['modules_private'] if x['pure_c_exact_span_eligible']]
    if interval_bytes(exact) != baseline['totals']['exact_c_module_span_bytes']:
        raise ValueError('integrated exact spans do not reconcile')
    rows = {}
    for item in snapshot['submodules']:
        original = next(x for x in catalog['submodules'] if x['id']==item['id'])
        accounting = groups[item['id']]['actual']
        title = original['title']
        if item['id'] == 'earlier-and-shared-routines' and baseline.get('semantic_responsibility_unknowns'):
            title = 'Earlier, shared and unclassified routines'
        rows[item['id']] = {'id':item['id'], 'system':item['system'], 'title':title,
            'integrated_c_bytes':accounting['pure_c_bytes'], 'integrated_exact_bytes':accounting['exact_c_bytes'],
            'mixed_bytes':accounting['mixed_bytes'], 'pending_exact_bytes':0, 'pending_peer_exact_bytes':0,
            'pending_mixed_exact_bytes':0, 'pending_peer_mixed_exact_bytes':0,
            'tasks':item['tasks'], 'states':item['states'],
                'last_completed_hour_exact_B_per_hour':item['gates']['local_exact']['last_hour']['original_B_per_hour']}
    for item in snapshot['unassigned_submodules']:
        if not item['tasks']:continue
        key='unassigned-'+item['system']
        rows[key]={'id':key,'system':item['system'],'title':'Unassigned submodule',
            'integrated_c_bytes':0,'integrated_exact_bytes':0,'mixed_bytes':0,'pending_exact_bytes':0,'pending_peer_exact_bytes':0,
            'pending_mixed_exact_bytes':0,'pending_peer_mixed_exact_bytes':0,
            'tasks':item['tasks'],'states':item['states'],
            'last_completed_hour_exact_B_per_hour':item['gates']['local_exact']['last_hour']['original_B_per_hour']}
    # Deduplicate original ranges across the validated image and every live local credit.
    task_index={t['id']:t for t in tasks};occupied=list(exact);unlocated=0
    peer_ranges=list(exact)
    integrated_mixed = [(x['rom_offset'], x['end_exclusive']) for x in baseline['modules_private']
                        if x.get('kind') == 'mixed']
    mixed_ranges=list(integrated_mixed);peer_mixed_ranges=list(integrated_mixed)
    for credit in sorted(credits,key=lambda x:(x['at'],x['module'])):
        if credit['gate'] not in ('local_exact','peer_exact'):continue
        task=task_index[credit['task_id']];start=task['spec'].get('rom_offset')
        if type(start) is not int or start<0:
            unlocated+=1;continue
        interval=(start,start+credit['original_bytes'])
        system,module,_=classified[task['id']];key=module or 'unassigned-'+system
        if credit['mixed']:
            pool=mixed_ranges if credit['gate']=='local_exact' else peer_mixed_ranges
            field='pending_mixed_exact_bytes' if credit['gate']=='local_exact' else 'pending_peer_mixed_exact_bytes'
        else:
            pool=occupied if credit['gate']=='local_exact' else peer_ranges
            field='pending_exact_bytes' if credit['gate']=='local_exact' else 'pending_peer_exact_bytes'
        new=interval_bytes(pool+[interval])-interval_bytes(pool);pool.append(interval)
        rows[key][field]+=new
    for row in rows.values():row['exact_available_bytes']=row['integrated_exact_bytes']+row['pending_exact_bytes']
    sum_fields=('integrated_c_bytes','integrated_exact_bytes','mixed_bytes','pending_exact_bytes',
                'pending_peer_exact_bytes','pending_mixed_exact_bytes','pending_peer_mixed_exact_bytes',
                'exact_available_bytes','tasks')
    def aggregate(selected):
        return {**{key:sum(x[key] for x in selected) for key in sum_fields},
                'states':{state:sum(x['states'][state] for x in selected) for state in STATES}}
    systems=[]
    for group in catalog['groups']+[{'id':'unclassified','title':'Unclassified'}]:
        selected=[x for x in rows.values() if x['system']==group['id']]
        if selected:systems.append({'id':group['id'],'title':group['title'],**aggregate(selected),'modules':selected})
    overview=aggregate(list(rows.values()))
    if overview['integrated_c_bytes']!=baseline['totals']['pure_c_bytes'] or overview['integrated_exact_bytes']!=interval_bytes(exact):
        raise ValueError('dashboard integrated totals do not reconcile')
    if overview['exact_available_bytes']!=interval_bytes(occupied):raise ValueError('dashboard exact union does not reconcile')
    performance=[]
    for actor in ['team',*LANES]:
        if actor=='other' and not any(x['id']=='other' and x['active_tasks'] for x in snapshot['actors']):continue
        lane=next((x for x in snapshot['actors'] if x['id']==actor),None)
        gates=lane['delivery'] if lane else snapshot['totals']['gates']
        current=stats['throughput']['windows']['last_hour']
        rounds=current['actors'].get(actor,{}).get('rounds',{}) if lane else current['rounds']
        performance.append({'id':actor,'active_tasks':lane['active_tasks'] if lane else overview['states']['active'],
            'exact_methods_last_completed_hour':gates['local_exact']['last_hour']['functions'],
            'exact_B_per_completed_hour':gates['local_exact']['last_hour']['original_B_per_hour'],
            'previous_completed_hour_exact_B_per_hour':gates['local_exact']['previous_hour']['original_B_per_hour'],
            'peer_exact_B_per_completed_hour':gates['peer_exact']['last_hour']['original_B_per_hour'],
            'integrated_exact_B_per_completed_hour':gates['integrated_exact']['last_hour']['original_B_per_hour'],
            'median_seconds':rounds.get('median_seconds'),'p90_seconds':rounds.get('p90_seconds')})
    eligible_integrated = integrated_mixed_completion(baseline)
    eligible_integrated_ranges = [(x['rom_offset'], x['end_exclusive']) for x in eligible_integrated]
    integrated_completed = exact + eligible_integrated_ranges
    completed = list(integrated_completed)
    for credit in credits:
        if credit['gate'] != 'local_exact' or not credit['completion_eligible']: continue
        start = task_index[credit['task_id']]['spec'].get('rom_offset')
        if type(start) is int and start >= 0:
            completed.append((start, start + credit['original_bytes']))
    # Keep the module/system headline linked to the same eligible union as the
    # overall ratio, while preserving explicit pure-C and mixed components.
    for row in rows.values():
        row['pure_c_exact_available_bytes'] = row['exact_available_bytes']
        row['integrated_eligible_mixed_exact_bytes'] = 0
    attributed = list(occupied)
    for module in eligible_integrated:
        span = (module['rom_offset'], module['end_exclusive'])
        new = interval_bytes(attributed + [span]) - interval_bytes(attributed)
        attributed.append(span)
        row = rows[module['public_submodule_id']]
        row['exact_available_bytes'] += new
        row['integrated_eligible_mixed_exact_bytes'] += span[1] - span[0]
    for credit in credits:
        if credit['gate'] != 'local_exact' or not credit['mixed'] or not credit['completion_eligible']: continue
        start = task_index[credit['task_id']]['spec'].get('rom_offset')
        if type(start) is not int or start < 0: continue
        span = (start, start + credit['original_bytes'])
        new = interval_bytes(attributed + [span]) - interval_bytes(attributed)
        attributed.append(span)
        system, module, _ = classified[credit['task_id']]
        rows[module or 'unassigned-' + system]['exact_available_bytes'] += new
    for system in systems:
        for key in ('exact_available_bytes', 'pure_c_exact_available_bytes', 'integrated_eligible_mixed_exact_bytes'):
            system[key] = sum(row[key] for row in system['modules'])
    for key in ('exact_available_bytes', 'pure_c_exact_available_bytes', 'integrated_eligible_mixed_exact_bytes'):
        overview[key] = sum(row[key] for row in rows.values())
    overview['completed_exact_original_bytes'] = interval_bytes(completed)
    if overview['exact_available_bytes'] != overview['completed_exact_original_bytes']:
        raise ValueError('eligible mixed completion attribution does not reconcile')
    asm_rewrite = asm_match_progress(baseline,completed,integrated_completed)
    asm_rewrite['pure_c_original_asm_bytes'] = intersection_bytes(occupied, baseline.get('original_asm_inventory', {}).get('ranges', []))
    asm_rewrite['eligible_mixed_added_original_asm_bytes'] = asm_rewrite.get('rewritten_original_asm_bytes', 0) - asm_rewrite['pure_c_original_asm_bytes']
    return {'schema_version':2,'as_of':snapshot['as_of'],'integrated_rom_sha256':baseline['baseline_rom_sha256'],
            'overview':overview,'performance':performance,'systems':systems,
            'asm_rewrite':asm_rewrite, 'c_match':asm_rewrite,
            'daily':daily_progress(tasks, credits, baseline, stats, asm_rewrite),
            'classification':snapshot['totals']['classification'],'unlocated_exact_records':unlocated,
            'windows':snapshot['windows'],'recording_gaps':snapshot['recording_gaps']}


def check_public(data):
    text = json.dumps(data, ensure_ascii=False, allow_nan=False)
    if re.search(r'/(?:Users|home)/|Application[ ]Support|plugin://|(?:token|password|api_key)\s*[=:]|[A-Za-z]:\\', text, re.I):
        raise ValueError('private material found in public aggregate')


def without_staffing(data):
    """Public progress exposes aggregate output, never staffing identities/counts."""
    if isinstance(data, list):
        return [without_staffing(x) for x in data]
    if not isinstance(data, dict):
        return data
    result = {}
    for key, value in data.items():
        if key in {'actors', 'actor', 'workers', 'worker_count', 'active_workers',
                   'lane_count', 'lanes', 'session_count'}:
            continue
        if key == 'performance' and isinstance(value, list):
            value = [x for x in value if x.get('id') == 'team']
        result[key] = without_staffing(value)
    return result


def public_files(ledger, public_dir, mapping, baseline=None, migration_audit=None):
    root = Path(public_dir)
    progress = wf.load_json(root/'data/progress.json')
    catalog = wf.load_json(root/'data/submodules.json')
    if 'dashboard' in progress and baseline is None:
        raise ValueError('unified dashboard requires its pinned integrated baseline')
    snapshot = public_snapshot(ledger, catalog, mapping, baseline, migration_audit)
    if baseline is not None:
        progress['dashboard']=snapshot['dashboard']
        progress['asm_rewrite']=snapshot['dashboard']['asm_rewrite']
        progress['c_match']=snapshot['dashboard']['c_match']
        for item in catalog['submodules']:
            current=next(row for system in snapshot['dashboard']['systems'] for row in system['modules'] if row['id']==item['id'])
            item['current']=current
    progress['live_recovery'] = {'as_of':snapshot['as_of'], 'data':'data/workflow.json',
                                'totals':snapshot['totals'], 'recording_gaps':snapshot['recording_gaps']}
    if migration_audit is not None:
        progress['live_recovery']['migration_attribution'] = snapshot['migration_attribution']
    progress['active_work'] = [{'title':'Core recovery',
        'scope':f"{snapshot['totals']['states']['active']} active tasks; {snapshot['totals']['states']['ready']} ready tasks.",
        'status':'Automatic activity data separates local exact, peer acceptance and integration. Pending work is excluded from verified ROM totals.'}]
    catalog['activity_as_of'] = snapshot['as_of']
    catalog['activity_data'] = 'data/workflow.json'
    for item, activity in zip(catalog['submodules'], snapshot['submodules']):
        item['activity'] = {key:activity[key] for key in ('tasks','states','classification','gates')}
    result = {name:without_staffing(data) for name,data in zip(PUBLIC_FILES, (snapshot, progress, catalog))}
    for data in result.values():check_public(data)
    return {name:json.dumps(data,indent=2,ensure_ascii=False,allow_nan=False)+'\n' for name,data in result.items()}


def run(argv, cwd=None):
    return subprocess.run(argv, cwd=cwd, check=True, capture_output=True, text=True,
                          timeout=90, env={**os.environ, 'GIT_TERMINAL_PROMPT':'0'}).stdout.strip()


def match_commit_message(previous, current):
    """Match recovered C's original ASM coverage against the original ASM catalogue."""
    def metrics(document):
        match = document.get('asm_rewrite', document.get('c_match', {}))
        if match.get('basis') != 'original_asm_spans':return None,None,None,None
        return (match.get('rewritten_original_asm_bytes', match.get('matched_asm_bytes')),
                match.get('integrated_original_asm_bytes', match.get('integrated_matched_asm_bytes')),
                match.get('known_original_asm_bytes', match.get('total_asm_bytes')), match.get('denominator_id'))
    exact, integrated, denominator, identity = metrics(current)
    old_exact, _, old_denominator, old_identity = metrics(previous)
    valid = lambda value: type(value) is int and value >= 0
    if not valid(exact) or not valid(denominator) or denominator == 0 or exact > denominator:
        return 'Update recovery activity: ASM rewrite ratio unknown\n\nA valid rewritten original-ASM count and total original-ASM denominator are required; generated C size and ROM size are not substitutes.'
    percent = 100 * exact / denominator
    policy = lambda doc: doc.get('asm_rewrite', doc.get('c_match', {})).get('completion_policy')
    delta = exact - old_exact if valid(old_exact) and identity and old_identity == identity and old_denominator == denominator and policy(previous) == policy(current) else None
    change = f'{delta:+,} B' if delta is not None else 'delta unavailable'
    lines = [f'ASM rewrite: {percent:.4f}% of known ASM ({change})', '',
             f'Matched original ASM: {exact:,}/{denominator:,} catalogued ASM bytes ({percent:.6f}%).',
             'The numerator counts original ASM ranges rewritten as byte-identical C or eligible mixed code, deduplicated across the verified baseline and local whole-exact spans. Pure-C/mixed components remain separate; generated C byte counts never supply this ratio.']
    if delta is not None:
        lines.append(f'Change since previous publication: {delta:+,} B ({100 * delta / denominator:+.6f} percentage points).')
    if valid(integrated) and integrated <= exact:
        lines.append(f'Verified image baseline: {integrated:,} matched ASM bytes ({100 * integrated / denominator:.6f}% of ASM); remaining matched spans are local.')
    lines.append('The denominator retains already migrated original code and excludes resource ranges. Both counts include in-function literals/alignment. Unclassified code remains outside the known ASM catalogue; this is not gameplay completion.')
    return '\n'.join(lines)


def publish_checkout(ledger, checkout, mapping, baseline=None):
    """Mutate only a fresh checkout; remote is selected and checked by publish()."""
    previous = wf.load_json(Path(checkout)/'data/progress.json')
    files = public_files(ledger, checkout, mapping, baseline)
    message = match_commit_message(previous, json.loads(files['data/progress.json']))
    for name, content in files.items():wf.atomic_write(Path(checkout)/name, content)
    run(['git','diff','--check'], checkout)
    run(['git','add','--',*PUBLIC_FILES], checkout)
    changed = run(['git','diff','--cached','--name-only'], checkout).splitlines()
    if not changed:return {'status':'unchanged'}
    if not set(changed) <= set(PUBLIC_FILES):raise ValueError('publication contains non-data files')
    run(['git','-c','user.name=FFTA Recovery Publisher','-c','user.email=ffta-recovery@users.noreply.github.com','-c','commit.gpgsign=false','commit','-m',message], checkout)
    sha = run(['git','rev-parse','HEAD'], checkout)
    run(['git','push','origin','HEAD:refs/heads/main'], checkout)
    remote = run(['git','ls-remote','origin','refs/heads/main'], checkout).split()[0]
    if remote != sha:raise ValueError('published ref changed before readback')
    snapshot = json.loads(files['data/workflow.json'])
    return {'status':'published','commit':sha,'commit_message':message,'as_of':snapshot['as_of'],
            'classification':snapshot['totals']['classification'],
            'files':{name:hashlib.sha256(content.encode()).hexdigest() for name,content in files.items()}}


def publish(ledger, config):
    repository = config['repository']
    if not re.fullmatch(r'[A-Za-z0-9_.-]+/[A-Za-z0-9_.-]+',repository):raise ValueError('invalid repository')
    # Confirm the destination remains public; do not push the implementation repository.
    metadata = json.loads(run(['gh','api','repos/'+repository]))
    if metadata['private'] or metadata['full_name'].lower()!=repository.lower() or metadata['default_branch']!='main':
        raise ValueError('destination must be the configured public main repository')
    work = Path(config['work_dir']);work.mkdir(parents=True,exist_ok=True)
    with (work/'publish.lock').open('a') as lock:
        try:fcntl.flock(lock,fcntl.LOCK_EX|fcntl.LOCK_NB)
        except BlockingIOError:return {'status':'busy'}
        with tempfile.TemporaryDirectory(prefix='publication-',dir=work) as checkout:
            run(['git','clone','--depth','1','--single-branch','--branch','main','https://github.com/'+repository+'.git',checkout])
            baseline=None
            if config.get('refresh_integrated_baseline'):
                from recovery_public_baseline import refresh
                baseline = refresh(ledger, config)
                wf.atomic_write(work/'latest-integrated-baseline.json', json.dumps(baseline, indent=2)+'\n')
            elif config.get('baseline'):
                raw=Path(config['baseline']).read_bytes()
                if hashlib.sha256(raw).hexdigest()!=config['baseline_sha256']:raise ValueError('integrated baseline hash changed')
                baseline=json.loads(raw)
            if config.get('asm_inventory'):
                raw=Path(config['asm_inventory']).read_bytes()
                if hashlib.sha256(raw).hexdigest()!=config['asm_inventory_sha256']:
                    raise ValueError('original ASM inventory hash changed')
                if baseline is None:raise ValueError('ASM accounting requires an integrated baseline')
                baseline={**baseline,'original_asm_inventory':json.loads(raw)}
            result = publish_checkout(ledger,checkout,wf.load_json(config['mapping']),baseline)
        wf.atomic_write(work/'latest-publication.json',json.dumps(result,indent=2)+'\n')
        return result
