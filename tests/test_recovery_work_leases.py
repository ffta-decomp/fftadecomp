"""Work-lease API checks using temporary ledgers and real spawned processes.

Only public mutations arrange state, except the additive-migration fixture,
which removes new tables from an isolated DB to reproduce the legacy schema.
No project ledger, compiler, or game input is used.
"""
import concurrent.futures
import json
import hashlib
import multiprocessing
from pathlib import Path
import sqlite3
import subprocess
import sys
import tempfile
import time
import unittest

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools'))
import recovery_workflow as wf


def _mutate_process(db, actor, operation, data, barrier):
    ledger = wf.Ledger(db)
    try:
        barrier.wait(timeout=20)
        try:
            return ledger.mutate(operation, actor, data)
        except ValueError as error:
            return {'rejected': str(error)}
    finally:
        ledger.close()


def _promote_process(db, task, lease, probing, promoted):
    ledger = wf.Ledger(db)
    try:
        if not probing.wait(timeout=20):
            raise AssertionError('competitor never observed discovery ownership')
        result = ledger.mutate('claim', 'owner', {
            'task': task, 'work_lease': {'id': lease['id'], 'token': lease['token']}})
        if not result.get('task'):
            raise AssertionError('owner promotion failed')
        promoted.set()
        return result
    finally:
        ledger.close()


def _probe_transition_process(db, probing, promoted):
    ledger = wf.Ledger(db)
    try:
        observations = []
        deadline = time.monotonic() + 20
        while time.monotonic() < deadline:
            after = promoted.is_set()
            result = ledger.mutate('lease-claim', 'contender', {
                'kind': 'source', 'rom_offset': 0x1008, 'size': 8,
                'module': 'different-module', 'summary': 'atomic transition probe'})
            if result.get('lease') is not None:
                raise AssertionError('ownership gap exposed during promotion')
            if 'token' in json.dumps(result.get('busy')):
                raise AssertionError('busy result leaked a token')
            observations.append('native' if after else 'discovery')
            probing.set()
            if after:
                return observations
            time.sleep(0.001)
        raise AssertionError('promotion was not observed within bounded probe')
    finally:
        ledger.close()


class WorkLeaseTests(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory()
        self.root = Path(self.temp.name)
        self.db = self.root / 'ledger.sqlite3'
        self.ledger = wf.Ledger(self.db, initialize=True,
                                epoch='2026-01-01T00:00:00Z')
        self.evidence = self.root / 'proof.json'
        self.evidence.write_text('{"passed":true}')
        self.binary = self.root / 'method.bin'
        self.binary.write_bytes(bytes(16))

    def tearDown(self):
        self.ledger.close()
        self.temp.cleanup()

    def add(self, ident='native', offset=0x1000, size=16, **data):
        spec = {'task_id': ident, 'module': ident, 'rom_offset': offset,
                'original_span_bytes': size}
        return self.ledger.mutate('add', 'administrator',
                                  {'document': spec, **data})

    def source(self, actor='owner', offset=0x1000, size=16, module='source'):
        return self.ledger.mutate('lease-claim', actor, {
            'kind': 'source', 'rom_offset': offset, 'size': size,
            'module': module, 'summary': 'source qualification'})

    def release(self, lease, actor='owner', token=None):
        return self.ledger.mutate('lease-release', actor, {
            'lease_id': lease['id'],
            'token': lease['token'] if token is None else token,
            'summary': 'qualification complete'})

    def assert_busy(self, result):
        self.assertIsNone(result.get('lease'))
        self.assertTrue(result.get('busy'))
        self.assertNotIn('token', json.dumps(result['busy']))

    def assert_claim_blocked(self, actor, task='native', **data):
        try:
            result = self.ledger.mutate('claim', actor, {'task': task, **data})
        except ValueError:
            return
        self.assertIsNone(result.get('task'))

    def frozen_local(self, ident='native', offset=0x1000):
        self.add(ident, offset)
        task = self.ledger.mutate('claim', 'producer', {'task': ident})['task']
        self.ledger.mutate('credit', 'producer', {
            'task': ident, 'gate': 'local_exact', 'binary': str(self.binary),
            'evidence': [str(self.evidence)]})
        self.ledger.mutate('finish', 'producer', {
            'task': ident, 'token': task['token'], 'state': 'frozen',
            'summary': 'complete local proof'})
        return task

    def race(self, requests):
        context = multiprocessing.get_context('spawn')
        with context.Manager() as manager:
            barrier = manager.Barrier(len(requests))
            with concurrent.futures.ProcessPoolExecutor(
                    max_workers=len(requests), mp_context=context) as pool:
                futures = [pool.submit(_mutate_process, str(self.db), actor,
                                       operation, data, barrier)
                           for actor, operation, data in requests]
                return [future.result(timeout=40) for future in futures]

    def test_same_actor_exact_range_reentry_preserves_identity_and_token(self):
        first = self.source()['lease']
        again = self.source(module='renamed-alias')
        self.assertTrue(again['resumed'])
        for key in ('id', 'token', 'actor', 'kind', 'rom_offset', 'size'):
            self.assertEqual(first[key], again['lease'][key])
        self.assert_busy(self.source('other', offset=0x100F, size=1))

    def test_release_owner_and_token_validation_and_stale_token(self):
        lease = self.source()['lease']
        with self.assertRaises(ValueError):
            self.release(lease, actor='third-party')
        with self.assertRaises(ValueError):
            self.release(lease, token='incorrect')
        self.assert_busy(self.source('other'))
        self.release(lease)
        fresh = self.source()['lease']
        self.assertNotEqual(fresh['token'], lease['token'])
        with self.assertRaises(ValueError):
            self.release(lease)
        self.assert_busy(self.source('other'))

    def test_true_multiprocess_identical_range_different_modules_one_winner(self):
        requests = [(f'actor-{i}', 'lease-claim', {
            'kind': 'source', 'rom_offset': 0x2000, 'size': 32,
            'module': f'unrelated-module-{i}', 'summary': 'race'})
                    for i in range(4)]
        results = self.race(requests)
        self.assertEqual(sum(bool(r.get('lease')) for r in results), 1)
        for result in results:
            if not result.get('lease'):
                self.assert_busy(result)

    def test_true_multiprocess_partial_overlap_is_not_module_scoped(self):
        results = self.race([
            ('left', 'lease-claim', {'kind': 'source', 'rom_offset': 0x2000,
             'size': 32, 'module': 'left', 'summary': 'partial overlap'}),
            ('right', 'lease-claim', {'kind': 'source', 'rom_offset': 0x2010,
             'size': 32, 'module': 'right', 'summary': 'partial overlap'})])
        self.assertEqual(sum(bool(r.get('lease')) for r in results), 1)
        self.assert_busy(next(r for r in results if not r.get('lease')))

    def test_true_multiprocess_disjoint_and_adjacent_ranges_can_coexist(self):
        results = self.race([
            ('left', 'lease-claim', {'kind': 'source', 'rom_offset': 0x2000,
             'size': 16, 'module': 'same-label', 'summary': 'adjacent'}),
            ('right', 'lease-claim', {'kind': 'source', 'rom_offset': 0x2010,
             'size': 16, 'module': 'same-label', 'summary': 'adjacent'}),
            ('far', 'lease-claim', {'kind': 'source', 'rom_offset': 0x9000,
             'size': 16, 'summary': 'disjoint'})])
        self.assertTrue(all(r.get('lease') for r in results), results)

    def test_invalid_source_ranges_are_rejected(self):
        for offset, size in ((-1, 16), (0x1000, 0), (0x1000, -1),
                             ('4096', 16), (0x1000, 1.5), (True, 16)):
            with self.subTest(offset=offset, size=size):
                with self.assertRaises(ValueError):
                    self.source(offset=offset, size=size)

    def test_true_multiprocess_peer_review_has_one_owner(self):
        self.frozen_local()
        results = self.race([(f'reviewer-{i}', 'lease-claim', {
            'kind': 'peer', 'task': 'native', 'summary': 'peer race'})
                             for i in range(3)])
        self.assertEqual(sum(bool(r.get('lease')) for r in results), 1)
        for result in results:
            if not result.get('lease'):
                self.assert_busy(result)

    def test_active_native_blocks_new_source_and_legacy_claim_still_works(self):
        self.add()
        task = self.ledger.mutate('claim', 'legacy', {'task': 'native'})['task']
        self.assertEqual(task['actor'], 'legacy')
        self.assert_busy(self.source('discoverer', offset=0x1008, size=1))
        self.assertTrue(self.source('independent', offset=0x1010, size=1)['lease'])

    def test_native_claim_requires_own_lease_correct_token_and_consumes_it(self):
        self.add()
        lease = self.source()['lease']
        self.assert_claim_blocked('other')
        self.assert_claim_blocked('owner')
        self.assert_claim_blocked('owner', work_lease={
            'id': lease['id'], 'token': 'wrong'})
        self.assert_busy(self.source('third'))
        task = self.ledger.mutate('claim', 'owner', {
            'task': 'native', 'work_lease': {
                'id': lease['id'], 'token': lease['token']}})['task']
        self.assertEqual(task['actor'], 'owner')
        with self.assertRaises(ValueError):
            self.release(lease)
        self.assert_busy(self.source('other'))

    def test_add_rejects_others_overlap_and_accepts_own_pinned_source(self):
        lease = self.source()['lease']
        with self.assertRaises(ValueError):
            self.add('other-module', offset=0x1008)
        self.assertIsNone(self.ledger.db.execute(
            'SELECT id FROM tasks WHERE id=?', ('other-module',)).fetchone())
        self.release(lease)
        own = self.source('administrator')['lease']
        with self.assertRaises(ValueError):
            self.add(work_lease={'id': own['id'], 'token': 'wrong'})
        result = self.add(work_lease={'id': own['id'], 'token': own['token']})
        self.assertIn('native', result['added'])
        # Add alone cannot open the discover→claim gap.
        self.assert_busy(self.source('third'))
        task = self.ledger.mutate('claim', 'administrator', {
            'task': 'native', 'work_lease': {
                'id': own['id'], 'token': own['token']}})['task']
        self.assertEqual(task['actor'], 'administrator')

    def test_peer_requires_frozen_nonrevoked_local_exact_and_nonproducer(self):
        self.add()
        with self.assertRaises(ValueError):
            self.ledger.mutate('lease-claim', 'reviewer', {
                'kind': 'peer', 'task': 'native', 'summary': 'not frozen'})
        task = self.ledger.mutate('claim', 'producer', {'task': 'native'})['task']
        self.ledger.mutate('credit', 'producer', {
            'task': 'native', 'gate': 'local_exact', 'binary': str(self.binary),
            'evidence': [str(self.evidence)]})
        with self.assertRaises(ValueError):
            self.ledger.mutate('lease-claim', 'reviewer', {
                'kind': 'peer', 'task': 'native', 'summary': 'active producer'})
        self.ledger.mutate('finish', 'producer', {
            'task': 'native', 'token': task['token'], 'state': 'frozen',
            'summary': 'freeze'})
        with self.assertRaises(ValueError):
            self.ledger.mutate('lease-claim', 'producer', {
                'kind': 'peer', 'task': 'native', 'summary': 'self review'})
        result = self.ledger.mutate('lease-claim', 'reviewer', {
            'kind': 'peer', 'task': 'native', 'summary': 'independent'})
        lease = result['lease']
        self.assertEqual((lease['kind'], lease['rom_offset'], lease['size']),
                         ('peer', 0x1000, 16))
        self.assert_busy(self.source('discoverer', offset=0x100F, size=1))
        again = self.ledger.mutate('lease-claim', 'reviewer', {
            'kind': 'peer', 'task': 'native', 'summary': 'resume'})
        self.assertTrue(again['resumed'])
        self.assertEqual(again['lease']['token'], lease['token'])

    def test_frozen_without_local_or_with_revoked_local_is_not_peer_ready(self):
        self.add()
        task = self.ledger.mutate('claim', 'producer', {'task': 'native'})['task']
        self.ledger.mutate('finish', 'producer', {
            'task': 'native', 'token': task['token'], 'state': 'frozen',
            'summary': 'source contract only'})
        with self.assertRaises(ValueError):
            self.ledger.mutate('lease-claim', 'reviewer', {
                'kind': 'peer', 'task': 'native', 'summary': 'no exact proof'})
        self.frozen_local('with-credit', offset=0x2000)
        credit = self.ledger.db.execute(
            "SELECT id FROM credits WHERE task_id='with-credit' "
            "AND gate='local_exact'").fetchone()[0]
        self.ledger.mutate('revoke', 'administrator', {
            'credit_id': credit, 'summary': 'synthetic invalid proof'})
        with self.assertRaises(ValueError):
            self.ledger.mutate('lease-claim', 'reviewer', {
                'kind': 'peer', 'task': 'with-credit', 'summary': 'revoked proof'})

    def test_peer_and_source_conflict_in_both_directions(self):
        self.frozen_local()
        source = self.source()['lease']
        self.assert_busy(self.ledger.mutate('lease-claim', 'reviewer', {
            'kind': 'peer', 'task': 'native', 'summary': 'source busy'}))
        self.release(source)
        peer = self.ledger.mutate('lease-claim', 'reviewer', {
            'kind': 'peer', 'task': 'native', 'summary': 'independent'})['lease']
        self.assert_busy(self.source())
        with self.assertRaises(ValueError):
            self.add('overlapping-peer', offset=0x1008)
        self.release(peer, actor='reviewer')

    def test_true_process_promotion_has_no_discovery_to_native_gap(self):
        self.add()
        lease = self.source()['lease']
        context = multiprocessing.get_context('spawn')
        with context.Manager() as manager:
            probing, promoted = manager.Event(), manager.Event()
            with concurrent.futures.ProcessPoolExecutor(
                    max_workers=2, mp_context=context) as pool:
                probe = pool.submit(_probe_transition_process, str(self.db),
                                    probing, promoted)
                owner = pool.submit(_promote_process, str(self.db), 'native',
                                    lease, probing, promoted)
                self.assertEqual(owner.result(timeout=40)['task']['actor'], 'owner')
                observations = probe.result(timeout=40)
                self.assertIn('discovery', observations)
                self.assertIn('native', observations)

    def test_required_mode_rejects_bypass_and_accepts_complete_lease_chain(self):
        self.frozen_local('peer-target', offset=0x6000)
        self.add('ready-before-required', offset=0x3000)
        self.ledger.mutate('coordination', 'administrator', {
            'mode': 'required', 'summary': 'enable coordination contract'})
        with self.assertRaisesRegex(ValueError, 'lease'):
            self.add('no-source', offset=0x8000)
        self.assert_claim_blocked('unleased', task='ready-before-required')
        peer_credit = {'task': 'peer-target', 'gate': 'peer_exact',
                       'binary': str(self.binary), 'evidence': [str(self.evidence)]}
        with self.assertRaisesRegex(ValueError, 'lease'):
            self.ledger.mutate('credit', 'reviewer', peer_credit)
        peer = self.ledger.mutate('lease-claim', 'reviewer', {
            'kind': 'peer', 'task': 'peer-target', 'summary': 'required peer'})['lease']
        credited = self.ledger.mutate('credit', 'reviewer', {
            **peer_credit, 'work_lease': {'id': peer['id'], 'token': peer['token']}})
        self.assertEqual(credited['gate'], 'peer_exact')
        self.release(peer, actor='reviewer')
        source = self.source('implementer', offset=0x8000)['lease']
        pin = {'id': source['id'], 'token': source['token']}
        self.add('leased-new', offset=0x8000, work_lease=pin)
        task = self.ledger.mutate('claim', 'implementer', {
            'task': 'leased-new', 'work_lease': pin})['task']
        self.assertEqual(task['actor'], 'implementer')

    def test_required_continue_checks_lease_after_valid_pinned_admission(self):
        pin = {'path': str(self.evidence),
               'sha256': hashlib.sha256(self.evidence.read_bytes()).hexdigest()}
        hypotheses = [{'id': 'previous-source-family'}]
        spec = {'task_id': 'continuation', 'module': 'ContinuationModule',
                'rom_offset': 0x7000, 'original_span_bytes': 16,
                'thumb_entry': '0x08007001',
                'original_reference_span_sha256': 'a' * 64,
                'original_source': pin, 'hypotheses': hypotheses}
        self.ledger.mutate('add', 'administrator', {'document': spec})
        original = self.ledger.mutate('claim', 'previous-owner', {
            'task': 'continuation'})['task']
        self.ledger.mutate('finish', 'previous-owner', {
            'task': 'continuation', 'token': original['token'],
            'state': 'blocked', 'summary': 'known source-family blocker'})
        self.ledger.mutate('coordination', 'administrator', {
            'mode': 'required', 'summary': 'test continuation ownership'})
        frozen = self.ledger.task('continuation')
        history = [dict(row) for row in self.ledger.db.execute(
            'SELECT seq,at,actor,kind,payload FROM events '
            "WHERE task_id='continuation' ORDER BY seq")]
        identity = {'task_id': 'continuation', 'module': 'ContinuationModule',
                    'original_span_bytes': 16,
                    **{k: spec[k] for k in (
                        'rom_offset', 'thumb_entry',
                        'original_reference_span_sha256', 'original_source')}}
        packet = {
            'task_id': 'continuation', 'expected_state': 'blocked',
            'expected_token': frozen['token'] or '', 'native_identity': identity,
            'canonical_started_at': original['started_at'],
            'prior_hypotheses_sha256': hashlib.sha256(
                wf.encode(hypotheses).encode()).hexdigest(),
            'prior_event_count': len(history),
            'prior_event_sha256': hashlib.sha256(wf.encode(history).encode()).hexdigest(),
            'continuation_index': 1, 'full_method_percent': 80,
            'terminal_state': {key: False for key in (
                'complete', 'unknown', 'exhausted', 'native_duplicate')},
            'effective_matching_causes': 0,
            'budgets': [{'hypothesis_id': 'previous-source-family', 'known': True,
                         'attempts_used': 0, 'attempt_limit': 3}],
            'new_original_asm_cause': {'kind': 'original_asm',
                                      'cause_id': 'new-source-cause', 'evidence': [pin]},
            'full_method_evidence': [pin]}
        data = {'task': 'continuation', 'owner': 'next_owner',
                'continuation_packet': packet, 'summary': 'pinned continuation'}
        with self.assertRaisesRegex(ValueError, 'lease'):
            self.ledger.mutate('continue', 'administrator', data)
        lease = self.source('next_owner', offset=0x7000)['lease']
        result = self.ledger.mutate('continue', 'administrator', {
            **data, 'work_lease': {'id': lease['id'], 'token': lease['token']}})
        self.assertEqual(result['task']['actor'], 'next_owner')
        self.assertEqual(result['task']['started_at'], original['started_at'])
        with self.assertRaises(ValueError):
            self.release(lease, actor='next_owner')

    def test_required_mode_does_not_strand_preexisting_active_native(self):
        self.add()
        task = self.ledger.mutate('claim', 'legacy', {'task': 'native'})['task']
        self.ledger.mutate('coordination', 'administrator', {
            'mode': 'required', 'summary': 'do not interrupt existing owner'})
        self.ledger.mutate('record', 'legacy', {
            'task': 'native', 'token': task['token'], 'round': 'legacy-closeout',
            'outcome': 'exact', 'summary': 'existing work completes',
            'generated_bytes': 16, 'matching_bytes': 16,
            'evidence': [str(self.evidence)]})
        self.ledger.mutate('credit', 'legacy', {
            'task': 'native', 'gate': 'local_exact', 'binary': str(self.binary),
            'evidence': [str(self.evidence)]})
        self.ledger.mutate('finish', 'legacy', {
            'task': 'native', 'token': task['token'], 'state': 'frozen',
            'summary': 'legacy safe boundary'})
        final = self.ledger.task('native')
        self.assertEqual(final['state'], 'frozen')
        self.assertEqual(final['started_at'], task['started_at'])

    def test_released_source_request_id_cannot_replay_old_token(self):
        data = {'kind': 'source', 'rom_offset': 0x1000, 'size': 16,
                'summary': 'original source request'}
        lease = self.ledger.mutate('lease-claim', 'owner', data,
                                   request_id='old-source-request')['lease']
        self.release(lease)
        other = self.source('replacement')['lease']
        try:
            replay = self.ledger.mutate('lease-claim', 'owner', data,
                                        request_id='old-source-request')
        except ValueError:
            pass
        else:
            self.assertIsNone(replay.get('lease'))
            self.assertNotIn(lease['token'], json.dumps(replay))
        again = self.source('replacement')
        self.assertTrue(again['resumed'])
        self.assertEqual(again['lease']['token'], other['token'])

    def test_finished_native_request_id_cannot_replay_old_claim_token(self):
        self.add()
        data = {'task': 'native'}
        task = self.ledger.mutate('claim', 'old-owner', data,
                                  request_id='old-native-request')['task']
        self.ledger.mutate('finish', 'old-owner', {
            'task': 'native', 'token': task['token'], 'state': 'frozen',
            'summary': 'completed original episode'})
        other = self.source('replacement')['lease']
        try:
            replay = self.ledger.mutate('claim', 'old-owner', data,
                                        request_id='old-native-request')
        except ValueError:
            pass
        else:
            self.assertIsNone(replay.get('task'))
            self.assertNotIn(task['token'], json.dumps(replay))
        self.assertEqual(self.source('replacement')['lease']['token'], other['token'])

    def test_cli_save_equal_database_is_rejected_before_any_mutation(self):
        self.add('cli-save-task', offset=0x4000)
        commands = [
            ['lease-claim', '--actor', 'cli-source', '--kind', 'source',
             '--rom-offset', '0x5000', '--size', '16', '--summary', 'unsafe save'],
            ['claim', '--actor', 'cli-native', '--task', 'cli-save-task'],
        ]
        for command in commands:
            with self.subTest(command=command[0]):
                before = {table: [tuple(row) for row in self.ledger.db.execute(
                    f'SELECT * FROM {table} ORDER BY 1')]
                          for table in ('tasks', 'events', 'credits', 'requests',
                                        'work_leases')}
                result = subprocess.run([
                    sys.executable, str(Path(wf.__file__).resolve()), '--db',
                    str(self.db), *command, '--save', str(self.db)],
                    text=True, capture_output=True, timeout=20)
                self.assertNotEqual(result.returncode, 0, result.stdout)
                self.assertTrue(self.db.read_bytes().startswith(b'SQLite format 3\x00'))
                after = {table: [tuple(row) for row in self.ledger.db.execute(
                    f'SELECT * FROM {table} ORDER BY 1')] for table in before}
                self.assertEqual(after, before)

    def test_cli_source_add_claim_finish_peer_credit_and_release_receipts(self):
        def cli(*arguments, success=True):
            result = subprocess.run(
                [sys.executable, str(Path(wf.__file__).resolve()),
                 '--db', str(self.db), *map(str, arguments)],
                text=True, capture_output=True, timeout=20)
            if not success:
                self.assertNotEqual(result.returncode, 0, result.stdout)
                return result
            self.assertEqual(result.returncode, 0, result.stderr)
            return json.loads(result.stdout)

        source_receipt = self.root / 'source-lease.json'
        claim_receipt = self.root / 'claim.json'
        peer_receipt = self.root / 'peer-lease.json'
        spec = self.root / 'task.json'
        spec.write_text(json.dumps({
            'task_id': 'cli-native', 'module': 'CLIIndependentModule',
            'rom_offset': 0x4000, 'original_span_bytes': 16}))
        source = cli('lease-claim', '--actor', 'cli-producer', '--kind', 'source',
                     '--rom-offset', '0x4000', '--size', '16',
                     '--module', 'discovery-label', '--summary', 'CLI discover',
                     '--save', source_receipt)['lease']
        saved = json.loads(source_receipt.read_text())
        self.assertEqual(saved['lease']['token'], source['token'])
        cli('add', '--actor', 'administrator', '--file', spec,
            '--lease', source_receipt)
        self.assertEqual(self.ledger.task('cli-native')['reservation'],
                         'cli-producer')
        claim = cli('claim', '--actor', 'cli-producer', '--task', 'cli-native',
                    '--lease', source_receipt, '--save', claim_receipt)['task']
        self.assertEqual(json.loads(claim_receipt.read_text())['task']['token'],
                         claim['token'])
        # Consumed discovery receipt cannot be released as an active lease.
        cli('lease-release', '--actor', 'cli-producer', '--lease', source_receipt,
            '--summary', 'stale source receipt', success=False)
        local = self.root / 'local-credit.json'
        local.write_text(json.dumps({
            'gate': 'local_exact', 'binary': str(self.binary),
            'evidence': [str(self.evidence)]}))
        cli('credit', '--actor', 'cli-producer', '--task', 'cli-native',
            '--file', local)
        cli('finish', '--claim', claim_receipt, '--state', 'frozen',
            '--summary', 'CLI local freeze')
        peer = cli('lease-claim', '--actor', 'cli-reviewer', '--kind', 'peer',
                   '--task', 'cli-native', '--summary', 'CLI independent review',
                   '--save', peer_receipt)['lease']
        self.assertEqual((peer['rom_offset'], peer['size']), (0x4000, 16))
        listing = cli('leases', '--json')
        self.assertNotIn(peer['token'], json.dumps(listing))
        independent = self.root / 'peer-credit.json'
        independent.write_text(json.dumps({
            'gate': 'peer_exact', 'binary': str(self.binary),
            'evidence': [str(self.evidence)]}))
        cli('credit', '--actor', 'cli-reviewer', '--task', 'cli-native',
            '--file', independent, success=False)
        credited = cli('credit', '--actor', 'cli-reviewer', '--task', 'cli-native',
                       '--file', independent, '--lease', peer_receipt)
        self.assertEqual(credited['gate'], 'peer_exact')
        cli('lease-release', '--actor', 'cli-reviewer', '--lease', peer_receipt,
            '--summary', 'CLI peer complete')
        cli('lease-release', '--actor', 'cli-reviewer', '--lease', peer_receipt,
            '--summary', 'stale peer receipt', success=False)
        task = self.ledger.task('cli-native')
        self.assertEqual(task['state'], 'frozen')
        self.assertEqual(task['started_at'], claim['started_at'])
        self.assertEqual(self.ledger.db.execute(
            "SELECT COUNT(*) FROM credits WHERE task_id='cli-native' "
            "AND revoked=0").fetchone()[0], 2)
        self.assertEqual(self.ledger.db.execute(
            "SELECT COUNT(*) FROM work_leases WHERE state='active'").fetchone()[0], 0)

    def test_legacy_db_additive_migration_preserves_history_and_clocks(self):
        self.frozen_local()
        def snapshot():
            return {table: [tuple(r) for r in self.ledger.db.execute(
                f'SELECT * FROM {table} ORDER BY 1')]
                    for table in ('meta', 'tasks', 'events', 'credits')}
        before = snapshot()
        self.ledger.close()
        legacy_tables = {'meta', 'tasks', 'events', 'requests', 'legacy_imports',
                         'credits', 'commits', 'sqlite_sequence'}
        connection = sqlite3.connect(self.db)
        connection.execute('PRAGMA foreign_keys=OFF')
        for (name,) in connection.execute(
                "SELECT name FROM sqlite_master WHERE type='table'").fetchall():
            if name not in legacy_tables:
                connection.execute('DROP TABLE "' + name.replace('"', '""') + '"')
        connection.execute('PRAGMA user_version=1')
        connection.commit()
        connection.close()
        self.ledger = wf.Ledger(self.db)
        self.assertEqual(snapshot(), before)
        lease = self.source(offset=0x7000)['lease']
        self.release(lease)
        after = snapshot()
        self.assertEqual(after['tasks'], before['tasks'])
        self.assertEqual(after['credits'], before['credits'])
        self.assertEqual(after['meta'], before['meta'])
        self.assertEqual(after['events'][:len(before['events'])], before['events'])


if __name__ == '__main__':
    unittest.main()
