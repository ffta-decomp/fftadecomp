# Boundary and ABI

Read before drafting C or when an apparent register mismatch may be a contract
error. Use the original ROM, its complete disassembly, callers and neighboring
entries. Metadata helps navigation; it does not establish executable ownership.

## Establish the whole original envelope

Record ROM offset, GBA address, ARM/Thumb mode, callable entry and full byte span.
The Thumb callable address carries bit zero; distinguish it from the aligned
instruction address. Follow every return, branch, fallthrough and indirect edge.
Identify literal pools, jump tables, shared tails, embedded data and alignment.
An internal entry inheriting registers or a stack frame is not an ordinary C
function. Do not split a shared frame at a label or infer size from the distance
to a neighboring entry. A selected historical C prefix may be shorter than the
original function; that discrepancy must be resolved explicitly, not trimmed away.

Confirm a reconstructed ASM envelope by assembly/linking at the original address
and complete retail equality. Keep uncertainty explicit. Original-byte inclusion
or a byte array does not constitute a reconstructed implementation.

## Stack objects and helper contracts

For the entry and each direct/indirect call, map:

- Register and stack inputs, sign/zero extension and outgoing setup sites.
- Return width and whether incidental registers are actually consumed.
- Preserved registers, total frame including saved registers, stack alignment,
  independently addressed scalar OUT values, true arrays and hidden structure
  return pointers.
- Exact target, Thumb/interwork form, callback arguments and observable effects.
- Which pointer/value is captured before the call and which object must be read
  again after it. An interface declaration is not a recovered helper body.

Audit fifth and later arguments before fixing allocation. Matching four register
arguments does not establish the stack ABI. Ordinary local copies of stack
formals may coalesce; they do not prove safety around a forced r7 binding.
A fixed-register annotation can overwrite a live incoming parameter home.
Use source-derived paired execution where that risk exists, not a byte-score
increase as a substitute for correctness.

Keep independent scalar OUT objects separate when their identities are observed
independently. Keep a true indexed array intact when the original accesses it as
one object. Neither arrays nor individual locals are universally preferable.

## Physical memory map

Recover field offsets, storage width, signedness, stride, extent, packing and
untouched bits from actual accesses and producers/consumers. A byte load does
not establish the width of the later arithmetic or helper argument. A pointer
field is not its pointee or a numeric ID. Distinguish ordinary RAM, MMIO and
callback/alias-visible memory before choosing qualifiers.

Use target-compatible size/offset assertions. With this old compiler, C89-style
negative-sized typedef checks are usable; a host preprocessor accepting a modern
builtin does not make agbcc accept it. Never weaken a layout assertion merely
because a candidate fits. Do not invent array capacity, members or padding to
steer output. A symbol bound to a verified object can prevent numeric-address
folding, but the real object and its extent still require evidence.

## Minimal source map

Keep one compact record beside the change: original entry/span, ABI, object
layout, ordered calls/loads/stores, CFG joins, unresolved facts, and the predicted
source/code-generation relation. Reuse verified helper facts when their target
and inputs agree. Similar names, adjacent addresses and a related game feature
are insufficient to transfer a contract.
