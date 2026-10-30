"""ROM-free builds must verify the complete selected range set and inputs."""
import copy
import hashlib
from pathlib import Path
import sys
import tempfile
import unittest
from unittest import mock

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools'))
import build_source_hashes as verifier


class SourceHashTests(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory()
        self.addCleanup(self.temp.cleanup)
        self.root = Path(self.temp.name)
        self.source = self.root / 'input.c'
        self.source.write_bytes(b'int example;\n')
        self.native = b'\x01\x02\x03\x04'
        self.config = {'sha256': verifier.RETAIL_SHA256, 'size': 1024, 'rom_base': 0x08000000,
                       'modules': [{'name': 'example', 'offset': 8, 'size': 4,
                                    'kind': 'c', 'source': 'input.c'}]}
        self.index = {'retail_sha256': verifier.RETAIL_SHA256,
                      'modules': [{'name': 'example', 'rom_offset': 8, 'original_bytes': 4,
                                   'kind': 'c', 'source': 'input.c'}],
                      'files': [{'path': 'input.c', 'sha256': verifier.sha256(self.source.read_bytes())}]}
        rows = [{'name': 'example', 'rom_offset': 8, 'original_bytes': 4,
                 'sha256': verifier.sha256(self.native)}]
        self.expected = {'schema': 'completed-module-sha256-v1', 'retail_sha256': verifier.RETAIL_SHA256,
                         'modules': rows, 'module_set_sha256': verifier.set_hash(rows)}

    def test_hash_target_and_exact_selection_required(self):
        self.assertEqual(len(verifier.validate_inputs(self.config, self.index, self.expected, self.root)), 1)
        for fault in ('missing', 'extra', 'duplicate', 'target_checksum', 'target_range', 'source_hash', 'retail'):
            config, index, expected = map(copy.deepcopy, (self.config, self.index, self.expected))
            if fault == 'missing': expected['modules'] = []
            elif fault == 'extra': expected['modules'].append({'name': 'extra', 'rom_offset': 20, 'original_bytes': 4, 'sha256': 'a' * 64})
            elif fault == 'duplicate': expected['modules'].append(copy.deepcopy(expected['modules'][0]))
            elif fault == 'target_checksum': expected['module_set_sha256'] = '0' * 64
            elif fault == 'target_range': expected['modules'][0]['rom_offset'] = 9
            elif fault == 'source_hash': index['files'][0]['sha256'] = 'a' * 64
            else: config['sha256'] = 'a' * 64
            if fault not in ('target_checksum', 'retail', 'source_hash'):
                expected['module_set_sha256'] = verifier.set_hash(expected['modules'])
            with self.subTest(fault=fault), self.assertRaises(ValueError):
                verifier.validate_inputs(config, index, expected, self.root)

    def test_generated_native_hash_and_size_are_checked_without_rom(self):
        original = verifier.validate_inputs
        with mock.patch.object(verifier, 'validate_inputs', side_effect=lambda c, i, e: original(c, i, e, self.root)), \
             mock.patch.object(verifier.build_rom, 'validate_source_mix'), \
             mock.patch.object(verifier.build_rom, 'compile_module', return_value=self.native) as compile_module, \
             mock.patch.object(verifier.build_rom, 'check_linked_function_entries', return_value=1), \
             mock.patch.object(verifier.build_rom, 'BUILD_ROOT', self.root):
            result = verifier.verify_build(self.config, self.index, self.expected, self.root, jobs=1)
            self.assertFalse(result['rom_verified'])
            self.assertEqual(result['module_set_sha256'], self.expected['module_set_sha256'])
            self.assertEqual(compile_module.call_args.args[-2:], (None, None))
            for bad in (b'\x01\x02\x03\x05', b'\x01\x02'):
                compile_module.return_value = bad
                with self.subTest(bad=bad), self.assertRaisesRegex(ValueError, 'generated'):
                    verifier.verify_build(self.config, self.index, self.expected, self.root, jobs=1)

    def test_function_hash_table_and_generated_ranges(self):
        header = b'id,address,original_bytes,sha256,kind,module,name\n'
        row = ('US-00000008-000004,0x08000008,4,' + verifier.sha256(self.native)
               + ',function,example,example\n').encode()
        raw = header + row
        self.expected['function_table_sha256'] = verifier.sha256(raw)
        self.expected['function_range_count'] = 1
        targets = verifier.load_function_targets(self.config, self.expected, raw)
        verifier.verify_function_ranges(self.native, targets['example'])
        with self.assertRaisesRegex(ValueError, 'range SHA-256 mismatch'):
            verifier.verify_function_ranges(b'\x01\x02\x03\x05', targets['example'])
        with self.assertRaisesRegex(ValueError, 'table checksum'):
            verifier.load_function_targets(self.config, self.expected, raw + b'changed')
        for altered in (header, raw + row, raw.replace(b'0x08000008', b'0x08000009'),
                        raw.replace(b'function,example', b'data,example')):
            expected = copy.deepcopy(self.expected)
            expected['function_table_sha256'] = verifier.sha256(altered)
            expected['function_range_count'] = len(altered.splitlines()) - 1
            with self.subTest(altered=altered), self.assertRaises(ValueError):
                verifier.load_function_targets(self.config, expected, altered)

    def test_mismatch_identifies_each_function_in_changed_module(self):
        self.config['modules'][0]['functions'] = [
            {'name': 'first', 'offset': 8, 'size': 2},
            {'name': 'second', 'offset': 10, 'size': 2}]
        spans = {'example': [(0, 2, verifier.sha256(self.native[:2]), 'first-id'),
                             (2, 2, verifier.sha256(self.native[2:]), 'second-id')]}
        outcomes = {}
        original = verifier.validate_inputs
        with mock.patch.object(verifier, 'validate_inputs', side_effect=lambda c, i, e: original(c, i, e, self.root)), \
             mock.patch.object(verifier.build_rom, 'validate_source_mix'), \
             mock.patch.object(verifier.build_rom, 'compile_module', return_value=b'\x01\x02\x03\x05'), \
             mock.patch.object(verifier.build_rom, 'check_linked_function_entries', return_value=2):
            with self.assertRaises(ValueError):
                verifier.verify_build(self.config, self.index, self.expected, self.root, jobs=1,
                                      function_targets=spans, outcomes=outcomes)
        self.assertEqual(outcomes['example']['status'], 'mismatch')
        self.assertEqual([row['status'] for row in outcomes['example']['functions']], ['match', 'mismatch'])

    def test_delta_summary_distinguishes_match_mismatch_and_unbuilt(self):
        summary = self.root / 'summary.md'
        matched = {'example': {'status': 'match', 'functions': [
            {'name': 'example', 'id': 'US-00000008-000004', 'status': 'match'}]}}
        verifier.write_delta_summary(self.config, ['input.c', 'include/shared.h'], matched, None, summary)
        text = summary.read_text()
        self.assertIn('`example` (US-00000008-000004) | match', text)
        self.assertIn('include/shared.h', text)
        summary.unlink()
        mismatch = {'example': {'status': 'mismatch', 'error': 'wrong hash', 'functions': [
            {'name': 'example', 'id': 'US-00000008-000004', 'status': 'mismatch'}]}}
        verifier.write_delta_summary(self.config, ['input.c'], mismatch, 'failed', summary)
        self.assertIn('US-00000008-000004) | mismatch', summary.read_text())
        summary.unlink()
        verifier.write_delta_summary(self.config, ['input.c'], {}, 'preflight failed', summary)
        self.assertIn('US-00000008-000004) | not built', summary.read_text())

    def test_tampered_index_source_is_rejected(self):
        self.source.write_bytes(b'int changed;\n')
        with self.assertRaisesRegex(ValueError, 'source/header hash mismatch'):
            verifier.validate_inputs(self.config, self.index, self.expected, self.root)


if __name__ == '__main__':
    unittest.main()
