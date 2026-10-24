import importlib.util
import json
from pathlib import Path
import sqlite3
import tempfile
import unittest

MODULE = Path(__file__).resolve().parents[1] / 'tools/build_recovery_group_pool.py'
spec = importlib.util.spec_from_file_location('group_pool', MODULE)
pool = importlib.util.module_from_spec(spec)
spec.loader.exec_module(pool)


class GroupPoolTests(unittest.TestCase):
    def test_only_explicit_site_and_direct_calls(self):
        text = '.L_08000100:\n bl RetailCall_08000201\n bl RetailCall_08000301\n.L_08000104:\n blx r3\n.L_08000108:\n bl Alias\n'
        self.assertEqual(list(pool.direct_edges(text, 0x100, 12, {'Alias':0x400})),
                         [{'caller':0x100,'site':0x100,'target':0x200}, {'caller':0x100,'site':0x108,'target':0x400}])

    def test_catalog_target_history_sdk_hash_and_unknown_group(self):
        with tempfile.TemporaryDirectory() as temporary:
            root=Path(temporary);(root/'asm').mkdir()
            (root/'asm/seed.s').write_text(''.join(f'.L_{0x8000100+i*4:08x}:\n bl RetailCall_{0x8000200+i*0x10:08x}\n' for i in range(5)))
            rows=[{'rom_offset':0x100,'original_bytes':20,'name':'seed','group':'battle','asm_paths':['asm/seed.s']}]
            modules=[{'offset':0x100,'size':20,'name':'seed','kind':'assembly'}]
            for i in range(5):
                offset=0x200+i*0x10
                (root/f'asm/t{i}.s').write_text(f'/* original{i} */')
                rows.append({'rom_offset':offset,'original_bytes':8,'name':f't{i}','entry_kind':'declared_function','group':'unclassified','asm_paths':[f'asm/t{i}.s']})
                modules.append({'offset':offset,'size':8,'name':f't{i}','kind':'c' if i==1 else 'assembly','match_policy':'exact' if i==1 else None})
            modules[-1] = {'offset':0x238,'size':32,'name':'parent','kind':'assembly','functions':[{'name':'t4','offset':0x240,'size':8}]}
            catalog=root/'catalog.json';catalog.write_text(json.dumps({'functions':rows}))
            manifest=root/'manifest.json';manifest.write_text(json.dumps({'modules':modules}))
            db=root/'ledger.db';c=sqlite3.connect(db)
            c.execute('create table tasks(id,state,original_bytes,spec)')
            c.execute('insert into tasks values(?,?,?,?)',('alias','frozen',8,json.dumps({'rom_offset':0x204})));c.commit();c.close()
            sdk=root/'sdk.json';sdk.write_text(json.dumps({'entries':[{'name':'runtime','rom_offset':0x220,'original_span_bytes':8}]}))
            closed=root/'closed.json';closed.write_text(json.dumps({'entries':[{'rom_offset':'00000230','source_sha256':pool.pin(root/'asm/t3.s')['sha256']}]}))
            before=db.read_bytes()
            result=pool.build_pool(root,catalog,manifest,db,sdk,closed)
            targets={r['rom_offset']:r for r in result['candidates']}
            self.assertIn('historical_native_overlap',targets[0x200]['exclusion_reasons'])
            self.assertIn('selected_exact_c',targets[0x210]['exclusion_reasons'])
            self.assertIn('sdk_runtime_driver_overlap',targets[0x220]['exclusion_reasons'])
            self.assertIn('source_hash_disposition',targets[0x230]['exclusion_reasons'])
            self.assertEqual(targets[0x240]['eligibility'],'qualification_only')
            self.assertEqual(targets[0x240]['group'],'unclassified')
            self.assertEqual(targets[0x240]['module'],'parent')
            self.assertEqual(targets[0x240]['edge']['site'],0x110)
            self.assertEqual(db.read_bytes(),before)
            campaign=pool.build_pool(root,catalog,manifest,db,sdk,closed,group='battle',qualification_group='test-campaign')
            self.assertEqual(campaign['qualification_group'],'test-campaign')
            self.assertTrue(all(r['qualification_group']=='test-campaign' for r in campaign['candidates']))
            self.assertEqual(campaign['metrics']['seed_catalog_rows'],1)
            self.assertTrue(all(r['priority']==r['original_span_bytes'] for r in campaign['candidates']))
            self.assertTrue(all(r['group']=='unclassified' for r in campaign['candidates']))

    def test_different_qualification_group_keeps_seed_group_and_size_priority(self):
        with tempfile.TemporaryDirectory() as temporary:
            root=Path(temporary); (root/'asm').mkdir()
            (root/'asm/seed.s').write_text('.L_08000100:\n bl RetailCall_08000200\n.L_08000104:\n bl RetailCall_08000300\n')
            rows=[{'rom_offset':0x100,'original_bytes':8,'name':'seed','group':'seed-domain','asm_paths':['asm/seed.s']}]
            modules=[]
            for off,size in [(0x200,516),(0x300,4)]:
                source=f'asm/{off}.s';(root/source).write_text('/* pinned source */')
                rows.append({'rom_offset':off,'original_bytes':size,'name':str(off),'group':'unclassified','entry_kind':'declared_function','asm_paths':[source]})
                modules.append({'offset':off,'size':size,'name':str(off),'kind':'assembly'})
            catalog=root/'catalog.json';catalog.write_text(json.dumps({'functions':rows}))
            manifest=root/'manifest.json';manifest.write_text(json.dumps({'modules':modules}))
            result=pool.build_pool(root,catalog,manifest,group='seed-domain',qualification_group='different-campaign')
            self.assertEqual(result['metrics']['seed_catalog_rows'],1)
            self.assertEqual([r['original_span_bytes'] for r in result['candidates']],[4,516])
            self.assertTrue(all(r['qualification_group']=='different-campaign' for r in result['candidates']))
            self.assertTrue(all(r['group']=='unclassified' for r in result['candidates']))
            default=pool.build_pool(root,catalog,manifest,group='seed-domain')
            self.assertEqual(default['qualification_group'],'seed-domain')

    def test_matching_ledger_task_adds_new_source_seed_without_reopening_it(self):
        with tempfile.TemporaryDirectory() as temporary:
            root=Path(temporary);(root/'asm').mkdir()
            (root/'asm/new.s').write_text('.L_08000300:\n bl RetailCall_08000400\n')
            (root/'asm/target.s').write_text('/* original callee */')
            rows=[{'rom_offset':off,'original_bytes':8,'name':str(off),'group':'unclassified',
                   'entry_kind':'declared_function','asm_paths':[path]} for off,path in [(0x300,'asm/new.s'),(0x400,'asm/target.s')]]
            catalog=root/'catalog.json';catalog.write_text(json.dumps({'functions':rows}))
            manifest=root/'manifest.json';manifest.write_text(json.dumps({'modules':[{'offset':r['rom_offset'],'size':8,'name':r['name'],'kind':'assembly'} for r in rows]}))
            db=root/'ledger.db';c=sqlite3.connect(db);c.execute('create table tasks(id,state,original_bytes,spec)')
            c.execute('insert into tasks values(?,?,?,?)',('already-blocked','blocked',8,json.dumps({'rom_offset':0x300,'work_group':'campaign-X'})))
            c.commit();c.close();before=db.read_bytes()
            baseline=pool.build_pool(root,catalog,manifest,db,group='battle')
            self.assertEqual(baseline['candidates'],[])
            result=pool.build_pool(root,catalog,manifest,db,group='battle',qualification_group='campaign-X')
            self.assertEqual(result['metrics']['ledger_seed_rows_added'],1)
            self.assertEqual(result['metrics']['seed_catalog_rows'],0)
            self.assertEqual(result['candidates'][0]['rom_offset'],0x400)
            self.assertEqual(result['candidates'][0]['eligibility'],'qualification_only')
            self.assertEqual(result['candidates'][0]['edge']['caller'],0x300)
            self.assertEqual(result['ledger_seed_provenance'][0]['state'],'blocked')
            self.assertEqual(db.read_bytes(),before)

    def test_missing_catalog_target_is_not_invented(self):
        self.assertEqual(list(pool.direct_edges('.L_08000100:\n bl UnknownSymbol\n',0x100,4,{})),[])
        self.assertEqual(list(pool.direct_edges('.L_08000100:\n .word 0\n bl RetailCall_08000200\n',0x100,8,{})),[])
        self.assertTrue(pool.overlaps(100,8,104,8))
        self.assertFalse(pool.overlaps(100,8,108,8))


if __name__=='__main__':
    unittest.main()
