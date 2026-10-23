#!/usr/bin/env python3
"""Regenerate a private ASM tree from a verified, user-supplied US retail ROM."""
from __future__ import annotations
import argparse
import hashlib
import json
import os
from pathlib import Path, PurePosixPath
import re
import shutil
import subprocess
import tempfile
import struct

ROOT = Path(__file__).resolve().parents[1]
RETAIL = '43fc8204c6dceee58828aebc7af0c72eb807e99f35ad641c8bb0a4fa8b6edc19'


def safe_path(value):
    if not isinstance(value, str) or '\\' in value:
        raise ValueError('invalid output path')
    p = PurePosixPath(value)
    if p.is_absolute() or not p.parts or p.parts[0] != 'asm' or '..' in p.parts or p.suffix != '.s':
        raise ValueError('invalid assembly path')
    return p


def validate(layout, rom):
    if layout.get('schema') != 'rom-assembly-layout-v1' or layout.get('retail_sha256') != RETAIL:
        raise ValueError('unsupported layout or target revision')
    if len(rom) != layout['rom_size'] or hashlib.sha256(rom).hexdigest() != RETAIL:
        raise ValueError('retail revision mismatch')
    paths = set()
    for f in layout['files']:
        p = safe_path(f['path'])
        if p in paths: raise ValueError('duplicate assembly path')
        paths.add(p)
        cursor = f.get('rom_offset')
        for offset, size, kind in f['segments']:
            if type(offset) is not int or type(size) is not int or size <= 0 or offset != cursor or not 0 <= offset < offset+size <= len(rom):
                raise ValueError('invalid or discontinuous native range')
            if kind not in ('thumb','arm','data32','data16','data8','padding'):
                raise ValueError('unsupported layout kind')
            if kind == 'arm' and (offset % 4 or size % 4): raise ValueError('misaligned ARM range')
            if kind in ('thumb','data16') and (offset % 2 or size % 2): raise ValueError('misaligned halfword range')
            cursor += size
        if f['segments'] and cursor != f['rom_offset']+f['size']: raise ValueError('native size mismatch')
    return paths


def elf_text(raw):
    if raw[:6] != b'\x7fELF\x01\x01': raise ValueError('expected ELF32 little endian')
    off=struct.unpack_from('<I',raw,32)[0];size,num,strings=struct.unpack_from('<HHH',raw,46)
    sections=[struct.unpack_from('<10I',raw,off+i*size) for i in range(num)]
    table=sections[strings]; names=raw[table[4]:table[4]+table[5]]
    for section in sections:
        name=names[section[0]:].split(b'\0',1)[0]
        if name==b'.text':
            text=raw[section[4]:section[4]+section[5]]
            values={}
            for symbols in sections:
                if symbols[1]!=2:continue
                strings=sections[symbols[6]]; table=raw[strings[4]:strings[4]+strings[5]]
                for i in range(symbols[4],symbols[4]+symbols[5],symbols[9]):
                    name,value=struct.unpack_from('<II',raw,i);name=table[name:].split(b'\0',1)[0]
                    if name in (b'.L__extract_native_start',b'.L__extract_native_end'):values[name.decode()]=value
            return text,values
    raise ValueError('missing text section')


def render(f, rom, base):
    from capstone import Cs, CS_ARCH_ARM, CS_MODE_ARM, CS_MODE_THUMB
    from capstone.arm import ARM_OP_IMM, ARM_OP_MEM, ARM_REG_PC, ARM_INS_B, ARM_INS_BL, ARM_INS_BLX
    decoders={k:Cs(CS_ARCH_ARM,v) for k,v in [('arm',CS_MODE_ARM),('thumb',CS_MODE_THUMB)]}
    for decoder in decoders.values():decoder.detail=True
    symbols={}; code={}; targets={}; lines=['/* Generated privately from the pinned retail revision. Do not upload. */','.syntax unified','.cpu arm7tdmi','.section .text, "ax", %progbits']
    for offset,name,glob in f['labels']:
        if offset is None:continue
        if not re.fullmatch(r'[A-Za-z_.$][\w.$]*',name):raise ValueError('invalid symbol')
        if name.startswith('.L_'):continue
        symbols.setdefault(offset,[]).append((name,glob))
    for off,n,kind in f['segments']:
        if kind not in decoders:continue
        cursor=off
        for ins in decoders[kind].disasm(rom[off:off+n],base+off):
            if ins.address != base+cursor:raise ValueError('decoder gap')
            if ins.id==ARM_INS_BLX or ins.mnemonic.endswith('.w'):raise ValueError('not an ARMv4T instruction')
            mnemonic,operands=ins.mnemonic,ins.op_str
            # Capstone spells Thumb high-register ADD as a three-register form;
            # GNU ARMv4T unified syntax requires its two-operand spelling.
            if kind=='thumb' and mnemonic=='add':
                parts=[p.strip() for p in operands.split(',')]
                if len(parts)==3 and parts[0]==parts[2] and not parts[1].startswith('#'):
                    operands=parts[0]+', '+parts[1]
            if ins.id in (ARM_INS_B,ARM_INS_BL) and ins.operands and ins.operands[0].type==ARM_OP_IMM:
                target=ins.operands[0].imm
                name=f'.Ltarget_{target:08x}'; targets[name]=(target,kind,ins.id==ARM_INS_BL);operands=name
            elif len(ins.operands)>=2 and ins.operands[1].type==ARM_OP_MEM and ins.operands[1].mem.base==ARM_REG_PC:
                mem=ins.operands[1].mem
                if mem.index:raise ValueError('indexed PC-relative load needs an explicit layout rule')
                target=((ins.address+4)&~3 if kind=='thumb' else ins.address+8)+mem.disp
                # Keep the encoded PC displacement. This also preserves native
                # word-alignment phase and literals in neighboring modules.
                operands=ins.op_str
            elif kind=='thumb' and mnemonic=='adr':
                mnemonic='add'
                operands=ins.reg_name(ins.operands[0].reg)+', pc, #'+str(ins.operands[1].imm)
            code[cursor]=(kind,ins.size,mnemonic+' '+operands);cursor+=ins.size
        if cursor != off+n:raise ValueError(f'undecodable declared code at {base+cursor:08x}')
    for name,(target,kind,call) in sorted(targets.items()):
        # Absolute call symbols preserve native placement without replacement stubs.
        directive='.thumb_set' if kind=='thumb' and call else '.set'
        lines.append(f'{directive} {name}, 0x{target | (1 if directive==".thumb_set" else 0):08x}')
    for name,value,thumb,guard in f['aliases']:
        if not re.fullmatch(r'[A-Za-z_.$][\w.$]*',name):raise ValueError('invalid alias')
        if guard:
            if not re.fullmatch(r'\w+',guard):raise ValueError('invalid alias guard')
            lines.append('.ifndef '+guard)
        lines += ['.global '+name,('.thumb_set ' if thumb else '.set ')+name+f', 0x{value:08x}']
        if guard:lines.append('.endif')
    current=None
    lines+=['.L__extract_native_start:']
    for off,n,kind in f['segments']:
        cursor=off;end=off+n
        while cursor<end:
            if kind in decoders and current!=kind:lines.append('.'+kind);current=kind
            lines.append(f'.Lrom_{base+cursor:08x}:')
            for name,glob in symbols.get(cursor,[]):
                if glob:lines.append('.global '+name)
                if glob and kind=='thumb':lines.append('.thumb_func')
                lines.append(name+':')
            if kind in decoders:
                _,size,assembly=code[cursor];lines.append('    '+assembly)
            else:
                size=4 if kind=='data32' and cursor+4<=end else 2 if kind=='data16' and cursor+2<=end else 1
                val=int.from_bytes(rom[cursor:cursor+size],'little');directive={4:'.word',2:'.hword',1:'.byte'}[size]
                lines.append(f'    {directive} 0x{val:0{size*2}x}')
            cursor+=size
    lines+=['.L__extract_native_end:']
    return '\n'.join(lines)+'\n'


def verify_source(source, f, rom, base, work):
    for tool in ('arm-none-eabi-as','arm-none-eabi-ld'):
        if not shutil.which(tool):raise ValueError('verification needs ARM binutils')
    obj=work/'candidate.o';elf=work/'candidate.elf';script=work/'layout.ld'
    subprocess.run(['arm-none-eabi-as','-L','-mcpu=arm7tdmi','-mthumb-interwork',str(source),'-o',str(obj)],check=True,capture_output=True)
    script.write_text('SECTIONS { . = '+hex(base+f['rom_offset'])+'; .text : { *(.text) } /DISCARD/ : { *(.ARM.attributes) } }')
    subprocess.run(['arm-none-eabi-ld','-T',str(script),str(obj),'-o',str(elf)],check=True,capture_output=True)
    actual,symbols=elf_text(elf.read_bytes());phase=0
    start=base+f['rom_offset'];end=start+f['size']
    if symbols.get('.L__extract_native_start')!=start or symbols.get('.L__extract_native_end')!=end:
        raise ValueError('generated native boundary symbols mismatch')
    if len(actual)-phase-f['size'] not in range(4):raise ValueError('unexpected section tail')
    # Boundary symbols identify the complete declared range. Implicit section
    # alignment after the end symbol supplies no native identity or recovery.
    actual=actual[phase:phase+f['size']];expected=rom[f['rom_offset']:f['rom_offset']+f['size']]
    if actual != expected:
        first=next((i for i,(a,b) in enumerate(zip(actual,expected)) if a!=b),min(len(actual),len(expected)))
        raise ValueError(f'assembled native span mismatch at +{first:#x}; sizes {len(actual)}/{len(expected)}')


def extract(rom_path,layout_path,output,verify=False,selected=None):
    tool_sha=hashlib.sha256(Path(__file__).read_bytes()).hexdigest()
    layout_raw=Path(layout_path).read_bytes();layout_sha=hashlib.sha256(layout_raw).hexdigest()
    rom=Path(rom_path).read_bytes();layout=json.loads(layout_raw);validate(layout,rom)
    output=Path(output).resolve();repo=ROOT.resolve()
    if output==repo or output in repo.parents or repo in output.parents:
        raise ValueError('generated ASM must be outside the public source checkout')
    if output.exists():raise ValueError('output directory must not already exist')
    output.parent.mkdir(parents=True,exist_ok=True)
    items=layout['files']
    if selected:
        items=[f for f in items if f['path'] in selected]
        if {f['path'] for f in items}!=set(selected):raise ValueError('unknown selected assembly path')
    receipts=[]
    with tempfile.TemporaryDirectory(prefix='.asm-extract-',dir=output.parent) as temporary:
        stage=Path(temporary)/'output';stage.mkdir();work=Path(temporary)/'check';work.mkdir()
        for f in items:
            p=stage/f['path'];p.parent.mkdir(parents=True,exist_ok=True)
            try:p.write_text(render(f,rom,layout['rom_base']))
            except ValueError as exc:raise ValueError(f"{f['path']}: {exc}") from exc
            if verify and f['segments']:
                try:verify_source(p,f,rom,layout['rom_base'],work)
                except subprocess.CalledProcessError as exc:
                    detail=re.sub(r'/[^\s:]+', '<input>', exc.stderr.decode(errors='replace'))
                    raise ValueError(f"{f['path']}: binutils rejected generated source: {detail[:1600]}") from exc
                except ValueError as exc:raise ValueError(f"{f['path']}: {exc}") from exc
            receipts.append({'path':f['path'],'source_sha256':hashlib.sha256(p.read_bytes()).hexdigest(),'rom_offset':f.get('rom_offset'),'size':f.get('size',0),'native_bytes_verified':bool(verify and f['segments'])})
        if hashlib.sha256(Path(__file__).read_bytes()).hexdigest()!=tool_sha or hashlib.sha256(Path(layout_path).read_bytes()).hexdigest()!=layout_sha:
            raise ValueError('extraction input/tool changed before publication')
        report={'schema':'asm-extraction-report-v1','extractor_sha256':tool_sha,'retail_sha256':RETAIL,'layout_sha256':layout_sha,'capstone_version':__import__('capstone').__version__,'files':receipts,'scope':'Local generated content; source formatting/comments differ from historical files. No C recovery or gameplay credit.'}
        (stage/'report.json').write_text(json.dumps(report,indent=2)+'\n');os.rename(stage,output)
    return {'ok':True,'files':len(receipts),'verified_native_files':sum(x['native_bytes_verified'] for x in receipts),'retail_sha256':RETAIL}


def main():
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--rom',type=Path,required=True);p.add_argument('--layout',type=Path,default=ROOT/'data/asm-layout.json');p.add_argument('--output',type=Path,required=True);p.add_argument('--verify',action='store_true');p.add_argument('--file',action='append');a=p.parse_args()
    try:print(json.dumps(extract(a.rom,a.layout,a.output,a.verify,a.file)))
    except (ValueError,OSError,ImportError,subprocess.CalledProcessError) as exc:
        # Avoid printing host paths or binary bytes into shareable command summaries.
        message=str(exc) if isinstance(exc,ValueError) else type(exc).__name__
        p.exit(1,json.dumps({'ok':False,'error':message})+'\n')
if __name__=='__main__':main()
