import importlib.util
import pathlib
import sys
import tempfile
import unittest
ROOT=pathlib.Path(__file__).resolve().parents[1];sys.path.insert(0,str(ROOT/'tools'))
import check_public_bundle as privacy
import extract_asm as asm

class PublicToolkit(unittest.TestCase):
    def test_actual_payload_and_metadata(self):self.assertTrue(privacy.check()['ok'])
    def test_private_paths_sessions_and_keys_rejected(self):
        for value in ['/'+ 'Users/example/work','/'+ 'home/example/work','01a'+'00000-1234-1234-1234-123456789abc','ghp_'+'x'*35]:
            with self.subTest(value=value):
                with self.assertRaises(ValueError):privacy.check_text(value)
    def test_builder_preflight_import_closure_is_complete(self):
        import build_rom, compare_module_build, prepare_module_selection, build_function
        self.assertTrue(callable(build_rom.compile_module))
        self.assertTrue(callable(build_function.run_job))
    def test_game_addresses_and_normal_commands_allowed(self):
        privacy.check_text('0x080A5A7D python3 tools/extract_asm.py --rom "$RETAIL_ROM"')
    def test_traversal_and_nonasm_rejected(self):
        for path in ['../asm/a.s','/asm/a.s','asm/../a.s','asm/a.py','asm\\a.s']:
            with self.subTest(path=path):
                with self.assertRaises(ValueError):asm.safe_path(path)
    def test_unknown_revision_rejected_before_output(self):
        with tempfile.TemporaryDirectory() as d:
            p=pathlib.Path(d);(p/'rom').write_bytes(b'not a retail ROM');(p/'layout').write_text('{"schema":"rom-assembly-layout-v1","retail_sha256":"'+asm.RETAIL+'","rom_size":16}')
            with self.assertRaisesRegex(ValueError,'revision mismatch'):asm.extract(p/'rom',p/'layout',p/'out')
            self.assertFalse((p/'out').exists())
    def test_capstone_thumb_alias_is_assemblable_spelling(self):
        if importlib.util.find_spec('capstone') is None:self.skipTest('install requirements-extract.txt for decoder test')
        # Synthetic Thumb ADD r1,sp (independent of the game image).
        f={'segments':[[0,2,'thumb']],'labels':[],'aliases':[]}
        self.assertIn('add r1, sp',asm.render(f,bytes.fromhex('6944'),0x08000000))

if __name__=='__main__':unittest.main()
