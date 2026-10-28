import hashlib
import json
from pathlib import Path
import sys
import tempfile
import unittest
import shutil
import contextlib
import io
from unittest import mock

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools'))
from build_extensions import apply_extensions


def sha(data):
    return hashlib.sha256(data).hexdigest()


class BuildExtensionTests(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory()
        self.addCleanup(self.temp.cleanup)
        self.root = Path(self.temp.name)
        self.reference = bytes(range(64))
        self.config = {'modules': [{'name': 'Example', 'kind': 'c', 'offset': 8,
                                   'size': 8, 'source': 'original.c'}]}
        (self.root / 'extension.c').write_text('void Example(void) {}\n')
        self.pin = {'path': 'extension.c', 'sha256': sha((self.root / 'extension.c').read_bytes())}
        self.document = {'schema': 'build-extension-v1',
                         'reference_sha256': sha(self.reference), 'sources': [self.pin],
                         'source_replacements': [], 'fragments': []}

    def run_extension(self, compiler=None):
        manifest = self.root / 'extension.json'
        manifest.write_text(json.dumps(self.document))
        return apply_extensions(self.reference, self.reference, self.config, manifest, compiler)

    def fragment(self, offset=20, data=b'CN'):
        name = 'fragment-' + str(len(self.document['fragments']))
        (self.root / name).write_bytes(data)
        record = {'path': name, 'sha256': sha(data), 'rom_offset': offset,
                  'reference_sha256': sha(self.reference[offset:offset + len(data)]), 'kind': 'resource'}
        self.document['fragments'].append(record)
        return record

    def replacement(self):
        record = {'module': 'Example', 'source': self.pin,
                  'reference_sha256': sha(self.reference[8:16]), 'fill_byte': 0xff}
        self.document['source_replacements'].append(record)
        return record

    def test_empty_selected_extension_preserves_image(self):
        image, report = self.run_extension()
        self.assertEqual(image, self.reference)
        self.assertFalse(report['recovery_credit_eligible'])

    def test_resource_does_not_modify_baseline(self):
        self.fragment()
        image, _ = self.run_extension()
        self.assertEqual(image[20:22], b'CN')
        self.assertEqual(self.reference[20:22], bytes([20, 21]))

    def test_complete_source_module_and_explicit_padding(self):
        self.replacement()
        def compiler(module):
            self.assertEqual(Path(module['source']), (self.root / 'extension.c').resolve())
            return b'CODE'
        image, report = self.run_extension(compiler)
        self.assertEqual(image[8:16], b'CODE' + b'\xff' * 4)
        self.assertEqual(report['source_replacements'][0]['generated_bytes'], 4)
        self.assertEqual(self.config['modules'][0]['source'], 'original.c')

    def test_wrong_reference_rejected(self):
        self.document['reference_sha256'] = '0' * 64
        with self.assertRaisesRegex(ValueError, 'reference'): self.run_extension()

    def test_changed_source_rejected(self):
        (self.root / 'extension.c').write_text('changed')
        with self.assertRaisesRegex(ValueError, 'hash'): self.run_extension()

    def test_missing_provenance_rejected(self):
        self.document['sources'] = []
        with self.assertRaisesRegex(ValueError, 'provenance'): self.run_extension()

    def test_wrong_original_range_rejected_before_compile(self):
        self.replacement()['reference_sha256'] = '0' * 64
        with self.assertRaisesRegex(ValueError, 'range hash'):
            self.run_extension(lambda module: self.fail('Compiler must not start'))

    def test_oversized_source_rejected(self):
        self.replacement()
        with self.assertRaisesRegex(ValueError, 'envelope'): self.run_extension(lambda module: b'x' * 9)

    def test_unknown_and_duplicate_module_rejected(self):
        self.replacement()['module'] = 'Missing'
        with self.assertRaisesRegex(ValueError, 'unknown'): self.run_extension()
        self.document['source_replacements'] = []
        self.replacement(); self.replacement()
        with self.assertRaisesRegex(ValueError, 'Duplicate'): self.run_extension()

    def test_outside_rom_rejected(self):
        self.fragment(63, b'bad')
        with self.assertRaisesRegex(ValueError, 'outside'): self.run_extension()

    def test_conflicting_fragments_rejected(self):
        self.fragment(20, b'CN'); self.fragment(21, b'bad')
        with self.assertRaisesRegex(ValueError, 'Conflicting'): self.run_extension()

    def test_equal_resource_overlap_permitted(self):
        self.fragment(20, b'CN'); self.fragment(21, b'N!')
        image, _ = self.run_extension()
        self.assertEqual(image[20:23], b'CN!')

    def test_source_overlap_rejected_before_compile(self):
        self.replacement(); self.fragment(9)
        with self.assertRaisesRegex(ValueError, 'Overlapping'):
            self.run_extension(lambda module: self.fail('Compiler must not start'))

    def test_malformed_kind_rejected(self):
        self.fragment()['kind'] = 'unclassified'
        with self.assertRaisesRegex(ValueError, 'classification'): self.run_extension()

    def test_exported_dependency_revision(self):
        import build_rom
        (self.root / 'SOURCE_REVISION').write_text('a' * 40 + '\n')
        self.assertEqual(build_rom.dependency_revision(self.root), 'a' * 40)
        (self.root / 'SOURCE_REVISION').write_text('not-a-commit')
        with self.assertRaisesRegex(ValueError, 'revision'):
            build_rom.dependency_revision(self.root)

    def test_published_source_cli_applies_extension_after_exact_baseline(self):
        import build_completed
        project=self.root/'project';project.mkdir()
        (project/'config').mkdir();(project/'src').mkdir()
        reference=bytes.fromhex('00207047')+bytes(60)
        module={'name':'Example','kind':'c','offset':0,'size':4,'source':'src/original.c'}
        config={'size':64,'sha256':sha(reference),'rom_base':0x08000000,'modules':[module]}
        index={'files':[],'modules':[{'name':'Example','rom_offset':0,'original_bytes':4,
                                     'kind':'c','source':'src/original.c'}]}
        (project/'config/completed-build.json').write_text(json.dumps(config))
        (project/'src/completed-index.json').write_text(json.dumps(index))
        source=self.root/'extension.c'
        document={'schema':'build-extension-v1','reference_sha256':sha(reference),'sources':[self.pin],
                  'source_replacements':[{'module':'Example','source':self.pin,
                                          'reference_sha256':sha(reference[:4])}]}
        manifest=self.root/'extension.json';manifest.write_text(json.dumps(document))
        input_path=self.root/'input.bin';input_path.write_bytes(reference)
        output=self.root/'output.gba';report=self.root/'report.json'
        argv=['build_completed.py','--input',str(input_path),'--output',str(output),
              '--report',str(report),'--extension-config',str(manifest),
              '--build-dir',str(self.root/'external-build')]
        def compiler(selected,*args,**kwargs):
            return bytes.fromhex('01207047') if Path(selected['source']).is_absolute() else reference[:4]
        with mock.patch.object(build_completed,'ROOT',project), \
             mock.patch.object(build_completed.build_rom,'BUILD_ROOT'), \
             mock.patch.object(build_completed.build_rom,'compile_module',side_effect=compiler), \
             mock.patch.object(build_completed.build_rom,'check_linked_function_entries',return_value=1), \
             mock.patch.object(sys,'argv',argv), contextlib.redirect_stdout(io.StringIO()):
            build_completed.main()
        self.assertEqual(output.read_bytes(),bytes.fromhex('01207047')+reference[4:])
        result=json.loads(report.read_text())
        self.assertTrue(result['baseline_build']['whole_image_identical'])
        self.assertFalse(result['recovery_credit_eligible'])
        self.assertFalse((project/'build').exists())

    def test_external_generated_header_keeps_vendor_untouched(self):
        from generate_asset_addresses import ASSET_SITES, write
        modules = {}
        for _, name, offset in ASSET_SITES:
            modules[name] = {'name': name, 'kind': 'asset', 'offset': 0,
                             'size': max(offset + 1, modules.get(name, {}).get('size', 0))}
        config = {'modules': list(modules.values()), 'rom_base': 0x08000000}
        header = self.root / 'build/generated/assets.h'
        write(config, header, build_root=self.root / 'build')
        self.assertTrue(header.is_file())
        with self.assertRaisesRegex(ValueError, 'build'):
            write(config, self.root / 'forbidden.h', build_root=self.root / 'build')

    @unittest.skipUnless(all(shutil.which('arm-none-eabi-' + tool)
                             for tool in ('as', 'ld', 'objcopy')), 'ARM binutils unavailable')
    def test_real_thumb_source_replacement(self):
        import build_rom
        source = self.root / 'replacement.s'
        source.write_text('.syntax unified\n.cpu arm7tdmi\n.thumb\n.text\n'
                          '.global Example\n.thumb_func\nExample:\nmovs r0, #1\nbx lr\n')
        self.reference = bytes.fromhex('00207047') + bytes(60)
        self.document['reference_sha256'] = sha(self.reference)
        self.config['modules'][0].update(kind='assembly', offset=0, size=4,
                                         external_symbols=False)
        self.document['source_replacements'] = [{
            'module': 'Example', 'source': {'path': str(source), 'sha256': sha(source.read_bytes())},
            'reference_sha256': sha(self.reference[:4])}]
        work = self.root / 'compile'
        work.mkdir()
        def compiler(module):
            return build_rom.compile_module(module, work, 0x08000000, None,
                                             reference=self.reference)
        image, report = self.run_extension(compiler)
        self.assertEqual(image, bytes.fromhex('01207047') + self.reference[4:])
        self.assertEqual(report['source_replacements'][0]['generated_bytes'], 4)


if __name__ == '__main__':
    unittest.main()
