#!/usr/bin/env python3
"""Transactional task claims, append-only recovery events, and delivery reports.

This ledger records evidence; it does not replace compiler or independent review
validators. It never builds game code. Opt-in publication queues public data
updates in a detached process; implementation Git remains untouched.
"""
from __future__ import annotations

import argparse
import datetime as dt
import hashlib
import html
import json
import math
import os
from pathlib import Path
import secrets
import sqlite3
import statistics
import subprocess
import sys
import tempfile
import uuid
from zoneinfo import ZoneInfo

ROOT = Path(__file__).resolve().parents[1]
SCHEMA = 1
GATES = ('local_semantic', 'local_exact', 'peer_semantic', 'peer_exact', 'integrated')
DELIVERY_GATES = GATES + ('integrated_exact',)  # Derived subset, never a new credit gate.
REPORT_TIMEZONE = ZoneInfo('Asia/Shanghai')
DDL = '''
CREATE TABLE meta(key TEXT PRIMARY KEY, value TEXT NOT NULL);
CREATE TABLE tasks(
 id TEXT PRIMARY KEY, module TEXT NOT NULL, original_bytes INTEGER NOT NULL,
 reservation TEXT, state TEXT NOT NULL, actor TEXT, token TEXT,
 priority INTEGER NOT NULL, created_at TEXT NOT NULL, started_at TEXT,
 last_round_at TEXT, spec TEXT NOT NULL);
CREATE UNIQUE INDEX one_active_per_actor ON tasks(actor) WHERE state='active';
CREATE INDEX ready_tasks ON tasks(state,reservation,priority,id);
CREATE TABLE events(
 seq INTEGER PRIMARY KEY AUTOINCREMENT, at TEXT NOT NULL, actor TEXT NOT NULL,
 task_id TEXT REFERENCES tasks(id), kind TEXT NOT NULL, payload TEXT NOT NULL);
CREATE INDEX task_events ON events(task_id,seq);
CREATE TABLE requests(key TEXT PRIMARY KEY, fingerprint TEXT NOT NULL, result TEXT NOT NULL);
CREATE TABLE legacy_imports(fingerprint TEXT PRIMARY KEY);
CREATE TABLE credits(
 id INTEGER PRIMARY KEY, task_id TEXT NOT NULL REFERENCES tasks(id),
 module TEXT NOT NULL, gate TEXT NOT NULL, actor TEXT NOT NULL, at TEXT NOT NULL,
 binary_sha256 TEXT NOT NULL, generated_bytes INTEGER NOT NULL,
 original_bytes INTEGER NOT NULL, payload TEXT NOT NULL, revoked INTEGER NOT NULL DEFAULT 0);
CREATE UNIQUE INDEX one_live_credit ON credits(module,gate) WHERE revoked=0;
CREATE TABLE commits(sha TEXT PRIMARY KEY, recorded_at TEXT NOT NULL, payload TEXT NOT NULL);
CREATE TRIGGER events_no_update BEFORE UPDATE ON events BEGIN SELECT RAISE(ABORT,'events are append-only'); END;
CREATE TRIGGER events_no_delete BEFORE DELETE ON events BEGIN SELECT RAISE(ABORT,'events are append-only'); END;
'''

# Additive coordination extension. Existing tasks, clocks, credits and schema
# version stay intact; old ledgers gain only this table and its indexes.
LEASE_DDL = '''
CREATE TABLE IF NOT EXISTS work_leases(
 id TEXT PRIMARY KEY, kind TEXT NOT NULL, actor TEXT NOT NULL, token TEXT NOT NULL,
 rom_offset INTEGER, size INTEGER NOT NULL, module TEXT NOT NULL, task_id TEXT,
 acquired_at TEXT NOT NULL, ended_at TEXT, state TEXT NOT NULL,
 payload TEXT NOT NULL);
CREATE INDEX IF NOT EXISTS active_work_leases ON work_leases(state,kind,rom_offset);
CREATE UNIQUE INDEX IF NOT EXISTS one_source_lease_per_actor
 ON work_leases(actor) WHERE state='active' AND kind='source';
'''


def encode(value):
    return json.dumps(value, ensure_ascii=False, sort_keys=True, allow_nan=False)


def timestamp(value=None):
    value = value or dt.datetime.now(dt.timezone.utc).isoformat(timespec='microseconds')
    parsed = dt.datetime.fromisoformat(value.replace('Z', '+00:00'))
    if parsed.tzinfo is None:
        raise ValueError('timestamps must include a timezone')
    return parsed.astimezone(dt.timezone.utc).isoformat(timespec='microseconds')


def seconds(start, end):
    return (dt.datetime.fromisoformat(end) - dt.datetime.fromisoformat(start)).total_seconds()


def completed_clock_windows(now, epoch):
    """Return the two completed Asia/Shanghai clock hours ending before this hour."""
    cutoff = dt.datetime.fromisoformat(now)
    epoch_at = dt.datetime.fromisoformat(epoch)
    local_cutoff = cutoff.astimezone(REPORT_TIMEZONE)
    current_start = local_cutoff.replace(minute=0, second=0, microsecond=0)
    windows = {}
    for name, hours_back in (('last_hour', 0), ('previous_hour', 1)):
        end_local = current_start - dt.timedelta(hours=hours_back)
        start_local = end_local - dt.timedelta(hours=1)
        start_utc = start_local.astimezone(dt.timezone.utc)
        end_utc = end_local.astimezone(dt.timezone.utc)
        observed_start = max(start_utc, epoch_at)
        observed_seconds = max(0.0, (end_utc - observed_start).total_seconds()) if end_utc > epoch_at else 0.0
        partial_reason = ('before_epoch' if end_utc <= epoch_at else
                          'epoch_partial' if start_utc < epoch_at else None)
        label_end = end_local - dt.timedelta(seconds=1)
        windows[name] = {
            'timezone': 'Asia/Shanghai',
            'basis': 'completed_absolute_clock_hour',
            'start_inclusive': start_utc.isoformat(timespec='microseconds'),
            'end_exclusive': end_utc.isoformat(timespec='microseconds'),
            'start_inclusive_local': start_local.isoformat(timespec='microseconds'),
            'end_exclusive_local': end_local.isoformat(timespec='microseconds'),
            'display': f"{start_local:%Y-%m-%d %H:%M:%S}–{label_end:%Y-%m-%d %H:%M:%S} Asia/Shanghai (UTC+08:00)",
            'observed_seconds': observed_seconds,
            'partial': observed_seconds < 3600,
            'partial_reason': partial_reason,
        }
    current_start_utc = current_start.astimezone(dt.timezone.utc)
    current = {
        'timezone': 'Asia/Shanghai',
        'basis': 'current_incomplete_clock_hour',
        'start_inclusive': current_start_utc.isoformat(timespec='microseconds'),
        'observed_until_inclusive': cutoff.isoformat(timespec='microseconds'),
        'start_inclusive_local': current_start.isoformat(timespec='microseconds'),
        'observed_until_inclusive_local': local_cutoff.isoformat(timespec='microseconds'),
        'display': f"{current_start:%Y-%m-%d %H:%M:%S}–{local_cutoff:%Y-%m-%d %H:%M:%S} Asia/Shanghai (UTC+08:00), in progress",
        'observed_seconds': max(0.0, (cutoff-current_start_utc).total_seconds()),
        'partial': True,
        'comparison_eligible': False,
    }
    return windows, current


def nonnegative(value, name):
    if type(value) is not int or value < 0:
        raise ValueError(f'{name} must be a nonnegative integer')
    return value


def load_json(path):
    return json.loads(Path(path).read_text(encoding='utf-8'))


def evidence(paths):
    pins = []
    for name in paths:
        path = Path(name).resolve(strict=True)
        digest = hashlib.sha256()
        with path.open('rb') as stream:
            before = os.fstat(stream.fileno())
            for block in iter(lambda: stream.read(1024 * 1024), b''):
                digest.update(block)
            after = os.fstat(stream.fileno())
        if (before.st_size, before.st_mtime_ns, before.st_ino) != (after.st_size, after.st_mtime_ns, after.st_ino):
            raise ValueError(f'evidence changed while reading: {path}')
        pins.append({'path': str(path), 'sha256': digest.hexdigest(), 'bytes': after.st_size})
    return pins


class NativeScopeExclusions:
    """Pinned, database-local admission policy; existing history remains untouched."""

    @staticmethod
    def path(value):
        if not isinstance(value, str) or not value.strip():
            raise ValueError('scope exclusions require a nonempty path')
        path = Path(value)
        return path if path.is_absolute() else ROOT / path

    @staticmethod
    def digest(value):
        if (not isinstance(value, str) or len(value) != 64
                or any(c not in '0123456789abcdef' for c in value)):
            raise ValueError('scope exclusions require a SHA-256 pin')
        return value

    @classmethod
    def load(cls, database):
        config_path = ROOT / '.local/recovery-workflow.json'
        if not config_path.is_file():
            return None
        config = load_json(config_path)
        if cls.path(config['db']).resolve() != Path(database).resolve():
            return None
        if 'scope_exclusions' not in config:
            return None
        pin = config['scope_exclusions']
        if not isinstance(pin, dict):
            raise ValueError('scope exclusions pin must be an object')
        path, digest = cls.path(pin.get('path')), cls.digest(pin.get('sha256'))
        raw = path.read_bytes()
        if hashlib.sha256(raw).hexdigest() != digest:
            raise ValueError('scope exclusions registry hash changed')
        registry = json.loads(raw)
        if not isinstance(registry, dict) or registry.get('schema') != 'recovery-native-exclusions-v1':
            raise ValueError('scope exclusions registry schema is invalid')
        cls.digest(registry.get('retail_sha256'))
        entries = registry.get('entries')
        if not isinstance(entries, list):
            raise ValueError('scope exclusions entries must be a list')
        for entry in entries:
            if (not isinstance(entry, dict) or type(entry.get('rom_offset')) is not int
                    or entry['rom_offset'] < 0 or type(entry.get('original_span_bytes')) is not int
                    or entry['original_span_bytes'] <= 0
                    or not isinstance(entry.get('classification'), str) or not entry['classification'].strip()
                    or not isinstance(entry.get('source'), dict)):
                raise ValueError('scope exclusions entry is malformed')
            cls.path(entry['source'].get('path'))
            cls.digest(entry['source'].get('sha256'))
        policy = cls()
        policy.registry = {'path': str(path), 'sha256': digest,
                           'retail_sha256': registry['retail_sha256']}
        policy.entries = entries
        return policy

    def overlaps(self, spec):
        start, size = spec.get('rom_offset'), spec.get('original_span_bytes')
        size = nonnegative(size, 'original_span_bytes')
        if 'rom_offset' in spec:
            start = nonnegative(start, 'rom_offset')
        if 'rom_offset' not in spec or size == 0:
            return []
        matches = []
        for entry in self.entries:
            if start < entry['rom_offset'] + entry['original_span_bytes'] and entry['rom_offset'] < start + size:
                source = entry['source']
                if evidence([self.path(source['path'])])[0]['sha256'] != source['sha256']:
                    raise ValueError('scope exclusions source hash changed')
                matches.append({'registry': self.registry, 'entry': entry})
        return matches

    def require_allowed(self, spec):
        if self.overlaps(spec):
            raise ValueError('native range excluded by pinned scope policy')


class Ledger:
    def __init__(self, path, initialize=False, epoch=None):
        self.path = Path(path)
        if not initialize and not self.path.is_file():
            raise ValueError('ledger does not exist; run init explicitly')
        if initialize:
            self.path.parent.mkdir(parents=True, exist_ok=True)
        self.db = sqlite3.connect(self.path, timeout=15, isolation_level=None)
        self.db.row_factory = sqlite3.Row
        self.db.execute('PRAGMA foreign_keys=ON')
        if initialize:
            self.db.execute('PRAGMA journal_mode=WAL')
            # executescript controls its own transaction. Exclusive initialization
            # is requested by the administrator before workers attach.
            if self.db.execute('PRAGMA user_version').fetchone()[0] == 0:
                self.db.executescript('BEGIN IMMEDIATE;\n' + DDL)
                self.db.execute('INSERT INTO meta VALUES (?,?)', ('epoch', timestamp(epoch)))
                self.db.execute(f'PRAGMA user_version={SCHEMA}')
                self.db.commit()
        if self.db.execute('PRAGMA user_version').fetchone()[0] != SCHEMA:
            raise ValueError('unsupported ledger schema')
        if not self.db.execute("SELECT 1 FROM sqlite_master WHERE type='table' AND name='work_leases'").fetchone():
            self.db.executescript('BEGIN IMMEDIATE;\n' + LEASE_DDL + '\nCOMMIT;')

    def close(self):
        self.db.close()

    def event(self, actor, task, kind, payload, at):
        cur = self.db.execute('INSERT INTO events(at,actor,task_id,kind,payload) VALUES(?,?,?,?,?)',
                              (at, actor, task, kind, encode(payload)))
        return cur.lastrowid

    def task(self, task_id):
        row = self.db.execute('SELECT * FROM tasks WHERE id=?', (task_id,)).fetchone()
        if row is None:
            raise ValueError(f'unknown task: {task_id}')
        return dict(row)

    def owned(self, actor, data):
        task = self.task(data['task'])
        if task['state'] != 'active' or task['actor'] != actor or not secrets.compare_digest(task['token'] or '', data.get('token', '')):
            raise ValueError('active claim token/actor mismatch; no automatic takeover')
        return task

    @staticmethod
    def scope_overlaps(start, size, module, other_start, other_size, other_module):
        if type(start) is int and type(other_start) is int:
            return size > 0 and other_size > 0 and start < other_start + other_size and other_start < start + size
        return bool(module) and module == other_module

    def leases(self):
        return [{k: v for k, v in dict(row).items() if k not in ('token', 'payload')}
                for row in self.db.execute("SELECT * FROM work_leases WHERE state='active' ORDER BY acquired_at,id")]

    def leases_required(self):
        row = self.db.execute("SELECT value FROM meta WHERE key='work_coordination'").fetchone()
        return bool(row and row['value'] == 'required')

    def coordination_audit(self):
        self.db.execute('BEGIN')
        try:
            scopes = [dict(row, phase='lease') for row in self.leases()]
            for row in self.db.execute("SELECT id,actor,module,original_bytes,spec FROM tasks WHERE state='active'"):
                spec = json.loads(row['spec'])
                scopes.append({'id': row['id'], 'actor': row['actor'], 'phase': 'native',
                               'rom_offset': spec.get('rom_offset'), 'size': row['original_bytes'],
                               'module': row['module']})
            conflicts = [{'left': left, 'right': right}
                         for i, left in enumerate(scopes) for right in scopes[i+1:]
                         if self.scope_overlaps(left['rom_offset'], left['size'], left['module'],
                                                right['rom_offset'], right['size'], right['module'])]
            result = {'ok': not conflicts, 'mode': 'required' if self.leases_required() else 'compatible',
                      'active_scopes': scopes, 'conflicts': conflicts}
            self.db.commit()
            return result
        except BaseException:
            self.db.rollback()
            raise

    def work_lease(self, actor, data, kind='source', administrator=False):
        pin = data.get('work_lease')
        if pin is None:
            return None
        if not isinstance(pin, dict):
            raise ValueError('work lease must contain id and token')
        row = self.db.execute('SELECT * FROM work_leases WHERE id=?', (pin.get('id'),)).fetchone()
        if (not row or row['state'] != 'active' or row['kind'] != kind
                or not isinstance(pin.get('token'), str)
                or not secrets.compare_digest(row['token'], pin['token'])
                or (row['actor'] != actor and not (administrator and actor == 'administrator'))):
            raise ValueError('active work lease token/actor mismatch; no automatic takeover')
        return dict(row)

    def lease_conflict(self, start, size, module, ignore=None):
        for row in self.leases():
            if row['id'] != ignore and self.scope_overlaps(
                    start, size, module, row['rom_offset'], row['size'], row['module']):
                return row
        return None

    def native_conflict(self, start, size, module):
        for row in self.db.execute("SELECT id,actor,module,original_bytes,spec FROM tasks WHERE state='active'"):
            spec = json.loads(row['spec'])
            if self.scope_overlaps(start, size, module, spec.get('rom_offset'), row['original_bytes'], row['module']):
                return {'task_id': row['id'], 'actor': row['actor'], 'module': row['module'],
                        'rom_offset': spec.get('rom_offset'), 'size': row['original_bytes'], 'state': 'active'}
        return None

    @staticmethod
    def require_lease_scope(lease, start, size, module):
        if lease and not ((type(start) is int and lease['rom_offset'] == start and lease['size'] == size)
                          or (start is None and lease['rom_offset'] is None and module == lease['module'])):
            raise ValueError('work lease does not cover the complete native scope')

    def promote_lease(self, lease, task_id, at):
        if lease:
            self.db.execute("UPDATE work_leases SET state='promoted',ended_at=?,task_id=? WHERE id=? AND state='active'",
                            (at, task_id, lease['id']))
            self.event(lease['actor'], task_id, 'lease_promoted', {'lease_id': lease['id']}, at)

    def mutate(self, operation, actor, data, request_id=None):
        if not actor or not actor.strip():
            raise ValueError('actor is required')
        fingerprint = hashlib.sha256(encode([operation, actor, data]).encode()).hexdigest()
        request_id = request_id or str(uuid.uuid4())
        self.db.execute('BEGIN IMMEDIATE')
        try:
            prior = self.db.execute('SELECT * FROM requests WHERE key=?', (request_id,)).fetchone()
            if prior:
                if prior['fingerprint'] != fingerprint:
                    raise ValueError('request-id reused with different input')
                result = json.loads(prior['result'])
                if operation == 'lease-claim' and result.get('lease'):
                    saved = result['lease']
                    live = self.db.execute('SELECT state,token FROM work_leases WHERE id=?', (saved['id'],)).fetchone()
                    if not live or live['state'] != 'active' or live['token'] != saved['token']:
                        raise ValueError('saved lease is no longer active; use a new request-id')
                if operation in ('claim', 'continue') and result.get('task'):
                    saved = result['task']
                    live = self.db.execute('SELECT state,actor,token FROM tasks WHERE id=?', (saved['id'],)).fetchone()
                    if (not live or live['state'] != 'active' or live['actor'] != saved['actor']
                            or live['token'] != saved['token']):
                        raise ValueError('saved native claim is no longer active; use a new request-id')
                    spec = saved['spec']
                    if self.lease_conflict(spec.get('rom_offset'), saved['original_bytes'], saved['module']):
                        raise ValueError('saved native claim conflicts with a current work lease')
                    policy = NativeScopeExclusions.load(self.path)
                    if policy:
                        policy.require_allowed(result['task']['spec'])
                self.db.commit()
                return result
            at = timestamp()
            result = self.apply(operation, actor, data, at)
            result.update(ok=True, operation=operation, request_id=request_id)
            self.db.execute('INSERT INTO requests VALUES(?,?,?)', (request_id, fingerprint, encode(result)))
            self.db.commit()
            return result
        except BaseException:
            self.db.rollback()
            raise

    def apply(self, op, actor, data, at):
        if op in ('add', 'import-pool', 'requeue', 'import-log', 'schedule', 'continue', 'coordination') and actor != 'administrator':
            raise ValueError('administrator operation')
        policy = NativeScopeExclusions.load(self.path) if op in ('add', 'import-pool', 'claim', 'continue') else None
        if op == 'coordination':
            mode = data.get('mode')
            if mode not in ('required', 'compatible') or not data.get('summary', '').strip():
                raise ValueError('coordination mode and reason are required')
            self.db.execute("INSERT INTO meta(key,value) VALUES('work_coordination',?) ON CONFLICT(key) DO UPDATE SET value=excluded.value", (mode,))
            self.event(actor, None, 'work_coordination', {'mode': mode, 'summary': data['summary']}, at)
            return {'mode': mode}
        if op == 'lease-claim':
            kind = data.get('kind')
            if kind not in ('source', 'peer') or not data.get('summary', '').strip():
                raise ValueError('lease requires source/peer kind and a reason')
            task_id = data.get('task')
            if kind == 'peer':
                task = self.task(task_id)
                gate = data.get('gate') or 'peer_exact'
                if gate not in ('peer_exact', 'peer_semantic'):
                    raise ValueError('peer lease gate must be peer_exact or peer_semantic')
                local = self.db.execute('SELECT actor FROM credits WHERE task_id=? AND gate=? AND revoked=0',
                                        (task_id, gate.replace('peer_', 'local_'))).fetchone()
                if task['state'] not in ('frozen', 'blocked') or not local or local['actor'] == actor:
                    raise ValueError('peer lease requires a frozen local gate and an independent actor')
                if self.db.execute('SELECT 1 FROM credits WHERE task_id=? AND gate=? AND revoked=0', (task_id, gate)).fetchone():
                    raise ValueError('peer gate already recorded; no duplicate verification')
                spec = json.loads(task['spec'])
                start, size, module = spec.get('rom_offset'), task['original_bytes'], task['module']
            else:
                start = nonnegative(data.get('rom_offset'), 'rom_offset')
                size = nonnegative(data.get('size'), 'size')
                module = data.get('module') or ''
                if not size or not isinstance(module, str):
                    raise ValueError('source lease requires positive size and a valid module')
            busy = self.lease_conflict(start, size, module)
            if busy:
                if (busy['actor'] == actor and busy['kind'] == kind and busy['rom_offset'] == start
                        and busy['size'] == size and (start is not None or busy['module'] == module)):
                    row = dict(self.db.execute('SELECT * FROM work_leases WHERE id=?', (busy['id'],)).fetchone())
                    row.pop('payload')
                    return {'lease': row, 'resumed': True}
                return {'lease': None, 'busy': busy}
            if kind == 'source':
                other = self.db.execute("SELECT id FROM work_leases WHERE actor=? AND kind='source' AND state='active'", (actor,)).fetchone()
                if other:
                    return {'lease': None, 'busy': next(row for row in self.leases() if row['id'] == other['id'])}
            busy = self.native_conflict(start, size, module)
            if busy:
                return {'lease': None, 'busy': busy}
            ident, token = uuid.uuid4().hex, secrets.token_hex(16)
            self.db.execute('INSERT INTO work_leases VALUES(?,?,?,?,?,?,?,?,?,?,?,?)',
                            (ident, kind, actor, token, start, size, module, task_id, at, None, 'active', encode(data)))
            self.event(actor, task_id if kind == 'peer' else None, 'lease_claimed',
                       {'lease_id': ident, 'kind': kind, 'rom_offset': start, 'size': size, 'module': module,
                        'summary': data['summary']}, at)
            row = dict(self.db.execute('SELECT * FROM work_leases WHERE id=?', (ident,)).fetchone()); row.pop('payload')
            return {'lease': row, 'resumed': False}
        if op == 'lease-release':
            row = self.db.execute('SELECT * FROM work_leases WHERE id=?', (data.get('lease_id'),)).fetchone()
            if (not row or row['state'] != 'active' or actor not in (row['actor'], 'administrator')
                    or not isinstance(data.get('token'), str) or not secrets.compare_digest(row['token'], data['token'])):
                raise ValueError('active work lease token/actor mismatch; no automatic takeover')
            if not data.get('summary', '').strip():
                raise ValueError('lease release requires a reason')
            self.db.execute("UPDATE work_leases SET state='released',ended_at=? WHERE id=?", (at, row['id']))
            self.event(actor, row['task_id'], 'lease_released', {'lease_id': row['id'], 'summary': data['summary']}, at)
            return {'lease_id': row['id'], 'state': 'released'}
        if op == 'schedule':
            task = self.task(data['task'])
            if (task['state'] != 'ready' or task['priority'] != data.get('expected_priority')
                    or task['reservation'] != data.get('expected_reservation')):
                raise ValueError('schedule requires unchanged ready priority/reservation')
            if not data.get('summary', '').strip():
                raise ValueError('schedule requires a reason')
            priority = nonnegative(data['priority'], 'priority')
            reservation = task['reservation']
            if data.get('clear_reservation'):
                if data.get('reserve_for'):
                    raise ValueError('cannot reserve and clear reservation together')
                reservation = None
            elif data.get('reserve_for'):
                reservation = data['reserve_for']
                if not isinstance(reservation, str) or not reservation.isidentifier():
                    raise ValueError('reservation must be an actor identifier')
            self.db.execute('UPDATE tasks SET priority=?,reservation=? WHERE id=?',
                            (priority, reservation, task['id']))
            seq = self.event(actor, task['id'], 'scheduled', {
                'summary': data['summary'], 'previous_priority': task['priority'],
                'priority': priority, 'previous_reservation': task['reservation'],
                'reservation': reservation, 'original_spec_preserved': True}, at)
            return {'task_id': task['id'], 'priority': priority, 'reservation': reservation,
                    'state': 'ready', 'event_seq': seq}
        if op in ('add', 'import-pool'):
            doc = data['document']
            records = doc.get('records', [doc])
            added = []
            work = self.work_lease(actor, data, administrator=True)
            if work and len(records) != 1:
                raise ValueError('one source lease can register only one native task')
            for index, spec in enumerate(records):
                task_id, module = spec['task_id'], spec['module']
                if not isinstance(task_id, str) or not task_id.strip() or not isinstance(module, str) or not module.strip():
                    raise ValueError('task_id and module must be nonempty strings')
                if self.db.execute('SELECT 1 FROM tasks WHERE id=?', (task_id,)).fetchone():
                    old = json.loads(self.task(task_id)['spec'])
                    if old != spec:
                        raise ValueError(f'existing task differs: {task_id}; never overwrite live state from a pool')
                    continue
                state = spec.get('state', 'ready') if op == 'import-pool' else 'ready'
                if policy and state in ('ready', 'active'):
                    policy.require_allowed(spec)
                size = nonnegative(spec['original_span_bytes'], 'original_span_bytes')
                if self.leases_required() and size > 0 and not work:
                    raise ValueError('source work lease required for new native registration; use lease-claim and --lease')
                priority = nonnegative(spec.get('priority', index), 'priority')
                if 'rom_offset' in spec:
                    nonnegative(spec['rom_offset'], 'rom_offset')
                self.require_lease_scope(work, spec.get('rom_offset'), size, module)
                busy_lease = self.lease_conflict(spec.get('rom_offset'), size, module, work['id'] if work else None)
                if busy_lease:
                    raise ValueError(f"native registration overlaps work lease held by {busy_lease['actor']}; supply its valid lease")
                # Native identity is the original ROM envelope, independent of task/module aliases.
                if size and type(spec.get('rom_offset')) is int:
                    start, end = spec['rom_offset'], spec['rom_offset'] + size
                    for old_task in self.db.execute('SELECT id,original_bytes,spec FROM tasks'):
                        old_spec = json.loads(old_task['spec'])
                        old_start = old_spec.get('rom_offset')
                        if (old_task['original_bytes'] and type(old_start) is int
                                and old_start == start and old_start + old_task['original_bytes'] == end):
                            raise ValueError(f'native range already registered by task {old_task["id"]}')
                reservation = spec.get('owner') or None
                if work:
                    if reservation not in (None, work['actor']):
                        raise ValueError('source lease conflicts with task reservation')
                    reservation = work['actor']
                state = spec.get('state', 'ready') if op == 'import-pool' else 'ready'
                state = state if state in ('ready', 'active', 'blocked') else 'frozen'
                owner = reservation if state != 'ready' else None
                if state == 'active' and not owner:
                    raise ValueError('imported active task requires owner')
                if state == 'active':
                    for live in self.db.execute("SELECT module,spec FROM tasks WHERE state='active'"):
                        other = json.loads(live['spec'])
                        overlap = ('rom_offset' in spec and 'rom_offset' in other and
                                   spec['rom_offset'] < other['rom_offset'] + other['original_span_bytes'] and
                                   other['rom_offset'] < spec['rom_offset'] + size)
                        if module == live['module'] or overlap:
                            raise ValueError('imported active task overlaps an existing active task')
                started = timestamp(spec['started_utc']) if spec.get('started_utc') else (at if state == 'active' else None)
                if started and started > at:
                    raise ValueError('task start cannot be in the future')
                token = secrets.token_hex(16) if state == 'active' else None
                self.db.execute('INSERT INTO tasks VALUES(?,?,?,?,?,?,?,?,?,?,?,?)',
                    (task_id, module, size, reservation, state, owner, token, priority, at, started, None, encode(spec)))
                self.event(actor, task_id, 'imported' if op == 'import-pool' else 'added',
                           {'source': data.get('source'), 'legacy_state': spec.get('state'), 'no_acceptance_credit': True}, at)
                if state == 'active':
                    self.promote_lease(work, task_id, at)
                added.append(task_id)
            return {'added': added}
        if op == 'claim':
            current = self.db.execute("SELECT id FROM tasks WHERE actor=? AND state='active'", (actor,)).fetchone()
            if current:
                if data.get('task') and data['task'] != current['id']:
                    raise ValueError('finish/release current task before another claim')
                task = self.task(current['id']); task['spec'] = json.loads(task['spec'])
                excluded = policy.overlaps(task['spec']) if policy else []
                if excluded:
                    return {'task': None, 'resumed': False, 'active_task_preserved': task['id'],
                            'reason': 'active task excluded by scope; finish/release remains available',
                            'scope_exclusions': excluded}
                return {'task': task, 'resumed': True}
            sql = "SELECT * FROM tasks WHERE state='ready' AND (reservation IS NULL OR reservation=?)"
            args = [actor]
            if data.get('task'):
                sql += ' AND id=?'; args.append(data['task'])
            candidates = self.db.execute(sql + ' ORDER BY priority,id', args).fetchall()
            excluded = []
            work = self.work_lease(actor, data)
            if self.leases_required() and candidates and not work:
                raise ValueError('source work lease required for a new native claim; use lease-claim and --lease')
            work_busy = []
            for row in candidates:
                spec = json.loads(row['spec'])
                matches = policy.overlaps(spec) if policy else []
                if matches:
                    excluded.append({'task_id': row['id'], 'matches': matches})
                    continue
                if work:
                    if not data.get('task') and not self.scope_overlaps(
                            spec.get('rom_offset'), row['original_bytes'], row['module'],
                            work['rom_offset'], work['size'], work['module']):
                        continue
                    self.require_lease_scope(work, spec.get('rom_offset'), row['original_bytes'], row['module'])
                lease_busy = self.lease_conflict(spec.get('rom_offset'), row['original_bytes'], row['module'],
                                                 work['id'] if work else None)
                if lease_busy:
                    work_busy.append(lease_busy)
                    continue
                busy = False
                for live in self.db.execute("SELECT module,spec FROM tasks WHERE state='active'"):
                    other = json.loads(live['spec'])
                    overlap = ('rom_offset' in spec and 'rom_offset' in other and
                               spec['rom_offset'] < other['rom_offset'] + other['original_span_bytes'] and
                               other['rom_offset'] < spec['rom_offset'] + spec['original_span_bytes'])
                    if row['module'] == live['module'] or overlap:
                        busy = True; break
                if busy:
                    continue
                token = secrets.token_hex(16)
                self.db.execute("UPDATE tasks SET state='active',actor=?,token=?,started_at=COALESCE(started_at,?),last_round_at=NULL WHERE id=?",
                                (actor, token, at, row['id']))
                canonical_start = self.task(row['id'])['started_at']
                self.event(actor, row['id'], 'claimed', {
                    'canonical_started_at': canonical_start,
                    'episode_started_at': at,
                    'clock_policy': 'preserve_original_start'}, at)
                self.promote_lease(work, row['id'], at)
                task = self.task(row['id']); task['spec'] = json.loads(task['spec'])
                return {'task': task, 'resumed': False}
            if work_busy:
                return {'task': None, 'reason': 'native work held by source/peer lease', 'busy': work_busy}
            if excluded:
                return {'task': None, 'reason': 'no eligible ready task; scope exclusions skipped',
                        'scope_exclusions': excluded}
            return {'task': None, 'reason': 'no eligible ready task; reserved/busy work not stolen'}
        if op == 'continue':
            task = self.task(data['task'])
            if policy:
                policy.require_allowed(json.loads(task['spec']))
            packet = data.get('continuation_packet')
            if not isinstance(packet, dict):
                raise ValueError('continuation requires a pinned admission packet')
            if (task['state'] != 'blocked' or packet.get('expected_state') != task['state']
                    or (task['token'] or '') != packet.get('expected_token', '')):
                raise ValueError('continuation compare-and-swap state/token mismatch')
            if packet.get('task_id') != task['id']:
                raise ValueError('continuation task identity changed')
            spec = json.loads(task['spec'])
            identity = {'task_id': task['id'], 'module': task['module'],
                        'original_span_bytes': task['original_bytes']}
            for key in ('rom_offset', 'thumb_entry', 'original_reference_span_sha256', 'original_source'):
                if key not in spec:
                    raise ValueError(f'continuation native identity is incomplete: {key}')
                identity[key] = spec[key]
            source = identity['original_source']
            if (type(identity['rom_offset']) is not int or identity['rom_offset'] < 0
                    or not isinstance(identity['thumb_entry'], str)
                    or not isinstance(identity['original_reference_span_sha256'], str)
                    or len(identity['original_reference_span_sha256']) != 64
                    or any(c not in '0123456789abcdef' for c in identity['original_reference_span_sha256'])
                    or not isinstance(source, dict) or not isinstance(source.get('path'), str)
                    or not isinstance(source.get('sha256'), str) or len(source['sha256']) != 64):
                raise ValueError('continuation native identity is incomplete or malformed')
            if evidence([source['path']])[0]['sha256'] != source['sha256']:
                raise ValueError('continuation original source changed')
            if packet.get('native_identity') != identity:
                raise ValueError('continuation native identity changed')
            if not task['started_at'] or timestamp(packet.get('canonical_started_at')) != timestamp(task['started_at']):
                raise ValueError('continuation canonical start is missing or changed')
            hypotheses = spec.get('hypotheses')
            if not isinstance(hypotheses, list):
                raise ValueError('continuation prior hypothesis history is unknown')
            prior_hypotheses_hash = hashlib.sha256(encode(hypotheses).encode()).hexdigest()
            if packet.get('prior_hypotheses_sha256') != prior_hypotheses_hash:
                raise ValueError('continuation prior hypotheses changed')
            history = [dict(row) for row in self.db.execute(
                'SELECT seq,at,actor,kind,payload FROM events WHERE task_id=? ORDER BY seq', (task['id'],))]
            history_hash = hashlib.sha256(encode(history).encode()).hexdigest()
            if (packet.get('prior_event_count') != len(history)
                    or packet.get('prior_event_sha256') != history_hash):
                raise ValueError('continuation history snapshot is stale')
            continuation_count = sum(row['kind'] == 'continued' for row in history)
            if packet.get('continuation_index') != continuation_count + 1:
                raise ValueError('continuation already consumed or index is stale')
            percentage = packet.get('full_method_percent')
            if (isinstance(percentage, bool) or not isinstance(percentage, (int, float))
                    or not 70 < percentage <= 100):
                raise ValueError('continuation requires full-method progress above 70 percent')
            terminal = packet.get('terminal_state')
            if not isinstance(terminal, dict) or any(terminal.get(k) is not False for k in
                    ('complete', 'unknown', 'exhausted', 'native_duplicate')):
                raise ValueError('continuation excludes complete, unknown, exhausted, or duplicate work')
            causes = packet.get('effective_matching_causes')
            if type(causes) is not int or not 0 <= causes < 6:
                raise ValueError('continuation requires fewer than six effective matching causes')
            budget_rows = packet.get('budgets')
            if not isinstance(budget_rows, list) or not budget_rows:
                raise ValueError('continuation requires complete known budget history')
            prior_ids = {item.get('id') for item in hypotheses if isinstance(item, dict)}
            budgets = {}
            for item in budget_rows:
                if not isinstance(item, dict) or item.get('known') is not True:
                    raise ValueError('continuation budget history contains an unknown budget')
                ident = item.get('hypothesis_id')
                used, limit = item.get('attempts_used'), item.get('attempt_limit')
                if (not isinstance(ident, str) or not ident or ident in budgets
                        or type(used) is not int or type(limit) is not int or used < 0 or limit <= used):
                    raise ValueError('continuation budget is exhausted or malformed')
                budgets[ident] = {'attempts_used': used, 'attempt_limit': limit}
            if set(budgets) != prior_ids:
                raise ValueError('continuation budget list does not cover every prior hypothesis')
            recorded_attempts = {ident: 0 for ident in budgets}
            for row in self.db.execute("SELECT payload FROM events WHERE task_id=? AND kind='round'", (task['id'],)):
                round_payload = json.loads(row['payload'])
                if round_payload.get('outcome') == 'diagnostic':
                    continue
                hypothesis_id = round_payload.get('hypothesis_id')
                if hypothesis_id not in recorded_attempts:
                    raise ValueError('continuation prior round has unknown hypothesis attribution')
                recorded_attempts[hypothesis_id] += 1
            if any(budgets[ident]['attempts_used'] < count for ident, count in recorded_attempts.items()):
                raise ValueError('continuation budget understates recorded hypothesis attempts')
            cause = packet.get('new_original_asm_cause')
            if (not isinstance(cause, dict) or cause.get('kind') != 'original_asm'
                    or not isinstance(cause.get('cause_id'), str) or not cause['cause_id']
                    or not isinstance(cause.get('evidence'), list) or not cause['evidence']):
                raise ValueError('continuation requires a new original-ASM-backed cause')
            pins = []
            for pin in cause['evidence']:
                if not isinstance(pin, dict) or set(pin) != {'path', 'sha256'}:
                    raise ValueError('continuation cause evidence pin is malformed')
                actual = evidence([pin['path']])[0]
                if actual['sha256'] != pin['sha256']:
                    raise ValueError('continuation cause evidence changed')
                pins.append(actual)
            method_pins = packet.get('full_method_evidence')
            if not isinstance(method_pins, list) or not method_pins:
                raise ValueError('continuation requires pinned full-method evidence')
            for pin in method_pins:
                if not isinstance(pin, dict) or set(pin) != {'path', 'sha256'}:
                    raise ValueError('continuation full-method evidence pin is malformed')
                actual = evidence([pin['path']])[0]
                if actual['sha256'] != pin['sha256']:
                    raise ValueError('continuation full-method evidence changed')
                pins.append(actual)
            for other in self.db.execute('SELECT id,module,original_bytes,spec FROM tasks WHERE id<>?', (task['id'],)):
                other_spec = json.loads(other['spec'])
                if (other_spec.get('rom_offset') == identity['rom_offset']
                        and other['original_bytes'] == task['original_bytes']
                        and other_spec.get('original_reference_span_sha256') == identity['original_reference_span_sha256']):
                    raise ValueError('continuation native range is already registered under another task')
            if self.db.execute('SELECT 1 FROM credits WHERE task_id=? AND revoked=0', (task['id'],)).fetchone():
                raise ValueError('completed or credited task cannot be continued')
            owner = data.get('owner')
            if not isinstance(owner, str) or not owner.isidentifier() or owner == 'administrator':
                raise ValueError('continuation requires an implementation actor')
            if self.db.execute("SELECT 1 FROM tasks WHERE actor=? AND state='active'", (owner,)).fetchone():
                raise ValueError('continuation actor already owns active work')
            if not data.get('summary', '').strip():
                raise ValueError('continuation requires a concrete reason')
            work = self.work_lease(owner, data)
            if self.leases_required() and not work:
                raise ValueError('source work lease required for continuation')
            self.require_lease_scope(work, spec.get('rom_offset'), task['original_bytes'], task['module'])
            if self.lease_conflict(spec.get('rom_offset'), task['original_bytes'], task['module'], work['id'] if work else None):
                raise ValueError('continuation overlaps an active source/peer work lease')
            if self.native_conflict(spec.get('rom_offset'), task['original_bytes'], task['module']):
                raise ValueError('continuation overlaps an active native task')
            token = secrets.token_hex(16)
            self.db.execute("UPDATE tasks SET state='active',actor=?,token=?,last_round_at=NULL WHERE id=? AND state='blocked'",
                            (owner, token, task['id']))
            if self.db.execute('SELECT changes()').fetchone()[0] != 1:
                raise ValueError('continuation state changed during compare-and-swap')
            continuation_evidence = {'native_identity': identity,
                'canonical_started_at': task['started_at'], 'episode_started_at': at,
                'continuation_index': packet['continuation_index'],
                'prior_hypotheses_sha256': prior_hypotheses_hash,
                'prior_event_count': len(history), 'prior_event_sha256': history_hash,
                'full_method_percent': percentage, 'effective_matching_causes': causes,
                'budgets': budgets, 'new_original_asm_cause_id': cause['cause_id'],
                'evidence': pins, 'summary': data['summary'],
                'clock_policy': 'canonical start retained; episode start recorded'}
            self.event(owner, task['id'], 'continued', continuation_evidence, at)
            self.promote_lease(work, task['id'], at)
            result_task = self.task(task['id']); result_task['spec'] = json.loads(result_task['spec'])
            return {'task': result_task, 'resumed': True, 'continuation_index': packet['continuation_index']}
        if op in ('record', 'finish', 'release'):
            task = self.owned(actor, data)
            if not data.get('summary', '').strip():
                raise ValueError('summary is required')
            payload = {k: v for k, v in data.items() if k not in ('token', 'task')}
            payload['evidence'] = evidence(payload.get('evidence', []))
            if op == 'record':
                kind = data.get('kind', 'round')
                if kind not in ('round', 'progress'):
                    raise ValueError('record kind must be round or progress')
                if kind == 'round':
                    if 'round' not in data or data.get('outcome') not in ('exact', 'nonexact', 'unchanged', 'compile_failed', 'check_failed', 'diagnostic'):
                        raise ValueError('round and a valid outcome are required')
                    payload['round'] = str(data['round'])
                    for old in self.db.execute("SELECT payload FROM events WHERE task_id=? AND kind='round'", (task['id'],)):
                        if str(json.loads(old['payload'])['round']) == payload['round']:
                            raise ValueError('round already recorded; retry with the same request-id')
                    for name in ('generated_bytes', 'matching_bytes', 'compile_attempts'):
                        if name in data:
                            nonnegative(data[name], name)
                    episode = self.db.execute("SELECT at,kind FROM events WHERE task_id=? AND kind IN ('claimed','continued') ORDER BY seq DESC LIMIT 1",
                                              (task['id'],)).fetchone()
                    episode_start = episode['at'] if episode else task['started_at']
                    payload['interval_seconds'] = seconds(task['last_round_at'] or episode_start, at)
                    payload['interval_kind'] = ('decision' if task['last_round_at'] else
                                                ('continuation_preparation' if episode and episode['kind'] == 'continued'
                                                 else 'initial_preparation'))
                    payload['since_claim_seconds'] = seconds(episode_start, at)
                    payload['since_original_start_seconds'] = seconds(task['started_at'], at)
                    self.db.execute('UPDATE tasks SET last_round_at=? WHERE id=?', (at, task['id']))
            else:
                kind = op
                state = data.get('state', 'frozen') if op == 'finish' else 'ready'
                if state not in ('frozen', 'blocked', 'ready') or (op == 'finish' and state == 'ready'):
                    raise ValueError('finish state must be frozen or blocked')
                payload['gross_seconds'] = seconds(task['started_at'], at)
                self.db.execute('UPDATE tasks SET state=?,token=NULL WHERE id=?', (state, task['id']))
            seq = self.event(actor, task['id'], kind, payload, at)
            return {'event_seq': seq, 'at': at, 'payload': payload, 'state': self.task(task['id'])['state']}
        if op == 'requeue':
            task = self.task(data['task'])
            if not data.get('summary') or data.get('expected_token') != task['token'] or data.get('expected_state') != task['state']:
                raise ValueError('requeue requires reason and current expected state/token')
            reservation = data.get('reserve_for') or task['reservation']
            if reservation is not None and (not isinstance(reservation, str) or not reservation.isidentifier()):
                raise ValueError('reservation must be an actor identifier')
            priority = task['priority'] if data.get('priority') is None else nonnegative(data['priority'], 'priority')
            self.db.execute("UPDATE tasks SET state='ready',actor=NULL,token=NULL,last_round_at=NULL,priority=?,reservation=? WHERE id=?",
                            (priority, reservation, task['id']))
            self.event(actor, task['id'], 'requeued', {'summary': data['summary'], 'previous_actor': task['actor'],
                       'previous_priority': task['priority'], 'priority': priority,
                       'previous_reservation': task['reservation'], 'reservation': reservation}, at)
            return {'task_id': task['id'], 'state': 'ready', 'priority': priority, 'reservation': reservation}
        if op == 'credit':
            task = self.task(data['task']); gate = data['gate']
            if gate not in GATES or actor == 'administrator':
                raise ValueError('invalid gate or administrator cannot accept C')
            if not data.get('evidence'):
                raise ValueError('a gate requires an evidence receipt')
            pins = evidence(data['evidence']); binary = evidence([data['binary']])[0]
            occurred_at = timestamp(data.get('occurred_at') or at)
            if occurred_at > at:
                raise ValueError('credit occurrence cannot be in the future')
            implementer = task['actor'] or task['reservation']
            if gate.startswith('local_') and actor != implementer:
                raise ValueError('local gate belongs to implementer')
            if gate.startswith('peer_'):
                work = self.work_lease(actor, data, kind='peer')
                if self.leases_required() and not work:
                    raise ValueError('peer work lease required; use lease-claim and --lease')
                if self.leases_required() or work:
                    scope = json.loads(task['spec'])
                    if (task['state'] not in ('frozen', 'blocked')
                            or self.native_conflict(scope.get('rom_offset'), task['original_bytes'], task['module'])):
                        raise ValueError('peer gate requires frozen scope without active native work')
                if work:
                    requested = json.loads(self.db.execute('SELECT payload FROM work_leases WHERE id=?', (work['id'],)).fetchone()[0])
                    if (requested.get('gate') or 'peer_exact') != gate or work['task_id'] != task['id']:
                        raise ValueError('peer lease belongs to a different task/gate')
                spec = json.loads(task['spec'])
                self.require_lease_scope(work, spec.get('rom_offset'), task['original_bytes'], task['module'])
                if self.lease_conflict(spec.get('rom_offset'), task['original_bytes'], task['module'], work['id'] if work else None):
                    raise ValueError('peer credit overlaps an active source/peer work lease')
                if actor == implementer:
                    raise ValueError('independent peer must differ from implementer')
                prior = self.db.execute('SELECT * FROM credits WHERE module=? AND gate=? AND revoked=0',
                                        (task['module'], gate.replace('peer_', 'local_'))).fetchone()
                if not prior or prior['binary_sha256'] != binary['sha256']:
                    raise ValueError('peer gate requires same-binary local credit')
                if occurred_at < prior['at']:
                    raise ValueError('peer occurrence predates local gate')
            if gate.endswith('exact') and binary['bytes'] != task['original_bytes']:
                raise ValueError('whole exact credit requires complete original envelope size')
            if gate.endswith('semantic') and json.loads(task['spec']).get('existing_semantic_source'):
                raise ValueError('already recovered semantic method: no new semantic credit')
            if gate == 'integrated':
                if actor != 'main':
                    raise ValueError('only main records integration')
                commit = self.db.execute('SELECT payload FROM commits WHERE sha=?', (data.get('commit'),)).fetchone()
                prior = self.db.execute("SELECT 1 FROM credits WHERE module=? AND gate IN ('peer_exact','peer_semantic') AND binary_sha256=? AND revoked=0",
                                        (task['module'], binary['sha256'])).fetchone()
                if not commit or task['id'] not in json.loads(commit['payload'])['tasks'] or not prior:
                    raise ValueError('integration needs linked commit and same-binary peer acceptance')
            parts = data.get('accounting', {})
            values = [parts.get(k) for k in ('instruction_bytes', 'literal_bytes', 'alignment_bytes')]
            if any(v is not None for v in values):
                if any(v is None for v in values) or sum(nonnegative(v, 'accounting bytes') for v in values) != task['original_bytes']:
                    raise ValueError('complete original accounting must sum to original envelope')
            payload = {'evidence': pins, 'binary': binary, 'accounting': parts, 'commit': data.get('commit'),
                       'assertion': 'Recorded actor evidence assertion; existing acceptance validators remain authoritative.'}
            cur = self.db.execute('INSERT INTO credits(task_id,module,gate,actor,at,binary_sha256,generated_bytes,original_bytes,payload) VALUES(?,?,?,?,?,?,?,?,?)',
                (task['id'], task['module'], gate, actor, occurred_at, binary['sha256'], binary['bytes'], task['original_bytes'], encode(payload)))
            self.event(actor, task['id'], 'credit', {'credit_id': cur.lastrowid, 'gate': gate, 'occurred_at': occurred_at, **payload}, at)
            return {'credit_id': cur.lastrowid, 'gate': gate, 'original_bytes': task['original_bytes']}
        if op == 'revoke':
            credit = self.db.execute('SELECT * FROM credits WHERE id=? AND revoked=0', (data['credit_id'],)).fetchone()
            if not credit or actor not in ('administrator', credit['actor']) or not data.get('summary'):
                raise ValueError('live credit, its actor/administrator, and reason required')
            # Invalidate all downstream credit on this binary, retaining its history.
            downstream = {'local_exact': ('local_exact', 'peer_exact', 'integrated'), 'local_semantic': ('local_semantic','peer_semantic','integrated'),
                          'peer_exact': ('peer_exact','integrated'), 'peer_semantic': ('peer_semantic','integrated'), 'integrated': ('integrated',)}[credit['gate']]
            rows = self.db.execute('SELECT id,gate FROM credits WHERE module=? AND binary_sha256=? AND revoked=0', (credit['module'], credit['binary_sha256'])).fetchall()
            ids = [x['id'] for x in rows if x['gate'] in downstream]
            for ident in ids:
                self.db.execute('UPDATE credits SET revoked=1 WHERE id=?', (ident,))
            self.event(actor, credit['task_id'], 'revoked', {'credit_ids': ids, 'summary': data['summary']}, at)
            return {'revoked_credit_ids': ids}
        if op == 'commit':
            if actor != 'main':
                raise ValueError('main owns Git milestone records')
            sha = data['sha']
            if not 7 <= len(sha) <= 40 or any(c not in '0123456789abcdefABCDEF' for c in sha):
                raise ValueError('use a Git commit hash, not a revision expression')
            if not data.get('tasks') or not data.get('evidence'):
                raise ValueError('commit requires tasks and evidence')
            for ident in data['tasks']:
                self.task(ident)
            proc = subprocess.run(['git', '-C', data.get('repo', str(ROOT)), 'show', '-s', '--format=%H%x00%cI%x00%s', sha],
                                  check=True, capture_output=True, text=True)
            full, committed, subject = proc.stdout.rstrip('\n').split('\0', 2)
            payload = {'sha': full, 'committed_at': timestamp(committed), 'subject': subject,
                       'tasks': data['tasks'], 'evidence': evidence(data['evidence'])}
            self.db.execute('INSERT INTO commits VALUES(?,?,?)', (full, at, encode(payload)))
            self.event(actor, None, 'commit', payload, at)
            return payload
        if op == 'import-log':
            count = 0
            for item in data['records']:
                if not isinstance(item, dict):
                    continue
                ident = item.get('task_id'); time = item.get('timestamp_utc')
                if not ident or not time or not self.db.execute('SELECT 1 FROM tasks WHERE id=?', (ident,)).fetchone():
                    continue
                item_time = timestamp(time)
                if item_time > at:
                    raise ValueError('legacy event is in the future')
                digest = hashlib.sha256(encode(item).encode()).hexdigest()
                if self.db.execute('SELECT 1 FROM legacy_imports WHERE fingerprint=?', (digest,)).fetchone():
                    continue
                self.db.execute('INSERT INTO legacy_imports VALUES(?)', (digest,))
                self.event(item.get('actor', 'unknown'), ident, 'legacy', {'original': item, 'source': data['source'], 'no_automatic_credit': True}, item_time)
                task = self.task(ident)
                if 'round' in item and task['actor'] == item.get('actor') and task['state'] == 'active' and task['started_at'] <= item_time:
                    self.db.execute('UPDATE tasks SET last_round_at=? WHERE id=?', (max(task['last_round_at'] or task['started_at'], item_time), ident))
                count += 1
            return {'imported': count, 'malformed_lines': data.get('malformed_lines', [])}
        raise ValueError(f'unknown operation: {op}')

    def tasks(self, actor=None):
        rows = self.db.execute('SELECT * FROM tasks ORDER BY priority,id').fetchall()
        result = []
        for row in rows:
            item = dict(row)
            if actor and item['reservation'] not in (None, actor) and item['actor'] != actor:
                continue
            item.pop('token')  # Tokens are only returned by claim/resume.
            item['spec'] = json.loads(item['spec'])
            result.append(item)
        return result

    def history(self, task=None, limit=100):
        if not 1 <= limit <= 10000:
            raise ValueError('limit must be 1..10000')
        where, args = (' WHERE task_id=?', [task]) if task else ('', [])
        rows = self.db.execute('SELECT * FROM events' + where + ' ORDER BY seq DESC LIMIT ?', args + [limit]).fetchall()
        return [{**dict(row), 'payload': json.loads(row['payload'])} for row in reversed(rows)]

    def stats(self, now=None):
        now = timestamp(now); epoch = self.db.execute("SELECT value FROM meta WHERE key='epoch'").fetchone()[0]
        elapsed = seconds(epoch, now)
        if elapsed <= 0:
            raise ValueError('report cutoff must follow ledger epoch')
        credits = [dict(x) for x in self.db.execute('SELECT * FROM credits') if x['at'] <= now]
        throughput = self.throughput(now, epoch, credits)
        gates = {}
        for gate in GATES:
            live = [x for x in credits if x['gate'] == gate and not x['revoked']]
            cumulative = [x for x in live if x['at'] >= epoch]
            def in_window(row, window, current=False):
                if row['at'] < epoch:
                    return False
                if current:
                    return window['start_inclusive'] <= row['at'] <= window['observed_until_inclusive']
                return window['start_inclusive'] <= row['at'] < window['end_exclusive']
            last_hour = throughput['windows']['last_hour']
            previous_hour = throughput['windows']['previous_hour']
            current_hour = throughput['current_incomplete_hour']
            original = sum(x['original_bytes'] for x in cumulative)
            gates[gate] = {'retained_functions':len(live), 'retained_original_bytes':sum(x['original_bytes'] for x in live),
                'window_original_bytes':original, 'window_generated_bytes':sum(x['generated_bytes'] for x in cumulative),
                'original_B_per_hour':original * 3600 / elapsed,
                'last_completed_hour_original_bytes':sum(x['original_bytes'] for x in live if in_window(x,last_hour)),
                'previous_completed_hour_original_bytes':sum(x['original_bytes'] for x in live if in_window(x,previous_hour)),
                'current_incomplete_hour_original_bytes':sum(x['original_bytes'] for x in live if in_window(x,current_hour,True)),
                'revoked_records':sum(x['gate'] == gate and bool(x['revoked']) for x in credits)}
        intervals, initial, first, open_intervals = [], [], {}, []
        unknown_first = {row['task_id'] for row in self.db.execute("SELECT task_id,payload FROM events WHERE kind='imported'")
                         if json.loads(row['payload']).get('legacy_state', 'ready') != 'ready'}
        observed_unknown = set()
        for row in self.db.execute("SELECT task_id,at,payload FROM events WHERE kind='round' ORDER BY seq"):
            if row['at'] > now:
                continue
            p = json.loads(row['payload'])
            if row['at'] >= epoch:
                (initial if p['interval_kind']=='initial_preparation' else intervals).append(p['interval_seconds'])
            if p['outcome'] != 'diagnostic':
                if row['task_id'] in unknown_first:
                    observed_unknown.add(row['task_id'])
                else:
                    first.setdefault(row['task_id'], p['outcome'])
        for t in self.db.execute("SELECT * FROM tasks WHERE state='active'"):
            if (t['last_round_at'] or t['started_at']) > now:
                continue
            open_intervals.append({'task':t['id'],'seconds':seconds(t['last_round_at'] or t['started_at'],now),
                                   'kind':'decision_open' if t['last_round_at'] else 'initial_preparation_open'})
        return {'as_of':now,'epoch':epoch,'elapsed_seconds':elapsed,'gates':gates,
            'throughput':throughput,
            'rounds':{'completed_decision_intervals':len(intervals),'median_seconds':statistics.median(intervals) if intervals else None,
                      'p90_seconds':sorted(intervals)[math.ceil(.9*len(intervals))-1] if intervals else None,
                      'initial_preparation_seconds':initial,'open_intervals':open_intervals,
                      'first_round_exact':sum(v=='exact' for v in first.values()),'first_round_methods':len(first),
                      'first_round_unknown_imported_methods':len(observed_unknown)},
            'legacy_events_uncredited':self.db.execute("SELECT count(*) FROM events WHERE kind='legacy'").fetchone()[0],
            'limits':['Gate totals are separate, not additive unique bytes.','Original envelopes include declared literals/alignment; unknown breakdown stays unknown.',
                      'Legacy events preserve history but do not create delivery credit or trusted round intervals.',
                      'Rates include all wall time since epoch, including failures, administration and gaps; no model speedup inference.']}

    def throughput(self, now, epoch, credits):
        """Occurrence-time windows from live credit; no inferred acceptance or actor hours."""
        live = [x for x in credits if not x['revoked']]
        delivery = live + [{**x, 'gate':'integrated_exact'} for x in live if x['gate']=='integrated' and any(
            y['gate']=='peer_exact' and y['module']==x['module'] and y['binary_sha256']==x['binary_sha256']
            for y in live)]
        rounds = [{**dict(x), 'payload':json.loads(x['payload'])} for x in self.db.execute(
            "SELECT task_id,actor,at,payload FROM events WHERE kind='round' AND at<=? ORDER BY seq", (now,))]
        unknown = {x['task_id'] for x in self.db.execute("SELECT task_id,payload FROM events WHERE kind='imported'")
                   if json.loads(x['payload']).get('legacy_state', 'ready') != 'ready'}
        first = {}
        for row in rounds:
            if row['task_id'] not in unknown and row['payload']['outcome'] != 'diagnostic':
                first.setdefault(row['task_id'], row)

        def implementer(credit):
            if credit['gate'].startswith('local_'):
                return credit['actor']
            actors = {x['actor'] for x in live if x['module'] == credit['module']
                      and x['binary_sha256'] == credit['binary_sha256'] and x['gate'].startswith('local_')}
            return next(iter(actors)) if len(actors) == 1 else 'unknown'

        def counts(rows, duration):
            original = sum(x['original_bytes'] for x in rows)
            return {'functions':len(rows), 'original_bytes':original,
                    'generated_bytes':sum(x['generated_bytes'] for x in rows),
                    'original_B_per_hour':original * 3600 / duration if duration else None}

        def latency(rows):
            values = [x['payload']['interval_seconds'] for x in rows
                      if x['payload']['interval_kind'] == 'decision']
            first_rows = [x for x in rows if first.get(x['task_id']) is x]
            return {'rounds':len(rows), 'completed_decision_intervals':len(values),
                    'median_seconds':statistics.median(values) if values else None,
                    'p90_seconds':sorted(values)[math.ceil(.9*len(values))-1] if values else None,
                    'initial_preparations':sum(x['payload']['interval_kind']=='initial_preparation' for x in rows),
                    'first_round_methods':len(first_rows),
                    'first_round_exact':sum(x['payload']['outcome']=='exact' for x in first_rows)}

        actors = sorted({x['actor'] for x in rounds} | {implementer(x) for x in live}
                        | {x['actor'] for x in self.db.execute("SELECT actor FROM tasks WHERE state='active'")})
        windows, current_window = completed_clock_windows(now, epoch)
        for name, window in windows.items():
            start, end = window['start_inclusive'], window['end_exclusive']
            duration = window['observed_seconds']
            inside = lambda at: at >= epoch and start <= at < end
            selected = [x for x in delivery if inside(x['at'])]
            selected_rounds = [x for x in rounds if inside(x['at'])]
            window.update({
                'gates':{g:counts([x for x in selected if x['gate']==g], duration) for g in DELIVERY_GATES},
                'rounds':latency(selected_rounds),
                'actors':{actor:{'gates':{g:counts([x for x in selected if x['gate']==g and implementer(x)==actor], duration)
                                         for g in DELIVERY_GATES},
                                 'rounds':latency([x for x in selected_rounds if x['actor']==actor])} for actor in actors}})
        changes = {}
        for gate in DELIVERY_GATES:
            recent = windows['last_hour']['gates'][gate]['original_B_per_hour']
            previous = windows['previous_hour']['gates'][gate]['original_B_per_hour']
            changes[gate] = {'rate_ratio':recent / previous if previous and recent is not None else None,
                             'comparable_full_hours':all(x['observed_seconds'] == 3600 for x in windows.values())}
        def pending(gate, next_gate):
            return [{'task':x['task_id'], 'module':x['module'], 'implementer':implementer(x),
                     'original_bytes':x['original_bytes'], 'waiting_seconds':seconds(x['at'], now)}
                    for x in live if x['gate']==gate and not any(
                        y['module']==x['module'] and y['binary_sha256']==x['binary_sha256'] and y['gate']==next_gate for y in live)]
        latest = {x['task_id']:x for x in rounds}
        missing = [{'task':task, 'actor':x['actor'], 'round_at':x['at']}
                   for task,x in latest.items() if x['payload']['outcome']=='exact'
                   and not any(y['task_id']==task and y['gate']=='local_exact' for y in live)]
        return {'windows':windows, 'current_incomplete_hour':current_window, 'change':changes,
                'pending_peer_exact':pending('local_exact', 'peer_exact'),
                'pending_integration_exact':pending('peer_exact', 'integrated'),
                'exact_rounds_without_local_credit':missing,
                'limits':['Only registered, non-revoked credits count; zero does not establish no unregistered output.',
                          'Backfills use occurred_at, not registration time. Current revocations restate both windows.',
                          'Actor delivery follows same-binary local implementer, never the peer reviewer or Git committer.',
                          'Rates use completed Asia/Shanghai clock hours with start-inclusive/end-exclusive bounds; partial first-observed hours are flagged and small samples are not speedup proof.',
                          'Latency includes whole intervals ending in the window, not clipped durations; first-round exactness is not acceptance.',
                          'Integrated_exact is the same-binary peer-exact subset of integrated, dated at integration; never add it to integrated.',
                          'Pending lists are gate gaps, not proven idle time.']}

    def report(self):
        self.db.execute('BEGIN')
        try:
            result = {'stats':self.stats(),'tasks':self.tasks(),'events':self.history(limit=200),
                      'commits':[json.loads(x['payload']) for x in self.db.execute('SELECT payload FROM commits ORDER BY recorded_at DESC LIMIT 100')]}
            self.db.commit(); return result
        except BaseException:
            self.db.rollback(); raise


def throughput_text(stats):
    data = stats['throughput']; recent = data['windows']['last_hour']; previous = data['windows']['previous_hour']
    number = lambda x: 'n/a' if x is None else f'{x:.1f}'
    lines = [f"Snapshot {stats['as_of']}",
             f"Completed clock hours ({recent['timezone']}): {recent['display']}; {previous['display']}",
             f"Observed minutes: last completed hour {recent['observed_seconds']/60:.1f}; previous completed hour {previous['observed_seconds']/60:.1f}",
             'Gate | last completed hour functions / B / B/h | previous completed B/h | rate ratio']
    for gate in DELIVERY_GATES:
        row = recent['gates'][gate]
        lines.append(f"{gate} | {row['functions']} / {row['original_bytes']} / {number(row['original_B_per_hour'])} | "
                     f"{number(previous['gates'][gate]['original_B_per_hour'])} | {number(data['change'][gate]['rate_ratio'])}")
    lines.append('Implementer | last completed hour local exact B / peer exact B / integrated B | decision median / p90 s')
    for actor, row in recent['actors'].items():
        lines.append(f"{actor} | " + ' / '.join(str(row['gates'][g]['original_bytes']) for g in ('local_exact','peer_exact','integrated'))
                     + f" | {number(row['rounds']['median_seconds'])} / {number(row['rounds']['p90_seconds'])}")
    rounds = recent['rounds']
    lines.append(f"Last completed hour decisions: {rounds['completed_decision_intervals']}; median {number(rounds['median_seconds'])}s; "
                 f"p90 {number(rounds['p90_seconds'])}s; first-round exact {rounds['first_round_exact']}/{rounds['first_round_methods']}")
    for key in ('pending_peer_exact','pending_integration_exact','exact_rounds_without_local_credit'):
        lines.append(f"{key}: {len(data[key])}")
    lines.extend(data['limits'])
    return '\n'.join(lines)


def render(report):
    esc = lambda x: html.escape(str(x), quote=True)
    def table(headers, rows):
        return '<table><thead><tr>' + ''.join('<th>'+esc(x)+'</th>' for x in headers) + '</tr></thead><tbody>' + ''.join('<tr>'+''.join('<td>'+esc(x)+'</td>' for x in row)+'</tr>' for row in rows) + '</tbody></table>'
    stats = report['stats']
    throughput = stats['throughput']; recent = throughput['windows']['last_hour']; previous = throughput['windows']['previous_hour']
    number = lambda x: 'unknown' if x is None else f'{x:.1f}'
    speed = table(['Gate','Last completed hour functions','Last completed hour original B','Generated B','Last completed B/h','Previous completed B/h','Rate ratio'],
        [(g,recent['gates'][g]['functions'],recent['gates'][g]['original_bytes'],recent['gates'][g]['generated_bytes'],
          number(recent['gates'][g]['original_B_per_hour']),number(previous['gates'][g]['original_B_per_hour']),
          number(throughput['change'][g]['rate_ratio'])) for g in DELIVERY_GATES])
    lanes = table(['Implementer','Local exact B','Peer exact B','Integrated C B','Decision samples','Median s','p90 s'],
        [(actor,*[row['gates'][g]['original_bytes'] for g in ('local_exact','peer_exact','integrated')],
          row['rounds']['completed_decision_intervals'],number(row['rounds']['median_seconds']),number(row['rounds']['p90_seconds']))
         for actor,row in recent['actors'].items()])
    iterations = table(['Window','Decision samples','Median s','p90 s','Initial preparations','First-round exact / methods'],
        [(w['display'],w['rounds']['completed_decision_intervals'],number(w['rounds']['median_seconds']),number(w['rounds']['p90_seconds']),
          w['rounds']['initial_preparations'],f"{w['rounds']['first_round_exact']} / {w['rounds']['first_round_methods']}")
         for name,w in throughput['windows'].items()])
    pending = table(['Gate gap','Task','Implementer','Original B','Elapsed minutes (not idle)'],
        [(key,x['task'],x['implementer'],x['original_bytes'],number(x['waiting_seconds']/60))
         for key in ('pending_peer_exact','pending_integration_exact') for x in throughput[key]])
    missing = table(['Exact round without local credit (not accepted)','Actor','Round time'],
                    [(x['task'],x['actor'],x['round_at']) for x in throughput['exact_rounds_without_local_credit']])
    gates = table(['Gate','Retained functions','Since-epoch original B','B/hour','Last completed hour B','Previous completed hour B'],
                  [(k,v['retained_functions'],v['window_original_bytes'],f"{v['original_B_per_hour']:.1f}",v['last_completed_hour_original_bytes'],v['previous_completed_hour_original_bytes']) for k,v in stats['gates'].items()])
    tasks = table(['Task','Module','State','Reservation','Actor','Original B'],[(x['id'],x['module'],x['state'],x['reservation'] or 'shared',x['actor'] or '',x['original_bytes']) for x in report['tasks']])
    event_rows = []
    for event in reversed(report['events']):
        p = event['payload']; legacy = event['kind'] == 'legacy'
        display = p.get('original', {}) if legacy else p
        summary = display.get('summary', display.get('decision', display.get('next_step', '')))
        cells = [event['at'],event['actor'],event['task_id'] or '',event['kind'],
                 display.get('round',''),display.get('outcome',display.get('status','')),
                 '' if legacy else display.get('interval_seconds',''),
                 display.get('generated_bytes',''),summary]
        event_rows.append('<tr>'+''.join('<td>'+esc(x)+'</td>' for x in cells)+
                          '<td><details><summary>Evidence / full record</summary><pre>'+esc(encode(p))+'</pre></details></td></tr>')
    events = '<table><thead><tr>'+''.join('<th>'+esc(x)+'</th>' for x in
        ['Time','Actor','Task','Kind','Round','Outcome','Interval s','Generated B','Decision','Evidence'])+'</tr></thead><tbody>'+''.join(event_rows)+'</tbody></table>'
    commits = table(['Commit','Git time','Subject','Tasks','Evidence'],[(x['sha'],x['committed_at'],x['subject'],', '.join(x['tasks']),encode(x['evidence'])) for x in report['commits']])
    return '''<!doctype html><html lang="en"><meta charset="utf-8"><meta name="viewport" content="width=device-width"><title>C recovery workflow</title>
<style>body{font:15px system-ui;margin:24px;color:#172334;background:#f6f8fb}h1{margin-bottom:8px}table{border-collapse:collapse;width:100%;background:white;margin:16px 0}th,td{padding:9px;border:1px solid #dde3eb;text-align:left;vertical-align:top}td{overflow-wrap:anywhere;max-width:700px}th{background:#e9eef5}input{padding:10px;width: min(600px,90%)}details{margin:16px 0}pre{white-space:pre-wrap}</style>
<h1>C recovery workflow</h1><p>Snapshot '''+esc(stats['as_of'])+''' — refresh with the report command. No background service.</p>
<p>Gate totals are separate. Legacy imports do not earn automatic credit. Envelope bytes include constants/alignment; independent evidence remains required.</p>
<label>Filter tasks, rounds and commits <input id="filter" placeholder="Task / actor / outcome / commit"></label>
<h2>Completed clock-hour production</h2><p>Timezone: '''+esc(recent['timezone'])+'. Bounds are start-inclusive and end-exclusive. '+esc(recent['display'])+'; '+esc(previous['display'])+'. Observed minutes: last completed hour '+number(recent['observed_seconds']/60)+', previous completed hour '+number(previous['observed_seconds']/60)+'. Partial first-observed hours are normalized to observed wall time. The current unfinished hour is excluded. Zero means no registered credit; gate totals are not additive.</p>'+speed+'<h2>Last completed hour by implementer</h2>'+lanes+'<h2>Iteration latency</h2>'+iterations+'<h2>Pending gates and registration gaps</h2>'+pending+missing+'<h2>Cumulative delivery</h2>'+gates+'<details><summary>Iteration metrics and accounting limits</summary><pre>'+esc(encode(stats))+'</pre></details><h2>Tasks</h2>'+tasks+'<h2>Git milestones</h2>'+commits+'<h2>Recent records (latest 200)</h2>'+events+'''
<script>document.getElementById('filter').addEventListener('input',e=>{const q=e.target.value.toLowerCase();document.querySelectorAll('tbody tr').forEach(r=>r.hidden=!r.textContent.toLowerCase().includes(q));});</script></html>'''


def atomic_write(path, content):
    path = Path(path); path.parent.mkdir(parents=True, exist_ok=True)
    fd, temporary = tempfile.mkstemp(prefix='.'+path.name+'.', dir=path.parent)
    try:
        with os.fdopen(fd,'w',encoding='utf-8') as stream:
            stream.write(content); stream.flush(); os.fsync(stream.fileno())
        os.replace(temporary,path)
    finally:
        if os.path.exists(temporary): os.unlink(temporary)


def parser():
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument('--db', help='SQLite path; otherwise FFTA_WORK_DB or ignored .local/recovery-workflow.json')
    sub = p.add_subparsers(dest='command',required=True)
    init = sub.add_parser('init'); init.add_argument('--epoch')
    for name in ('add','import-pool','claim','continue','record','finish','release','requeue','schedule','credit','revoke','commit','import-log','lease-claim','lease-release','coordination'):
        cmd = sub.add_parser(name); cmd.add_argument('--actor', required=name not in ('record','finish','release')); cmd.add_argument('--request-id')
        if name in ('add','import-pool','record','credit','import-log','continue'): cmd.add_argument('--file', required=name!='record')
        if name in ('claim','record','finish','release','requeue','schedule','credit','lease-claim'): cmd.add_argument('--task', required=name in ('requeue','schedule','credit'))
        if name in ('add','import-pool','claim','continue','credit','lease-release'):
            cmd.add_argument('--lease',help='Saved work-lease receipt; never a hand-written owner directory')
        if name == 'lease-claim':
            cmd.add_argument('--kind',choices=['source','peer'],required=True)
            cmd.add_argument('--rom-offset',type=lambda value:int(value,0))
            cmd.add_argument('--size',type=int)
            cmd.add_argument('--module')
            cmd.add_argument('--summary',required=True)
            cmd.add_argument('--gate',choices=['peer_exact','peer_semantic'],help='Peer gate; defaults to peer_exact')
            cmd.add_argument('--save',help='Atomically save the private lease/token receipt')
        if name == 'lease-release':
            cmd.add_argument('--lease-id');cmd.add_argument('--token');cmd.add_argument('--summary',required=True)
        if name == 'coordination':
            cmd.add_argument('--mode',choices=['required','compatible'],required=True)
            cmd.add_argument('--summary',required=True)
        if name == 'schedule':
            cmd.add_argument('--priority',type=int,required=True,help='Lower numbers are claimed first')
            cmd.add_argument('--expected-priority',type=int,required=True)
            cmd.add_argument('--expected-reservation',default=None)
            reservation = cmd.add_mutually_exclusive_group()
            reservation.add_argument('--reserve-for')
            reservation.add_argument('--clear-reservation',action='store_true')
        if name == 'claim': cmd.add_argument('--save',help='Atomically save the claim receipt for subsequent commands')
        if name == 'continue':
            cmd.add_argument('--owner',required=True,help='Implementation actor who will own the continued claim')
            cmd.add_argument('--save',help='Atomically save the continued claim receipt for subsequent commands')
        if name in ('record','finish','release'):
            cmd.add_argument('--token'); cmd.add_argument('--claim',help='Saved claim receipt supplies actor/task/token')
        if name == 'record':
            cmd.add_argument('--kind',choices=['round','progress'])
            cmd.add_argument('--round');cmd.add_argument('--outcome',choices=['exact','nonexact','unchanged','compile_failed','check_failed','diagnostic'])
            cmd.add_argument('--summary');cmd.add_argument('--generated-bytes',type=int);cmd.add_argument('--matching-bytes',type=int)
            cmd.add_argument('--evidence',action='append');cmd.add_argument('--next-action');cmd.add_argument('--binary-sha256')
        if name in ('finish','release','requeue','schedule','revoke'): cmd.add_argument('--summary',required=True)
        if name=='finish': cmd.add_argument('--state',choices=['frozen','blocked'],default='frozen'); cmd.add_argument('--evidence',action='append',default=[])
        if name=='requeue':
            cmd.add_argument('--expected-state',required=True); cmd.add_argument('--expected-token',default=None)
            cmd.add_argument('--reserve-for',help='Reserve atomically before any actor can claim')
            cmd.add_argument('--priority',type=int,help='Optional lower-number-first runtime priority')
        if name=='revoke': cmd.add_argument('--credit-id',type=int,required=True)
        if name=='commit':
            cmd.add_argument('--sha',required=True);cmd.add_argument('--tasks',nargs='+',required=True)
            cmd.add_argument('--evidence',action='append',required=True);cmd.add_argument('--repo',default=str(ROOT))
    show = sub.add_parser('status');show.add_argument('--actor');show.add_argument('--json',action='store_true')
    leases = sub.add_parser('leases');leases.add_argument('--json',action='store_true')
    audit = sub.add_parser('coordination-audit');audit.add_argument('--json',action='store_true')
    audit.add_argument('--require-mode',choices=['required','compatible'])
    hist = sub.add_parser('history');hist.add_argument('--task');hist.add_argument('--limit',type=int,default=50)
    sub.add_parser('stats')
    speed = sub.add_parser('throughput');speed.add_argument('--json', action='store_true')
    public = sub.add_parser('public-export');public.add_argument('--public-dir',required=True);public.add_argument('--mapping',required=True);public.add_argument('--output-dir',required=True)
    public.add_argument('--baseline',help='Pinned private integrated accounting registry for the unified dashboard'); public.add_argument('--migration-attribution',help='Pinned private source/range attribution proof; raw gate counts stay unchanged')
    publish = sub.add_parser('publish');publish.add_argument('--config',required=True)
    rep = sub.add_parser('report');rep.add_argument('--format',choices=['html','json'],default='html');rep.add_argument('--output')
    return p


def main(argv=None):
    args = vars(parser().parse_args(argv)); command=args.pop('command'); path=args.pop('db')
    if not path:
        path=os.environ.get('FFTA_WORK_DB')
        config=ROOT/'.local/recovery-workflow.json'
        if not path and config.exists():path=load_json(config)['db']
    if not path:raise ValueError('specify --db or configure FFTA_WORK_DB/.local/recovery-workflow.json')
    # Check before opening/mutating the ledger, not after committing a claim.
    if args.get('save') and Path(args['save']).resolve() == Path(path).resolve():
        raise ValueError('claim/lease receipt cannot overwrite database')
    ledger=Ledger(path,initialize=command=='init',epoch=args.get('epoch'))
    try:
        if command=='init':result={'ok':True,'db':str(ledger.path),'schema':SCHEMA}
        elif command=='status':
            rows=ledger.tasks(args['actor'])
            if not args['json']:
                print('TASK\tSTATE\tOWNER\tMODULE\tORIGINAL_B')
                for x in rows:print('\t'.join(str(v) for v in [x['id'],x['state'],x['actor'] or x['reservation'] or 'shared',x['module'],x['original_bytes']]))
                return 0
            result=rows
        elif command=='history':result=ledger.history(args['task'],args['limit'])
        elif command=='coordination-audit':
            result=ledger.coordination_audit()
            if args['require_mode'] and result['mode'] != args['require_mode']:
                result.update(ok=False, error='required coordination mode is not enabled')
        elif command=='leases':
            result=ledger.leases()
            if not args['json']:
                print('LEASE\tKIND\tACTOR\tROM_OFFSET\tSIZE\tTASK')
                for row in result:
                    print('\t'.join(str(row.get(k) or '') for k in ('id','kind','actor','rom_offset','size','task_id')))
                return 0
        elif command in ('public-export','publish'):
            import recovery_public
            if command=='publish':result=recovery_public.publish(ledger,load_json(args['config']))
            else:
                files=recovery_public.public_files(ledger,args['public_dir'],load_json(args['mapping']),load_json(args['baseline']) if args['baseline'] else None,load_json(args['migration_attribution']) if args['migration_attribution'] else None)
                for name,content in files.items():atomic_write(Path(args['output_dir'])/name,content)
                result={'ok':True,'files':list(files),'output_dir':args['output_dir']}
        elif command in ('stats','throughput'):
            ledger.db.execute('BEGIN')
            result=ledger.stats();ledger.db.commit()
            if command=='throughput' and not args['json']:
                print(throughput_text(result));return 0
        elif command=='report':
            result=ledger.report();content=render(result) if args['format']=='html' else json.dumps(result,indent=2,ensure_ascii=False)
            if args['output']:
                if Path(args['output']).resolve() == Path(path).resolve():raise ValueError('report cannot overwrite database')
                atomic_write(args['output'],content);result={'ok':True,'output':args['output']}
            else:print(content);return 0
        else:
            actor=args.pop('actor');key=args.pop('request_id');filename=args.pop('file',None)
            claim_path=args.pop('claim',None);save=args.pop('save',None)
            lease_path=args.pop('lease',None)
            if lease_path:
                leased=load_json(lease_path).get('lease')
                if not isinstance(leased, dict) or not leased.get('id') or not leased.get('token'):
                    raise ValueError('saved receipt contains no work lease')
                if command == 'lease-release':
                    for field, value in (('lease_id',leased['id']),('token',leased['token'])):
                        if args.get(field) and args[field] != value:
                            raise ValueError('lease identity conflicts with CLI')
                        args[field]=value
                else:
                    args['work_lease']={'id':leased['id'],'token':leased['token']}
            if command == 'record':args={k:v for k,v in args.items() if v is not None}
            if claim_path:
                claimed=load_json(claim_path).get('task')
                if not claimed:raise ValueError('saved claim contains no task')
                if actor and actor != claimed['actor']:raise ValueError('claim actor conflicts with CLI')
                actor=claimed['actor']
                for field in ('task','token'):
                    value=claimed['id'] if field=='task' else claimed['token']
                    if args.get(field) and args[field] != value:raise ValueError('claim identity conflicts with CLI')
                    args[field]=value
            if command in ('record','finish','release') and (not actor or not args.get('task') or not args.get('token')):
                raise ValueError('provide --claim or all of --actor/--task/--token')
            if filename:
                if command=='import-log':
                    records=[];malformed=[]
                    for n,line in enumerate(Path(filename).read_text().splitlines(),1):
                        try:records.append(json.loads(line))
                        except ValueError:malformed.append(n)
                    args.update(records=records,malformed_lines=malformed,source=evidence([filename])[0])
                elif command in ('add','import-pool'):args.update(document=load_json(filename),source=evidence([filename])[0])
                elif command == 'continue':
                    packet=load_json(filename)
                    args.update(task=packet.get('task_id'), summary=packet.get('summary'), continuation_packet=packet)
                else:
                    payload=load_json(filename)
                    if any(k in payload for k in ('task','token','actor','request_id')):raise ValueError('identity fields belong in CLI arguments')
                    args.update(payload)
            if key is None and (command in ('finish','release') or (command=='record' and args.get('kind','round')=='round')):
                key=hashlib.sha256(encode([command,actor,args]).encode()).hexdigest()
            result=ledger.mutate(command,actor,args,key)
            if command in ('finish','credit','revoke','commit'):
                from recovery_publish_queue import after_mutation
                after_mutation(path, command)
            if save:
                if Path(save).resolve() == Path(path).resolve():raise ValueError('claim receipt cannot overwrite database')
                atomic_write(save,json.dumps(result,indent=2,ensure_ascii=False)+'\n')
        print(json.dumps(result,indent=2,ensure_ascii=False,allow_nan=False))
        return 1 if command=='coordination-audit' and not result['ok'] else 0
    finally:ledger.close()


if __name__=='__main__':
    try:sys.exit(main())
    except (ValueError,TypeError,KeyError,OSError,sqlite3.Error,subprocess.SubprocessError) as exc:
        print(json.dumps({'ok':False,'error':str(exc)},ensure_ascii=False),file=sys.stderr);sys.exit(1)
