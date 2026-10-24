"""Continuation exclusion and stale-receipt regressions on isolated ledgers."""
import hashlib
import json
from pathlib import Path
import sys
import tempfile
import unittest

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools'))
import recovery_workflow as wf


class WorkLeaseContinuationGuardTests(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory()
        self.root = Path(self.temp.name)
        self.ledger = wf.Ledger(self.root / 'ledger.sqlite3', initialize=True,
                                epoch='2026-01-01T00:00:00Z')
        self.method = self.root / 'method.s'
        self.method.write_text('original method fixture\n')
        self.asm_cause = self.root / 'cause.s'
        self.asm_cause.write_text('new original-ASM observation\n')
        self.task_id = 'T-CONT'
        spec = {
            'task_id': self.task_id, 'module': 'NativeFixture',
            'original_span_bytes': 8, 'rom_offset': 0x100,
            'started_utc': '2026-01-01T00:00:01Z',
            'thumb_entry': '0x08000101',
            'original_reference_span_sha256': 'a' * 64,
            'original_source': self.pin(self.method),
            'hypotheses': [{'id': 'h0', 'summary': 'initial source hypothesis'}],
        }
        self.ledger.mutate('add', 'administrator', {'document': spec})
        claim = self.ledger.mutate('claim', 'workerx', {'task': self.task_id})['task']
        self.ledger.mutate('record', 'workerx', {
            'task': self.task_id, 'token': claim['token'], 'round': 'r0',
            'summary': 'bounded failed hypothesis', 'outcome': 'nonexact',
            'hypothesis_id': 'h0'})
        self.ledger.mutate('finish', 'workerx', {
            'task': self.task_id, 'token': claim['token'], 'state': 'blocked',
            'summary': 'blocked after source diagnosis'})

    def tearDown(self):
        self.ledger.close()
        self.temp.cleanup()

    def pin(self, path):
        return {'path': str(path), 'sha256': hashlib.sha256(path.read_bytes()).hexdigest()}

    def packet(self):
        task = self.ledger.task(self.task_id)
        spec = json.loads(task['spec'])
        history = [dict(row) for row in self.ledger.db.execute(
            'SELECT seq,at,actor,kind,payload FROM events WHERE task_id=? ORDER BY seq',
            (self.task_id,))]
        identity = {'task_id': task['id'], 'module': task['module'],
                    'original_span_bytes': task['original_bytes']}
        for key in ('rom_offset', 'thumb_entry', 'original_reference_span_sha256',
                    'original_source'):
            identity[key] = spec[key]
        return {
            'task_id': self.task_id, 'expected_state': task['state'],
            'expected_token': task['token'] or '', 'native_identity': identity,
            'canonical_started_at': task['started_at'],
            'prior_hypotheses_sha256': hashlib.sha256(wf.encode(spec['hypotheses']).encode()).hexdigest(),
            'prior_event_count': len(history),
            'prior_event_sha256': hashlib.sha256(wf.encode(history).encode()).hexdigest(),
            'continuation_index': 1, 'full_method_percent': 75.0,
            'full_method_evidence': [self.pin(self.method)],
            'terminal_state': {'complete': False, 'unknown': False,
                               'exhausted': False, 'native_duplicate': False},
            'effective_matching_causes': 2,
            'budgets': [{'hypothesis_id': 'h0', 'known': True,
                         'attempts_used': 1, 'attempt_limit': 3}],
            'new_original_asm_cause': {'kind': 'original_asm', 'cause_id': 'cause-2',
                                      'evidence': [self.pin(self.asm_cause)]},
            'summary': 'One new ASM-backed cause with remaining budget',
        }

    def snapshot(self):
        return '\n'.join(self.ledger.db.iterdump())

    def continuation_data(self):
        packet = self.packet()
        return {'task': self.task_id, 'owner': 'worker2',
                'summary': packet['summary'], 'continuation_packet': packet}

    def test_partial_overlap_active_native_rejects_continuation(self):
        overlapping = json.loads(self.ledger.task(self.task_id)['spec'])
        overlapping.update(task_id='T-PARTIAL', module='PartialOverlap',
                           rom_offset=0x104, thumb_entry='0x08000105')
        self.ledger.mutate('add', 'administrator', {'document': overlapping})
        other = self.ledger.mutate('claim', 'otherworker',
                                   {'task': 'T-PARTIAL'})['task']
        self.assertEqual(other['state'], 'active')
        self.assertEqual(other['spec']['rom_offset'], 0x104)
        # T1 [100,108) and T2 [104,10c) overlap without identical envelopes.
        self.assertEqual(self.ledger.task(self.task_id)['state'], 'blocked')
        data = self.continuation_data()
        before = self.snapshot()
        with self.assertRaisesRegex(ValueError, 'overlaps an active native task'):
            self.ledger.mutate('continue', 'administrator', data,
                               request_id='partial-overlap-continuation')
        self.assertEqual(self.snapshot(), before)
        self.assertEqual(self.ledger.task('T-PARTIAL')['token'], other['token'])

    def test_old_continuation_request_cannot_replay_after_finish_and_source_lease(self):
        data = self.continuation_data()
        request = 'original-continuation-request'
        result = self.ledger.mutate('continue', 'administrator', data,
                                    request_id=request)
        active = result['task']
        self.assertEqual(active['state'], 'active')
        before_replay = self.snapshot()
        self.assertEqual(self.ledger.mutate('continue', 'administrator', data,
                                          request_id=request), result)
        self.assertEqual(self.snapshot(), before_replay)

        self.ledger.mutate('finish', 'worker2', {
            'task': self.task_id, 'token': active['token'], 'state': 'blocked',
            'summary': 'Stop the valid continuation before another source owner'})
        source = self.ledger.mutate('lease-claim', 'otherworker', {
            'kind': 'source', 'rom_offset': 0x100, 'size': 8,
            'module': 'NativeFixture', 'summary': 'New source qualification'})['lease']
        self.assertIsNotNone(source)
        before = self.snapshot()
        with self.assertRaisesRegex(ValueError, 'saved native claim is no longer active'):
            self.ledger.mutate('continue', 'administrator', data,
                               request_id=request)
        self.assertEqual(self.snapshot(), before)
        self.assertEqual(self.ledger.task(self.task_id)['state'], 'blocked')
        self.assertIsNone(self.ledger.task(self.task_id)['token'])
        self.assertEqual(self.ledger.leases()[0]['id'], source['id'])


if __name__ == '__main__':
    unittest.main()
