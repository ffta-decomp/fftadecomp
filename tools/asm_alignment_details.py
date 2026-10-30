"""Addressed alignment symptoms; never infer ABI correctness or equivalence."""
import re
from collections import Counter

REG = re.compile(r'\b(?:r(?:1[0-5]|[0-9])|sl|fp|ip|sb|sp|lr|pc)\b')
ALIASES = {'sl':'r10', 'fp':'r11', 'ip':'r12', 'sb':'r9'}

def key(line):
    text = re.sub(r'\s+', ' ', line.normalized_original.strip())
    text = REG.sub(lambda m: ALIASES.get(m[0], m[0]), text)
    # Upstream renderers may trim leading zeroes on branch operands.
    if line.mnemonic in ('bl', 'blx'):
        text = re.sub(r'^(blx? )((?:0x)?[0-9a-fA-F]+)(?= |$)',
                      lambda m: m[1] + hex(int(m[2], 16)), text)
    return text

def record(line):
    return None if line is None else {'address':line.line_num, 'instruction':key(line)}

def details(left, right, pairs):
    sites, calls, edits = [], [], []
    li = {id(x):i for i,x in enumerate(left)}
    ri = {id(x):i for i,x in enumerate(right)}
    def context(lines, index):
        return [record(x) for x in lines[max(0,index-2):index+3]]
    def setup(lines, index):
        # Bounded local window only: never walk through control transfers/data.
        result = []
        for x in reversed(lines[max(0,index-10):index]):
            op = x.mnemonic.lower()
            if op.startswith(('b', '.', '<')) or op in ('pop','push'): break
            result.append(x)
        return list(reversed(result))
    def carriers(lines):
        out=[]
        for x in lines:
            t=key(x)
            if re.match(r'\w+ r[0-3],',t) or re.match(r'str\w* .*\[sp(?:,|\])',t):
                out.append(record(x))
        return out
    for a,b in pairs:
        if a is None or b is None:
            edits.append({'kind':'inserted' if a is None else 'deleted',
                          'reference':record(a),'current':record(b)})
            continue
        ka,kb=key(a),key(b)
        if ka!=kb and not a.mnemonic.startswith(('.', '<')) and REG.sub('REG',ka)==REG.sub('REG',kb):
            sites.append({'reference':record(a),'current':record(b),
                          'operand_changes':[{'operand_index':i,'reference':x,'current':y}
                                             for i,(x,y) in enumerate(zip(REG.findall(ka),REG.findall(kb))) if x!=y],
                          'reference_context':context(left,li[id(a)]),
                          'current_context':context(right,ri[id(b)]),
                          'confidence':'aligned_register_text_only_not_value_flow'})
        if a.mnemonic not in ('bl','blx') or b.mnemonic not in ('bl','blx'): continue
        aw,bw=setup(left,li[id(a)]),setup(right,ri[id(b)])
        ac,bc=carriers(aw),carriers(bw)
        if ka!=kb or [x['instruction'] for x in ac]!=[x['instruction'] for x in bc]:
            # Order observation only; even identical copy sets may have dependencies.
            same_set=bool(ac) and Counter(x['instruction'] for x in ac)==Counter(x['instruction'] for x in bc)
            calls.append({'reference_call':record(a),'current_call':record(b),
                          'same_textual_target':ka==kb,
                          'kind':'same_setup_multiset_different_order' if ka==kb and same_set else 'call_or_argument_setup_difference',
                          'reference_setup':ac,'current_setup':bc,
                          'reference_window':[record(x) for x in aw],
                          'current_window':[record(x) for x in bw],
                          'confidence':'bounded_text_window_not_argument_value_or_ABI_proof'})
    return {'register_difference_sites':sites,'call_setup_differences':calls,
            'insertions_deletions':edits,
            'limits':['Calls are paired by monotonic alignment, not proven call identity.',
                      'r0-r3 destinations and SP stores are setup candidates, not proved arguments.',
                      'Windows stop at control transfers and may omit earlier definitions.',
                      'Register aliases normalized; no global register mapping or semantic proof.']}
