"""Read-only supervision detects overlapping state left by legacy writers."""
import json
from pathlib import Path
import subprocess
import sys
import tempfile
import unittest

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools'))
import recovery_workflow as wf


class WorkLeaseAuditTests(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory()
        self.path = Path(self.temp.name) / 'ledger.sqlite3'
        self.ledger = wf.Ledger(self.path, initialize=True)

    def tearDown(self):
        self.ledger.close()
        self.temp.cleanup()

    def source(self):
        return self.ledger.mutate('lease-claim', 'owner', {
            'kind': 'source', 'rom_offset': 0x1000, 'size': 16,
            'summary': 'original source'})['lease']

    def test_clean_audit_is_read_only_and_never_exposes_token(self):
        lease = self.source()
        before = list(self.ledger.db.iterdump())
        result = self.ledger.coordination_audit()
        self.assertTrue(result['ok'])
        self.assertEqual(result['mode'], 'compatible')
        self.assertEqual(result['conflicts'], [])
        self.assertNotIn(lease['token'], json.dumps(result))
        self.assertNotIn('token', json.dumps(result))
        self.assertEqual(before, list(self.ledger.db.iterdump()))

    def test_legacy_overlapping_leases_are_detected_and_cli_exits_nonzero(self):
        lease = self.source()
        # Reproduce an older/noncooperating writer, not a supported mutation.
        self.ledger.db.execute(
            "INSERT INTO work_leases SELECT 'legacy','source','other','secret',"
            "4104,16,'alias',NULL,acquired_at,NULL,'active','{}' FROM work_leases WHERE id=?",
            (lease['id'],))
        result = self.ledger.coordination_audit()
        self.assertFalse(result['ok'])
        self.assertEqual(len(result['conflicts']), 1)
        cli = subprocess.run([sys.executable, str(wf.ROOT / 'tools/recovery_workflow.py'),
                              '--db', str(self.path), 'coordination-audit', '--json'],
                             capture_output=True, text=True)
        self.assertEqual(cli.returncode, 1, cli.stderr)
        self.assertFalse(json.loads(cli.stdout)['ok'])
        self.assertNotIn('secret', cli.stdout)

    def test_legacy_native_source_overlap_is_detected(self):
        self.ledger.mutate('add', 'administrator', {'document': {
            'task_id': 'native', 'module': 'native', 'rom_offset': 0x1008,
            'original_span_bytes': 8}})
        self.source()
        self.ledger.db.execute(
            "UPDATE tasks SET state='active',actor='legacy',token='hidden' WHERE id='native'")
        result = self.ledger.coordination_audit()
        self.assertFalse(result['ok'])
        self.assertEqual(len(result['conflicts']), 1)
        self.assertEqual({result['conflicts'][0][side]['phase'] for side in ('left', 'right')},
                         {'lease', 'native'})
        self.assertNotIn('hidden', json.dumps(result))

    def test_supervisor_requires_enforced_mode_without_changing_it(self):
        args = [sys.executable, str(wf.ROOT / 'tools/recovery_workflow.py'),
                '--db', str(self.path), 'coordination-audit', '--json', '--require-mode', 'required']
        first = subprocess.run(args, capture_output=True, text=True)
        self.assertEqual(first.returncode, 1, first.stderr)
        self.assertEqual(json.loads(first.stdout)['mode'], 'compatible')
        self.ledger.mutate('coordination', 'administrator', {
            'mode': 'required', 'summary': 'explicit operator activation'})
        second = subprocess.run(args, capture_output=True, text=True)
        self.assertEqual(second.returncode, 0, second.stderr)
        self.assertTrue(json.loads(second.stdout)['ok'])


if __name__ == '__main__':
    unittest.main()
