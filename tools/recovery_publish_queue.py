#!/usr/bin/env python3
"""Coalesced, opt-in public data publication after committed ledger mutations."""
from __future__ import annotations
import argparse
from contextlib import contextmanager
import fcntl
import json
import os
from pathlib import Path
import subprocess
import sys
import time

import recovery_workflow as wf

TRIGGERS = frozenset(('finish', 'credit', 'revoke', 'commit'))


@contextmanager
def locked(path):
    with path.open('a') as handle:
        fcntl.flock(handle, fcntl.LOCK_EX)
        yield handle


def read_state(work):
    path = work / 'queue.json'
    return json.loads(path.read_text()) if path.exists() else {'generation': 0, 'completed': 0}


def write_state(work, state):
    wf.atomic_write(work / 'queue.json', json.dumps(state, indent=2) + '\n')


def settings(config_path, db):
    config = wf.load_json(config_path)
    auto = config.get('automatic_publication', {})
    if not auto.get('enabled') or Path(config['db']).resolve() != Path(db).resolve():
        return None
    public_path = Path(auto['config'])
    if not public_path.is_absolute():
        public_path = wf.ROOT / public_path
    public_path = public_path.resolve()
    public = wf.load_json(public_path)
    work = Path(public['work_dir']).resolve() / 'automatic'
    work.mkdir(parents=True, exist_ok=True)
    debounce = float(auto.get('debounce_seconds', 30))
    if not 0 <= debounce <= 300:
        raise ValueError('publication debounce must be between 0 and 300 seconds')
    return public_path, work, debounce


def enqueue(db, operation, config_path=None, launch=True):
    """Persist first, then launch a detached drainer. Never access Git here."""
    if operation not in TRIGGERS and operation != 'sync':
        return None
    config_path = Path(config_path or wf.ROOT / '.local/recovery-workflow.json').resolve()
    if not config_path.exists():
        return None
    configured = settings(config_path, db)
    if configured is None:
        return None
    _, work, _ = configured
    with locked(work / 'queue.lock'):
        state = read_state(work)
        if state['generation'] == state['completed']:
            state['first_pending_at'] = time.time()
        state['generation'] += 1
        state.update(last_requested_at=time.time(), last_operation=operation)
        write_state(work, state)
        if launch:
            with (work / 'worker.log').open('ab') as log:
                subprocess.Popen([sys.executable, str(Path(__file__).resolve()), 'drain',
                                  '--workflow-config', str(config_path), '--db', str(Path(db).resolve())],
                                 stdin=subprocess.DEVNULL, stdout=log, stderr=log,
                                 start_new_session=True, close_fds=True, cwd=wf.ROOT)
    return {'status': 'queued', 'generation': state['generation']}


def after_mutation(db, operation, config_path=None):
    """Publication errors must not change the outcome of a committed task event."""
    try:
        return enqueue(db, operation, config_path)
    except Exception as exc:
        print(json.dumps({'automatic_publication': 'enqueue_failed', 'error': str(exc)}), file=sys.stderr)
        return None


def drain(db, config_path, publish=None, sleep=time.sleep):
    configured = settings(config_path, db)
    if configured is None:
        return {'status': 'disabled'}
    public_path, work, debounce = configured
    if publish is None:
        from recovery_public import publish
    with (work / 'worker.lock').open('a') as owner:
        try:
            fcntl.flock(owner, fcntl.LOCK_EX | fcntl.LOCK_NB)
        except BlockingIOError:
            return {'status': 'already_running'}
        failures = 0
        while True:
            with locked(work / 'queue.lock'):
                state = read_state(work)
                if state['generation'] == state['completed']:
                    # Release ownership before the queue lock: a new enqueuer cannot
                    # lose its wakeup to an exiting owner.
                    fcntl.flock(owner, fcntl.LOCK_UN)
                    return {'status': 'drained', 'generation': state['completed']}
                target = state['generation']
                delay = max(0, state['first_pending_at'] + debounce - time.time())
            if delay:
                sleep(delay)
                continue
            started = time.time()
            ledger = None
            try:
                ledger = wf.Ledger(db)
                result = publish(ledger, wf.load_json(public_path))
                if result.get('status') not in ('published', 'unchanged'):
                    raise RuntimeError('publisher returned ' + str(result.get('status')))
                error = None
            except Exception as exc:
                result, error = None, str(exc)
            finally:
                if ledger is not None:
                    ledger.close()
            with locked(work / 'queue.lock'):
                state = read_state(work)
                state['last_attempt'] = {'generation': target, 'started_at': started,
                                         'finished_at': time.time(), 'result': result, 'error': error}
                if error is None:
                    state['completed'] = target
                    failures = 0
                    if state['generation'] > target:
                        state['first_pending_at'] = time.time()
                else:
                    failures += 1
                write_state(work, state)
                if failures >= 3:
                    # Keep the pending generation. A new submission or explicit
                    # sync retries it; failed publication never loses a task event.
                    fcntl.flock(owner, fcntl.LOCK_UN)
                    return {'status': 'pending_retry', 'error': error}
            if error:
                sleep(15 * failures)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('operation', choices=('enqueue', 'drain', 'status'))
    parser.add_argument('--workflow-config', default=str(wf.ROOT / '.local/recovery-workflow.json'))
    parser.add_argument('--db')
    args = parser.parse_args()
    db = args.db or wf.load_json(args.workflow_config)['db']
    if args.operation == 'enqueue':
        result = enqueue(db, 'sync', args.workflow_config)
    elif args.operation == 'drain':
        result = drain(db, args.workflow_config)
    else:
        config = settings(args.workflow_config, db)
        if config:
            with locked(config[1] / 'queue.lock'):
                result = read_state(config[1])
        else:
            result = {'status': 'disabled'}
    print(json.dumps(result, indent=2))


if __name__ == '__main__':
    main()
