import importlib.util
import json
from pathlib import Path
import subprocess
import tempfile
import unittest

spec = importlib.util.spec_from_file_location(
    'source_layout', Path(__file__).resolve().parents[1] / 'tools/source_layout.py')
layout = importlib.util.module_from_spec(spec)
spec.loader.exec_module(layout)


class SourceLayoutTests(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory()
        self.addCleanup(self.temp.cleanup)
        self.root = Path(self.temp.name).resolve()
        self.module = {'name': 'Example', 'kind': 'c', 'offset': 0x1000, 'size': 12,
                       'source': 'build/work/08001000/candidate.c', 'match_policy': 'exact',
                       'functions': [{'name': 'Example', 'offset': 0x1000, 'size': 12}]}
        self.write(self.module['source'], '#include "local.h"\nint Example(void) { return VALUE; }\n')
        self.write('build/work/08001000/local.h', '#include "types.h"\n#define VALUE 3\n')
        self.write('include/types.h', 'typedef unsigned int u32;\n')
        self.write('config/retail-us.json', json.dumps({'modules': [self.module]}))

    def write(self, name, text):
        path = self.root / name
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_text(text)

    def prepare(self, destination='src/engine/example.c'):
        return layout.prepare(self.root, 'config/retail-us.json', 'Example', destination)

    def test_layout_rejects_batch_and_trial_paths(self):
        for path in ['src/campaign_gameplay_50k/001000.c',
                     'src/upstream_shubshub_20261028/08001000.c',
                     'src/core-exact-batch99/example.c', 'src/ui/round00.c',
                     'src/exact_import_97/candidate.c', 'src/Example.c',
                     '../src/engine/example.c']:
            self.assertIsNotNone(layout.source_path_error(path), path)
        self.assertIsNone(layout.source_path_error('src/battle/target_candidates.c'))
        self.assertIsNone(layout.source_path_error('src/unknown/08001000.c'))

    def test_prepare_preserves_identity_bytes_dependencies_and_original(self):
        manifest = (self.root / 'config/retail-us.json').read_bytes()
        result = self.prepare()
        self.assertEqual(result['status'], 'prepared_only')
        self.assertEqual(result['candidate_module'], dict(self.module, source='src/engine/example.c'))
        self.assertEqual((self.root / 'src/engine/example.c').read_bytes(),
                         (self.root / self.module['source']).read_bytes())
        self.assertEqual((self.root / 'src/engine/local.h').read_bytes(),
                         (self.root / 'build/work/08001000/local.h').read_bytes())
        self.assertEqual((self.root / 'config/retail-us.json').read_bytes(), manifest)
        self.assertEqual(len(result['input_closure']), 3)
        self.assertEqual(len(result['copied_files']), 2)
        self.assertFalse(result['production_manifest_changed'])
        self.assertEqual(self.prepare(), result)  # No extra version on an identical retry.

    def test_conflicting_header_leaves_no_new_source(self):
        self.write('src/engine/local.h', '#define VALUE 9\n')
        with self.assertRaisesRegex(ValueError, 'overwrite'):
            self.prepare()
        self.assertFalse((self.root / 'src/engine/example.c').exists())
        self.assertEqual((self.root / 'src/engine/local.h').read_text(), '#define VALUE 9\n')

    def test_unresolved_or_parent_include_is_not_guessed(self):
        for include in ['missing.h', '../local.h']:
            self.write(self.module['source'], '#include "' + include + '"\n')
            with self.assertRaises(ValueError):
                self.prepare()
            self.assertFalse((self.root / 'src/engine/example.c').exists())

    def test_path_sensitive_source_needs_manual_proof(self):
        self.write(self.module['source'], 'const char *file = __FILE__;\n')
        with self.assertRaisesRegex(ValueError, 'path-sensitive'):
            self.prepare()

    def test_macro_selected_include_needs_manual_dependency_proof(self):
        self.write(self.module['source'], '#define HEADER "local.h"\n#include HEADER\n')
        with self.assertRaisesRegex(ValueError, 'macro-selected'):
            self.prepare()
        self.assertFalse((self.root / 'src/engine/example.c').exists())

    def test_destination_symlink_cannot_escape_root(self):
        with tempfile.TemporaryDirectory() as external:
            (self.root / 'src').mkdir()
            (self.root / 'src/engine').symlink_to(external, target_is_directory=True)
            with self.assertRaisesRegex(ValueError, 'outside'):
                self.prepare()
            self.assertFalse((Path(external) / 'example.c').exists())

    def test_in_tree_symlink_is_not_a_production_source_location(self):
        (self.root / 'src').mkdir()
        (self.root / 'src/engine').symlink_to(self.root / 'build/work', target_is_directory=True)
        with self.assertRaisesRegex(ValueError, 'symlinks'):
            self.prepare()
        self.assertFalse((self.root / 'build/work/example.c').exists())

    def test_audit_checks_selected_sources_only(self):
        self.assertFalse(layout.audit(self.root, 'config/retail-us.json')['ok'])
        self.prepare()
        module = dict(self.module, source='src/engine/example.c')
        parked = dict(self.module, name='Parked', enabled=False, source='missing.c')
        self.write('config/retail-us.json', json.dumps({'modules': [module, parked]}))
        self.assertTrue(layout.audit(self.root, 'config/retail-us.json')['ok'])
        (self.root / 'src/engine/example.c').unlink()
        self.assertFalse(layout.audit(self.root, 'config/retail-us.json')['ok'])

    def test_baseline_exempts_only_unchanged_legacy_identity_and_bytes(self):
        self.module['source'] = 'src/old_batch01/round00.c'
        self.write(self.module['source'], 'int Example(void) { return 3; }\n')
        self.write('config/retail-us.json', json.dumps({'modules': [self.module]}))
        def git(*args):
            return subprocess.run(['git', '-C', str(self.root), *args], check=True,
                                  capture_output=True)
        git('init', '-q')
        git('add', 'src', 'config')
        git('-c', 'user.name=Test', '-c', 'user.email=test@example.invalid',
            '-c', 'commit.gpgsign=false', 'commit', '-qm', 'baseline')
        result = layout.audit(self.root, 'config/retail-us.json', 'HEAD')
        self.assertTrue(result['ok'])
        self.assertEqual(len(result['legacy_unchanged']), 1)
        self.write(self.module['source'], 'int Example(void) { return 4; }\n')
        self.assertFalse(layout.audit(self.root, 'config/retail-us.json', 'HEAD')['ok'])
        self.write(self.module['source'], 'int Example(void) { return 3; }\n')
        self.module['size'] = 14
        self.write('config/retail-us.json', json.dumps({'modules': [self.module]}))
        self.assertFalse(layout.audit(self.root, 'config/retail-us.json', 'HEAD')['ok'])


if __name__ == '__main__':
    unittest.main()
