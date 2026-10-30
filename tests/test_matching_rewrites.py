"""Deterministic source/ASM hints, with counterexamples and read-only CLI checks."""
import contextlib
import hashlib
import io
import json
from pathlib import Path
import sys
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
import check_matching_rewrites as checker


REFERENCE = """.type original, %function
original:
 push {r4, lr}
 cmp r0, #0
 blt .Lbad
 cmp r0, #15
 bgt .Lbad
 cmp r1, #0
 blt .Lbad
 cmp r1, #15
 bgt .Lbad
 movs r0, #1
 bx lr
.Lbad:
 movs r0, #0
 bx lr
"""
FOLDED = """.type candidate, %function
candidate:
 push {r4, lr}
 cmp r0, #15
 bhi .Lbad
 cmp r1, #15
 bhi .Lbad
 movs r0, #1
 bx lr
.Lbad:
 movs r0, #0
 bx lr
"""


class RewriteTests(unittest.TestCase):
    def test_fixed_binding_before_stack_formal_use_warns_not_proves_ABI(self):
        source='''int f(void *a, void *b, unsigned action, unsigned detail,
                       unsigned argument, unsigned mode) {
            register unsigned home __asm__("r7") = detail;
            __asm__("" : "+r"(home));
            return eval(a,b,action,home,argument,mode);
        }'''
        result=checker.analyze(source)
        hits=[x for x in result['findings'] if x['rule']=='FIXED_REGISTER_STACK_FORMAL_LIVENESS']
        self.assertEqual(len(hits),1)
        self.assertIn('argument',hits[0]['evidence']['later_stack_formals'])
        self.assertFalse(hits[0]['evidence']['parameter_home_conflict_proven'])

    def test_prebinding_ordinary_copy_does_not_prove_input_safety(self):
        source='''int f(void *a, void *b, unsigned action, unsigned detail,
                     unsigned argument, unsigned mode) {
            unsigned saved_argument=argument;
            unsigned saved_mode=mode;
            register unsigned home __asm__("r7") = detail;
            return eval(a,b,action,home,saved_argument,saved_mode);
        }'''
        hits=[x for x in checker.analyze(source)['findings']
              if x['rule']=='FIXED_REGISTER_STACK_FORMAL_LIVENESS']
        self.assertEqual(len(hits),1)
        self.assertEqual(hits[0]['evidence']['later_input_carriers'],
                         {'saved_argument':['argument'], 'saved_mode':['mode']})
        self.assertFalse(hits[0]['evidence']['parameter_home_conflict_proven'])

    def test_transitive_prebinding_copy_keeps_lifetime_warning(self):
        source='''int f(int a,int b,int c,int d,int fifth) {
            int saved=fifth; int again=saved;
            register int home __asm__("r7")=d;
            return again+home;
        }'''
        hits=[x for x in checker.analyze(source)['findings']
              if x['rule']=='FIXED_REGISTER_STACK_FORMAL_LIVENESS']
        self.assertEqual(hits[0]['evidence']['later_input_carriers'], {'again':['fifth']})

    def test_four_formals_and_unused_stack_input_are_counterexamples(self):
        four='''int f(int a,int b,int c,int d) {
            register int home __asm__("r7")=d;
            return a+b+c+home;
        }'''
        unused='''int f(int a,int b,int c,int d,int fifth) {
            register int home __asm__("r7")=d;
            return a+b+c+home;
        }'''
        for source in [unused,four]:
            self.assertNotIn('FIXED_REGISTER_STACK_FORMAL_LIVENESS',self.rules(source))

    def test_six_readwrite_outputs_expand_to_twelve_operands(self):
        source='''void f(void) {int a,b,c,d,e,f;
            asm("" : "+r"(a), "+r"(b), "+r"(c), "+r"(d), "+r"(e), "+r"(f)); }'''
        hits=[x for x in checker.analyze(source)['findings'] if x['rule']=='AGBCC_ASM_OPERAND_LIMIT']
        self.assertEqual(len(hits),1)
        self.assertEqual(hits[0]['evidence']['expanded_operands'],12)
        self.assertFalse(hits[0]['evidence']['abi_safety_proven'])

    def test_five_readwrite_and_one_explicit_input_exceeds_limit(self):
        source='''void f(void) {int a,b,c,d,e,f;
            asm("mov %0,%1" : "+r"(a), "+r"(b), "+r"(c), "+r"(d), "+r"(e) : "r"(f)); }'''
        hits=[x for x in checker.analyze(source)['findings'] if x['rule']=='AGBCC_ASM_OPERAND_LIMIT']
        self.assertEqual(hits[0]['evidence']['expanded_operands'],11)

    def test_five_readwrite_at_limit_and_clobbers_not_operands(self):
        source='''void f(void) {int a,b,c,d,e;
            __asm__ volatile("" : "+r"(a), "+r"(b), "+r"(c), "+r"(d), "+r"(e) : : "cc", "memory"); }'''
        self.assertNotIn('AGBCC_ASM_OPERAND_LIMIT',self.rules(source))

    def test_two_three_operand_groups_are_syntax_only_counterexample(self):
        source='''void f(void) {int a,b,c,d,e,f;
            asm("" : "+r"(a), "+r"(b), "+r"(c));
            asm("" : "+r"(d), "+r"(e), "+r"(f)); }'''
        self.assertNotIn('AGBCC_ASM_OPERAND_LIMIT',self.rules(source))

    def test_output_only_not_double_counted(self):
        source='''void f(void) {int a,b,c,d,e,f;
            asm("real instruction" : "=r"(a), "=r"(b), "=r"(c), "=r"(d), "=r"(e), "=r"(f)); }'''
        self.assertNotIn('AGBCC_ASM_OPERAND_LIMIT',self.rules(source))

    def test_nested_expression_separators_do_not_hide_overflow(self):
        source='''void f(void) {int a,b,c,d,e,f;
            asm("template:comma," : "+r"(a), "+r"(b), "+r"(c), "+r"(d), "+r"(e)
                : "r"(choose(a,b) ? c : d), "r"(f) : "cc"); }'''
        hits=[x for x in checker.analyze(source)['findings'] if x['rule']=='AGBCC_ASM_OPERAND_LIMIT']
        self.assertEqual(hits[0]['evidence']['expanded_operands'],12)

    def test_adjacent_constraint_strings_and_legacy_modifier_order(self):
        source='''void f(void) {int a,b,c,d,e,f;
            asm("" : "+" "r"(a), "r+"(b), "+r"(c), "+r"(d), "+r"(e), "+r"(f)); }'''
        self.assertIn('AGBCC_ASM_OPERAND_LIMIT',self.rules(source))

    def test_unexpanded_constraint_is_not_claimed_countable(self):
        source='''void f(void) {int a,b,c,d,e,f;
            asm("" : OUTPUT(a), "+r"(b), "+r"(c), "+r"(d), "+r"(e), "+r"(f)); }'''
        self.assertNotIn('AGBCC_ASM_OPERAND_LIMIT',self.rules(source))

    def rules(self, source, a=None, b=None, function=None):
        return [x["rule"] for x in checker.analyze(source, a, b, function)["findings"]]

    def test_late_declaration_after_asm_and_assignment(self):
        self.assertEqual(self.rules('int f(void) { int a; a=1; asm("" : "+r"(a)); int b; return a; }'),
                         ["C89_LATE_DECLARATION"])

    def test_nested_real_scope_preserves_late_local(self):
        self.assertEqual(self.rules('int f(void) { int a; a=1; { int b=2; a=b; } return a; }'), [])

    def test_for_c99_declaration(self):
        self.assertIn("C89_FOR_DECLARATION", self.rules('int f(void) { for (u16 i=0; i<3; i++) {} return 0; }'))

    def test_for_old_style_is_not_error(self):
        self.assertEqual(self.rules('int f(void) { u16 i; for(i=0;i<3;i++) {} return 0; }'), [])

    def test_comments_strings_and_preprocessor_not_code(self):
        text = '#define EXAMPLE int b;\nint f(void) { char *s="int b; for(int i=0;;)"; /* asm(\"\"); int b; */ return 0; }'
        self.assertEqual(self.rules(text), [])

    def test_null_statement_still_statement(self):
        self.assertIn("C89_LATE_DECLARATION", self.rules('int f(void) { ; int b; return 0; }'))

    def test_aggregate_initializer_does_not_create_statement_scope(self):
        self.assertEqual(self.rules('int f(void) { int a[2]={1,2}; int b=0; return b; }'), [])

    def test_simple_typedef_declaration(self):
        self.assertIn("C89_LATE_DECLARATION", self.rules('typedef int Count; int f(void) { x(); Count a; return a; }'))

    def test_function_pointer_typedef_declaration_at_block_start(self):
        source = 'typedef unsigned short u16; typedef u16 (*Callback)(void *); int f(void) { Callback callback; u16 size; return 0; }'
        self.assertNotIn('C89_LATE_DECLARATION', self.rules(source))

    def test_function_pointer_typedef_still_detects_late_declaration(self):
        source = 'typedef int (*Callback)(void *); int f(void) { run(); Callback callback; return 0; }'
        self.assertIn('C89_LATE_DECLARATION', self.rules(source))

    def test_function_pointer_parameter_name_is_not_typedef(self):
        source = 'typedef int (*Callback)(void (*nested)(void)); int f(void) { int nested; nested = 1; int later; return nested; }'
        findings = checker.analyze(source)['findings']
        self.assertEqual([x['evidence']['declaration_start'] for x in findings if x['rule'] == 'C89_LATE_DECLARATION'], ['int'])

    def test_struct_fields_and_asm_qualifiers_not_declarations(self):
        source = 'typedef struct { int mode,selector; } Work; int f(Work *work) { Work *w=work; switch(w->mode) { case 0: w->selector=1; break; default: break; } __asm__ volatile("" : "+r"(w)); return 0; }'
        self.assertEqual(self.rules(source), [])

    def test_typedef_struct_alias_retained_after_body(self):
        self.assertIn("C89_LATE_DECLARATION", self.rules('typedef struct { int field; } Work; int f(void) { run(); Work w; return 0; }'))

    def test_only_requested_function_checked(self):
        text = 'int a(void) { x(); int b; return b; } int ok(void) { return 0; }'
        self.assertEqual(self.rules(text, function="ok"), [])
        with self.assertRaisesRegex(ValueError, "not found"):
            checker.analyze(text, function="missing")

    def test_no_definition_is_explicit_not_clean_syntax(self):
        report = checker.analyze('int callback(void);')
        self.assertTrue(any("no function checks ran" in x for x in report["limits"]))

    def test_unsupported_unbalanced_input_rejected(self):
        with self.assertRaises(ValueError):
            checker.analyze('int f(void) { if (x) { return 0; }')

    def test_compound_range_requires_actual_paired_asm(self):
        source = 'int f(int x,int y) { if(x<0 || x>=16 || y<0 || y>=16) return 0; return 1; }'
        self.assertIn("O2_COMPOUND_SIGNED_RANGE", self.rules(source, REFERENCE, FOLDED))
        self.assertNotIn("O2_COMPOUND_SIGNED_RANGE", self.rules(source))
        self.assertNotIn("O2_COMPOUND_SIGNED_RANGE", self.rules(source, FOLDED, FOLDED))

    def test_independent_guards_do_not_get_compound_hint(self):
        source = 'int f(int x,int y) { if(x<0) goto bad; if(x>15) goto bad; if(y<0) goto bad; if(y>15) goto bad; return 1; bad: return 0; }'
        self.assertNotIn("O2_COMPOUND_SIGNED_RANGE", self.rules(source, REFERENCE, FOLDED))

    def test_multiple_asm_entries_disable_shape_hints(self):
        source = 'int f(int x) { if(x<0 || x>15) return 0; return 1; }'
        report = checker.analyze(source, REFERENCE + '\n.type other, %function\nother:\n bx lr\n', FOLDED)
        self.assertNotIn("O2_COMPOUND_SIGNED_RANGE", [x["rule"] for x in report["findings"]])
        self.assertTrue(any("skipped" in x for x in report["limits"]))

    def test_generated_ram_literal_needs_numeric_source_pointer(self):
        a = 'original:\n ldr r0, .Lbase\n bx lr\n.Lbase:\n .word 0x02000000\n'
        b = 'candidate:\n ldr r0, .Lbase\n bx lr\n.Lbase:\n .word 0x02000020\n'
        self.assertIn("NUMERIC_RAM_BASE_FOLD", self.rules('int f(void) { return ((u16 *)0x02000000)[16]; }', a, b))
        self.assertNotIn("NUMERIC_RAM_BASE_FOLD", self.rules('int f(void) { return root->amount; }', a, b))
        self.assertNotIn("NUMERIC_RAM_BASE_FOLD", self.rules('int f(void) { return ((u16 *)0x02000000)[16]; }', a, a))

    def test_signed_switch_snapshot_question_needs_paired_narrow_load_and_guard(self):
        source = 'int f(Ctx *ctx) { u32 state=ctx->state; switch(state) { case 0: return 0; default: return 1; } }'
        original = '08001000: 8804 ldrh r4,[r0,#0]\n08001002: 2c01 cmp r4,#1\n08001004: dc00 bgt.n 0x8001008\n08001006: 2000 movs r0,#0\n08001008: 4770 bx lr\n'
        generated = original.replace('dc00 bgt.n 0x8001008', 'd800 bhi.n 8001008 <candidate+0x8>')
        report = checker.analyze(source, original, generated)
        item = next(x for x in report['findings'] if x['rule'] == 'SWITCH_SNAPSHOT_SIGNEDNESS')
        self.assertEqual(item['evidence']['snapshot'], 'state')
        self.assertIn('keep storage, helper ABI and writes unchanged', item['suggestion'])
        self.assertNotIn('SWITCH_SNAPSHOT_SIGNEDNESS', self.rules(source.replace('u32 state', 's32 state'), original, generated))
        self.assertNotIn('SWITCH_SNAPSHOT_SIGNEDNESS', self.rules(source, original, original))

    def test_switch_question_rejects_wide_or_changed_value_and_target(self):
        source = 'int f(Ctx *ctx) { u32 state=ctx->state; switch(state) { default: return 0; } }'
        original = '08001000: 8804 ldrh r4,[r0,#0]\n08001002: 2c01 cmp r4,#1\n08001004: dc00 bgt 0x8001008\n'
        generated = original.replace('dc00 bgt', 'd800 bhi')
        cases = [(original.replace('ldrh', 'ldr'), generated.replace('ldrh', 'ldr')),
                 (original, generated.replace('0x8001008', '0x800100a')),
                 (original, generated.replace('cmp r4,#1', 'cmp r4,#2'))]
        for a, b in cases:
            with self.subTest(original=a, generated=b):
                self.assertNotIn('SWITCH_SNAPSHOT_SIGNEDNESS', self.rules(source, a, b))

    def test_switch_question_requires_immediate_named_snapshot(self):
        original = '08001000: 8804 ldrh r4,[r0,#0]\n08001002: 2c01 cmp r4,#1\n08001004: dc00 bgt 0x8001008\n'
        generated = original.replace('bgt', 'bhi')
        for body in ['switch(ctx->state) { default: return 0; }',
                     'u32 state=ctx->state; state=another(); switch(state) { default: return 0; }',
                     'u32 state=ctx->state; switch(other) { default: return 0; }']:
            self.assertNotIn('SWITCH_SNAPSHOT_SIGNEDNESS', self.rules('int f(Ctx *ctx) { '+body+' }', original, generated))

    def test_switch_question_does_not_cross_a_working_register_redefinition(self):
        source = 'int f(Ctx *ctx) { u32 state=ctx->state; switch(state) { default: return 0; } }'
        original = '08001000: 8804 ldrh r4,[r0,#0]\n08001002: 1c14 adds r4,r2,#0\n08001004: 2c01 cmp r4,#1\n08001006: dc00 bgt 0x800100a\n'
        self.assertNotIn('SWITCH_SNAPSHOT_SIGNEDNESS', self.rules(source, original, original.replace('bgt', 'bhi')))
        unchanged = original.replace('1c14 adds r4,r2,#0', '2101 movs r1,#1')
        self.assertNotIn('SWITCH_SNAPSHOT_SIGNEDNESS', self.rules(source, unchanged, original.replace('bgt', 'bhi')))

    def test_raw_disassembly_pool_is_not_proof_of_a_new_ram_literal(self):
        source = 'int f(void) { return *((u16 *)0x03003900); }'
        raw = '08001000: 4800 ldr r0, [pc, #0]\n08001002: 4770 bx lr\n08001004: 3900 subs r1, #0\n08001006: 0300 lsls r0, r0, #12\n'
        mapped = '08001000: 4800 ldr r0, [pc, #0]\n08001002: 4770 bx lr\n08001004: 03003900 .word 0x03003900\n'
        report = checker.analyze(source, raw, mapped)
        self.assertNotIn("NUMERIC_RAM_BASE_FOLD", [x["rule"] for x in report["findings"]])
        self.assertTrue(any("lack explicit .word" in x for x in report["limits"]))

    def test_addressed_explicit_pool_still_detects_a_different_literal(self):
        original = '08001000: 4800 ldr r0, [pc, #0]\n08001002: 4770 bx lr\n08001004: 02000000 .word 0x02000000\n'
        generated = original.replace('02000000', '02000020')
        self.assertIn("NUMERIC_RAM_BASE_FOLD", self.rules('int f(void) { return ((u16 *)0x02000000)[16]; }', original, generated))

    def test_partial_literal_inventory_does_not_establish_absence(self):
        original = '08001000: 4801 ldr r0, [pc, #4]\n08001002: 4770 bx lr\n08001004: 02000000 .word 0x02000000\n'
        generated = original.replace('02000000', '02000020')
        report = checker.analyze('int f(void) { return ((u16 *)0x02000000)[16]; }', original, generated)
        self.assertNotIn("NUMERIC_RAM_BASE_FOLD", [x["rule"] for x in report["findings"]])

    def test_operand_normalization_before_subtraction_hint(self):
        a = 'original:\n sub sp, #4\n lsls r0,r0,#16\n asrs r0,r0,#16\n subs r0,r0,r1\n bx lr\n'
        b = 'candidate:\n sub sp, #4\n subs r0,r0,r1\n lsls r0,r0,#16\n asrs r0,r0,#16\n bx lr\n'
        self.assertIn("SIGNED_NORMALIZATION_SITE", self.rules('int f(int a,int b) { return (s16)(a-b); }', a, b))
        self.assertNotIn("SIGNED_NORMALIZATION_SITE", self.rules('int f(int a,int b) { s16 x=a,y=b; return (s16)(x-y); }', a, a))

    def test_register_only_difference_is_not_exact_or_cause_proof(self):
        a, b = 'original:\n mov r4,r0\n bx lr\n', 'candidate:\n mov r5,r0\n bx lr\n'
        report = checker.analyze('int f(int x) { return x; }', a, b)
        item = next(x for x in report["findings"] if x["rule"] == "REGISTER_OPERANDS_ONLY")
        self.assertEqual(item["evidence"]["first_difference"]["original"]["line"], 2)
        self.assertIn("does not prove", item["suggestion"])
        self.assertNotIn("REGISTER_OPERANDS_ONLY", self.rules('int f(int x) { return x; }', a, 'mov r4,#7\n bx lr\n'))

    def test_entry_argument_capture_order(self):
        a = 'push {r4,r5,lr}\n mov r4,r0\n adds r5,r1,#0\n cmp r0,#0\n bx lr\n'
        b = 'push {r4,r5,lr}\n adds r5,r1,#0\n mov r4,r0\n cmp r0,#0\n bx lr\n'
        self.assertIn("ENTRY_ARGUMENT_COPY_ORDER", self.rules('int f(int a,int b) { return a+b; }', a, b))
        self.assertNotIn("ENTRY_ARGUMENT_COPY_ORDER", self.rules('int f(int a,int b) { return a+b; }', a, a))

    def test_entry_does_not_follow_clobbered_formal_or_call(self):
        a = checker.parse_asm('mov r0,#7\n mov r4,r0\n mov r5,r1\n')['instructions']
        self.assertEqual([x['argument'] for x in checker.entry_copies(a)], [1])
        b = checker.parse_asm('bl helper\n mov r4,r0\n mov r5,r1\n')['instructions']
        self.assertEqual(checker.entry_copies(b), [])

    def test_entry_aliases_are_physical_registers(self):
        a = 'mov sl,r0\n mov r5,r1\n cmp r0,#0\n'
        b = 'mov r5,r1\n mov r10,r0\n cmp r0,#0\n'
        self.assertIn("ENTRY_ARGUMENT_COPY_ORDER", self.rules('int f(int a,int b) { return a+b; }',a,b))

    def test_local_register_signatures_require_real_addresses(self):
        a = '.L_08000000:\n str r6,[sp,#4]\n.L_08000002:\n add r0,r0,#1\n.L_08000004:\n str r6,[sp,#12]\n'
        b = '08001000 <f>:\n8001000: 9601 str r7,[sp,#4]\n8001002: 3002 add r0,r0,#2\n8001004: 9703 str r7,[sp,#12]\n'
        source='int f(void) { return 0; }'
        self.assertIn("LOCAL_REGISTER_DIFFERENCES",self.rules(source,a,b))
        self.assertNotIn("LOCAL_REGISTER_DIFFERENCES",self.rules(source,'str r6,[sp,#4]\nadd r0,r0,#1\nstr r6,[sp,#12]\n',b))

    def test_call_setup_order_requires_same_callee_and_exact_moves(self):
        a = 'mov r0,r4\n mov r1,r5\n bl helper\n bx lr\n'
        b = 'mov r1,r5\n mov r0,r4\n bl helper\n bx lr\n'
        self.assertIn("CALL_ARGUMENT_SETUP_ORDER", self.rules('int f(void) { return helper(); }', a, b))
        self.assertNotIn("CALL_ARGUMENT_SETUP_ORDER", self.rules('int f(void) { return helper(); }', a, b.replace('bl helper', 'bl other')))

    def test_objdump_add_opcode_not_eaten_as_hex(self):
        insns = checker.parse_asm('08000000 <f>:\n 8000000: 1c08 add r0, r1, #0\n 8000002: 4770 bx lr\n')['instructions']
        self.assertEqual([x['op'] for x in insns], ['add','bx'])

    def test_empty_asm_outputs_and_truthful_inputs(self):
        self.assertIn("EMPTY_ASM_OUTPUT_ONLY", self.rules('int f(void) { int x; asm("" : "=r"(x)); return x; }'))
        self.assertIn("EMPTY_ASM_OUTPUT_ONLY", self.rules('int f(void) { int x; asm("" : "=r"(x) : : "memory"); return x; }'))
        self.assertNotIn("EMPTY_ASM_OUTPUT_ONLY", self.rules('int f(void) { int x=1; asm("" : "+r"(x)); return x; }'))
        self.assertNotIn("EMPTY_ASM_OUTPUT_ONLY", self.rules('int f(void) { int x=1; asm("" : "=r"(x) : "0"(x)); return x; }'))

    def test_cli_repeated_binary_hashes_and_inputs_remain_unchanged(self):
        with tempfile.TemporaryDirectory() as temp:
            p = Path(temp); source=p/'a.c'; source.write_text('int f(void) { return 1; }')
            a=p/'a.bin'; b=p/'b.bin'; a.write_bytes(b'\x01\x20\x70\x47'); b.write_bytes(a.read_bytes())
            original = {x:hashlib.sha256(x.read_bytes()).hexdigest() for x in (source,a,b)}
            output=p/'hints.json'
            with contextlib.redirect_stdout(io.StringIO()):
                code=checker.main([str(source),'--binary',str(a),'--previous-binary',str(b),'--output',str(output),'--json'])
            self.assertEqual(code,0);report=json.loads(output.read_text())
            self.assertEqual(report['findings'][0]['rule'],'IDENTICAL_CANDIDATE_BINARY')
            self.assertEqual(len(report['inputs']),3)
            self.assertTrue(all(hashlib.sha256(x.read_bytes()).hexdigest()==sha for x,sha in original.items()))

    def test_cli_existing_output_is_never_overwritten(self):
        with tempfile.TemporaryDirectory() as temp:
            source=Path(temp)/'a.c'; original='int f(void) { return 0; }'; source.write_text(original)
            with contextlib.redirect_stderr(io.StringIO()):
                self.assertEqual(checker.main([str(source),'--output',str(source)]),2)
            self.assertEqual(source.read_text(),original)

    def test_cli_incomplete_pair_rejected_before_work(self):
        with contextlib.redirect_stderr(io.StringIO()), self.assertRaises(SystemExit) as error:
            checker.main(['missing.c','--reference-asm','missing.s'])
        self.assertEqual(error.exception.code,2)

    def test_build_report_single_command_and_tamper_rejection(self):
        with tempfile.TemporaryDirectory() as temp:
            p=Path(temp); src=p/'f.i'; asm=p/'f.s'; ref=p/'ref.s'; doc=p/'report.json'
            src.write_text('int f(void) { return 0; }');asm.write_text('movs r0,#0\nbx lr\n');ref.write_text(asm.read_text())
            pins={key:{'path':str(file),'sha256':hashlib.sha256(file.read_bytes()).hexdigest()} for key,file in [('preprocessed',src),('disassembly',asm)]}
            build={'segments':[{'reference_disassembly':str(ref)}],'compile_inputs':{'artifacts':pins}};doc.write_text(json.dumps(build))
            output=io.StringIO()
            with contextlib.redirect_stdout(output):self.assertEqual(checker.main(['--build-report',str(doc),'--json']),0)
            self.assertEqual(json.loads(output.getvalue())['functions'],['f'])
            src.write_text('int f(void) { return 7; }')
            with contextlib.redirect_stderr(io.StringIO()):self.assertEqual(checker.main(['--build-report',str(doc),'--json']),2)

    def test_build_report_multiple_segments_fail_closed(self):
        with tempfile.TemporaryDirectory() as temp:
            path=Path(temp)/'report.json';path.write_text(json.dumps({'segments':[{},{}]}))
            with contextlib.redirect_stderr(io.StringIO()):self.assertEqual(checker.main(['--build-report',str(path)]),2)


if __name__ == '__main__':
    unittest.main()
