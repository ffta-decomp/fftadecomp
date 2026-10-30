import importlib.util
from pathlib import Path
import sys
import unittest
sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools'))
from diagnose_module_build import summarize

class SummaryTests(unittest.TestCase):
    def test_shifted_text_never_inflates_byte_credit(self):
        segment = dict(module='M', matching_bytes=2, reference_size=100, generated_size=102, fits=False)
        alignment = dict(diagnostic_line_counts={'same_text_lines':40},
                         shifted_runs=[dict(aligned_lines=20, address_delta=2)],
                         possible_moved_sequences=[{}], report_sha256='pinned')
        result = summarize(segment, alignment, '/tmp/diagnostic')
        self.assertEqual(result['positional']['matching_bytes'], 2)
        self.assertFalse(result['positional']['fits'])
        self.assertTrue(result['diagnostic_only'])
        self.assertNotIn('matched_bytes', result)
        self.assertEqual(result['possible_moved_sequence_count'], 1)

    def test_largest_runs_bounded_without_losing_total(self):
        alignment = dict(diagnostic_line_counts={}, shifted_runs=[dict(aligned_lines=i) for i in range(12)],
                         possible_moved_sequences=[], report_sha256='pinned')
        result = summarize({'module':'M'}, alignment, '/tmp/diagnostic')
        self.assertEqual(result['shifted_run_count'], 12)
        self.assertEqual([x['aligned_lines'] for x in result['largest_shifted_runs']], list(range(11,3,-1)))

if __name__ == '__main__': unittest.main()
