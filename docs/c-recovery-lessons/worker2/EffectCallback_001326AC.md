> Public toolkit edition. Local assignments, evidence and game implementations are not distributed. See [the contributor guide](../../../CONTRIBUTING.md).

# EffectCallback_001326AC: seven threshold lifetimes

The 552-byte Thumb entry at ROM `0x1326AC` now has a fixed-O2 local exact C
candidate. The frozen package is
Private evidence locator omitted; reuse the hash-bound native method report.
Its `frozen-index.json` pins the source, header, build report, binary, case bank,
and execution results. Independent acceptance is pending; no production code
has changed.

## Structure taken from the original entry

The entry takes a context pointer in r0, preserves r4-r6 and has no semantic
return value. The ordinary-RAM context fields used here are actor at `+0`,
affected unit at `+8`, and u16 flags at `+0x26`. The entry first tests only the
low byte of the status helper's fullword return. The normal path contains seven
source-ordered property checks with codes `51, 35, 41, 56, 12, 61, 45`, effects
`22, 10, 28, 27, 8, 9, 26`, and corresponding setters. Each product is 32-bit;
random and modulo values are narrowed and sign-extended from their low halfword
before the signed comparison. The success count is narrowed to u8. Flags and
the affected pointer are reread at the observed post-callback sites.

The matching C uses an ordinary `ApplicationContext *` and gives each threshold
calculation its own block scope. This preserves the seven independent source
computations and their order while letting agbcc reuse r4 for each temporary;
the long-lived context remains in r5 as in the original. The bytes establish
this source-to-output result. The responsible compiler pass was not isolated,
so the register-allocation explanation remains an observed structural match,
not a pass-traced claim. Blanket `volatile` was removed because these fields are
ordinary RAM; callback-visible reloads are expressed through the actual helper
calls and field reads.

## Validation and limits

The fixed `-O2 -mthumb-interwork` local build passed strict selection preflight
and produced a 552-byte binary identical to the retail span: 552/552 matching,
zero differing or overflow bytes. Ten independent cases passed on retail and
the candidate overlay. They cover the low-byte status branch, bit-`0x10`
short-circuit, upper-byte contrast, signed RNG/modulo conversions, callback and
property-helper mutations, signed comparison boundaries, all seven effect
calls, and the rooted callback path. The void return's incidental r0 is not
compared. These fixtures are bounded evidence; exact byte identity establishes
the complete function bytes.

## Failed forms retained

- Reordering declarations alone emitted the same 483/552-byte candidate as the
  first draft.
- Removing the blanket volatile pointer qualifier alone also emitted that same
  binary.
- Naming an extra property-value intermediate overflowed the envelope by 16
  bytes and was rejected by strict preflight; it was not behavior-tested.
- Giving each threshold the distinct lifetime visible in the original CFG
  produced the exact span without changing helper order or width behavior.

The case bank is pinned to the source evidence and helper ABI records from the
existing effect-application family. The pre-existing semantic C is included in
the frozen package for context only and was not used as the oracle. The method
claims no new semantic credit, and integration remains pending.
