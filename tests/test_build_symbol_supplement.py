"""Fixed-address supplements must not introduce emitted code or stale caches."""
import json
from pathlib import Path
import sys
import tempfile
import unittest
from unittest import mock

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools'))
import build_rom


class SymbolSupplementTests(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory()
        self.root = Path(self.tmp.name).resolve()
        (self.root / 'config').mkdir()
        self.root_patch = mock.patch.object(build_rom, 'ROOT', self.root)
        self.root_patch.start()

    def tearDown(self):
        self.root_patch.stop()
        self.tmp.cleanup()

    def test_only_fixed_address_directives_are_accepted(self):
        path = self.root / 'aliases.s'
        path.write_text('.syntax unified\n.thumb\n.global x\n.thumb_set x, 0x08000101\n.set y, 0x03000000\n')
        module = {'kind': 'c', 'external_symbol_supplement': 'aliases.s'}
        self.assertEqual(build_rom.external_symbol_supplement(module), path.resolve())
        for invalid in ('.word 0x123\n', 'mov r0, r0\n', '.include "x"\n', '.set x, y+1\n'):
            path.write_text(invalid)
            with self.assertRaises(ValueError):
                build_rom.external_symbol_supplement(module)
        with self.assertRaises(ValueError):
            build_rom.external_symbol_supplement({'kind': 'c', 'external_symbol_supplement': '/etc/passwd'})
        self.assertIsNone(build_rom.external_symbol_supplement({'kind': 'c'}))

    def test_symbol_supplement_contents_are_in_cache_identity(self):
        path = self.root / 'aliases.s'
        path.write_text('.global x\n.set x, 0x03000000\n')
        source = self.root / 'function.c'
        source.write_text('void f(void) {}\n')
        module = {'name': 'f', 'kind': 'c', 'source': 'function.c',
                  'offset': 256, 'size': 4, 'external_symbol_supplement': 'aliases.s'}
        context = {'inputs': {}, 'resource_inputs': {}, 'source_headers': {},
                   'python': 'test', 'platform': 'test'}
        first = build_rom.build_cache_fingerprint(module, 0x08000000, {'id': 'test', 'sha256': '0' * 64}, None, context)
        path.write_text('.global x\n.set x, 0x03000004\n')
        # Calls are separate input sessions; this is an actual input mutation.
        with mock.patch.object(build_rom, 'INPUT_SESSION', None):
            second = build_rom.build_cache_fingerprint(module, 0x08000000, {'id': 'test', 'sha256': '0' * 64}, None, context)
        self.assertNotEqual(first, second)


if __name__ == '__main__':
    unittest.main()
