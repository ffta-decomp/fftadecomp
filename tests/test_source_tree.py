import importlib.util
import shutil
import tempfile
from pathlib import Path
import unittest

spec = importlib.util.spec_from_file_location('source_tree', Path(__file__).resolve().parents[1] / 'tools/source_tree.py')
tree = importlib.util.module_from_spec(spec)
spec.loader.exec_module(tree)


class SourceTreeTests(unittest.TestCase):
    def test_scalar_extraction_does_not_add_an_absent_type(self):
        data = b'typedef unsigned char u8;\ntypedef unsigned int u32;\nu32 f(u8 a) { return a; }\n'
        self.assertEqual(tree.canonical_types(data), (data, None))
        full = b'typedef unsigned short u16;\n' + data
        changed, header = tree.canonical_types(full)
        self.assertEqual(header, 'ffta/unsigned_types.h')
        self.assertIn(b'u32 f(u8 a) { return a; }', changed)

    def test_noncanonical_alias_and_local_typedef_stay_untouched(self):
        data = b'typedef unsigned long u32;\ntypedef unsigned char u8;\ntypedef unsigned short u16;\n'
        self.assertEqual(tree.canonical_types(data), (data, None))
        local = b'int f(void) { typedef unsigned char u8; return 0; }\n'
        self.assertEqual(tree.canonical_types(local), (local, None))

    def test_token_proof_preserves_string_contents(self):
        self.assertEqual(tree.cpp_identity(b'int f ( void ) { return 2; }'),
                         tree.cpp_identity(b'int f(void){return 2;}'))
        self.assertNotEqual(tree.cpp_identity(b'char *s="a b";'), tree.cpp_identity(b'char *s="ab";'))

    def test_token_proof_handles_adjacent_typedefs_without_erasing_literals(self):
        self.assertEqual(tree.cpp_identity(b'typedef signed char s8; typedef signed short s16; int x;'),
                         tree.cpp_identity(b'int x;'))
        self.assertNotEqual(tree.cpp_identity(b'typedef unsigned long u32; int x;'),
                            tree.cpp_identity(b'int x;'))
        self.assertNotEqual(tree.cpp_identity(b'char *s="typedef signed char s8;";'),
                            tree.cpp_identity(b'char *s="";'))
        self.assertEqual(tree.cpp_identity(b'typedef short s16; typedef int s32; int x;'),
                         tree.cpp_identity(b'int x;'))

    @unittest.skipUnless(shutil.which('clang'), 'requires the production preprocessor')
    def test_complete_unit_relocation_preserves_preprocessed_program(self):
        with tempfile.TemporaryDirectory() as raw:
            root = Path(raw).resolve()
            old = root / 'src/batch99'
            old.mkdir(parents=True)
            (root / 'include').mkdir()
            (root / 'include/state.h').write_text('struct State { unsigned int count; };\n')
            (old / 'contract.h').write_text('#include "state.h"\n')
            source = ('typedef unsigned char u8;\ntypedef unsigned short u16;\ntypedef unsigned int u32;\n'
                      '#include "contract.h"\nu32 Count(struct State *s) { return s->count; }\n')
            (old / 'round00.c').write_text(source)
            module = {'name': 'Count', 'kind': 'c', 'source': 'src/batch99/round00.c',
                      'offset': 4096, 'size': 8, 'compiler_flags': ['-O2', '-mthumb-interwork']}
            migration = tree.SourceTree(root, [module], {'Count': {'domain': 'engine/state'}},
                                        shared_headers={'include/state.h': 'include/engine/state.h'})
            before = migration.preprocess()
            migration.stage()
            self.assertEqual(migration.preprocess(True), before)
            new = migration.relocate(module)
            self.assertEqual(new['source'], 'src/engine/state/08001000.c')
            self.assertEqual({k: v for k, v in new.items() if k != 'source'},
                             {k: v for k, v in module.items() if k != 'source'})
            self.assertEqual((old / 'round00.c').read_text(), source)
            self.assertTrue((root / 'include/ffta/unsigned_types.h').is_file())
            self.assertTrue((root / 'include/engine/state.h').is_file())

    def test_unknown_ownership_is_explicit_and_conflicts_fail_before_write(self):
        with tempfile.TemporaryDirectory() as raw:
            root = Path(raw).resolve()
            p = root / 'src/round00.c'
            p.parent.mkdir()
            p.write_text('int F(void) { return 2; }\n')
            module = {'name': 'F', 'kind': 'c', 'source': 'src/round00.c', 'offset': 4096, 'size': 8}
            migration = tree.SourceTree(root, [module], {})
            target = root / 'src/unknown/08001000.c'
            target.parent.mkdir()
            target.write_text('do not replace\n')
            with self.assertRaisesRegex(ValueError, 'overwrite'):
                migration.stage()
            self.assertEqual(target.read_text(), 'do not replace\n')


if __name__ == '__main__':
    unittest.main()
