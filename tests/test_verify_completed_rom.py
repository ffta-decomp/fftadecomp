import sys
import tempfile
import unittest
from pathlib import Path
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'tools'))
from verify_completed_rom import verify
import hashlib
class VerifyImage(unittest.TestCase):
    def test_one_existing_file_verified_without_writes(self):
        with tempfile.TemporaryDirectory() as tmp:
            p=Path(tmp)/'image';p.write_bytes(b'original')
            result=verify(p,hashlib.sha256(b'original').hexdigest(),8)
            self.assertTrue(result['verified']);self.assertEqual(list(Path(tmp).iterdir()),[p])
            self.assertEqual(p.read_bytes(),b'original')
    def test_changed_image_rejected(self):
        with tempfile.TemporaryDirectory() as tmp:
            p=Path(tmp)/'image';p.write_bytes(b'changed!')
            with self.assertRaises(ValueError):verify(p,hashlib.sha256(b'original').hexdigest(),8)
    def test_truncated_image_rejected(self):
        with tempfile.TemporaryDirectory() as tmp:
            p=Path(tmp)/'image';p.write_bytes(b'a')
            with self.assertRaises(ValueError):verify(p,hashlib.sha256(b'a').hexdigest(),2)
