import sys,json,unittest
from pathlib import Path
from unittest.mock import Mock,patch
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'tools'))
import recovery_public_baseline as b
class ListEvidence(unittest.TestCase):
    def test_unrelated_authenticated_list_is_not_image(self):
        ledger=Mock();sha='a'*40;ledger.db.execute.return_value=[(sha,json.dumps({'sha':sha,'evidence':[{'path':'list.json'}]}))]
        with patch.object(b,'ancestor',return_value=True),patch.object(b,'json_pin',return_value=[1,2]) as read:
            self.assertEqual(b._packets(ledger,Path('.')),[]);read.assert_called_once()
    def test_named_invalid_image_still_rejected(self):
        ledger=Mock();sha='a'*40;ledger.db.execute.return_value=[(sha,json.dumps({'sha':sha,'evidence':[{'path':'actual-image-identity.json'}]}))]
        with patch.object(b,'ancestor',return_value=True),patch.object(b,'json_pin',return_value=[]):
            with self.assertRaises(ValueError):b._packets(ledger,Path('.'))
if __name__=='__main__':unittest.main()
