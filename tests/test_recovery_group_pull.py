"""Isolated group intake tests; never opens the configured live database."""
import concurrent.futures
import contextlib
import io
import hashlib
import json
from pathlib import Path
import subprocess
import sys
import tempfile
import unittest
from unittest.mock import patch

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools'))
import recovery_workflow as wf
import recovery_group_pull as gp
from recovery_group_pull import GroupLedger, pull_once_with_refresh


def pull_process(args):
    db, pool, actor = args
    ledger = GroupLedger(db)
    try:
        return ledger.mutate('group-pull', actor, {'group': 'battle', 'pool': wf.evidence([pool])[0], 'live_manifest': str(Path(pool).parent / 'manifest.json')})
    finally:
        ledger.close()


class PullTests(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory(); self.root = Path(self.temp.name)
        self.db = self.root / 'ledger.sqlite3'
        self.ledger = GroupLedger(self.db, initialize=True)
        self.source = self.root / 'original.s'; self.source.write_text('original assembly')
        self.manifest = self.root / 'manifest.json'
        self.pool = self.root / 'pool.json'
        self.rows = [self.candidate(100), self.candidate(200)]
        self.write_pool()

    def tearDown(self):
        self.ledger.close(); self.temp.cleanup()

    def candidate(self, offset):
        pin = wf.evidence([self.source])[0]
        return {'group': 'battle', 'module': 'M' + str(offset), 'rom_offset': offset,
                'original_span_bytes': 16, 'boundary_kind': 'whole_function', 'source': pin,
                'edge': dict(pin, caller=10, site=12, target=offset), 'priority': offset}

    def write_pool(self, kind='assembly'):
        self.manifest.write_text(json.dumps({'modules': [dict(name=r['module'], offset=r['rom_offset'],
            size=r['original_span_bytes'], kind=kind) for r in self.rows]}))
        self.pool.write_text(json.dumps({'schema': 'recovery-group-pool-v1',
            'manifest': wf.evidence([self.manifest])[0], 'candidates': self.rows}))

    def pull(self, actor='A'):
        return pull_process((self.db, self.pool, actor))

    def add_ready(self, row, ident):
        self.ledger.mutate('add', 'administrator', {'document': dict(row, task_id=ident)})

    def test_process_race_claims_distinct_ready_and_preserves_clock(self):
        for i, row in enumerate(self.rows): self.add_ready(row, 'T' + str(i))
        self.ledger.mutate('coordination', 'administrator', {'mode': 'required', 'summary': 'test'})
        with concurrent.futures.ProcessPoolExecutor(2) as executor:
            results = list(executor.map(pull_process, [(self.db, self.pool, 'A'), (self.db, self.pool, 'B')]))
        self.assertEqual({r['phase'] for r in results}, {'implementation'})
        self.assertEqual(len({r['task']['id'] for r in results}), 2)
        resumed = self.pull('A'); first = next(r for r in results if r['task']['actor'] == 'A')
        self.assertEqual(resumed['task']['started_at'], first['task']['started_at'])
        self.assertEqual(self.ledger.db.execute('select count(*) from credits').fetchone()[0], 0)

    def test_qualification_race_and_resume(self):
        with concurrent.futures.ProcessPoolExecutor(2) as executor:
            results = list(executor.map(pull_process, [(self.db, self.pool, 'A'), (self.db, self.pool, 'B')]))
        self.assertEqual(len({r['lease']['rom_offset'] for r in results}), 2)
        first = next(r for r in results if r['lease']['actor'] == 'A')
        resumed = self.pull('A')
        self.assertEqual(resumed['lease']['token'], first['lease']['token'])
        self.assertEqual(resumed['lease']['acquired_at'], first['lease']['acquired_at'])
        self.assertEqual(self.ledger.db.execute('select count(*) from tasks').fetchone()[0], 0)

    def test_closed_partial_history_and_exact_c_excluded(self):
        self.add_ready(dict(self.rows[0], rom_offset=108), 'OLD')
        self.ledger.db.execute("update tasks set state='blocked' where id='OLD'")
        self.rows[1]['eligibility'] = 'excluded'; self.write_pool()
        result = self.pull()
        self.assertEqual(result['phase'], 'blocked')
        self.assertEqual(result['reasons']['native_history_overlap'], 1)
        self.assertEqual(result['reasons']['pool_excluded'], 1)
        self.rows[1].pop('eligibility'); self.write_pool(kind='c')
        self.assertEqual(self.pull()['reasons']['already_exact_c'], 2)

    def test_stale_source_manifest_disposition(self):
        self.source.write_text('changed')
        self.assertEqual(self.pull()['reasons']['stale_or_invalid_source_evidence'], 2)
        self.rows = [self.candidate(100)]; self.write_pool()
        self.manifest.write_text('{}')
        with self.assertRaises(ValueError): self.pull()
        self.write_pool(); disposition = self.root / 'decision.json'
        disposition.write_text('{"state":"closed"}')
        self.rows[0]['disposition'] = wf.evidence([disposition])[0]; self.write_pool()
        self.assertEqual(self.pull()['reasons']['disposition_closed_or_unknown'], 1)

    def test_snapshot_stays_valid_live_function_exact_and_unrelated_changes(self):
        snapshot = self.root / 'snapshot.json'
        snapshot.write_bytes(self.manifest.read_bytes())
        pool = json.loads(self.pool.read_text()); pool['manifest'] = wf.evidence([snapshot])[0]
        self.pool.write_text(json.dumps(pool))
        self.manifest.write_text(json.dumps({'modules': [
            {'name': 'PARENT', 'offset': 90, 'size': 140, 'kind': 'assembly',
             'functions': [{'offset': 100, 'size': 16}, {'offset': 200, 'size': 16}]},
            {'name': 'unrelated', 'offset': 500, 'size': 10, 'kind': 'c'}]}))
        result = self.pull()
        self.assertEqual(result['phase'], 'qualification')
        lease = result['lease']
        self.ledger.mutate('lease-release', 'A', {'lease_id': lease['id'], 'token': lease['token'], 'summary': 'test'})
        live = json.loads(self.manifest.read_text()); live['modules'][0]['kind'] = 'c'
        self.manifest.write_text(json.dumps(live))
        self.assertEqual(self.pull()['reasons']['already_exact_c'], 2)

    def test_unknown_group_is_only_qualification_and_unproven_module_rejected(self):
        self.rows = [dict(self.rows[0], group='unclassified', qualification_group='battle',
                          eligibility='qualification_only')]
        self.write_pool()
        result = self.pull()
        self.assertEqual(result['phase'], 'qualification')
        self.assertEqual(self.ledger.db.execute('select count(*) from tasks').fetchone()[0], 0)
        lease = result['lease']
        self.ledger.mutate('lease-release', 'A', {'lease_id': lease['id'], 'token': lease['token'], 'summary': 'test'})
        self.rows[0].pop('boundary_kind'); self.write_pool()
        self.assertEqual(self.pull()['reasons']['snapshot_function_range_unknown'], 1)
        self.rows = []; self.write_pool()
        self.assertEqual(self.pull()['reasons'], {'empty_pool': 1})

    def test_resume_keeps_candidate_pool_and_acquisition_time(self):
        first = self.pull()
        resumed = self.pull()
        for key in ('candidate', 'pool', 'manifest', 'acquired_at'):
            self.assertEqual(first[key], resumed[key])

    def test_qualified_ready_without_pool_lead(self):
        self.add_ready(dict(self.rows[0], original_source=self.rows[0]['source']), 'QUALIFIED')
        pool = json.loads(self.pool.read_text()); pool['candidates'] = []
        self.pool.write_text(json.dumps(pool))
        self.ledger.mutate('coordination', 'administrator', {'mode': 'required', 'summary': 'test'})
        result = self.pull()
        self.assertEqual(result['phase'], 'implementation')
        self.assertEqual(result['task']['id'], 'QUALIFIED')

    def test_disposition_is_atomic_persistent_and_authorized(self):
        first = self.pull()
        proof = self.root / 'interface.json'; proof.write_text('{"result":"interface only"}')
        data = {'group': 'battle', 'disposition': 'interface_only', 'summary': 'typed interface retained',
                'work_lease': {'id': first['lease']['id'], 'token': first['lease']['token']},
                'evidence': wf.evidence([proof])}
        with self.assertRaises(ValueError):
            self.ledger.mutate('group-disposition', 'B', data)
        bad = dict(data, evidence=[dict(data['evidence'][0], sha256='0' * 64)])
        with self.assertRaises(ValueError):
            self.ledger.mutate('group-disposition', 'A', bad)
        self.assertEqual(len(self.ledger.leases()), 1)
        self.assertEqual(self.ledger.db.execute("select count(*) from events where kind='group_disposition'").fetchone()[0], 0)
        closed = self.ledger.mutate('group-disposition', 'A', data)
        self.assertTrue(closed['lease_released'])
        self.assertEqual(self.ledger.leases(), [])
        next_result = self.pull()
        self.assertEqual(next_result['candidate']['rom_offset'], 200)
        self.assertEqual(next_result['reasons']['qualification_already_disposed'], 1)
        self.assertEqual(self.ledger.db.execute('select count(*) from credits').fetchone()[0], 0)

    def test_cli_disposition_persists_and_releases(self):
        first = self.pull()
        lease = self.root / 'lease.json'; lease.write_text(json.dumps(first))
        proof = self.root / 'proof.json'; proof.write_text('{"classification":"out_of_scope"}')
        result = self.root / 'closed.json'
        run = subprocess.run([sys.executable, 'tools/recovery_group_pull.py', '--db', str(self.db),
            '--actor', 'A', '--group', 'battle', '--disposition', 'out_of_scope',
            '--lease', str(lease), '--evidence', str(proof), '--summary', 'original source interface',
            '--save', str(result)], capture_output=True, text=True, check=True)
        self.assertNotIn('token', run.stdout)
        self.assertTrue(json.loads(result.read_text())['lease_released'])
        self.assertEqual(self.pull()['candidate']['rom_offset'], 200)

    def test_replenish_once_then_success_preserves_revision_pin(self):
        old = self.root / 'old-pool.json'
        empty = json.loads(self.pool.read_text()); empty['candidates'] = []
        old.write_text(json.dumps(empty))
        link = self.root / 'current-pool.json'; link.symlink_to(old)
        old_pin = wf.evidence([link])[0]
        refresh = {'catalog': str(self.root / 'catalog.json'), 'seed_group': 'battle',
                   'output_root': str(self.root / 'refresh')}
        def build(repo, catalog, snapshot, db, exclusions, dispositions, seed, group):
            self.assertFalse(self.ledger.db.in_transaction)
            self.assertEqual(Path(snapshot).read_bytes(), self.manifest.read_bytes())
            return {'schema': 'recovery-group-pool-v1', 'manifest': wf.evidence([snapshot])[0],
                    'candidates': self.rows}
        with patch('build_recovery_group_pool.build_pool', side_effect=build) as builder:
            result = pull_once_with_refresh(self.ledger, 'A', 'battle', link, self.manifest, refresh, link)
        self.assertEqual(builder.call_count, 1)
        self.assertEqual(result['phase'], 'qualification')
        self.assertEqual(result['refresh']['attempts'], 1)
        self.assertEqual(result['pool']['path'], str(link.resolve()))
        self.assertNotEqual(result['pool']['path'], str(link))
        self.assertEqual(hashlib.sha256(Path(old_pin['path']).read_bytes()).hexdigest(), old_pin['sha256'])

    def test_true_exhaustion_refreshes_once_and_busy_owner_never_refreshes(self):
        empty = json.loads(self.pool.read_text()); empty['candidates'] = []
        self.pool.write_text(json.dumps(empty))
        refresh = {'catalog': str(self.root / 'catalog.json'), 'output_root': str(self.root / 'refresh')}
        def build(repo, catalog, snapshot, *unused):
            return dict(empty, manifest=wf.evidence([snapshot])[0])
        with patch('build_recovery_group_pool.build_pool', side_effect=build) as builder:
            result = pull_once_with_refresh(self.ledger, 'A', 'battle', self.pool, self.manifest, refresh)
        self.assertEqual(builder.call_count, 1)
        self.assertEqual(result['phase'], 'blocked')
        self.assertEqual(result['reasons']['empty_pool'], 1)
        self.ledger.mutate('lease-claim', 'A', {'kind': 'source', 'module': 'other',
            'rom_offset': 500, 'size': 16, 'summary': 'other group source'})
        with patch('build_recovery_group_pool.build_pool') as builder:
            result = pull_once_with_refresh(self.ledger, 'A', 'battle', self.pool, self.manifest, refresh)
        builder.assert_not_called()
        self.assertIn('own_source_other_or_unknown_group', result['reasons'])

    def test_cli_uses_configured_default_pool(self):
        local = self.root / '.local'; local.mkdir()
        (local / 'recovery-workflow.json').write_text(json.dumps({'db': str(self.db),
            'group_pull': {'groups': {'battle': {'pool': str(self.pool)}}}}))
        receipt = self.root / 'configured-receipt.json'
        argv = ['group-pull', '--actor', 'A', '--group', 'battle', '--manifest', str(self.manifest),
                '--save', str(receipt)]
        with patch.object(wf, 'ROOT', self.root), patch.object(sys, 'argv', argv), contextlib.redirect_stdout(io.StringIO()):
            self.assertEqual(gp.main(), 0)
        self.assertEqual(json.loads(receipt.read_text())['phase'], 'qualification')

    def test_sdk_exclusion_and_stdout_no_tokens(self):
        class Policy:
            def overlaps(self, spec): return [spec]
        with patch.object(wf.NativeScopeExclusions, 'load', return_value=Policy()):
            result = self.ledger.mutate('group-pull', 'A', {'group': 'battle', 'pool': wf.evidence([self.pool])[0], 'live_manifest': str(self.manifest)})
        self.assertEqual(result['reasons']['sdk_excluded'], 2)
        receipt = self.root / 'receipt.json'
        run = subprocess.run([sys.executable, 'tools/recovery_group_pull.py', '--db', str(self.db),
            '--manifest', str(self.manifest), '--actor', 'A', '--group', 'battle', '--pool', str(self.pool), '--save', str(receipt)],
            text=True, capture_output=True, check=True)
        saved = json.loads(receipt.read_text())
        self.assertNotIn('token', run.stdout)
        self.assertIn('token', saved['lease'])
        self.assertEqual(receipt.stat().st_mode & 0o777, 0o600)


if __name__ == '__main__': unittest.main()
