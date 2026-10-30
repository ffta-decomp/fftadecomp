import sys
from pathlib import Path
import unittest
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'tools'))
import asmdiff

def dump(ops):
    return '\n'.join(f' {0x8001000+i*2:x}:\t0000      \t{x}' for i,x in enumerate(ops))
def analyze(a,b):
    return asmdiff.analyze_dumps(dump(a),dump(b))[0]['difference_details']
class DetailTests(unittest.TestCase):
    def test_register_difference_addressed(self):
        r=analyze(['mov\tr0, r4'],['mov\tr0, r5'])['register_difference_sites'][0]
        self.assertEqual(r['reference']['address'],0x8001000)
        self.assertEqual(r['operand_changes'][0]['current'],'r5')
    def test_setup_order(self):
        r=analyze(['mov\tr0, r4','mov\tr1, r5','bl\t0x08002000'],
                  ['mov\tr1, r5','mov\tr0, r4','bl\t0x08002000'])
        self.assertEqual(r['call_setup_differences'][0]['kind'],'same_setup_multiset_different_order')
    def test_stack_argument_candidate(self):
        r=analyze(['str\tr4, [sp, #0]','bl\t0x08002000'],['str\tr5, [sp, #0]','bl\t0x08002000'])
        self.assertEqual(len(r['call_setup_differences'][0]['reference_setup']),1)
    def test_branch_stops_scan(self):
        r=analyze(['mov\tr0, r4','b\t0x08001004','bl\t0x08002000'],
                  ['mov\tr0, r5','b\t0x08001004','bl\t0x08002000'])
        self.assertEqual(r['call_setup_differences'],[])
    def test_changed_target_not_parameter_order(self):
        r=analyze(['mov\tr0, r4','bl\t0x08002000'],['mov\tr0, r4','bl\t0x08003000'])
        self.assertFalse(r['call_setup_differences'][0]['same_textual_target'])
    def test_equal_no_findings(self):
        a=['mov\tr0, r4','bl\t0x08002000'];r=analyze(a,a)
        self.assertEqual(r['call_setup_differences'],[])
        self.assertEqual(r['register_difference_sites'],[])
    def test_alias_not_difference(self):
        r=analyze(['mov\tr0, sl'],['mov\tr0, r10'])
        self.assertEqual(r['register_difference_sites'],[])
    def test_shifted_call_preserves_actual_target_and_displacement(self):
        reference = ' 8001000:\tf000 f800\tbl\t0x8002000\n 8001004:\t4620\tmov\tr0, r4\n'
        current = ' 8001004:\tf000 f800\tbl\t0x8002000\n 8001008:\t4628\tmov\tr0, r5\n'
        detail = asmdiff.analyze_dumps(reference, current)[0]['difference_details']
        site = detail['register_difference_sites'][0]
        left, right = site['reference_context'][0], site['current_context'][0]
        self.assertEqual(left['instruction'], 'bl 0x8002000')
        self.assertEqual(right['instruction'], 'bl 0x8002000')
        self.assertEqual(0x8002000 - left['address'], 0x1000)
        self.assertEqual(0x8002000 - right['address'], 0xffc)
        self.assertEqual(detail['call_setup_differences'], [])

    def test_shifted_call_does_not_hide_different_actual_target(self):
        reference = ' 8001000:\tf000 f800\tbl\t0x8002000\n 8001004:\t4620\tmov\tr0, r4\n'
        current = ' 8001004:\tf000 f800\tbl\t0x8002004\n 8001008:\t4628\tmov\tr0, r5\n'
        detail = asmdiff.analyze_dumps(reference, current)[0]['difference_details']
        call = detail['call_setup_differences'][0]
        self.assertEqual(call['reference_call']['instruction'], 'bl 0x8002000')
        self.assertEqual(call['current_call']['instruction'], 'bl 0x8002004')
        self.assertFalse(call['same_textual_target'])
        self.assertEqual(0x8002000 - call['reference_call']['address'], 0x1000)
        self.assertEqual(0x8002004 - call['current_call']['address'], 0x1000)
if __name__=='__main__':unittest.main()
