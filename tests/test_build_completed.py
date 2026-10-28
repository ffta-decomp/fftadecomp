import importlib.util
from pathlib import Path
import sys
import unittest
ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'tools'))
import build_completed as b
class FailClosedBuild(unittest.TestCase):
    def test_wrong_revision(self):
        with self.assertRaisesRegex(ValueError,'Wrong ROM'):
            b.validate(b'bad',{'size':3,'sha256':'0'*64},{})
    def test_nonexact_selection_rejected(self):
        raw=b'abcd'
        module={'name':'x','kind':'c','offset':0,'size':2,'match_policy':'allow-differences'}
        with self.assertRaisesRegex(ValueError,'Only exact'):
            b.validate(raw,{'size':4,'sha256':b.sha(raw),'modules':[module]}, {'modules':[{'name':'x'}]})
    def test_overlap_rejected(self):
        raw=b'abcd'
        modules=[{'name':n,'kind':'c','offset':o,'size':2} for n,o in [('a',0),('b',1)]]
        with self.assertRaisesRegex(ValueError,'overlapping'):
            b.validate(raw,{'size':4,'sha256':b.sha(raw),'modules':modules}, {'modules':[{'name':'a'},{'name':'b'}]})
    def test_changed_source_rejected(self):
        raw=b'abcd'
        with self.assertRaisesRegex(ValueError,'hash mismatch'):
            b.validate(raw,{'size':4,'sha256':b.sha(raw),'modules':[]}, {'modules':[], 'files':[{'path':'src/README.md','sha256':'0'*64}]})
    def test_wrong_compiled_byte(self):
        with self.assertRaisesRegex(ValueError,'refusing output'):
            b.checked_bytes({'name':'sample','offset':1,'size':2},b'zz',b'abcd')
    def test_wrong_compiled_size(self):
        with self.assertRaises(ValueError):
            b.checked_bytes({'name':'sample','offset':1,'size':2},b'b',b'abcd')
    def test_generated_bytes_used(self):
        generated=b'bc'
        self.assertIs(b.checked_bytes({'name':'sample','offset':1,'size':2},generated,b'abcd'),generated)
if __name__=='__main__':unittest.main()
