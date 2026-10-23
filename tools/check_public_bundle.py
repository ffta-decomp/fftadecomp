#!/usr/bin/env python3
"""Validate public text payloads and metadata schemas without private inputs."""
import json
from pathlib import Path
import re

ROOT=Path(__file__).resolve().parents[1]
PRIVATE=re.compile(r'/(?:Users|home)/|Application\s+Support|\.codex(?:-bridge)?(?:/|\\)|[A-Za-z]:\\\\|\b01a[0-9a-f]{5}-[0-9a-f]{4}-[0-9a-f]{4}-[0-9a-f]{4}-[0-9a-f]{12}\b|\b(?:gh[pousr]_[A-Za-z0-9]{20,}|sk-(?:proj-)?[A-Za-z0-9_-]{24,})',re.I)
ALLOWED_FUNCTION={'id','name','rom_offset','address','end_address_exclusive','original_bytes','mode','entry_kind','group','semantic_group','group_basis','representation','recorded_state','claim','callable_address','aliases','asm_paths'}

def check_text(content):
    if PRIVATE.search(content):raise ValueError('private host/session/credential material found')


def check(root=ROOT):
    checked=0
    shared=(root/'AGENTS.md').read_text()
    if any(x in shared for x in ('AGENTS.local.md','assignment.md','runtime-inputs.json','worker2-task-queue')):
        raise ValueError('private coordination belongs outside shared AGENTS')
    if (root/'AGENTS.local.md').exists():raise ValueError('private instructions must not exist in public checkout')
    for p in root.rglob('*'):
        rel=p.relative_to(root)
        if ('vendor' in rel.parts and len(rel.parts)>2) or any(x in ('.git','.venv','.local','build') for x in rel.parts) or 'assets' in rel.parts or '__pycache__' in rel.parts:continue
        if p.is_file() and p.suffix in ('.md','.json','.csv','.py','.js','.html','.yml','.txt','.c'):
            check_text(p.read_text());checked+=1
    cat=json.loads((root/'data/functions.json').read_text());ids=set()
    for f in cat['functions']:
        if set(f)-ALLOWED_FUNCTION:raise ValueError('nonallowlisted function field')
        if f['id'] in ids:raise ValueError('duplicate native identity')
        ids.add(f['id'])
        if f['address']!=f"0x{cat['rom_base']+f['rom_offset']:08X}":raise ValueError('address mismatch')
        if f['original_bytes']<=0 or f['end_address_exclusive']!=f"0x{cat['rom_base']+f['rom_offset']+f['original_bytes']:08X}":raise ValueError('span mismatch')
    layout=json.loads((root/'data/asm-layout.json').read_text());paths=set()
    for f in layout['files']:
        if set(f)-{'path','rom_offset','size','segments','labels','aliases','asm_paths'}:raise ValueError('nonallowlisted layout field')
        if not f['path'].startswith('asm/') or '..' in Path(f['path']).parts or f['path'] in paths:raise ValueError('invalid or duplicate ASM path')
        paths.add(f['path'])
    # All public Markdown download links must resolve; optional implementation
    # references are rendered as code, not misleading broken links.
    broken=[]
    for p in [root/'AGENTS.md',root/'CONTRIBUTING.md',root/'README.md',*(root/'docs').rglob('*.md')]:
        for target in re.findall(r'(?<!!)\[[^\]]+\]\(([^)]+)\)',p.read_text()):
            target=target.split('#')[0].strip('<>')
            if target and not re.match(r'[A-Za-z]+://',target) and not (p.parent/target).exists():broken.append((p.relative_to(root).as_posix(),target))
    if broken:raise ValueError('unresolved documentation links: '+repr(broken[:12]))
    return {'ok':True,'text_files_scanned':checked,'function_entries':len(ids),'asm_paths':len(paths)}

if __name__=='__main__':print(json.dumps(check()))
