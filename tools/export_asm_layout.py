#!/usr/bin/env python3
from pathlib import Path
import re,json,hashlib,collections
import argparse,datetime
p=argparse.ArgumentParser(description='Export only ASM path/symbol/layout metadata; never ROM bytes or instruction text.');p.add_argument('--source-root',type=Path,required=True);p.add_argument('--manifest',type=Path,required=True);p.add_argument('--output',type=Path,required=True);args=p.parse_args()
ROOT=args.source_root.resolve();m=json.loads(args.manifest.read_text());mods=m['modules'];byname={x['name']:x for x in mods};byfunc={f['name']:x for x in mods for f in x.get('functions',[])};base=m['rom_base'];files=[];errors=[];by_source=collections.defaultdict(list)
for module in mods:by_source[module.get('source')].append(module)
for path in sorted((ROOT/'asm').rglob('*.s')):
 text=path.read_text();text=re.sub(r'/\*.*?\*/','',text,flags=re.S);lines=[re.split(r'@|//',x)[0].strip() for x in text.splitlines()];lines=[x for x in lines if x];sym=re.findall(r'^\s*\.global\s+(\w+)',text,re.M);hints=list(by_source.get(path.relative_to(ROOT).as_posix(),[]));hints+= [byfunc[n] if n in byfunc else byname[n] for n in sym if n in byfunc or n in byname]; anchors=[int(a,16) for a in re.findall(r'^\s*\.L_(08[0-9a-fA-F]{6}):',text,re.M)];start=base+min(x['offset'] for x in hints) if hints else min(anchors) if anchors else None
 if start is None and re.search(r'^\s*\w+\s+[^\n]+',text,re.M):errors.append((str(path),'no_native_range'));continue
 pos=start;mode='thumb';segments=[];labels=[];aliases=[];guards=[];problem=None
 def emit(kind,n):
  global pos
  if n<=0:return
  if segments and segments[-1][2]==kind and segments[-1][0]+segments[-1][1]==pos:segments[-1][1]+=n
  else:segments.append([pos,n,kind])
  pos+=n
 try:
  for line in lines:
   if line.endswith(':'):
    name=line[:-1];
    if name in sym:labels.append([pos,name,True])
    addr=re.fullmatch(r'\.L_(08[0-9a-fA-F]{6})',name)
    if addr and int(addr[1],16)!=pos:raise ValueError(f'address_label {name} cursor {pos:x}')
   elif line.startswith('.'):
    cmd,_,args=line.partition(' ');args=args.strip()
    if cmd in ('.arm','.thumb'):mode=cmd[1:]
    elif cmd in ('.word','.short','.hword','.byte'):
     emit({'.word':'data32','.short':'data16','.hword':'data16','.byte':'data8'}[cmd],len(args.split(','))*{'.word':4,'.short':2,'.hword':2,'.byte':1}[cmd])
    elif cmd in ('.balign','.align') and pos is not None:
     align=int(args.split(',')[0],0);align=1<<align if cmd=='.align' else align;rel=pos-start;emit('padding',(-rel)%align)
    elif cmd=='.org':
     dst=int(args.split(',')[0],0);emit('padding',dst-(pos-start))
    elif cmd in ('.thumb_set','.set','.equ'):
     name,val=[x.strip() for x in args.split(',',1)]
     try:v=int(val,0)
     except ValueError:continue
     aliases.append([name,v,cmd=='.thumb_set',guards[-1] if guards else None])
    elif cmd=='.ifndef':guards.append(args)
    elif cmd=='.endif':
     if guards:guards.pop()
    elif cmd not in ('.syntax','.cpu','.section','.text','.type','.thumb_func','.global','.size'):
     raise ValueError('unsupported directive '+cmd)
   else:
    if pos is None:raise ValueError('instruction without native anchor')
    mnemonic=line.split()[0];emit(mode,4 if mode=='arm' or mnemonic in ('bl','blx') else 2)
 except Exception as exc:problem=str(exc)
 if problem:errors.append((str(path.relative_to(ROOT)),problem));continue
 record={'path':path.relative_to(ROOT).as_posix(),'segments':[[a-base,n,k] for a,n,k in segments],'labels':[[a-base if a is not None else None,n,g] for a,n,g in labels],'aliases':aliases}
 if start is not None:record['rom_offset']=start-base;record['size']=pos-start
 files.append(record)
layout={'schema':'rom-assembly-layout-v1','retail_sha256':m['sha256'],'rom_size':m['size'],'rom_base':base,'scope':'Original source file paths, labels, symbol addresses and code/data layout only. No ROM, opcodes, instructions, literal values, comments or game assets are distributed. Generated text is canonical, not a historical comment/format mirror.','files':files}
if errors:raise SystemExit('Unsupported source layouts; metadata was not published: '+repr(errors))
layout['as_of']=datetime.datetime.now(datetime.timezone.utc).isoformat()
args.output.parent.mkdir(parents=True,exist_ok=True);args.output.write_text(json.dumps(layout,separators=(',',':'))+'\n')
print(json.dumps({'ok':True,'files':len(files)}))
