#!/usr/bin/env python3
"""Atomic group intake using the existing workflow ledger and lease protocol.

Pools contain pinned source leads, never readiness or a fresh matching budget.
Only --save contains bearer tokens; stdout is a recursively redacted summary.
"""
import argparse
from collections import Counter
import hashlib
import json
import os
from pathlib import Path
import sys
import uuid

import recovery_workflow as wf


def pinned(pin):
    if not isinstance(pin, dict):
        raise ValueError('missing pin')
    path = Path(pin['path']).resolve(strict=True)
    raw = path.read_bytes()
    if hashlib.sha256(raw).hexdigest() != pin['sha256']:
        raise ValueError('stale pin: ' + str(path))
    return raw


def group_of(spec):
    value = spec.get('group') or spec.get('work_group')
    if value is None and isinstance(spec.get('spec'), dict):
        return group_of(spec['spec'])
    return value


def redacted(value):
    if isinstance(value, dict):
        return {k: redacted(v) for k, v in value.items() if k not in ('token', 'payload')}
    if isinstance(value, list):
        return [redacted(v) for v in value]
    return value


class GroupLedger(wf.Ledger):
    def apply(self, op, actor, data, at):
        if op == 'group-disposition':
            return self.dispose(actor, data, at)
        if op != 'group-pull':
            return super().apply(op, actor, data, at)
        group = data['group']
        if not isinstance(group, str) or not group.strip():
            raise ValueError('group is required')
        # Resume identity before loading potentially stale new-discovery input.
        active = self.db.execute("SELECT id FROM tasks WHERE actor=? AND state='active'", (actor,)).fetchone()
        if active:
            task = self.task(active['id']); task['spec'] = json.loads(task['spec'])
            if group_of(task['spec']) != group:
                return {'phase': 'blocked', 'reasons': {'own_active_other_group': 1}, 'owner_task': task['id']}
            return {'phase': 'implementation', 'task': task, 'resumed': True, 'credit': 0}
        own = self.db.execute("SELECT * FROM work_leases WHERE actor=? AND kind='source' AND state='active'", (actor,)).fetchone()
        if own:
            row = dict(own)
            payload = json.loads(row.pop('payload'))
            if payload.get('group') != group:
                return {'phase': 'blocked', 'reasons': {'own_source_other_or_unknown_group': 1}, 'lease_id': row['id']}
            return {'phase': 'qualification', 'lease': row, 'candidate': payload.get('candidate'),
                    'pool': payload.get('pool'), 'manifest': payload.get('manifest'),
                    'acquired_at': row['acquired_at'], 'resumed': True, 'credit': 0}
        pool = json.loads(pinned(data['pool']))
        if pool.get('schema') != 'recovery-group-pool-v1':
            raise ValueError('unsupported group pool schema')
        manifest = json.loads(pinned(pool['manifest']))
        live_path = Path(data.get('live_manifest') or wf.ROOT / 'config/retail-us.json')
        live = json.loads(live_path.read_text())
        modules = live['modules']
        snapshot_modules = manifest['modules']
        reasons = Counter()
        policy = wf.NativeScopeExclusions.load(self.path)
        historical = [dict(r) for r in self.db.execute('SELECT * FROM tasks')]

        dispositions = [json.loads(r['payload']) for r in self.db.execute(
            "SELECT payload FROM events WHERE kind='group_disposition'")]

        def reject(candidate, task_id=None, qualification=False, ready_spec=False):
            start, size = candidate.get('rom_offset'), candidate.get('original_span_bytes')
            if type(start) is not int or start < 0 or type(size) is not int or size <= 0:
                return 'invalid_range'
            if candidate.get('group') != group:
                if not (qualification and candidate.get('qualification_group') == group
                        and candidate.get('eligibility') == 'qualification_only'):
                    return 'other_group'
            if ready_spec and (candidate.get('basis') != 'qualified_native_task'
                               or candidate.get('task_id') != task_id):
                return 'invalid_ready_basis'
            try:
                pinned(candidate['source'])
                if not ready_spec:
                    edge = candidate['edge']; pinned(edge)
                    if (type(edge.get('caller')) is not int or type(edge.get('site')) is not int
                            or edge.get('target') != start):
                        return 'invalid_edge'
                if candidate.get('disposition'):
                    disposition = json.loads(pinned(candidate['disposition']))
                    if disposition.get('state') != 'eligible':
                        return 'disposition_closed_or_unknown'
            except (ValueError, KeyError, OSError, TypeError):
                return 'stale_or_invalid_source_evidence'
            for decision in dispositions:
                if decision.get('group') != group:
                    continue
                if self.scope_overlaps(start, size, candidate['module'], decision['rom_offset'],
                                       decision['original_span_bytes'], decision['module']):
                    if (start != decision['rom_offset'] or size != decision['original_span_bytes']):
                        return 'qualification_history_boundary_changed'
                    if candidate['source']['sha256'] == decision['source']['sha256']:
                        return 'qualification_already_disposed'
            if candidate.get('eligibility') == 'excluded':
                return 'pool_excluded'
            def containing(entries):
                found = []
                for module in entries:
                    functions = module.get('functions')
                    # A module without function records must explicitly declare a single entry.
                    ranges = functions if functions is not None else ([module] if candidate.get('boundary_kind') == 'whole_function' else [])
                    for function in ranges:
                        if function.get('offset') == start and function.get('size') == size:
                            found.append(module)
                return found
            if not ready_spec and len(containing(snapshot_modules)) != 1:
                return 'snapshot_function_range_unknown'
            selected = containing(modules)
            if len(selected) != 1:
                return 'live_function_range_unknown'
            selected = selected[0]
            for module in modules:
                if module.get('kind') != 'c' or module.get('match_policy', 'exact') != 'exact':
                    continue
                for function in module.get('functions', [module]):
                    offset, length = function.get('offset'), function.get('size')
                    if type(offset) is int and type(length) is int and start < offset + length and offset < start + size:
                        return 'already_exact_c'
            if selected.get('kind') == 'c' and selected.get('match_policy', 'exact') == 'exact':
                return 'already_exact_c'
            if policy and policy.overlaps(candidate):
                return 'sdk_excluded'
            for old in historical:
                if old['id'] == task_id:
                    continue
                spec = json.loads(old['spec'])
                if self.scope_overlaps(start, size, candidate['module'], spec.get('rom_offset'), old['original_bytes'], old['module']):
                    return 'native_history_overlap'
            if self.lease_conflict(start, size, candidate['module']) or self.native_conflict(start, size, candidate['module']):
                return 'busy'
            return None

        candidates = sorted(pool['candidates'], key=lambda x: (x.get('priority', 0), x.get('module', '')))
        for task in sorted(historical, key=lambda t: (t['priority'], t['id'])):
            spec = json.loads(task['spec'])
            if task['state'] != 'ready' or group_of(spec) != group:
                continue
            if task['reservation'] not in (None, actor):
                reasons['reserved'] += 1; continue
            leads = [c for c in candidates if c.get('rom_offset') == spec.get('rom_offset')
                     and c.get('original_span_bytes') == task['original_bytes']]
            if leads:
                candidate = dict(leads[0], group=group)
            else:
                candidate = {'group': group, 'module': task['module'],
                    'basis': 'qualified_native_task', 'task_id': task['id'],
                    'rom_offset': spec.get('rom_offset'), 'original_span_bytes': task['original_bytes'],
                    'source': spec.get('original_source'), 'boundary_kind': 'whole_function'}
            reason = reject(candidate, task['id'], ready_spec=not leads)
            if reason:
                reasons[reason] += 1; continue
            leased = super().apply('lease-claim', actor, {'kind': 'source', 'rom_offset': candidate['rom_offset'],
                'size': candidate['original_span_bytes'], 'module': candidate['module'], 'group': group,
                'summary': 'atomic group ready intake'}, at)
            if not leased.get('lease'):
                reasons['busy'] += 1; continue
            lease = leased['lease']
            claimed = super().apply('claim', actor, {'task': task['id'], 'work_lease': {'id': lease['id'], 'token': lease['token']}}, at)
            if not claimed.get('task'):
                raise ValueError('atomic ready promotion failed')
            return dict(claimed, phase='implementation', credit=0, reasons=dict(reasons))
        for candidate in candidates:
            reason = reject(candidate, qualification=True)
            if reason:
                reasons[reason] += 1; continue
            leased = super().apply('lease-claim', actor, {'kind': 'source', 'rom_offset': candidate['rom_offset'],
                'size': candidate['original_span_bytes'], 'module': candidate['module'], 'group': group,
                'summary': 'atomic group qualification intake', 'candidate': candidate,
                'pool': data['pool'], 'manifest': pool['manifest']}, at)
            if leased.get('lease'):
                return dict(leased, phase='qualification', candidate=candidate, pool=data['pool'],
                            manifest=pool['manifest'], acquired_at=leased['lease']['acquired_at'],
                            credit=0, reasons=dict(reasons))
            reasons['busy'] += 1
        if not candidates:
            reasons['empty_pool'] += 1
        return {'phase': 'blocked', 'reasons': dict(reasons), 'credit': 0, 'candidate_count': len(candidates),
                'scope': 'provided_pool_and_current_group_ready_tasks_only'}


    def dispose(self, actor, data, at):
        classification = data.get('disposition')
        if classification not in ('interface_only', 'out_of_scope', 'blocked'):
            raise ValueError('invalid qualification disposition')
        if not data.get('summary', '').strip():
            raise ValueError('disposition summary is required')
        lease = self.work_lease(actor, data)
        if not lease:
            raise ValueError('source lease is required')
        raw = self.db.execute('SELECT payload FROM work_leases WHERE id=?', (lease['id'],)).fetchone()
        payload = json.loads(raw['payload'])
        candidate = payload.get('candidate')
        if payload.get('group') != data.get('group') or not candidate:
            raise ValueError('lease has no matching group qualification identity')
        pins = data.get('evidence')
        if not isinstance(pins, list) or not pins:
            raise ValueError('pinned disposition evidence is required')
        for pin in pins:
            pinned(pin)
        pinned(candidate['source'])
        decision = {'group': data['group'], 'rom_offset': lease['rom_offset'],
                    'original_span_bytes': lease['size'], 'module': lease['module'],
                    'source': candidate['source'], 'classification': classification,
                    'evidence': pins, 'summary': data['summary'], 'lease_id': lease['id'],
                    'qualification_started_at': lease['acquired_at'], 'credit': 0}
        seq = self.event(actor, None, 'group_disposition', decision, at)
        super().apply('lease-release', actor, {'lease_id': lease['id'], 'token': lease['token'],
                                             'summary': data['summary']}, at)
        return {'phase': 'blocked', 'disposition': decision, 'event_seq': seq,
                'lease_released': True, 'credit': 0}


def refresh_pool(refresh, live_manifest, db, group, publish_pool=None):
    """Replenish outside the ledger transaction; each revision owns its snapshot."""
    from build_recovery_group_pool import build_pool
    revision = Path(refresh['output_root']) / 'revisions' / uuid.uuid4().hex
    revision.mkdir(parents=True, exist_ok=False)
    raw = Path(live_manifest).read_bytes()
    snapshot = revision / ('manifest-' + hashlib.sha256(raw).hexdigest() + '.json')
    snapshot.write_bytes(raw)
    pool = build_pool(wf.ROOT, refresh['catalog'], snapshot, db,
                      refresh.get('exclusions'), refresh.get('dispositions'),
                      refresh.get('seed_group', group), group)
    output = revision / 'pool.json'
    output.write_text(json.dumps(pool, indent=2) + '\n')
    if publish_pool:
        link = Path(publish_pool)
        if link.exists() and not link.is_symlink():
            raise ValueError('configured pool refresh target must be a symlink, not an immutable file')
        link.parent.mkdir(parents=True, exist_ok=True)
        temporary = link.parent / ('.' + link.name + '.' + uuid.uuid4().hex)
        try:
            temporary.symlink_to(output.resolve())
            os.replace(temporary, link)
        finally:
            if temporary.is_symlink():
                temporary.unlink()
    return output


def pull_once_with_refresh(ledger, actor, group, pool, live_manifest, refresh=None, publish_pool=None):
    def pull(path):
        # evidence() resolves symlinks, preserving the immutable revision in receipts.
        return ledger.mutate('group-pull', actor, {'group': group,
            'pool': wf.evidence([path])[0], 'live_manifest': str(live_manifest)})
    result = pull(pool)
    if (refresh and result.get('phase') == 'blocked'
            and result.get('scope') == 'provided_pool_and_current_group_ready_tasks_only'
            and not any(result.get('reasons', {}).get(reason) for reason in ('busy', 'reserved'))):
        assert not ledger.db.in_transaction
        rebuilt = refresh_pool(refresh, live_manifest, ledger.path, group, publish_pool)
        result = pull(rebuilt)
        result['refresh'] = {'attempts': 1, 'pool': wf.evidence([rebuilt])[0]}
    return result


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--db')
    parser.add_argument('--manifest', help='live manifest; defaults to config/retail-us.json')
    for name in ('actor', 'group', 'save'):
        parser.add_argument('--' + name, required=True)
    parser.add_argument('--pool')
    parser.add_argument('--disposition', choices=('interface_only', 'out_of_scope', 'blocked'))
    parser.add_argument('--lease')
    parser.add_argument('--evidence', action='append')
    parser.add_argument('--summary')
    args = parser.parse_args()
    config = wf.ROOT / '.local/recovery-workflow.json'
    settings = json.loads(config.read_text()) if config.is_file() else {}
    group_settings = settings.get('group_pull', {}).get('groups', {}).get(args.group, {})
    pool_path = args.pool or group_settings.get('pool')
    db = args.db or os.environ.get('FFTA_WORK_DB') or settings.get('db')
    if not db:
        raise ValueError('specify --db or existing workflow config')
    save = Path(args.save).resolve()
    protected = [Path(db).resolve()] + [Path(p).resolve() for p in (pool_path, args.lease) if p]
    if save in protected:
        raise ValueError('receipt cannot overwrite database or pool')
    if args.disposition:
        if not args.lease or not args.evidence or not args.summary:
            raise ValueError('disposition requires --lease, --evidence and --summary')
        lease = json.loads(Path(args.lease).read_text())['lease']
        operation = 'group-disposition'
        data = {'group': args.group, 'disposition': args.disposition, 'summary': args.summary,
                'work_lease': {'id': lease['id'], 'token': lease['token']},
                'evidence': wf.evidence(args.evidence)}
    else:
        if not pool_path:
            raise ValueError('group pull requires --pool or configured group pool')
        operation = 'group-pull'
    ledger = GroupLedger(db)
    try:
        if operation == 'group-pull':
            result = pull_once_with_refresh(ledger, args.actor, args.group, pool_path,
                args.manifest or wf.ROOT / 'config/retail-us.json', group_settings.get('refresh'),
                group_settings.get('pool') if not args.pool else None)
        else:
            result = ledger.mutate(operation, args.actor, data)
        wf.atomic_write(save, json.dumps(result, indent=2) + '\n')
        save.chmod(0o600)
        print(json.dumps(redacted(result), indent=2))
        return 0
    finally:
        ledger.close()


if __name__ == '__main__':
    try:
        sys.exit(main())
    except (ValueError, KeyError, TypeError, OSError) as exc:
        print(json.dumps({'ok': False, 'error': str(exc)}), file=sys.stderr)
        sys.exit(1)
