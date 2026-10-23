> Public toolkit edition. Local assignments, evidence and game implementations are not distributed. See [the contributor guide](../../../CONTRIBUTING.md).

# BattleStateDependency_000A4274

Local gate: complete 200/200-byte pure-C match at `-O2 -mthumb-interwork`; 8 direct and 2 parent-composition CPU cases pass. Independent peer acceptance and production integration remain pending.

## Original structure and successful representation

The 200-byte Thumb envelope contains 97 instructions, including three 32-bit BL instructions, with no literal or alignment bytes. The first candidate preserved the record base in the wrong transfer order until the formal record pointer itself remained the long-lived source object; that closed the entry-copy cluster. Four bytes remained at `0x080A42AA..0x080A42AD`: the retail spill reload preceded the row-count byte load, while R49 emitted the byte load before the accumulator reload.

The record field at offset 704 is ordinary RAM. R50 expresses only the two count reads as ordinary `u8` accesses while retaining all other field access qualifiers and the second read after opaque calls. In a reduced pressure probe, the `.rtl` count operand is ordinary `MEM:QI`; `.greg` places the accumulator spill reload before that load. The tail count reload remains after the call. The resulting full method is byte exact.

This is a verified local result for this field and compiler input, not a universal spill-order rule. Do not apply it to MMIO, asynchronous, or callback-mutated fields without checking ownership and reload behavior.

## Measurements and evidence

- R49: 196/200 bytes, 4 differing; R50: 200/200 bytes, 0 differing.
- 8 direct and 2 parent cases pass.
- R50 source SHA-256: `aefad3448d228a8c9d1fb1b2e718e6a72cd74ae1d9b0a4fed9465adcd8d972da`; header SHA-256: `b3702cdcb4ed05dbe29c0182a1007d02b44e49b340d942cdaf788b4c2c7cc70f`.
- R50 binary SHA-256: `30414fd09ca52de8022d93736a748d9d7c0a5bfaa180788f9489a250e79ea161`; local report SHA-256: `63422480df5d8770fb43dc4c5f86227c97f4487dcd8011457db222cb6c6682d4`.
- Compiler: agbcc `da598c1d918402c42c0c0d7128ba14567f3175e9`, fixed `-O2 -mthumb-interwork`.
- Task gross elapsed: 1677.829 seconds; two full-method builds and four reduced probes.
- Detailed hash-bound evidence is in the external G41 R50 causal-closure receipt.

## Failed hypotheses and next application

A named accumulator snapshot, the direct guard-exit form, and a C register-storage hint did not change the reduced `.greg` reload order. An ordinary-RAM access-class change did. For another method, first prove memory class and post-call read requirements, then use a reduced probe and confirm the full envelope; do not add `volatile`, inline assembly, or compiler constraints merely to order an unobservable spill.
