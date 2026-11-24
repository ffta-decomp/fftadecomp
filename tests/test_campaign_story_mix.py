import pathlib
import sys
import unittest

sys.path.insert(0, str(pathlib.Path(__file__).resolve().parents[1] / 'tools'))
import build_rom


class StoryMixedTests(unittest.TestCase):
    def test_story_is_supported_without_relaxing_ratio(self):
        module = {'name': 'scene', 'kind': 'mixed', 'component': 'story',
                  'instructions_bytes': 100, 'inline_assembly_bytes': 4}
        build_rom.validate_source_mix(module)
        module['inline_assembly_bytes'] = 11
        with self.assertRaises(ValueError):
            build_rom.validate_source_mix(module)
