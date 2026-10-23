#!/usr/bin/env python3
"""Prepare a single native method for the shared fixed-O2 local build tools.

Creates ignored local configuration only. It grants no claim or acceptance.
"""
import argparse
import hashlib
import json
from pathlib import Path
import re
import shutil

ROOT=Path(__file__).resolve().parents[1]


def prepare(native_id,symbol,source,asm_tree,asm_file=None):
    catalog=json.loads((ROOT/'data/functions.json').read_text())
    matches=[x for x in catalog['functions'] if x['id']==native_id]
    if len(matches)!=1:raise ValueError('unknown native identity')
    f=matches[0]
    if f['entry_kind']!='declared_function' or f['mode']!='thumb':
        raise ValueError('requires a proven complete Thumb function; qualify other entries separately')
    if not re.fullmatch(r'[A-Za-z_][A-Za-z0-9_]*',symbol):raise ValueError('invalid function symbol')
    source=Path(source).resolve(strict=True)
    try:relative=source.relative_to(ROOT).as_posix()
    except ValueError:raise ValueError('keep your C draft and its headers in ignored build/ inside this toolkit')
    if not relative.startswith('build/'):raise ValueError('candidate source must be in ignored build/')
    choices=f['asm_paths']
    if asm_file is None:
        if len(choices)!=1:raise ValueError('select --asm-file from this native entry asm_paths')
        asm_file=choices[0]
    if asm_file not in choices:raise ValueError('ASM path is not bound to this native entry')
    tree=Path(asm_tree).resolve(strict=True);assembly=(tree/asm_file).resolve(strict=True)
    if tree not in assembly.parents:raise ValueError('assembly path escapes input tree')
    work=ROOT/'build/public-methods'/native_id
    if work.exists():raise ValueError('method preparation already exists; reuse it for later rounds')
    work.mkdir(parents=True)
    reference=work/'reference.s';shutil.copyfile(assembly,reference)
    functions=[{'name':symbol,'offset':f['rom_offset'],'size':f['original_bytes']}]
    baseline={'name':symbol,'kind':'assembly','source':reference.relative_to(ROOT).as_posix(),'offset':f['rom_offset'],'size':f['original_bytes'],'external_symbols':False,'functions':functions}
    config={'id':'retail-us-public-method','sha256':catalog['retail_sha256'],'size':0x1000000,'rom_base':catalog['rom_base'],'compiler_flags':['-O2','-mthumb-interwork'],'modules':[baseline]}
    candidate={'kind':'c','source':relative,'functions':functions,'compiler_flags':['-O2','-mthumb-interwork'],'external_symbols':True,'external_exclude_symbols':[],'trailing_alignment_bytes':0}
    for name,value in [('manifest.json',config),('candidate-module.json',candidate)]:
        (work/name).write_text(json.dumps(value,indent=2)+'\n')
    return {'ok':True,'native_id':native_id,'module':symbol,'config':(work/'manifest.json').relative_to(ROOT).as_posix(),'candidate_module':(work/'candidate-module.json').relative_to(ROOT).as_posix(),'gate':'prepared_only; not compiled/claimed/accepted'}


def main():
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--native-id',required=True);p.add_argument('--symbol',required=True);p.add_argument('--source',type=Path,required=True);p.add_argument('--asm-tree',type=Path,required=True);p.add_argument('--asm-file');a=p.parse_args()
    try:print(json.dumps(prepare(a.native_id,a.symbol,a.source,a.asm_tree,a.asm_file)))
    except (ValueError,OSError) as e:p.exit(1,str(e)+'\n')
if __name__=='__main__':main()
