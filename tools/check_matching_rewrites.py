#!/usr/bin/env python3
"""Read-only agbcc source-form hints; no compilation, edits, or acceptance authority."""

import argparse
from dataclasses import dataclass
import hashlib
import json
from pathlib import Path
import re
import sys
import time


RULE_VERSION = 9
MAX_INPUT_BYTES = 2_000_000
STRATEGY = ".agents/skills/ffta-decomp/references/reconstruction.md"
QUICK = ".agents/skills/ffta-decomp/references/patterns.md"
TOKEN = re.compile(
    r'(?P<skip>\s+|/\*[\s\S]*?\*/|//[^\n]*|^[ \t]*\#(?:[^\n\\]|\\[^\n]|\\\n)*)'
    r'|(?P<string>"(?:\\[\s\S]|[^"\\])*"|\'(?:\\[\s\S]|[^\'\\])*\')'
    r'|(?P<id>[A-Za-z_]\w*)|(?P<number>0[xX][\da-fA-F]+[uUlL]*|\d+[uUlL]*)'
    r'|(?P<op>->|\+\+|--|&&|\|\||<<|>>|<=|>=|==|!=|[+*/%&|^!-]=|.)', re.M)
TYPES = set("void char short int long float double signed unsigned const volatile static extern register auto struct union enum typedef __const __volatile u8 u16 u32 u64 s8 s16 s32 s64 size_t intptr_t uintptr_t int8_t int16_t int32_t int64_t uint8_t uint16_t uint32_t uint64_t".split())
REG = re.compile(r"\b(?:r(?:1[0-5]|[0-9])|sp|lr|pc|ip|fp|sl|sb)\b", re.I)


@dataclass(frozen=True)
class Tok:
    value: str
    line: int
    column: int
    kind: str


def lex(text):
    result, line, column = [], 1, 1
    for match in TOKEN.finditer(text):
        value = match.group()
        if match.lastgroup != "skip":
            result.append(Tok(value, line, column, match.lastgroup))
        if "\n" in value:
            line += value.count("\n")
            column = len(value.rsplit("\n", 1)[1]) + 1
        else:
            column += len(value)
    return result


def closing(tokens, start):
    pairs = {"(": ")", "[": "]", "{": "}"}
    stack = []
    for i in range(start, len(tokens)):
        value = tokens[i].value
        if value in pairs:
            stack.append(pairs[value])
        elif value in pairs.values():
            if not stack or stack.pop() != value:
                raise ValueError("unbalanced C delimiters; use a complete method or preprocessed input")
            if not stack:
                return i
    raise ValueError("unclosed C delimiter; use a complete method or preprocessed input")


def functions(tokens):
    result, i = [], 0
    while i < len(tokens):
        if tokens[i].value == "{":
            end = closing(tokens, i)
            if i and tokens[i - 1].value == ")":
                level, j = 1, i - 2
                while j >= 0:
                    if tokens[j].value == ")":
                        level += 1
                    elif tokens[j].value == "(":
                        level -= 1
                        if level == 0:
                            break
                    j -= 1
                if j > 0 and tokens[j - 1].kind == "id":
                    result.append((tokens[j - 1].value, i, end))
            i = end
        i += 1
    return result


def declaration_types(tokens):
    types = set(TYPES)
    # Simple typedefs and the common single function-pointer alias form only.
    for i, token in enumerate(tokens):
        if token.value == "typedef":
            j = i + 1
            while j < len(tokens) and tokens[j].value != ";":
                if tokens[j].value in ("(", "[", "{"):
                    j = closing(tokens, j)
                j += 1
            if j < len(tokens) and tokens[j - 1].kind == "id":
                types.add(tokens[j - 1].value)
            elif j < len(tokens):
                for k in range(i + 1, j - 4):
                    if (tokens[k].value == "(" and tokens[k + 1].value == "*"
                            and tokens[k + 2].kind == "id" and tokens[k + 3].value == ")"
                            and tokens[k + 4].value == "("):
                        types.add(tokens[k + 2].value)
                        break
    return types


def finding(rule, category, token, message, suggestion, evidence, reference,
            confidence="conditional"):
    return {"rule": rule, "category": category, "line": token.line if token else None,
            "column": token.column if token else None, "confidence": confidence,
            "message": message, "suggestion": suggestion, "evidence": evidence,
            "reference": reference,
            "validation": "Verify the original operation, change one supported cause, and use the normal fixed-O2 whole-function gate."}


def syntax_findings(tokens, spans):
    types, results = declaration_types(tokens), []

    def block(start, stop):
        statements, i = False, start + 1
        while i < stop:
            t = tokens[i]
            if t.value == "{":
                end = closing(tokens, i)
                block(i, end)
                statements, i = True, end + 1
                continue
            if t.value in types:
                if statements:
                    results.append(finding("C89_LATE_DECLARATION", "syntax", t,
                        "A declaration appears after a statement in this lexical block.",
                        "Keep declarations before statements/asm, or create a real nested block preserving the intended lifetime. Consult c-parse.in before another syntax attempt.",
                        {"declaration_start": t.value}, STRATEGY + "#c89-and-readable-naming", "lexical"))
                # Skip the entire declaration, including aggregate initializers.
                while i < stop and tokens[i].value != ";":
                    if tokens[i].value in ("(", "[", "{"):
                        i = closing(tokens, i)
                    i += 1
                i += 1
                continue
            if t.value in ("case", "default") or (i + 1 < stop and tokens[i + 1].value == ":"):
                while i < stop and tokens[i].value != ":":
                    i += 1
                statements, i = True, i + 1
                continue
            if t.value == "for" and i + 1 < stop and tokens[i + 1].value == "(":
                end = closing(tokens, i + 1)
                if i + 2 < end and tokens[i + 2].value in types:
                    results.append(finding("C89_FOR_DECLARATION", "syntax", tokens[i + 2],
                        "The for initializer declares a variable, a C99 source form.",
                        "Declare the loop variable at the start of an appropriate real block; retain its original width, initialization site and lifetime.",
                        {"keyword": "for"}, STRATEGY + "#c89-and-readable-naming", "lexical"))
                statements, i = True, end + 1
                continue
            statements = True
            # Do not reinterpret field names, qualifiers or casts in a statement
            # as declarations. Re-enter only at a real statement/block boundary.
            while i < stop:
                value = tokens[i].value
                if value in ("(", "["):
                    i = closing(tokens, i) + 1
                elif value == "{":
                    end = closing(tokens, i)
                    block(i, end)
                    i = end + 1
                    break
                elif value == ";":
                    i += 1
                    break
                else:
                    i += 1

    for _, start, stop in spans:
        block(start, stop)
    return results


def parse_asm(text):
    insns, words, pending_address = [], [], None
    word_addresses = set()
    entries = re.findall(r"^\s*\.type\s+([\w.$]+)\s*,\s*[%@]function", text, re.M)
    if not entries:
        entries = re.findall(r"^\s*[0-9a-fA-F]+\s+<([^+>]+)>:", text, re.M)
    for line, raw in enumerate(text.splitlines(), 1):
        code = re.split(r"\s@|//", raw, 1)[0].strip().lower()
        address_label = re.fullmatch(r"\.l_([\da-f]{8}):", code)
        if address_label:
            pending_address = int(address_label[1], 16)
        if not code or code.endswith(":"):
            continue
        address = re.match(r"^([\da-f]+):\s+", code)
        if address:
            pending_address = int(address[1], 16)
        code = re.sub(r"^[\da-f]+:\s+(?:(?:[\da-f]{8}|[\da-f]{4}|[\da-f]{2})\s+)+", "", code)
        word = re.match(r"\.word\s+(0x[\da-f]+|\d+)\s*$", code)
        if word:
            words.append({"value": int(word[1], 0), "line": line})
            if pending_address is not None:
                word_addresses.add(pending_address)
        match = re.match(r"([a-z][a-z0-9]*)(?:\.[nw])?\s*(.*?)\s*$", code)
        if match and match[1] not in ("syntax", "cpu"):
            args = re.sub(r"\s+", "", match[2])
            for alias, reg in (("sl", "r10"), ("fp", "r11"), ("sb", "r9"), ("ip", "r12")):
                args = re.sub(r"\b" + alias + r"\b", reg, args)
            item = {"op": match[1], "args": args, "line": line}
            if pending_address is not None:
                item["address"] = pending_address
            insns.append(item)
            pending_address = None
    unresolved_pools = []
    for insn in insns:
        literal_load = re.fullmatch(r"r\d+,\[pc(?:,#(0x[\da-f]+|\d+))?\]", insn["args"])
        if insn["op"] != "ldr" or "address" not in insn or not literal_load:
            continue
        offset = int(literal_load[1], 0) if literal_load[1] else 0
        target = ((insn["address"] + 4) & ~3) + offset
        if target not in word_addresses:
            unresolved_pools.append({"line": insn["line"], "pool_address": target})
    return {"instructions": insns, "literal_words": words, "entries": sorted(set(entries)),
            "unresolved_literal_pools": unresolved_pools}


def copy_operands(insn):
    """Recognize real register copies, not arithmetic with similar spelling."""
    args = insn["args"].split(",")
    if insn["op"] in ("mov", "movs") and len(args) == 2:
        return args
    if insn["op"] in ("add", "adds") and len(args) == 3 and args[2] in ("#0", "#0x0"):
        return args[:2]
    return None


def entry_copies(insns):
    origins = {"r%d" % i: i for i in range(4)}
    result, recorded = [], set()
    for insn in insns[:24]:
        if insn["op"].startswith("b") or insn["op"] in ("cmp", "cmps", "tst"):
            break
        pair = copy_operands(insn)
        dest = insn["args"].split(",")[0]
        if pair:
            dest, src = pair
            value = origins.get(src)
            if value is not None:
                origins[dest] = value
                if re.fullmatch(r"r(?:[4-9]|10|11)|sl|fp|sb", dest) and value not in recorded:
                    result.append({"argument": value, "destination": dest, "line": insn["line"]})
                    recorded.add(value)
                continue
        # Stores and saves do not define their first source operand.
        if insn["op"] not in ("push", "str", "strb", "strh", "stmia"):
            origins.pop(dest, None)
    return result


def argument_order_findings(original, generated):
    a, b = original["instructions"], generated["instructions"]
    results, ac, bc = [], entry_copies(a), entry_copies(b)
    left = [(x["argument"], x["destination"]) for x in ac]
    right = [(x["argument"], x["destination"]) for x in bc]
    if len(left) >= 2 and left != right and sorted(left) == sorted(right):
        results.append(finding("ENTRY_ARGUMENT_COPY_ORDER", "shape", None,
            "Entry argument captures have the same arguments/destinations in a different order.",
            "Distinguish formal-parameter setup from body-local definitions. Inspect the original capture sites and lifetimes before a constraint; an initialized ordinary local and a truthful read/write operand solved one documented entry-copy case. This is not permission to change the ABI or reorder formal parameters.",
            {"original_captures": ac, "generated_captures": bc},
            ".agents/skills/ffta-decomp/references/patterns.md", "entry_dataflow_signature"))

    def setups(seq):
        calls = []
        for i, insn in enumerate(seq):
            if insn["op"] != "bl":
                continue
            moves = []
            for prev in reversed(seq[max(0, i - 8):i]):
                pair = copy_operands(prev)
                if not pair or pair[0] not in ("r0", "r1", "r2", "r3"):
                    break
                moves.append({"destination": pair[0], "source": pair[1], "line": prev["line"]})
            calls.append((insn, list(reversed(moves))))
        return calls

    for (call_a, ma), (call_b, mb) in zip(setups(a), setups(b)):
        left = [(x["destination"], x["source"]) for x in ma]
        right = [(x["destination"], x["source"]) for x in mb]
        if (call_a["args"] == call_b["args"] and len(left) >= 2 and left != right
                and sorted(left) == sorted(right) and len({x[0] for x in left}) == len(left)):
            results.append(finding("CALL_ARGUMENT_SETUP_ORDER", "shape", None,
                "The same textual BL target has the same adjacent argument moves in a different order.",
                "Map original argument definitions and call/alias effects. C argument evaluation order is not a source-level sequencing guarantee; use only source-proven evaluation boundaries. Do not swap the callee prototype or formal parameter order to change setup instructions.",
                {"original_call": call_a, "generated_call": call_b, "original_setup": ma, "generated_setup": mb},
                STRATEGY, "adjacent_instruction_signature"))
    return results


def switch_snapshot_findings(tokens, original, generated):
    snapshots = []
    for i in range(len(tokens) - 10):
        part = tokens[i:i + 11]
        v = [t.value for t in part]
        if (v[0] in ('u32', 'uint32_t') and part[1].kind == 'id' and v[2] == '='
                and part[3].kind == 'id' and v[4] in ('->', '.') and part[5].kind == 'id'
                and v[6:9] == [';', 'switch', '('] and v[9:11] == [v[1], ')']):
            snapshots.append(part)
    if len(snapshots) != 1:
        return []
    a = original['instructions']
    bm = {x['address']: x for x in generated['instructions'] if 'address' in x}

    def target(insn):
        match = re.fullmatch(r'(?:0x)?([\da-f]+)(?:<[^>]+>)?', insn['args'])
        return int(match[1], 16) if match else None

    for i, x in enumerate(a):
        y = bm.get(x.get('address'))
        if (not y or (x['op'], y['op']) != ('bgt', 'bhi')
                or target(x) is None or target(x) != target(y) or i == 0):
            continue
        cmp = a[i - 1]
        paired = bm.get(cmp.get('address'))
        if (cmp['op'] != 'cmp' or not paired
                or (cmp['op'], cmp['args']) != (paired['op'], paired['args'])):
            continue
        reg = cmp['args'].split(',')[0]
        for j in range(i - 2, max(-1, i - 11), -1):
            load = a[j]
            if load['op'] != 'ldrh' or not load['args'].startswith(reg + ','):
                continue
            other_load = bm.get(load.get('address'))
            if not other_load or (load['op'], load['args']) != (other_load['op'], other_load['args']):
                break
            window = a[j + 1:i - 1] + [p for p in bm.values()
                if load['address'] < p['address'] < cmp['address']]
            writes = [p for p in window if p['op'] in ('bl', 'blx') or (
                p['args'].split(',')[0] == reg and not p['op'].startswith('b')
                and p['op'] not in ('cmp', 'cmps', 'tst', 'push', 'str', 'strb', 'strh'))]
            if writes:
                break
            part = snapshots[0]
            return [finding('SWITCH_SNAPSHOT_SIGNEDNESS', 'shape', part[0],
                'An unsigned word member snapshot immediately feeds switch; a same-address signed original guard became unsigned after the same halfword load and compare.',
                'Check the switch working value separately from field storage. A verified u16-storage/s32-working snapshot restored BGT versus BHI in one whole312B function. Prove the loaded domain and every use before changing a local type; keep storage, helper ABI and writes unchanged. This signature is a question, not value-flow proof or an automatic signedness rewrite.',
                {'snapshot': part[1].value, 'member': part[5].value,
                 'original_load': load, 'original_compare': cmp,
                 'original_branch': x, 'generated_branch': y,
                 'same_numeric_branch_target': target(x)},
                STRATEGY + '#widths-and-destructive-arithmetic',
                'address_correlated_question')]
    return []


def product_phase_findings(tokens, spans, original, generated):
    """Correlate one narrow source form with local MUL input definitions.

    The four-instruction windows describe register expressions only. They do
    not connect a C field to a load, establish memory kind, or prove ordering
    across control flow. Ambiguous windows and explicitly volatile C are skipped.
    """
    if len(spans) != 1 or any(t.value in ('volatile', '__volatile', '__volatile__')
                              for t in tokens):
        return []
    _, start, stop = spans[0]
    body = tokens[start + 1:stop]
    # This transfer has no call/constraint boundary. Do not suggest commuting
    # operands in a method containing an unexamined call or ASM expression.
    controls = {'if', 'for', 'while', 'switch', 'sizeof'}
    if any(t.kind == 'id' and t.value not in controls and body[i + 1].value == '('
           for i, t in enumerate(body[:-1])):
        return []
    candidates = []
    for i in range(len(body) - 8):
        p = body[i:i + 9]
        if (p[0].value == '(' and p[1].kind == 'id' and p[2].value == '+'
                and p[3].kind == 'id' and p[4].value == ')'
                and p[5].value == '*' and p[6].kind == 'id'
                and p[7].value == '->' and p[8].kind == 'id'):
            candidates.append(p)
    if len(candidates) != 1:
        return []

    reg = r'r(?:1[0-5]|[0-9])'

    def windows(seq, load_first):
        found = []
        for i in range(4, len(seq)):
            mul = seq[i]
            if mul['op'] not in ('mul', 'muls'):
                continue
            w = seq[i - 4:i]
            base_copy, load, sum_copy, add = w if load_first else w[2:] + w[:2]
            bc, sc = copy_operands(base_copy), copy_operands(sum_copy)
            if not bc or not sc or bc[0] != sc[0]:
                continue
            scratch, base = bc
            other = sc[1]
            if not all(re.fullmatch(reg, x) for x in (scratch, base, other)):
                continue
            lm = re.fullmatch('(' + reg + r'),\[(' + reg + r'),#(0x[\da-f]+|\d+)\]', load['args'])
            args = add['args'].split(',')
            if (load['op'] != 'ldrb' or not lm or lm[2] != scratch
                    or add['op'] not in ('add', 'adds') or len(args) != 3
                    or not all(re.fullmatch(reg, x) for x in args)
                    or args[1:].count(scratch) != 1):
                continue
            summed, loaded = args[0], lm[1]
            row = next(x for x in args[1:] if x != scratch)
            # All roots must survive the entire window. The load and sum must
            # have distinct destinations, rather than depending on one another.
            written = {scratch, summed, loaded}
            if len(written) != 3 or written & {base, other, row}:
                continue
            ma = mul['args'].split(',')
            factors = ma if len(ma) == 2 else ma[1:] if len(ma) == 3 else []
            if (len(ma) not in (2, 3) or ma[0] not in (loaded, summed)
                    or sorted(factors) != sorted((loaded, summed))):
                continue
            offset = int(lm[3], 16 if lm[3].startswith('0x') else 10)
            found.append({'key': (base, offset, tuple(sorted((row, other)))),
                          'load': load, 'sum': add, 'multiply': mul})
        return found

    a = windows(original['instructions'], True)
    b = windows(generated['instructions'], False)
    if len(a) != 1 or len(b) != 1 or a[0]['key'] != b[0]['key']:
        return []
    part = candidates[0]
    return [finding('STRIDE_PRODUCT_DEFINITION_ORDER', 'shape', part[0],
        'A sum-first member product accompanies reversed byte-load/add definition order before MUL, with the same local register-expression roots.',
        'Map the actual field, row inputs and later descriptor uses. For proven ordinary memory with matching widths/frame/CFG, compare the original stride-load and row-sum phases before register tuning. One pinned agbcc pair matched after changing only product child order. C operand spelling is not a portable evaluation-order guarantee; do not commute volatile/MMIO accesses, calls or unrelated pointer arithmetic.',
        {'source_sum': [part[1].value, part[3].value],
         'source_member': part[6].value + '->' + part[8].value,
         'original': a[0], 'generated': b[0],
         'source_to_asm_value_flow_proven': False, 'ordinary_memory_proven': False,
         'frame_or_CFG_equivalence_proven': False},
        'docs/matching-rewrite-checker.md#stride-product-definition-order',
        'local_expression_signature_question')]


def shape_findings(tokens, original, generated):
    results = []
    if original is None or generated is None:
        return results
    a, b = original["instructions"], generated["instructions"]
    if not a or not b:
        return results
    # This only recognizes the evidenced zero/upper-bound signed-guard family.
    signed = [x for x in a if x["op"] in ("blt", "bgt", "bmi", "bge", "ble")]
    unsigned = [x for x in b if x["op"] in ("bhi", "bhs", "bcs", "bls", "blo", "bcc")]
    bounds = [x for x in a if x["op"] in ("cmp", "cmps") and re.search(r",#(?:0|15|0xf)$", x["args"])]
    for i, t in enumerate(tokens):
        if t.value != "if" or i + 1 >= len(tokens) or tokens[i + 1].value != "(":
            continue
        end = closing(tokens, i + 1)
        condition = tokens[i + 2:end]
        vals = {x.value for x in condition}
        comparisons = sum(x.value in ("<", ">", "<=", ">=") for x in condition)
        if vals & {"&&", "||"} and comparisons >= 2 and "0" in vals and vals & {"15", "16", "0xf", "0xF", "0x10"} and len(signed) >= 2 and len(bounds) >= 2 and unsigned:
            results.append(finding("O2_COMPOUND_SIGNED_RANGE", "shape", t,
                "A compound zero/15 range expression accompanies signed original guards and an unsigned generated branch.",
                "Check each original guard and its shared invalid tail. Independent signed guards can preserve that source topology when O2 merges a compound range; do not add guards or change signedness/domain.",
                {"original_signed_branches": signed[:4], "original_bound_compares": bounds[:4], "generated_unsigned_branches": unsigned[:4]},
                QUICK, "asm_correlated_hint"))
    # A post-subtraction sign conversion can differ from separately normalized inputs.
    for i in range(len(tokens) - 6):
        values = [t.value for t in tokens[i:i + 8]]
        if values[:3] not in (["(", "s16", ")"], ["(", "int16_t", ")"]):
            continue
        if values[3] != "(" or not set(values[4:]) & {"-", "+"}:
            continue
        def first(seq, op):
            return next((j for j, x in enumerate(seq) if x["op"] in op
                         and not x["args"].startswith("sp,")), None)
        ashift, asub = first(a, {"asr", "asrs"}), first(a, {"sub", "subs", "add", "adds"})
        bshift, bsub = first(b, {"asr", "asrs"}), first(b, {"sub", "subs", "add", "adds"})
        if None not in (ashift, asub, bshift, bsub) and ashift < asub and bshift > bsub:
            results.append(finding("SIGNED_NORMALIZATION_SITE", "shape", tokens[i],
                "A signed-halfword cast wraps arithmetic; the first arithmetic/right-shift order differs.",
                "Trace the exact operand definitions. If the original sign-normalizes each input before arithmetic, express those real inputs separately before result wrapping. A result-only cast is not equivalent source shape.",
                {"original_first_shift": a[ashift], "generated_first_shift": b[bshift], "scope": "first-operation ordering hint, not value-flow proof"}, QUICK, "asm_correlated_hint"))
            break
    numeric_pointers = [tokens[i] for i in range(1, len(tokens) - 1)
                        if tokens[i].kind == "number" and tokens[i - 1].value == ")"
                        and re.fullmatch(r"0[xX]0[23][\da-fA-F]{6}[uUlL]*", tokens[i].value)]
    aw = {x["value"] for x in original["literal_words"]}
    extra_ram = [x for x in generated["literal_words"] if 0x02000000 <= x["value"] < 0x04000000 and x["value"] not in aw]
    if numeric_pointers and extra_ram and not original["unresolved_literal_pools"]:
        results.append(finding("NUMERIC_RAM_BASE_FOLD", "shape", numeric_pointers[0],
            "Numeric fixed-RAM pointer construction accompanies a generated-only RAM literal.",
            "Check whether CSE folded a real object field address. For a source-proven fixed object, compare verified symbol-only linkage and the actual typed tail; do not invent arrays, capacities or arbitrary accessors.",
            {"generated_only_ram_literals": extra_ram[:6]},
            ".agents/skills/ffta-decomp/references/patterns.md", "asm_correlated_hint"))
    def normalized(insn):
        return insn["op"], REG.sub("REG", insn["args"])
    changed = [(x, y) for x, y in zip(a, b) if x["args"] != y["args"]]
    if len(a) == len(b) and changed and all(normalized(x) == normalized(y) for x, y in zip(a, b)):
        results.append(finding("REGISTER_OPERANDS_ONLY", "diagnosis", None,
            "Parsed instruction mnemonics and non-register operands agree; register operands differ.",
            "Locate the earliest differing definition/use and inspect frame, cross-call lifetime and .lreg/.greg/reload evidence before another source constraint. This signature does not prove an allocation cause or authorize forcing ASM.",
            {"first_difference": {"original": changed[0][0], "generated": changed[0][1]}, "literal_words_equal": [x["value"] for x in original["literal_words"]] == [x["value"] for x in generated["literal_words"]]},
            ".agents/skills/ffta-decomp/references/patterns.md", "instruction_signature_only"))
    else:
        # Only correlate local sites when both inputs provide actual addresses.
        # Compiler .s alone cannot establish same-offset windows.
        def offsets(seq):
            located = [x for x in seq if "address" in x]
            if not located:
                return {}
            base = min(x["address"] for x in located)
            return {x["address"] - base: x for x in located}
        am, bm = offsets(a), offsets(b)
        comparable = am.keys() & bm.keys()
        signature_matches = sum(normalized(am[x]) == normalized(bm[x]) for x in comparable)
        mostly_same_shape = signature_matches * 3 >= max(len(am), len(bm), 1) * 2
        windows = []
        for offset in sorted(am.keys() & bm.keys()):
            x, y = am[offset], bm[offset]
            if (not x["op"].startswith("b") and x["args"] != y["args"]
                    and normalized(x) == normalized(y)):
                windows.append({"relative_offset": offset, "original": x, "generated": y})
        if len(windows) >= 2 and mostly_same_shape:
            results.append(finding("LOCAL_REGISTER_DIFFERENCES", "diagnosis", None,
                "At least two same-offset instruction sites differ only in register operands; other differences remain.",
                "Trace the first listed value back to its actual definition, live range, call and reload. Treat these as local symptoms, not a whole-function allocation proof; do not edit every visibly swapped register or force ASM.",
                {"sites": windows[:6], "site_count": len(windows), "pairing": "instruction offsets relative to each supplied function entry",
                 "signature_sites_equal": signature_matches, "signature_sites_total": max(len(am), len(bm)),
                 "signature_filter_is_not_byte_match": True},
                ".agents/skills/ffta-decomp/references/patterns.md", "address_correlated_signature"))
    results.extend(argument_order_findings(original, generated))
    results.extend(switch_snapshot_findings(tokens, original, generated))
    return results


def asm_operand_findings(tokens, spans):
    """Count direct extended-ASM operands as the pinned agbcc expander does.

    A read-write output adds an implicit matching input (gcc/stmt.c). This
    checks the pinned compiler's limit, not register pressure or ABI safety.
    Unexpanded macros and nonliteral constraints cannot be counted reliably.
    """
    results = []

    def split_top_level(parts, delimiter):
        groups, current, i = [], [], 0
        while i < len(parts):
            token = parts[i]
            if token.value in ('(', '[', '{'):
                end = closing(parts, i)
                current.extend(parts[i:end + 1])
                i = end + 1
                continue
            if token.value == delimiter:
                groups.append(current)
                current = []
            else:
                current.append(token)
            i += 1
        groups.append(current)
        return groups

    def constraints(parts):
        if not parts:
            return []
        result = []
        for operand in split_top_level(parts, ','):
            i = 0
            if operand and operand[0].value == '[':
                i = closing(operand, 0) + 1
            value = ''
            while i < len(operand) and operand[i].kind == 'string' and operand[i].value.startswith('"'):
                value += operand[i].value[1:-1]
                i += 1
            if not value or i >= len(operand) or operand[i].value != '(':
                return None
            end = closing(operand, i)
            if end != len(operand) - 1:
                return None
            result.append(value)
        return result

    for _, start, stop in spans:
        for i in range(start + 1, stop):
            if tokens[i].value not in ('asm', '__asm', '__asm__'):
                continue
            begin = i + 1
            while begin < stop and tokens[begin].value in ('volatile', '__volatile', '__volatile__'):
                begin += 1
            if begin >= stop or tokens[begin].value != '(':
                continue
            end = closing(tokens, begin)
            sections = split_top_level(tokens[begin + 1:end], ':')
            if len(sections) < 2 or len(sections) > 4:
                continue
            if not sections[0] or any(t.kind != 'string' or not t.value.startswith('"') for t in sections[0]):
                continue
            outputs = constraints(sections[1])
            inputs = constraints(sections[2]) if len(sections) > 2 else []
            if outputs is None or inputs is None:
                continue
            # The legacy compiler also accepts '+' after the first character.
            readwrite = sum('+' in constraint and '=' not in constraint for constraint in outputs)
            expanded = len(outputs) + len(inputs) + readwrite
            if expanded > 10:
                results.append(finding('AGBCC_ASM_OPERAND_LIMIT', 'syntax', tokens[i],
                    'Extended ASM exceeds the pinned agbcc limit of 10 expanded operands.',
                    'Each read-write output also consumes an implicit input. Reduce or split only with truthful value lifetimes; a syntax-valid split does not prove stack-argument preservation or ABI correctness.',
                    {'explicit_outputs': len(outputs), 'explicit_inputs': len(inputs),
                     'implicit_readwrite_inputs': readwrite, 'expanded_operands': expanded,
                     'pinned_max_operands': 10, 'abi_safety_proven': False},
                    'vendor/agbcc/gcc/stmt.c', 'literal_constraint_count'))
    return results


def fixed_register_stack_formals(tokens, spans):
    """Lexical lifetime warning, not a claim about an actual parameter home."""
    results = []
    for _, start, stop in spans:
        if start < 2 or tokens[start - 1].value != ')':
            continue
        depth, begin = 1, start - 2
        while begin >= 0:
            if tokens[begin].value == ')': depth += 1
            elif tokens[begin].value == '(':
                depth -= 1
                if depth == 0: break
            begin -= 1
        if begin < 0:
            continue
        # Conservative direct scalar/pointer declarators only. Nested function
        # pointer declarations and aggregate ABI need the owner's actual trace.
        params, current = [], []
        for token in tokens[begin + 1:start - 1]:
            if token.value in ('(',')','[',']','...'):
                params = []; break
            if token.value == ',': params.append(current); current = []
            else: current.append(token)
        else: params.append(current)
        if len(params) <= 4:
            continue
        names = [p[-1].value for p in params[4:] if p and p[-1].kind == 'id'
                 and p[-1].value not in TYPES]
        # Conservative dependency propagation, not C alias or physical-register
        # analysis. An ordinary copy can still share the original input's home.
        carriers = {name: {name} for name in names}
        for i in range(start + 1, stop):
            if tokens[i].value == '=' and i > start + 1 and tokens[i - 1].kind == 'id':
                lhs = tokens[i - 1].value
                # Exclude obvious object-field and indirect assignments.
                before = tokens[i - 2].value
                if before not in ('.', '->', '*'):
                    end = next((j for j in range(i + 1, stop) if tokens[j].value == ';'), stop)
                    roots = set().union(*(carriers.get(t.value, set()) for t in tokens[i + 1:end]))
                    if roots:
                        carriers.setdefault(lhs, set()).update(roots)
            if tokens[i].value != 'register': continue
            end = next((j for j in range(i + 1, stop) if tokens[j].value == ';'), stop)
            declaration = tokens[i:end]
            regs = [t.value.strip('"') for t in declaration if t.kind == 'string'
                    and re.fullmatch(r'"(?:r[4-9]|r10|r11)"', t.value)]
            if not regs: continue
            used = {t.value for t in tokens[end + 1:stop] if t.kind == 'id'}
            live_carriers = {name: sorted(roots) for name, roots in carriers.items() if name in used}
            live = sorted(set().union(*(set(roots) for roots in live_carriers.values()))) if live_carriers else []
            if live:
                results.append(finding('FIXED_REGISTER_STACK_FORMAL_LIVENESS', 'constraint', tokens[i],
                    'An explicit preserved-register local precedes later uses of fifth-or-later inputs or their ordinary copied carriers.',
                    'Inspect actual entry parameter homes and initialization order before binding fixed locals. Ordinary prebinding C copies can coalesce and do not establish safe physical snapshots; replay stack arguments before considering match percentage.',
                    {'fixed_registers': regs, 'later_stack_formals': live,
                     'later_input_carriers': live_carriers,
                     'parameter_home_conflict_proven': False}, STRATEGY))
                break
    return results


def hard_store_zero_findings(tokens, spans):
    """Lexical shared-hard-register risk; neither lowering nor dominance proof."""
    results = []
    asm_names = {'asm', '__asm', '__asm__'}
    scalar_types = {'char', 'short', 'int', 'long', 'signed', 'unsigned',
                    'u8', 'u16', 'u32', 's8', 's16', 's32',
                    'uint8_t', 'uint16_t', 'uint32_t', 'int8_t', 'int16_t', 'int32_t'}

    def zero(token):
        if token.kind != 'number':
            return False
        value = token.value.lower().rstrip('ul')
        return int(value, 16 if value.startswith('0x') else 10) == 0

    for function, start, stop in spans:
        bindings = {}
        for i in range(start + 1, stop):
            if tokens[i].value != 'register':
                continue
            end = next((j for j in range(i + 1, stop) if tokens[j].value == ';'), stop)
            specs = [j for j in range(i + 1, end) if tokens[j].value in asm_names]
            if len(specs) != 1:
                continue
            spec = specs[0]
            if (spec + 3 >= end or tokens[spec - 1].kind != 'id'
                    or [t.value for t in tokens[spec + 1:spec + 4:2]] != ['(', ')']):
                continue
            match = re.fullmatch(r'"(r(?:1[0-2]|[0-9]))"', tokens[spec + 2].value)
            if not match:
                continue
            name = tokens[spec - 1].value
            declaration = {t.value for t in tokens[i:spec - 1]}
            pointer = '*' in declaration
            scalar = not pointer and bool(declaration & scalar_types) and not declaration & {'struct', 'union', '['}
            bindings.setdefault(name, []).append({'reg': match[1], 'pointer': pointer,
                                                  'scalar': scalar, 'index': i})
        # Repeated identifiers may shadow; this rule deliberately does not
        # resolve lexical scopes or expand typedefs/macros.
        bindings = {name: items[0] for name, items in bindings.items() if len(items) == 1}
        stores = []
        for i in range(start + 1, stop):
            if tokens[i].value not in ('=', '+=', '-=', '|=', '&=', '^='):
                continue
            begin = i - 1
            while begin > start and tokens[begin - 1].value not in (';', '{', '}'):
                begin -= 1
            left = tokens[begin:i]
            values = {t.value for t in left}
            if 'register' in values or not values & {'*', '->', '['}:
                continue
            for name, binding in bindings.items():
                if binding['pointer'] and binding['index'] < begin and name in values:
                    stores.append((i, name, binding['reg']))
        for i in range(start + 1, stop):
            if tokens[i].value not in ('if', 'while') or tokens[i + 1].value != '(':
                continue
            end = closing(tokens, i + 1)
            for j in range(i + 2, end - 2):
                a, op, b = tokens[j:j + 3]
                if op.value not in ('==', '!='):
                    continue
                # Restrict the complete comparison operands, not a triple
                # embedded in e.g. 0 == option + 1 or base->option == 0.
                if (tokens[j - 1].value not in ('(', '&&', '||')
                        or tokens[j + 3].value not in (')', '&&', '||')):
                    continue
                name = a.value if zero(b) else b.value if zero(a) else None
                binding = bindings.get(name)
                if not binding or not binding['scalar'] or binding['index'] >= j:
                    continue
                # Direct identifier comparisons only: exclude member/call/index
                # expressions whose spelling happens to contain a bound local.
                k = j if a.value == name else j + 2
                if tokens[k - 1].value in ('.', '->') or tokens[k + 1].value in ('(', '[', '.', '->'):
                    continue
                earlier = [(index, pointer) for index, pointer, reg in stores
                           if index < i and reg == binding['reg']]
                if not earlier:
                    continue
                index, pointer = earlier[0]
                results.append(finding('HARD_STORE_THEN_SCALAR_ZERO', 'constraint', tokens[k],
                    'A hard-bound scalar zero guard follows a lexical store through a pointer bound to the same register.',
                    'Inspect retained initial RTL and the first jump dump. The pinned nonnull pass can seed a hard register from a memory STORE yet ignore later hard-register SETs. Verify actual address lowering and dominance; keep real guards and input domains. A read/write ASM operand alone is not a proven repair. Do not change compiler flags or retry an exhausted task.',
                    {'function': function, 'hard_register': binding['reg'],
                     'store_pointer': pointer, 'store_line': tokens[index].line,
                     'scalar': name, 'comparison': op.value,
                     'memory_store_lowering_proven': False, 'dominance_proven': False,
                     'guard_deletion_proven': False},
                    'vendor/agbcc/gcc/gcse.c', 'lexical_question'))
    return results


def upstream_transfer_findings(tokens, spans):
    """Narrow lexical questions from upstream whole-exact transfers, not fixes."""
    results = []
    reference = ".agents/skills/ffta-decomp/references/patterns.md"
    for _, start, end in spans:
        body = tokens[start + 1:end]
        # An early void return before a later member write can skip a shared tail.
        # Do not call this a bug: legitimate guards have exactly this shape too.
        for i, token in enumerate(body[:-1]):
            if token.value != "return" or body[i + 1].value != ";":
                continue
            stores = []
            for j in range(i + 2, len(body) - 3):
                if (body[j].kind == "id" and body[j + 1].value == "->"
                        and body[j + 2].kind == "id" and body[j + 3].value == "="):
                    stores.append({"object": body[j].value, "field": body[j + 2].value,
                                   "line": body[j].line})
            if stores:
                results.append(finding("EARLY_RETURN_MEMBER_TAIL", "source_question", token,
                    "A void early return precedes later member stores in this function.",
                    "Trace this branch in original ASM: does it return, or join a common store? Preserve real early exits; never remove a return merely to satisfy this hint.",
                    {"later_stores": stores[:6], "cfg_proven": False}, reference, "lexical_question"))
        # Direct cast-back of a high-bit masked value: table may hold tagged words.
        for i, token in enumerate(body):
            if token.kind != "number" or token.value.lower().rstrip("ul") not in ("0x80000000", "0x7fffffff"):
                continue
            left = i
            while left > 0 and body[left - 1].value not in (";", "{", "}"):
                left -= 1
            statement = body[left:i]
            values = [x.value for x in statement]
            cast_types = [statement[j + 1].value for j in range(len(statement) - 2)
                          if statement[j].value == "(" and statement[j + 1].kind == "id"
                          and statement[j + 2].value == ")" and statement[j + 1].value not in TYPES]
            if "=" in values and cast_types and set(values) & {"|", "&"}:
                results.append(finding("TAGGED_WORD_CAST_BACK", "source_question", token,
                    "A bit31 flag operation is cast back through a named non-builtin type.",
                    "Check the typedef and original table readers/writers. If storage is a tagged 32-bit word, keep storage integer-typed and cast only at the actual call. Do not infer pointer type from this lexical hint or change an established ABI.",
                    {"cast_types": cast_types, "mask": token.value, "type_proven": False}, reference, "lexical_question"))
    return results


def analyze(source, reference_asm=None, generated_asm=None, function=None):
    tokens = lex(source)
    spans = functions(tokens)
    if function:
        spans = [span for span in spans if span[0] == function]
        if not spans:
            raise ValueError("requested C function not found; use a direct or preprocessed definition")
    findings = syntax_findings(tokens, spans)
    findings.extend(upstream_transfer_findings(tokens, spans))
    findings.extend(asm_operand_findings(tokens, spans))
    findings.extend(fixed_register_stack_formals(tokens, spans))
    findings.extend(hard_store_zero_findings(tokens, spans))
    active = [token for _, start, end in spans for token in tokens[start:end + 1]]
    # Keep strings (but not comments) for empty-ASM template inspection.
    for i, t in enumerate(active[:-3]):
        if t.value not in ("asm", "__asm__", "__asm"):
            continue
        start = i + 1
        if active[start].value in ("volatile", "__volatile__"):
            start += 1
        if active[start].value != "(":
            continue
        end = closing(active, start)
        body = active[start + 1:end]
        if not body or body[0].value != '\"\"':
            continue
        colons = [j for j, token in enumerate(body) if token.value == ":"]
        inputs = body[colons[1] + 1:colons[2] if len(colons) > 2 else len(body)] if len(colons) > 1 else []
        if colons and not inputs and any(token.kind == "string" and token.value.strip('"').startswith("=") for token in body[1:]):
            findings.append(finding("EMPTY_ASM_OUTPUT_ONLY", "constraint", t,
                "An empty template has output-only constraints and no input section.",
                "Verify the real value definition: empty output-only ASM must not fabricate a value. For an actual initialized live value, use a truthful input/read-write constraint only if original lifetime evidence supports it; never apply this mechanically.",
                {"template": "empty", "input_section": False}, STRATEGY, "lexical"))
    limits = ["Read-only heuristic suggestions, not C correctness, byte matching, or permission for another attempt.",
              "No preprocessing/type checking/CFG/alias or RTL value-flow analysis. Macro-generated declarations and complex typedefs may be missed.",
              "No compiler, network request, source rewrite, task mutation or automatic retry."]
    if not spans:
        limits.append("No direct C function definition identified; no function checks ran. This is not a clean syntax result.")
    original = parse_asm(reference_asm) if reference_asm is not None else None
    generated = parse_asm(generated_asm) if generated_asm is not None else None
    if original is not None and generated is not None:
        if len(spans) != 1 or len(original["entries"]) > 1 or len(generated["entries"]) > 1:
            limits.append("ASM-correlated rules skipped: supply exactly one C function and one complete original/generated ASM function each.")
        else:
            findings.extend(shape_findings(active, original, generated))
            findings.extend(product_phase_findings(tokens, spans, original, generated))
            if original["unresolved_literal_pools"]:
                limits.append("NUMERIC_RAM_BASE_FOLD skipped: addressed original PC-relative literal loads lack explicit .word pool entries. Raw disassembly can decode pool data as instructions; absence from parsed literal_words does not prove a generated-only constant.")
    else:
        limits.append("No paired ASM: source syntax/constraint checks only, not compiler-shape recommendations.")
    findings.sort(key=lambda x: (0 if x["category"] == "syntax" else 1, x["line"] or 0, x["rule"]))
    return {"schema": "matching-rewrite-hints-v1", "rule_version": RULE_VERSION,
            "functions": [x[0] for x in spans], "findings": findings, "limits": limits}


def read_input(path, role):
    with path.open("rb") as stream:
        data = stream.read(MAX_INPUT_BYTES + 1)
    if len(data) > MAX_INPUT_BYTES:
        raise ValueError(role + " exceeds 2MB; select a bounded method artifact")
    return data, {"role": role, "path": str(path), "bytes": len(data), "sha256": hashlib.sha256(data).hexdigest()}


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("source", nargs="?", type=Path, help="Owned C or retained preprocessed .i (read only)")
    parser.add_argument("--build-report", type=Path, help="Reuse a single-segment local report and its pinned .i/disassembly")
    parser.add_argument("--reference-asm", type=Path)
    parser.add_argument("--generated-asm", type=Path)
    parser.add_argument("--function", help="Select one direct C definition")
    parser.add_argument("--binary", type=Path, help="Existing candidate binary; no compilation")
    parser.add_argument("--previous-binary", type=Path, help="Existing earlier candidate; detect repeated output")
    parser.add_argument("--json", action="store_true", help="JSON to stdout instead of compact hints")
    parser.add_argument("--output", type=Path, help="Create a new JSON report; existing files are never overwritten")
    args = parser.parse_args(argv)
    started = time.perf_counter()
    if bool(args.source) == bool(args.build_report):
        parser.error("provide source OR --build-report")
    if args.build_report and (args.reference_asm or args.generated_asm):
        parser.error("--build-report supplies both ASM inputs; do not mix explicit ASM")
    if bool(args.reference_asm) != bool(args.generated_asm):
        parser.error("provide both original and generated ASM, or neither")
    if bool(args.binary) != bool(args.previous_binary):
        parser.error("provide both current and previous binary, or neither")
    try:
        values, pins, frozen_artifacts = {}, [], {}
        if args.build_report:
            data, pin = read_input(args.build_report, "build_report")
            pins.append(pin)
            build = json.loads(data)
            if not isinstance(build, dict) or len(build.get("segments", [])) != 1:
                raise ValueError("build report must describe one segment; otherwise select explicit method inputs")
            artifacts = build.get("compile_inputs", {}).get("artifacts", {})
            for role in ("preprocessed", "disassembly"):
                artifact = artifacts.get(role, {})
                if not artifact.get("path") or not artifact.get("sha256"):
                    raise ValueError("build report lacks pinned " + role)
                artifact_data, artifact_pin = read_input(Path(artifact["path"]), role)
                if artifact_pin["sha256"] != artifact["sha256"]:
                    raise ValueError("build artifact drift: " + role)
                frozen_artifacts["source" if role == "preprocessed" else "generated_asm"] = (artifact_data, artifact_pin)
            reference = build["segments"][0].get("reference_disassembly")
            if not reference:
                raise ValueError("build report lacks reference_disassembly; use explicit inputs")
            args.source = Path(artifacts["preprocessed"]["path"])
            args.reference_asm = Path(reference)
            args.generated_asm = Path(artifacts["disassembly"]["path"])
        for role, path in (("source", args.source), ("reference_asm", args.reference_asm),
                           ("generated_asm", args.generated_asm), ("binary", args.binary),
                           ("previous_binary", args.previous_binary)):
            if path is not None:
                data, pin = frozen_artifacts.get(role) or read_input(path, role)
                pin = dict(pin, role=role)
                pins.append(pin)
                values[role] = data if role.endswith("binary") else data.decode("utf-8")
        report = analyze(values["source"], values.get("reference_asm"), values.get("generated_asm"), args.function)
        if args.binary and values["binary"] == values["previous_binary"]:
            if not values["binary"]:
                raise ValueError("empty binary cannot establish repeated candidate output")
            report["findings"].insert(0, finding("IDENTICAL_CANDIDATE_BINARY", "iteration", None,
                "The supplied complete binary artifacts are byte-identical.",
                "Reuse previous binary checks. Another spelling change emitted no new candidate; preserve its charged time and diagnose a different supported source cause before compiling again. Whole-envelope completeness remains the owner's responsibility.",
                {"bytes": len(values["binary"]), "sha256": hashlib.sha256(values["binary"]).hexdigest()},
                ".agents/skills/ffta-decomp/references/patterns.md", "exact_artifact_identity"))
        report["inputs"] = pins
        report["elapsed_seconds"] = time.perf_counter() - started
        payload = json.dumps(report, indent=2) + "\n"
        if args.output:
            # Exclusive creation also protects an input accidentally passed as output.
            with args.output.open("x", encoding="utf-8") as stream:
                stream.write(payload)
        if args.json:
            print(payload, end="")
        else:
            print("%d suggestion(s), %.3fs; hints only" % (len(report["findings"]), report["elapsed_seconds"]))
            for item in report["findings"][:8]:
                print("%s:%s [%s] %s" % (args.source, item["line"] or "-", item["rule"], item["message"]))
                print("  " + item["suggestion"])
                print("  Reference: " + item["reference"])
            if len(report["findings"]) > 8:
                print("Additional suggestions are in JSON output.")
        return 0
    except (OSError, UnicodeError, ValueError, TypeError, KeyError, AttributeError) as error:
        print("matching rewrite scan: " + str(error), file=sys.stderr)
        return 2


if __name__ == "__main__":
    sys.exit(main())
