"""Ensure the selected gg contributions retain their source and attribution."""
import hashlib
import json
from pathlib import Path
import unittest

ROOT = Path(__file__).resolve().parents[1]


class GgContributionTests(unittest.TestCase):
    def test_selected_sources_and_attribution(self):
        config = json.loads((ROOT / 'config/completed-build.json').read_text())
        index = json.loads((ROOT / 'src/completed-index.json').read_text())
        proof = json.loads((ROOT / 'data/completed-build-validation.json').read_text())
        modules = {row['name']: row for row in config['modules']}
        files = {row['path']: row['sha256'] for row in index['files']}
        rows = [row for row in index['modules'] if row.get('contributor') == 'gg']
        self.assertEqual((len(rows), sum(row['original_bytes'] for row in rows)), (96, 5594))
        self.assertEqual(proof['contribution']['contributor'], 'gg')
        for row in rows:
            module = modules[row['name']]
            self.assertEqual((module['offset'], module['size'], module['source']),
                             (row['rom_offset'], row['original_bytes'], row['source']))
            self.assertEqual(module['compiler_flags'], ['-O2', '-mthumb-interwork'])
            self.assertEqual(module['contributor'], 'gg')
            raw = (ROOT / row['source']).read_bytes()
            self.assertIn(b'Contributed by gg', raw)
            self.assertEqual(hashlib.sha256(raw).hexdigest(), row['source_sha256'])
            self.assertEqual(files[row['source']], row['source_sha256'])
            if row.get('origin') == 'upstream_import':
                self.assertEqual(module['upstream_commit'], row['upstream_commit'])
                self.assertIn(row['upstream_commit'].encode(), raw)


if __name__ == '__main__':
    unittest.main()
