> Public toolkit edition. Local assignments, evidence and game implementations are not distributed. See [the contributor guide](../../../CONTRIBUTING.md).

# Effect feasibility: preserve pointer advance and the narrowing definition

`EFFECT195-12D2F0` / `EffectDirect_0012D2F0` is
`ScoreBattleEffectFeasibility`, a complete102B policy result. Actor coordinates
246/247 and target coordinates246/247/248 are signed bytes, passed as signed
fullword values to the existing eight-argument query. The selector stays full32
through both helpers. The first helper is tested as a FULL32 word: zero returns0.
Otherwise the second helper is called on the original target/selector, and only
its low byte controls returning100 or0. Keep opaque effects and this call order;
never prequery or cache the second result across the first helper.

The first fixed-O2 source generated100B with33 same-offset bytes. It indexed the
actor Y byte by1 rather than advancing the coordinate pointer and reading byte0.
It also defined score100 before the second call, preserving score in r5 across
that call and moving the selector to r6. The second source used the original
actor cursor advance and defined the raw second result before the score. It
restored the original28B frame and register roles, reaching98/102 matching bytes.
Its actual ELF function was102B; text was104B with a verified external C046 tail.
That compiler-only2B suffix is trimming metadata, not original alignment credit.

Complete original/C/header/generated ASM comparison isolated the remaining
MOV100/LSL24 pair. The source still converted the raw result to low8 only inside
the condition, after defining100. Naming the actual low-byte result before the
score definition restored LSL24 before MOV100 and all102 original bytes. The
comparison-only result needs no final LSR24. This is observed source/output
behavior; no compiler-pass trace or general scheduler claim is made.

The coordinate array view asserts offset246 but does not invent a whole unit
size or natural coordinate/selector domain. Caller-side fullword declarations
preserve the actual signed values even though the existing first callee retains
only low bytes. No helper body, instruction ASM, volatile, fixed register, padding
or compiler flag changed. Three source forms and the full clock are preserved.

Gate: local pure-C whole-native102/102 exact plus strict selection/provenance.
Accounting is102 original instruction bytes,0 literal and0 original alignment;
ELF text104 includes2 compiler-only trimmed bytes. No redundant behavior bank is
run solely for full machine-code identity. Independent frozen peer and actual
production identity remain separate. Transfer requires matching original pointer
and value/narrowing definitions, not arbitrary declaration reordering.
