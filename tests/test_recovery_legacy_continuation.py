"""Portable legacy continuation regression using disposable SQLite ledgers."""
import copy
import hashlib
import json
from pathlib import Path
import sys
import tempfile
import unittest

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools'))
import recovery_workflow as wf


class LegacyContinuationTests(unittest.TestCase):
    def pin(self, p):
        return {'path': str(p), 'sha256': hashlib.sha256(p.read_bytes()).hexdigest()}

    def write(self, name, content):
        p = self.root / name
        p.write_text(json.dumps(content) if not isinstance(content, str) else content)
        return p

    def setUp(self):
        self.temp = tempfile.TemporaryDirectory()
        self.root = Path(self.temp.name).resolve()
        self.l = wf.Ledger(self.root / 'ledger.sqlite3', initialize=True, epoch='2026-01-01T00:00:00Z')
        self.method = self.write('original.s', 'original complete ASM\n')
        self.c = self.write('best.c', 'complete prior C\n')
        self.gen = self.write('best.asm', 'complete prior generated ASM\n')
        self.cause = self.write('new-cause.txt', 'new late initialized value-definition barrier\n')
        self.ref = self.root / 'reference.bin';self.ref.write_bytes(bytes(range(192)))
        self.binary = self.root / 'generated.bin'
        self.binary.write_bytes(bytes(range(176))+bytes([255])*12)
        self.report = self.write('report.json', {'segments':[{
            'rom_offset':0xC48A4,'reference_size':192,'generated_size':188,
            'binary':str(self.binary),'binary_sha256':self.pin(self.binary)['sha256'],
            'reference_binary':str(self.ref),'matching_bytes':176,
            'source':str(self.c),'source_sha256':self.pin(self.c)['sha256'],'disassembly':str(self.gen)}]})
        self.spec = {'task_id':'LEGACY','module':'C48A4','rom_offset':0xC48A4,
                     'original_span_bytes':192,'thumb_entry':'0x080C48A5',
                     'original_reference_span_sha256':self.pin(self.ref)['sha256'],
                     'original_source':self.pin(self.method)}
        self.l.mutate('add','administrator',{'document':self.spec})
        claim=self.l.mutate('claim','oldworker',{'task':'LEGACY'})['task']
        for i in range(3):
            self.l.mutate('record','oldworker',{'task':'LEGACY','token':claim['token'],
                'round':'old'+str(i),'summary':'actual legacy source form '+str(i),
                'outcome':'nonexact','evidence':[str(self.report)]})
        self.l.mutate('finish','oldworker',{'task':'LEGACY','token':claim['token'],
            'state':'blocked','summary':'three ordinary source forms exhausted'})
        self.l.mutate('coordination','administrator',{'mode':'required','summary':'test required leases'})
        self.lease=self.l.mutate('lease-claim','workerb',{'kind':'source','rom_offset':0xC48A4,
            'size':192,'module':'C48A4','summary':'owner diagnosis'})['lease']
        t=self.l.task('LEGACY')
        self.identity={'task_id':'LEGACY','module':'C48A4','original_span_bytes':192}
        for k in ('rom_offset','thumb_entry','original_reference_span_sha256','original_source'):
            self.identity[k]=self.spec[k]
        self.diag=self.write('diagnosis.json',{'native_identity':self.identity,
            'canonical_started_at':t['started_at'],'owner':'workerb','new_cause_id':'late-barrier',
            'falsifiable_prediction':'only add two shared low8 normalization shifts',
            'complete_reads':{'original':self.pin(self.method),'c':self.pin(self.c),'generated':self.pin(self.gen)}})
        history=[dict(x) for x in self.l.db.execute('select seq,at,actor,kind,payload from events where task_id=? order by seq',('LEGACY',))]
        rounds=[]
        for i,r in enumerate(x for x in history if x['kind']=='round'):
            rounds.append({'seq':r['seq'],'payload_sha256':hashlib.sha256(r['payload'].encode()).hexdigest(),
                'hypothesis_id':'legacy'+str(i),'summary':'old actual source form '+str(i),
                'attempts_used':1,'attempt_limit':1,'evidence':[self.pin(self.report)]})
        self.side={'schema':'legacy-continuation-v1','native_identity':self.identity,
            'canonical_started_at':t['started_at'],'owner':'workerb','rounds':rounds,
            'best':{'report':self.pin(self.report),'reference':self.pin(self.ref),'binary':self.pin(self.binary)},
            'owner_diagnosis':self.pin(self.diag)}
        self.sidepath=self.write('legacy.json',self.side)
        self.packet={'task_id':'LEGACY','expected_state':'blocked','expected_token':'',
            'native_identity':self.identity,'canonical_started_at':t['started_at'],
            'prior_event_count':len(history),'prior_event_sha256':hashlib.sha256(wf.encode(history).encode()).hexdigest(),
            'continuation_index':1,'full_method_percent':100*176/192,
            'full_method_evidence':[self.pin(self.method)],
            'terminal_state':dict.fromkeys(['complete','unknown','exhausted','native_duplicate'],False),
            'effective_matching_causes':3,'legacy_history_sidecar':self.pin(self.sidepath),
            'legacy_owner':'workerb','budgets':[{'hypothesis_id':'legacy'+str(i),'known':True,'attempts_used':1,'attempt_limit':1} for i in range(3)],
            'new_original_asm_cause':{'kind':'original_asm','cause_id':'late-barrier','evidence':[self.pin(self.cause)]},
            'summary':'one new supported late return barrier'}

    def tearDown(self):
        self.l.close();self.temp.cleanup()

    def snapshot(self):
        return '\n'.join(self.l.db.iterdump())

    def sync_side(self):
        self.sidepath.write_text(json.dumps(self.side))
        self.packet['legacy_history_sidecar']=self.pin(self.sidepath)

    def apply(self,actor='administrator',lease=True):
        data={'task':'LEGACY','owner':'workerb','continuation_packet':self.packet,'summary':self.packet['summary']}
        if lease:data['work_lease']={k:self.lease[k] for k in ('id','token')}
        return self.l.mutate('continue',actor,data)

    def denied(self,pattern,**kwargs):
        before=self.snapshot()
        with self.assertRaisesRegex(ValueError,pattern):self.apply(**kwargs)
        self.assertEqual(self.snapshot(),before)

    def test_admit_preserves_history_clock_spec_and_records_independent_one_cause(self):
        before=self.l.task('LEGACY');history=[tuple(x) for x in self.l.db.execute('select * from events where task_id="LEGACY"')]
        got=self.apply();after=self.l.task('LEGACY')
        self.assertEqual(after['started_at'],before['started_at']);self.assertEqual(after['spec'],before['spec'])
        self.assertEqual([tuple(x) for x in self.l.db.execute('select * from events where task_id="LEGACY" order by seq')][:len(history)],history)
        e=json.loads(self.l.db.execute('select payload from events where kind="continued"').fetchone()[0])
        self.assertEqual(e['legacy_extension']['attempt_limit'],1)
        self.assertTrue(e['legacy_extension']['near_exact_plateau'])
        self.assertEqual([v['attempt_limit'] for v in e['budgets'].values()],[1,1,1])
        self.assertEqual(self.l.db.execute('select state from work_leases').fetchone()[0],'promoted')
        args={'task':'LEGACY','token':got['task']['token'],'round':'new1','outcome':'nonexact','summary':'one admitted source cause'}
        self.l.mutate('record','workerb',args)
        self.assertEqual(self.l.history('LEGACY')[-1]['payload']['hypothesis_id'],'late-barrier')
        before=self.snapshot();args['round']='new2'
        with self.assertRaisesRegex(ValueError,'extension budget exhausted'):self.l.mutate('record','workerb',args)
        self.assertEqual(self.snapshot(),before)

    def test_sidecar_hash_and_parser_share_one_read_even_if_file_changes(self):
        from unittest.mock import patch
        original_read = Path.read_bytes
        reads = []
        valid_raw = original_read(self.sidepath)

        def changing_read(path):
            raw = original_read(path)
            if path == self.sidepath:
                reads.append(raw)
                # A second read would parse this unpinned invalid payload.
                path.write_text('{"schema":"unhashed replacement"}')
            return raw

        with patch.object(Path, 'read_bytes', changing_read):
            result = self.apply()
        self.assertEqual(result['task']['state'], 'active')
        self.assertEqual(reads, [valid_raw])
        self.assertEqual(self.packet['legacy_history_sidecar']['sha256'],
                         hashlib.sha256(reads[0]).hexdigest())

    def test_pin_types_rejected_before_any_read(self):
        from unittest.mock import patch
        for key, value in [('path', 3), ('path', ''), ('sha256', None), ('sha256', 'z' * 64)]:
            with self.subTest(key=key, value=value):
                old = self.packet['legacy_history_sidecar']
                self.packet['legacy_history_sidecar'] = dict(old, **{key: value})
                # Original method pin uses evidence(), outside the sidecar helper.
                with patch.object(Path, 'read_bytes', side_effect=AssertionError('unexpected pin read')):
                    self.denied('legacy evidence pin is malformed')
                self.packet['legacy_history_sidecar'] = old

    def test_rejects_nonadmin(self):self.denied('administrator operation',actor='workerb')

    def test_rejects_unknown_missing_or_changed_round_without_mutation(self):
        for mode in ('missing','seq','payload','unknown','old_limit'):
            with self.subTest(mode=mode):
                old=copy.deepcopy(self.side)
                if mode=='missing':self.side['rounds'].pop()
                elif mode=='seq':self.side['rounds'][0]['seq']+=1
                elif mode=='payload':self.side['rounds'][0]['payload_sha256']='0'*64
                elif mode=='unknown':self.side['rounds'][0]['hypothesis_id']=None
                else:self.side['rounds'][0]['attempt_limit']=2
                self.sync_side();self.denied('legacy');self.side=old;self.sync_side()

    def test_rejects_changed_pin_native_identity_and_clock(self):
        for mode in ('pin','identity','clock'):
            with self.subTest(mode=mode):
                old=copy.deepcopy(self.side)
                if mode=='pin':self.packet['legacy_history_sidecar']['sha256']='0'*64
                elif mode=='identity':self.side['native_identity']=dict(self.identity,rom_offset=1);self.sync_side()
                else:self.side['canonical_started_at']='2020-01-01T00:00:00Z';self.sync_side()
                self.denied('legacy');self.side=old;self.sync_side()

    def test_rejects_reusing_old_cause_and_overbudget(self):
        self.packet['new_original_asm_cause']['cause_id']='legacy0';self.denied('reuse')
        self.packet['new_original_asm_cause']['cause_id']='late-barrier'
        self.packet['effective_matching_causes']=6;self.denied('fewer than six')

    def test_rejects_unproved_progress_and_incomplete_plateau_reads(self):
        self.packet['full_method_percent']=99;self.denied('progress')
        self.packet['full_method_percent']=100*176/192
        d=json.loads(self.diag.read_text());d['complete_reads'].pop('c');self.diag.write_text(json.dumps(d))
        self.side['owner_diagnosis']=self.pin(self.diag);self.sync_side();self.denied('full original/C/generated')

    def test_rejects_missing_or_foreign_lease(self):
        self.denied('source work lease required',lease=False)
        self.l.mutate('lease-release','workerb',{'lease_id':self.lease['id'],'token':self.lease['token'],'summary':'test handover'})
        other=self.l.mutate('lease-claim','otherworker',{'kind':'source','rom_offset':0xC48A4,'size':192,'module':'C48A4','summary':'foreign source owner'})['lease']
        self.denied('active work lease')
        self.packet['legacy_owner']='workerb'
        self.l.mutate('coordination','administrator',{'mode':'compatible','summary':'explicit conflict guard smoke'})
        before=self.snapshot()
        with self.assertRaisesRegex(ValueError,'overlaps an active source/peer'):
            self.l.mutate('continue','administrator',{'task':'LEGACY','owner':'workerb','continuation_packet':self.packet,'summary':'test other lock'})
        self.assertEqual(before,self.snapshot())

    def test_old_cause_record_cannot_bypass_independent_extension(self):
        got=self.apply();before=self.snapshot()
        with self.assertRaisesRegex(ValueError,'reuse a previous'):
            self.l.mutate('record','workerb',{'task':'LEGACY','token':got['task']['token'],
                'round':'new-old','outcome':'nonexact','summary':'bad attribution','hypothesis_id':'legacy0'})
        self.assertEqual(before,self.snapshot())


if __name__=='__main__':unittest.main()
