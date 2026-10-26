import sys
from pathlib import Path
import unittest
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'tools'))
from recovery_public import without_staffing
class StaffingRedaction(unittest.TestCase):
    def test_recursive_aggregate_only(self):
        source={'actors':[{'id':'worker2'}],'worker_count':8,'dashboard':{'performance':[{'id':'team','bytes':100},{'id':'worker2','bytes':50}]},'rows':[{'actor':'worker3','original_bytes':42}]}
        self.assertEqual(without_staffing(source),{'dashboard':{'performance':[{'id':'team','bytes':100}]},'rows':[{'original_bytes':42}]})
        self.assertEqual(source['worker_count'],8)
    def test_progress_unchanged(self):
        data={'matched':123,'denominator':456,'systems':[{'id':'battle','bytes':78}]}
        self.assertEqual(without_staffing(data),data)
if __name__=='__main__': unittest.main()
