"""Content-preserving source-tree migration backend for source_layout.

Ownership is supplied from reviewed metadata; unknown code is never named by guess.
Native selection, acceptance and publication remain separate operations.
"""
from collections import defaultdict
from concurrent.futures import ThreadPoolExecutor
import hashlib
import json
import os
from pathlib import Path
import re
import subprocess

INCLUDE = re.compile(rb'(^[ \t]*#[ \t]*include[ \t]*")([^"\n]+)(")', re.M)
TYPEDEF = re.compile(rb'^[ \t]*typedef[ \t]+((?:(?:unsigned|signed)[ \t]+)?(?:char|short|int)(?:[ \t]+int)?)[ \t]+(u8|s8|u16|s16|u32|s32)[ \t]*;[ \t]*\n?', re.M)
TYPES = {'u8': b'unsigned char', 's8': b'signed char', 'u16': b'unsigned short',
         's16': b'signed short', 'u32': b'unsigned int', 's32': b'signed int'}
UNSIGNED = b'''#ifndef FFTA_UNSIGNED_TYPES_H
#define FFTA_UNSIGNED_TYPES_H
/* ARMv4T/agbcc integer ABI. Keep these exact underlying C types. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
#endif
'''
BASIC = b'''#ifndef FFTA_BASIC_TYPES_H
#define FFTA_BASIC_TYPES_H
#include "ffta/unsigned_types.h"
typedef signed char s8;
typedef signed short s16;
typedef signed int s32;
#endif
'''


def digest(data):
    return hashlib.sha256(data).hexdigest()


def canonical_types(data):
    """Remove only already-present, compatible leading scalar typedefs."""
    limit = data.find(b'{')
    if limit < 0:
        limit = len(data)
    prelude = data[:limit]
    matches = list(TYPEDEF.finditer(prelude))
    found = {}
    for match in matches:
        spelling = b' '.join(match[1].split())
        if spelling in (b'short', b'short int', b'int'):
            spelling = b'signed ' + spelling.replace(b' int', b'')
        spelling = spelling.replace(b'short int', b'short')
        name = match[2].decode()
        if spelling != TYPES[name] or name in found:
            return data, None
        found[name] = match
    names = set(found)
    if names == set(TYPES):
        take, header = names, 'ffta/types.h'
    elif {'u8', 'u16', 'u32'}.issubset(names):
        take, header = {'u8', 'u16', 'u32'}, 'ffta/unsigned_types.h'
    else:
        return data, None
    first = min(found[name].start() for name in take)
    result = data
    for name in sorted(take, key=lambda n: found[n].start(), reverse=True):
        match = found[name]
        replacement = ('#include "' + header + '"\n').encode() if match.start() == first else b''
        result = result[:match.start()] + replacement + result[match.end():]
    return result, header


def cpp_identity(data):
    """Ignore moved compatible typedef declarations, preserve every other token/literal."""
    tokens = re.findall(rb'"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'|[A-Za-z_][A-Za-z_0-9]*|[0-9]+|[^\s]', data)
    # Clang may keep several declarations on one line. Match complete token
    # sequences, never text inside string literals or noncanonical aliases.
    aliases = {tuple((b'typedef ' + spelling + b' ' + name.encode() + b' ;').split())
               for name, spelling in TYPES.items()}
    for name, spellings in {'s16': (b'short', b'short int', b'signed short int'),
                            's32': (b'int',), 'u16': (b'unsigned short int',)}.items():
        aliases.update(tuple((b'typedef ' + spelling + b' ' + name.encode() + b' ;').split())
                       for spelling in spellings)
    kept, index = [], 0
    while index < len(tokens):
        width = (next((n for n in (4, 5, 6) if tuple(tokens[index:index + n]) in aliases), 0)
                 if tokens[index] == b'typedef' else 0)
        if width:
            index += width
        else:
            kept.append(tokens[index]); index += 1
    return digest(b'\0'.join(kept))


class SourceTree:
    def __init__(self, root, modules, ownership, extract_types=True, shared_headers=None):
        self.root = Path(root).resolve()
        self.modules = [m for m in modules if m.get('enabled', True) and m['kind'] in ('c', 'mixed')]
        self.ownership = ownership
        self.extract_types = extract_types
        self.raw, self.edges, self.mapping, self.outputs = {}, {}, {}, {}
        self.users = defaultdict(set)
        self.anchor, self.domains = {}, {}
        self.extracted = []
        grouped = defaultdict(list)
        for module in self.modules:
            grouped[module['source']].append(module)
        for name, members in grouped.items():
            self.anchor[name] = min(m['offset'] for m in members) + 0x08000000
            domains = {ownership.get(m['name'], {}).get('domain', 'unknown') for m in members}
            domain = next(iter(domains)) if len(domains) == 1 else 'unknown'
            if not re.fullmatch(r'[a-z][a-z0-9_-]*(?:/[a-z][a-z0-9_-]*)*', domain):
                raise ValueError('invalid reviewed subsystem: ' + domain)
            self.domains[name] = domain
            self.mapping[name] = f'src/{domain}/{self.anchor[name]:08x}.c'
            self.load(name, name)
        for name, target in (shared_headers or {}).items():
            if name not in self.raw:
                continue
            if not name.startswith('include/') or not target.startswith('include/') or '..' in Path(target).parts:
                raise ValueError('invalid reviewed shared header location')
            self.mapping[name] = target
        self.plan_headers()
        for module in self.modules:
            name = module.get('external_symbol_supplement')
            if name and name.startswith('src/'):
                target = f'asm/interfaces/{module["offset"] + 0x08000000:08x}.s'
                if name in self.mapping and self.mapping[name] != target:
                    target = self.mapping[name]
                self.mapping[name] = target
                self.raw[name] = (self.root / name).read_bytes()
        self.render()

    def resolve(self, origin, name):
        candidates = [self.root / Path(origin).parent / name,
                      self.root / 'include' / name, self.root / 'build/generated' / name]
        for candidate in candidates:
            path = candidate.resolve()
            if path.is_file() and path.is_relative_to(self.root):
                return path.relative_to(self.root).as_posix()
        raise ValueError(f'unresolved include {origin}: {name}')

    def load(self, name, source, stack=None):
        self.users[name].add(source)
        stack = set() if stack is None else stack
        if name in stack:
            return
        stack = stack | {name}
        if name not in self.raw:
            self.raw[name] = (self.root / name).read_bytes()
            if re.search(rb'\b__(?:FILE|BASE_FILE|INCLUDE_LEVEL)__\b|\.(?:incbin|include)\b', self.raw[name]):
                raise ValueError('path-sensitive source requires manual proof: ' + name)
            for directive in re.finditer(rb'^[ \t]*#[ \t]*include[ \t]+([^\n]+)', self.raw[name], re.M):
                if not directive[1].lstrip().startswith((b'"', b'<')):
                    raise ValueError('macro-selected include requires manual proof: ' + name)
            self.edges[name] = {match[2].decode(): self.resolve(name, match[2].decode())
                                for match in INCLUDE.finditer(self.raw[name])}
        for child in self.edges.get(name, {}).values():
            # Vendor inputs are immutable dependencies; do not rewrite their headers.
            if child.startswith('vendor/'):
                continue
            self.load(child, source, stack)

    def plan_headers(self):
        groups = defaultdict(list)
        claimed = {}
        for name, raw in self.raw.items():
            if name.startswith('src/') and name not in self.anchor:
                # Identical leaf contracts may be shared. Relative dependency graphs
                # are not merged merely because their immediate text happens to match.
                key = digest(raw) if not self.edges.get(name) else name
                groups[key].append(name)
        for names in groups.values():
            users = set().union(*(self.users[n] for n in names))
            anchor = min(self.anchor[n] for n in users)
            domains = {self.domains[n] for n in users}
            domain = next(iter(domains)) if len(domains) == 1 else 'abi'
            if domain == 'unknown':
                domain = 'abi'
            if any(Path(n).name == 'task_tree_core.h' for n in names):
                target = 'include/engine/tasks/task_tree.h'
            else:
                stem = Path(sorted(names)[0]).stem
                if (not re.fullmatch(r'[a-z][a-z0-9_]*', stem) or
                        any(x in stem for x in ('ffta', 'worker', 'contract', 'interface', 'cohort', 'round'))):
                    stem = 'bindings'
                target = f'include/{domain}/interfaces/{anchor:08x}_{stem}.h'
                ordinal = 2
                while target in claimed and claimed[target] != names:
                    target = f'include/{domain}/interfaces/{anchor:08x}_{stem}_{ordinal}.h'
                    ordinal += 1
            claimed[target] = names
            for name in names:
                self.mapping[name] = target

    def render(self):
        for name, raw in self.raw.items():
            if name not in self.mapping:
                continue
            target = self.mapping[name]
            def include(match):
                child = self.edges[name][match[2].decode()]
                dest = self.mapping.get(child, child)
                if dest.startswith('include/'):
                    value = dest[len('include/'):]
                elif dest.startswith('build/generated/'):
                    value = Path(dest).name
                else:
                    value = os.path.relpath(dest, Path(target).parent).replace(os.sep, '/')
                return match[1] + value.encode() + match[3]
            data = INCLUDE.sub(include, raw) if self.edges.get(name) else raw
            if self.extract_types and target.endswith(('.c', '.h')):
                data, header = canonical_types(data)
                if header:
                    self.extracted.append({'source': target, 'header': header})
            if target in self.outputs and self.outputs[target] != data:
                raise ValueError('destination collision: ' + target)
            self.outputs[target] = data
        if self.extracted:
            self.outputs['include/ffta/unsigned_types.h'] = UNSIGNED
            self.outputs['include/ffta/types.h'] = BASIC

    def stage(self):
        for name, data in self.outputs.items():
            path = self.root / name
            if any(parent.is_symlink() for parent in (path, *path.parents) if parent != self.root):
                raise ValueError('destination must not use symlinks: ' + name)
            if path.exists() and path.read_bytes() != data:
                raise ValueError('refusing to overwrite different destination: ' + name)
            if not path.resolve().is_relative_to(self.root):
                raise ValueError('destination escapes repository')
        for name, data in self.outputs.items():
            path = self.root / name
            path.parent.mkdir(parents=True, exist_ok=True)
            if not path.exists():
                with path.open('xb') as handle:
                    handle.write(data)

    def relocate(self, value):
        if isinstance(value, dict):
            return {k: self.relocate(v) for k, v in value.items()}
        if isinstance(value, list):
            return [self.relocate(v) for v in value]
        return self.mapping.get(value, value) if isinstance(value, str) else value

    def preprocess(self, relocated=False, jobs=4):
        def one(module):
            source = self.mapping[module['source']] if relocated else module['source']
            flags = [f for f in module.get('compiler_flags', []) if f.startswith(('-D', '-U'))]
            result = subprocess.run(['clang', '-E', '-P', '-x', 'c', '-nostdinc',
                                     '-I', str(self.root / 'include'), '-I', str(self.root / 'build/generated'),
                                     *flags, str(self.root / source)], capture_output=True)
            if result.returncode:
                raise ValueError(module['name'] + ': ' + result.stderr.decode()[:1200])
            return module['name'], cpp_identity(result.stdout)
        with ThreadPoolExecutor(max_workers=jobs) as pool:
            return dict(pool.map(one, self.modules))

    def record(self):
        return {'schema': 'source-tree-relocation-v1',
                'module_identities': [{k: m.get(k) for k in ('name', 'offset', 'size', 'kind', 'functions')}
                                      for m in self.modules],
                'files': [{'from': name, 'to': target, 'old_sha256': digest(self.raw[name]),
                           'new_sha256': digest(self.outputs[target])}
                          for name, target in sorted(self.mapping.items())],
                'ownership': self.ownership, 'type_extractions': self.extracted,
                'limits': 'Path/header transformation only. Requires preprocessing and complete native/image verification.'}
