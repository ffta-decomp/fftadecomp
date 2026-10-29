import importlib.util
from pathlib import Path
import unittest
ROOT=Path(__file__).resolve().parents[1]
spec=importlib.util.spec_from_file_location('progress_generator',ROOT/'tools/update_source_progress.py')
p=importlib.util.module_from_spec(spec);spec.loader.exec_module(p)
class ProgressValidation(unittest.TestCase):
    def test_false_proof_rejected_explicitly(self):
        with self.assertRaisesRegex(ValueError,'bad proof'):p.require(False,'bad proof')
    def test_union_deduplicates_overlap(self):
        self.assertEqual(p.measure([[2,8],[4,10],[10,12]]),10)
    def test_invalid_range_rejected(self):
        with self.assertRaises(ValueError):p.union([[4,4]])
