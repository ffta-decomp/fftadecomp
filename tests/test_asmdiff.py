import json
from pathlib import Path
import sys
import tempfile
import unittest
from unittest.mock import patch
from types import SimpleNamespace

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools'))
import asmdiff


def dump(ops, start=0x8001000):
    return '\n'.join(f' {start + i * 2:x}:\t0000      \t{op}' for i, op in enumerate(ops))


class AlignmentTests(unittest.TestCase):
    def analyze(self, a, b):
        return asmdiff.analyze_dumps(dump(a), dump(b))[0]

    def test_inserted_instruction_realigns_following_code(self):
        a = ['movs\tr0, #1', 'adds\tr1, #2', 'lsls\tr2, r2, #3',
             'str\tr1, [r4, #0]', 'ldrh\tr3, [r4, #2]', 'bx\tlr']
        r = self.analyze(a, ['push\t{r5}'] + a)
        self.assertEqual(r['diagnostic_line_counts']['inserted_lines'], 1)
        self.assertTrue(any(x['address_delta'] == 2 for x in r['shifted_runs']))

    def test_register_difference_not_equal_text(self):
        r = self.analyze(['adds\tr0, r1, #4'], ['adds\tr2, r3, #4'])
        self.assertEqual(r['diagnostic_line_counts']['register_only_text_differences'], 1)

    def test_immediate_difference_not_register_only(self):
        r = self.analyze(['movs\tr0, #1'], ['movs\tr0, #2'])
        self.assertEqual(r['diagnostic_line_counts']['other_aligned_differences'], 1)

    def test_changed_call_target_preserved(self):
        r = self.analyze(['bl\t0x08002000'], ['bl\t0x08003000'])
        self.assertEqual(r['diagnostic_line_counts']['other_aligned_differences'], 1)

    def test_equal_inputs_not_shifted(self):
        a = ['movs\tr0, #1', 'adds\tr1, #2', 'str\tr1, [r4, #0]', 'bx\tlr']
        r = self.analyze(a, a)
        self.assertFalse(r['shifted_runs'])
        self.assertFalse(r['possible_moved_sequences'])

    def test_unique_moved_sequence(self):
        a = ['adds\tr0, #1', 'lsls\tr1, r1, #2', 'str\tr0, [r4, #0]', 'ldrh\tr2, [r4, #2]']
        b = ['subs\tr3, #3', 'lsrs\tr5, r5, #4', 'strb\tr3, [r6, #0]', 'ldrb\tr7, [r6, #1]', 'eors\tr3, r7']
        r = self.analyze(a + b, b + a)
        self.assertTrue(r['possible_moved_sequences'])
        self.assertEqual(r['possible_moved_sequences'][0]['confidence'], 'unique_text_window_not_CFG_proof')

    def test_repeated_windows_not_unique_move(self):
        mod = asmdiff.upstream(); cfg = asmdiff.config(mod)
        a = ['movs\tr0, #1'] * 12
        lines = mod.process(dump(a), cfg)
        self.assertFalse(asmdiff.moved_candidates(lines, lines, []))

    def test_empty_disassembly_refused(self):
        with self.assertRaisesRegex(ValueError, 'No parsed'):
            asmdiff.analyze_dumps('', '')

    def test_bare_pc_pool_comments_preserve_address_and_literal(self):
        for comment in ('@ (0x8001004)', '; (8001004)'):
            with self.subTest(comment=comment):
                text = dump(['ldr\tr4, [pc, #0]\t' + comment, 'bx\tlr', '.word\t0x11223344'])
                result, plain = asmdiff.analyze_dumps(text, text)
                self.assertEqual(result['parser_comment_normalizations'], {'reference':1, 'current':1})
                self.assertEqual(result['diagnostic_line_counts'], {'same_text_lines':3})
                self.assertIn('(8001004)', plain)
                self.assertIn('0x11223344', plain)
                self.assertNotIn('invalid literal', plain)

    def test_symbol_comments_are_not_rewritten(self):
        text = dump(['ldr\tr4, [pc, #0]\t@ (8001004 <pool+4>)', 'bx\tlr', '.word\t0x11223344'])
        result, _ = asmdiff.analyze_dumps(text, text)
        self.assertEqual(result['parser_comment_normalizations'], {'reference':0, 'current':0})

    def test_unrelated_parenthesized_comments_not_rewritten(self):
        text = dump(['movs\tr0, #1\t@ (0x8001004)', 'ldr\tr0, [r4, #0]\t@ (0x8001004)'])
        self.assertEqual(asmdiff.BARE_POOL_COMMENT.subn(r'\1\2 \3\4', text), (text, 0))

    def test_parse_error_never_counts_as_an_equal_line(self):
        valid, invalid = dump(['bx\tlr']), dump(['bl\tnot_a_hex_target'])
        for a, b, side in ((invalid, valid, 'reference'), (valid, invalid, 'current')):
            with self.subTest(side=side), self.assertRaisesRegex(ValueError, side + ' disassembly has 1 parser errors'):
                asmdiff.analyze_dumps(a, b)


class ArtifactTests(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory()
        self.addCleanup(self.temp.cleanup)
        self.path = Path(self.temp.name)
        (self.path/'current.bin').write_bytes(b'\x70\x47')
        (self.path/'ref.bin').write_bytes(b'\x70\x47')
        self.segment = {'module': 'test', 'binary': 'current.bin', 'reference_binary': 'ref.bin',
                        'binary_sha256': asmdiff.sha(self.path/'current.bin'),
                        'generated_size': 2, 'reference_size': 2,
                        'functions': [{'mode': 'thumb'}]}
        self.report = self.path/'report.json'

    def save(self):
        self.report.write_text(json.dumps({'segments': [self.segment]}))

    def test_report_relative_paths(self):
        self.save()
        self.assertEqual(asmdiff.load_segment(self.report)[2]['binary'], (self.path/'current.bin').resolve())

    def test_drift_refused(self):
        self.save(); (self.path/'current.bin').write_bytes(b'xx')
        with self.assertRaisesRegex(ValueError, 'hash differs'):
            asmdiff.load_segment(self.report)

    def test_wrong_reference_extent_refused(self):
        self.segment['reference_size'] = 4; self.save()
        with self.assertRaisesRegex(ValueError, 'size differs'):
            asmdiff.load_segment(self.report)

    def test_mixed_mode_refused(self):
        self.segment['functions'].append({'mode': 'arm'}); self.save()
        with self.assertRaisesRegex(ValueError, 'mode required'):
            asmdiff.load_segment(self.report)

    def test_existing_output_refused(self):
        self.save()
        with self.assertRaisesRegex(ValueError, 'new directory'):
            asmdiff.run(self.report, self.path)

    def test_parse_error_does_not_publish_output(self):
        self.segment['gba_address'] = 0x8001000
        self.save()
        with patch.object(asmdiff.subprocess, 'run', return_value=SimpleNamespace(stdout=dump(['bl\tnot_hex']))):
            with self.assertRaisesRegex(ValueError, 'parser errors'):
                asmdiff.run(self.report, self.path/'new-output', objdump='unused-mocked-objdump')
        self.assertFalse((self.path/'new-output').exists())


class GeneratedExtentTests(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory()
        self.addCleanup(self.temp.cleanup)
        self.path = Path(self.temp.name)
        self.raw = bytes.fromhex('7047c046')
        self.function_size = 2
        self.entry = 0x8001001
        self.elf = self.path/'current.elf'
        self.elf.write_bytes(b'frozen ELF fixture')
        self.current = self.path/'current.bin'
        self.current.write_bytes(bytes.fromhex('7047'))
        self.ref = self.path/'reference.bin'
        self.ref.write_bytes(bytes.fromhex('7047'))
        self.report_path = self.path/'report.json'
        self.report = {
            'module_configuration': {'trailing_alignment_bytes': 2},
            'compile_inputs': {'artifacts': {'elf': {
                'path': str(self.elf), 'sha256': asmdiff.sha(self.elf)}}},
            'toolchain': {'tools': {key: {'path': key} for key in ('objcopy', 'readelf')}},
            'segments': [{'module': 'Sample', 'elf': str(self.elf),
                          'binary': str(self.current), 'reference_binary': str(self.ref),
                          'binary_sha256': asmdiff.sha(self.current),
                          'generated_size': 2, 'reference_size': 2, 'gba_address': 0x8001000,
                          'functions': [{'name': 'Sample', 'mode': 'thumb',
                                         'thumb_entry_address': 0x8001001}]}]}
        self.paths = {'binary': self.current, 'reference_binary': self.ref}

    def binutils(self, command, **kwargs):
        if command[0] == 'objcopy':
            Path(command[-1]).write_bytes(self.raw)
            return SimpleNamespace(stdout='')
        if command[0] == 'readelf':
            return SimpleNamespace(stdout=f'1: {self.entry:08x} {self.function_size} FUNC GLOBAL DEFAULT 1 Sample\n')
        return SimpleNamespace(stdout=dump(['bx\tlr', 'bx\tr1']))

    def extent(self, full=False):
        return asmdiff.generated_extent(self.report, self.report['segments'][0],
                                        self.paths, self.report_path, full)

    def test_verified_outside_function_nop_keeps_reported_view(self):
        with patch.object(asmdiff.subprocess, 'run', side_effect=self.binutils):
            raw, info, pin = self.extent()
        self.assertIsNone(raw)
        self.assertTrue(info['outside_FUNC_terminal_trim_verified'])
        self.assertEqual(info['removed_bytes_hex'], 'c046')
        self.assertEqual(pin['sha256'], asmdiff.sha(self.elf))

    def test_live_return_cannot_be_silently_trimmed(self):
        self.raw = bytes.fromhex('70470847')
        self.function_size = 4
        self.report_path.write_text(json.dumps(self.report))
        with patch.object(asmdiff.subprocess, 'run', side_effect=self.binutils):
            with self.assertRaisesRegex(ValueError, 'outside-FUNC C046'):
                asmdiff.run(self.report_path, self.path/'rejected', objdump='objdump')
        self.assertFalse((self.path/'rejected').exists())
        self.assertEqual(self.current.read_bytes(), bytes.fromhex('7047'))

    def test_explicit_full_view_restores_clipped_return_without_repairing_report(self):
        self.raw = bytes.fromhex('70470847')
        self.function_size = 4
        self.report_path.write_text(json.dumps(self.report))
        before = self.report_path.read_bytes()
        with patch.object(asmdiff.subprocess, 'run', side_effect=self.binutils):
            result = asmdiff.run(self.report_path, self.path/'full', objdump='objdump',
                                 full_elf_text=True)
        self.assertEqual(result['sizes']['generated'], 4)
        self.assertEqual(result['generated_extent']['reported_generated_bytes'], 2)
        self.assertFalse(result['generated_extent']['outside_FUNC_terminal_trim_verified'])
        self.assertEqual((self.path/'full/generated.elf-text.bin').read_bytes(), self.raw)
        self.assertEqual(result['full_elf_text_sha256'], asmdiff.sha(self.path/'full/generated.elf-text.bin'))
        self.assertEqual(self.report_path.read_bytes(), before)
        self.assertEqual(self.current.read_bytes(), bytes.fromhex('7047'))
        self.assertTrue(result['diagnostic_only'])

    def test_nop_inside_function_requires_explicit_full_view(self):
        self.function_size = 4
        with patch.object(asmdiff.subprocess, 'run', side_effect=self.binutils):
            with self.assertRaisesRegex(ValueError, 'outside-FUNC'):
                self.extent()

    def test_unpinned_or_changed_elf_is_refused(self):
        self.report['compile_inputs']['artifacts'] = {}
        with self.assertRaisesRegex(ValueError, 'Pinned ELF required'):
            self.extent(True)
        self.report['compile_inputs']['artifacts']['elf'] = {'path': str(self.elf), 'sha256': '0'*64}
        with self.assertRaisesRegex(ValueError, 'ELF differs'):
            self.extent(True)

    def test_full_view_cannot_substitute_a_different_binary(self):
        self.raw = bytes.fromhex('0847c046')
        with patch.object(asmdiff.subprocess, 'run', side_effect=self.binutils):
            with self.assertRaisesRegex(ValueError, 'not a prefix'):
                self.extent(True)

    def test_function_entry_and_extent_are_checked(self):
        for entry, size, message in ((0x8002001, 2, 'entry differs'),
                                      (0x8001001, 6, 'outside generated')):
            with self.subTest(entry=entry, size=size):
                self.entry, self.function_size = entry, size
                with patch.object(asmdiff.subprocess, 'run', side_effect=self.binutils):
                    with self.assertRaisesRegex(ValueError, message):
                        self.extent(True)

    def test_untrimmed_legacy_report_requires_no_new_elf_dependency(self):
        self.report['module_configuration']['trailing_alignment_bytes'] = 0
        self.report['compile_inputs']['artifacts'] = {}
        self.assertEqual(self.extent(), (None, None, None))

    def test_elf_drift_during_disassembly_does_not_publish(self):
        self.report_path.write_text(json.dumps(self.report))
        def drift(command, **kwargs):
            result = self.binutils(command, **kwargs)
            if command[0] == 'objdump':
                self.elf.write_bytes(b'changed')
            return result
        with patch.object(asmdiff.subprocess, 'run', side_effect=drift):
            with self.assertRaisesRegex(ValueError, 'ELF changed during'):
                asmdiff.run(self.report_path, self.path/'drift', objdump='objdump')
        self.assertFalse((self.path/'drift').exists())


if __name__ == '__main__':
    unittest.main()
