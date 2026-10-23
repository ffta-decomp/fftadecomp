> Public toolkit edition. Local assignments, evidence and game implementations are not distributed. See [the contributor guide](../../../CONTRIBUTING.md).

# Candidate chance source: preserve the scaled offset before the ROM base

`PROPERTY179-13413C` / `CoreRegion30_0013413C` restores the complete52B
`GetBattleCandidateChance` decision. The incoming action narrows to u16. Zero
reads unit byte5, selects a52B job row and returns byte50. Nonzero selects a28B
ability row and returns byte26 without reading the unit. The return is a full
zero-extended byte. Original battle callers use it as candidate byte16 or input
to a retention gate; the numerical scale and natural index domains are unknown.

The first source used typed ROM records and early returns. It generated48B with
11 same-offset bytes: physical branches reversed, and the numerical job base
absorbed field offset50 into its literal. The second source used symbol-only
linkage for the real ROM objects and a shared result. This restored the52B
extent and branch order, but only34 bytes matched: each ROM base was defined
before the scaled index, retaining the narrowed action in r2 rather than r1.

The third source preserves the original meaningful definitions: compute the
scaled byte offset first, then form the corresponding ROM record pointer, then
read its actual byte field. Typed records still assert52/28B strides and50/26
field offsets; unsized external objects introduce no array capacity. This
restored all52 bytes, including8 literal and2 internal alignment bytes, under
fixed O2/interworking. No instruction ASM, forced register, volatile, barriers,
padding or compiler flags were added. Symbol-only table/export bindings are not
instruction islands. The source-to-output effect is observed; no compiler-pass
trace is claimed. Transfer requires an original offset-before-base definition,
not a general recommendation to replace typed field access with byte arithmetic.

Local whole-native exact and strict selection passed; independent frozen peer
and production identity remain separate. Exact machine-code identity avoids a
redundant runtime bank. All three attempts and the full claim-to-freeze time are
retained in the ledger; size equality alone was not accepted.
