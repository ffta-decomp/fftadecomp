"""Exercise repository guidance retrieval and the actual ROM-free diagnostic CLI."""
import hashlib
import json
from pathlib import Path
import shutil
import subprocess
import sys
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'tools'))
import find_matching_rule as lookup
import check_matching_rewrites as checker


class GuidanceTests(unittest.TestCase):
    def test_all_index_entries_resolve_to_real_sections(self):
        for rule in lookup.rules():
            with self.subTest(rule=rule['id']):
                path, line, text = lookup.section(rule)
                self.assertTrue(path.is_relative_to(lookup.REFERENCES))
                self.assertEqual(path.read_text().splitlines()[line - 1], text[0])
                self.assertGreater(len(text), 2)

    def test_real_symptoms_and_case_insensitive_abi(self):
        for query, expected in [('代码错位', 'blocks'), ('ABI', 'arguments'),
                                ('栈帧', 'stack'), ('语法', 'syntax')]:
            with self.subTest(query=query):
                self.assertEqual(lookup.select(query, lookup.rules(), 1)[0]['id'], expected)

    def test_unknown_query_does_not_invent_a_rule(self):
        self.assertEqual(lookup.select('no_such_reconstruction_symptom', lookup.rules()), [])

    def test_index_cannot_escape_skill_references(self):
        with self.assertRaisesRegex(ValueError, 'escapes'):
            lookup.section({'document': '../../../../AGENTS.md', 'heading': 'Repository policy'})

    def test_cli_works_without_current_directory_or_user_installation(self):
        with tempfile.TemporaryDirectory() as temp:
            result = subprocess.run([sys.executable, str(ROOT / 'tools/find_matching_rule.py'),
                                     '参数错位', '--limit', '1'], cwd=temp,
                                    check=True, capture_output=True, text=True)
            self.assertIn('[arguments]', result.stdout)
            self.assertIn('.agents/skills/ffta-decomp/references/', result.stdout)
            self.assertEqual(list(Path(temp).iterdir()), [])

    def test_emitted_checker_references_exist_in_this_checkout(self):
        source = 'int f(void) { call(); int value; return value; }'
        report = checker.analyze(source)
        self.assertTrue(report['findings'])
        for finding in report['findings']:
            path, _, anchor = finding['reference'].partition('#')
            text = (ROOT / path).read_text()
            if anchor:
                import re
                headings = [re.sub(r'[^\w\- ]', '', x.lower()).replace(' ', '-')
                            for x in re.findall(r'^#+ (.+)$', text, re.M)]
                self.assertIn(anchor, headings)


class DiagnosticCliTests(unittest.TestCase):
    @unittest.skipUnless(shutil.which('arm-none-eabi-objdump'), 'optional ARM binutils not installed')
    def test_frozen_synthetic_binary_alignment_is_read_only(self):
        with tempfile.TemporaryDirectory() as temp:
            folder = Path(temp)
            # Synthetic Thumb code: movs r0,1; adds r1,2; lsls r2,3;
            # str r1,[r4]; ldrh r3,[r4,2]; bx lr. No game-derived bytes.
            reference = bytes.fromhex('012002310002216063887047')
            generated = bytes.fromhex('20b4') + reference
            (folder / 'reference.bin').write_bytes(reference)
            (folder / 'candidate.bin').write_bytes(generated)
            digest = lambda data: hashlib.sha256(data).hexdigest()
            report = folder / 'report.json'
            report.write_text(json.dumps({'segments': [{
                'module': 'SyntheticThumb', 'binary': 'candidate.bin',
                'reference_binary': 'reference.bin', 'binary_sha256': digest(generated),
                'reference_binary_sha256': digest(reference),
                'generated_size': len(generated), 'reference_size': len(reference),
                'matching_bytes': sum(a == b for a, b in zip(reference, generated)),
                'fits': False, 'gba_address': 0x08001000,
                'functions': [{'mode': 'thumb'}]}]}))
            before = {p.name: digest(p.read_bytes()) for p in folder.iterdir()}
            command = [sys.executable, str(ROOT / 'tools/diagnose_module_build.py'),
                       '--build-report', str(report), '--output', str(folder / 'diagnostic')]
            subprocess.run(command, check=True, capture_output=True, text=True)
            result = json.loads((folder / 'diagnostic/diagnosis.json').read_text())
            self.assertTrue(result['diagnostic_only'])
            self.assertFalse(result['positional']['fits'])
            self.assertTrue(any(row['address_delta'] == 2 for row in result['largest_shifted_runs']))
            self.assertEqual(before, {name: digest((folder / name).read_bytes()) for name in before})
            rejected = subprocess.run(command, capture_output=True, text=True)
            self.assertNotEqual(rejected.returncode, 0)
            self.assertIn('new directory', rejected.stderr)


if __name__ == '__main__':
    unittest.main()
