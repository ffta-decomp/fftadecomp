"""Release invariants: attribution, byte accounting and unchanged upstream bodies."""
import csv
import hashlib
import json
from pathlib import Path
import unittest
ROOT = Path(__file__).resolve().parents[1]
class ImportProvenanceTests(unittest.TestCase):
    def setUp(self):
        self.data = json.loads((ROOT/'data/upstream-imports.json').read_text())
        self.index = json.loads((ROOT/'src/completed-index.json').read_text())
    def test_csv_and_json_identify_same_entries(self):
        with (ROOT/'data/upstream-imports.csv').open() as f: rows=list(csv.DictReader(f))
        self.assertEqual({r['entry'] for r in rows}, {r['entry'] for r in self.data['entries']})
        self.assertTrue(all(r['origin']=='upstream_import' for r in rows))
    def test_sources_preserve_upstream_identity_or_verified_layout_equivalence(self):
        rows=[r for r in self.data['entries'] if r['upstream_commit']==self.data['latest_import_commit']]
        for r in rows:
            raw=(ROOT/r['source']).read_bytes()
            self.assertTrue(raw.startswith(b'/* Imported from https://github.com/shubshub/fftadecomp\n'))
            body=raw.split(b' */\n',1)[1]
            actual = hashlib.sha256(body).hexdigest()
            adaptation = r.get('source_layout_adaptation')
            if adaptation is None:
                self.assertEqual(actual,r['upstream_source_sha256'],r['source'])
            else:
                # Relocated includes and extracted equivalent type declarations
                # change raw bytes. Retain the immutable upstream digest, and
                # authenticate the explicit current-source equivalence evidence.
                self.assertEqual(adaptation['schema'], 'source-layout-equivalence-v1')
                self.assertEqual(adaptation['prior_upstream_body_sha256'],r['upstream_source_sha256'])
                self.assertEqual(actual, adaptation['current_body_sha256'])
                self.assertEqual(hashlib.sha256(raw).hexdigest(),r['source_sha256'])
                self.assertEqual(adaptation['current_source_sha256'], r['source_sha256'])
                self.assertEqual(adaptation['preprocessed_before_sha256'], adaptation['preprocessed_after_sha256'])
                self.assertEqual(len(adaptation['preprocessed_after_sha256']), 64)
                self.assertIn(r['upstream_source_sha256'].encode(), raw.split(b' */\n',1)[0])
                self.assertEqual(adaptation['validation_commit'], self.data['source_layout_validation_commit'])
    def test_ranges_are_disjoint_and_totals_nonadditive(self):
        end=0
        for r in sorted(self.index['modules'],key=lambda x:x['rom_offset']):
            self.assertGreaterEqual(r['rom_offset'],end)
            end=r['rom_offset']+r['original_bytes']
        self.assertEqual(sum(r['original_bytes'] for r in self.data['entries']),self.data['total_attributed_import_original_bytes'])
        self.assertEqual(sum(r['original_bytes'] for r in self.index['modules']),self.data['published_completed_original_bytes'])
    def test_index_and_manifest_keep_import_marker(self):
        idx={r['name']:r for r in self.index['modules']}
        config={r['name']:r for r in json.loads((ROOT/'config/completed-build.json').read_text())['modules']}
        for r in self.data['entries']:
            for source in (idx,config):
                self.assertEqual(source[r['name']]['origin'],'upstream_import')
                self.assertEqual(source[r['name']]['upstream_commit'],r['upstream_commit'])
if __name__=='__main__':unittest.main()
