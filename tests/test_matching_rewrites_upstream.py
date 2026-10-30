"""Upstream transfer questions: lexical recognition, never automatic repair."""
import sys
from pathlib import Path
import unittest
ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'tools'))
import check_matching_rewrites as c

class TransferQuestions(unittest.TestCase):
    def rules(self, source, **kwargs):
        return {f['rule'] for f in c.analyze(source, **kwargs)['findings']}

    def test_early_tail(self):
        self.assertIn('EARLY_RETURN_MEMBER_TAIL', self.rules('void f(S *s){if(s->mode==254)return; s->count=0;}'))

    def test_return_at_end(self):
        self.assertNotIn('EARLY_RETURN_MEMBER_TAIL', self.rules('void f(S *s){s->count=0;return;}'))

    def test_other_function_store_not_correlated(self):
        self.assertNotIn('EARLY_RETURN_MEMBER_TAIL', self.rules('void f(void){return;} void g(S*s){s->count=0;}'))

    def test_comment_string_ignored(self):
        self.assertNotIn('EARLY_RETURN_MEMBER_TAIL', self.rules('void f(void){/* return; s->count=0; */ puts("return; s->count=0;");}'))

    def test_tagged_cast(self):
        self.assertIn('TAGGED_WORD_CAST_BACK', self.rules('void f(S*s){s->words[0]=(Callback)(bits|0x80000000u);}'))

    def test_plain_integer_rmw(self):
        self.assertNotIn('TAGGED_WORD_CAST_BACK', self.rules('void f(S*s){s->words[0]|=0x80000000u;}'))

    def test_low_mask_not_tagged(self):
        self.assertNotIn('TAGGED_WORD_CAST_BACK', self.rules('void f(S*s){s->words[0]=(Callback)(bits|0x80u);}'))

    def test_function_filter(self):
        self.assertNotIn('EARLY_RETURN_MEMBER_TAIL', self.rules('void f(S*s){return;s->count=0;} void g(void){}',function='g'))

if __name__=='__main__': unittest.main()
