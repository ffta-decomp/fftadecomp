#!/usr/bin/env python3
"""Compile every published completed module and verify a private retail image.

Unrecovered code/resources are retained from the explicitly supplied private ROM.
No generated module is replaced with reference bytes on failure.
"""
import argparse
from concurrent.futures import ThreadPoolExecutor, as_completed
import hashlib
import json
from pathlib import Path
import tempfile
import time
import build_rom

ROOT = Path(__file__).resolve().parents[1]
def sha(raw): return hashlib.sha256(raw).hexdigest()
def validate(reference, config, index):
    if len(reference) != config['size'] or sha(reference) != config['sha256']:
        raise ValueError('Wrong ROM revision: expected the original US AFXE image')
    selected = {m['name']: m for m in config['modules']}
    if set(selected) != {m['name'] for m in index['modules']}:
        raise ValueError('Build selection differs from completed source index')
    last = 0
    for m in sorted(selected.values(), key=lambda x:x['offset']):
        if m['kind'] not in ('c', 'mixed') or m.get('match_policy','exact') != 'exact':
            raise ValueError('Only exact C/mixed modules may be built')
        if m['offset'] < last or m['size'] <= 0 or m['offset']+m['size'] > len(reference):
            raise ValueError('Invalid/overlapping module span')
        last = m['offset']+m['size']
    for f in index['files']:
        p = (ROOT/f['path']).resolve()
        if not p.is_relative_to(ROOT) or sha(p.read_bytes()) != f['sha256']:
            raise ValueError('Published source/header hash mismatch: '+f['path'])
    for row in index['modules']:
        m = selected[row['name']]
        if (m['offset'],m['size'],m['kind'],m['source']) != (row['rom_offset'],row['original_bytes'],row['kind'],row['source']):
            raise ValueError('Module/index identity mismatch: '+m['name'])

def checked_bytes(module, generated, reference):
    target = reference[module['offset']:module['offset']+module['size']]
    if generated != target:
        raise ValueError(f"{module['name']}: compiled bytes differ from retail ({len(generated)}/{len(target)} bytes); refusing output")
    return generated

def main():
    p=argparse.ArgumentParser(description=__doc__)
    p.add_argument('--input',required=True,type=Path)
    p.add_argument('--output',required=True,type=Path)
    p.add_argument('--report',required=True,type=Path)
    p.add_argument('--jobs',type=int,default=2,choices=(1,2,3,4))
    p.add_argument('--extension-config',type=Path,help='Explicit source/resource extension; output is not recovery credit')
    p.add_argument('--build-dir',type=Path,help='External compiler and intermediate directory for read-only source exports')
    args=p.parse_args()
    paths=[x.resolve() for x in (args.input,args.output,args.report)]
    if len(set(paths))!=3 or any(x.is_relative_to(ROOT) for x in paths):
        p.error('Input ROM, output ROM and report must be distinct external paths')
    if args.output.exists() or args.report.exists():p.error('Output/report already exist; choose fresh paths')
    config=json.loads((ROOT/'config/completed-build.json').read_text())
    index=json.loads((ROOT/'src/completed-index.json').read_text())
    reference=args.input.read_bytes();validate(reference,config,index)
    buildroot=args.build_dir.resolve() if args.build_dir else ROOT/'build'
    build_rom.BUILD_ROOT=buildroot
    started=time.monotonic();workroot=buildroot/'completed';workroot.mkdir(parents=True,exist_ok=True)
    # Invocation-owned temporary objects; no stale module cache can hide a source failure.
    with tempfile.TemporaryDirectory(prefix='run-',dir=workroot) as tmp:
        def compile_one(m):
            work=Path(tmp)/m['name'];work.mkdir()
            build_rom.validate_source_mix(m)
            data=build_rom.compile_module(m,work,config['rom_base'],None,reference)
            entries=build_rom.check_linked_function_entries(m,work,config['rom_base'])
            return m,checked_bytes(m,data,reference),entries
        built=bytearray(reference);rows=[]
        failures=[]
        with ThreadPoolExecutor(max_workers=args.jobs) as pool:
            futures={pool.submit(compile_one,m):m['name'] for m in config['modules']}
            for future in as_completed(futures):
                try:
                    m,data,entries=future.result()
                except (Exception, SystemExit) as error:
                    failures.append({'module':futures[future],'error':str(error)})
                    print('FAILED '+futures[future]+': '+str(error),flush=True)
                    continue
                built[m['offset']:m['offset']+m['size']]=data
                rows.append({'name':m['name'],'kind':m['kind'],'rom_offset':m['offset'],'original_bytes':len(data),'sha256':sha(data),'exact':True,'linked_entries':entries})
                if len(rows)%100==0:print(f'{len(rows)}/{len(config["modules"])} modules exact',flush=True)
        if failures:raise ValueError(json.dumps({'failed_modules':failures,'output_written':False}))
        rows.sort(key=lambda row:row['rom_offset'])
    if bytes(built)!=reference:raise ValueError('Final whole-image comparison failed')
    report={'schema':'completed-source-build-v1','input_sha256':sha(reference),'output_sha256':sha(built),'whole_image_identical':True,'rom_bytes':len(built),'compiled_original_bytes':sum(r['original_bytes'] for r in rows),'retained_original_bytes':len(built)-sum(r['original_bytes'] for r in rows),'compiler_starts':len(rows),'module_cache_hits':0,'elapsed_seconds':time.monotonic()-started,'modules':rows,'scope':'Compiled published modules; unrecovered code and resources retained from private reference. Not full source recovery.'}
    if args.extension_config:
        from build_extensions import apply_extensions
        with tempfile.TemporaryDirectory(prefix='extension-',dir=workroot) as tmp:
            def compile_extension(module):
                work=Path(tmp)/module['name'];work.mkdir()
                build_rom.validate_source_mix(module)
                data=build_rom.compile_module(module,work,config['rom_base'],None,reference)
                if module['kind'] in ('c','mixed'):
                    build_rom.check_linked_function_entries(module,work,config['rom_base'])
                return data
            built,extension=apply_extensions(built,reference,config,args.extension_config,compile_extension)
        report={'schema':'extended-completed-source-build-v1','build_mode':'optional-extension',
                'output_sha256':sha(built),'rom_bytes':len(built),'recovery_credit_eligible':False,
                'baseline_build':report,'extension':extension}
    for path in (args.output,args.report):path.parent.mkdir(parents=True,exist_ok=True)
    with args.output.open('xb') as f:f.write(built)
    with args.report.open('x') as f:json.dump(report,f,indent=2);f.write('\n')
    print(json.dumps({k:v for k,v in report.items() if k!='modules'},indent=2))
if __name__=='__main__':main()
