# Resolve a near match before forcing registers

Use this card when a complete fixed-O2 function differs by a few register
operands or cursor operations. It supplements [worker rules 10–12](worker-decomp-strategy.md#10-separate-different-phase-lifetimes-before-pinning-registers).
Keep the original complete envelope, native identity, clock and cause budget.
A recalled terminal method remains terminal until an explicit supported
continuation; a diagnostic experiment earns no implementation credit.

## Choose the next action from the earliest difference

| Earliest established difference | Next supported action | Avoid |
| --- | --- | --- |
| Effective source, header, macro, ABI or compiler flags differ between local and production | Repair input equivalence; compare the existing preprocessed source and actual compiler argv | Assuming a policy label proves the effective profile; the builder has a legacy fallback, so require explicit O2 in the effective module |
| Only relocated calls, literals, alignment or veneers differ | Compare compiler ASM/object relocations separately from final placement | Calling a linked-address difference register allocation |
| Different operations, truncation, CFG, snapshot or induction order already exist before allocation | Recover that source operation/lifetime first | Pinning the final visibly wrong register |
| The same real value must remain live across a phase or loop | Preserve its actual base/result lifetime; separate a moving iterator from its original base | Joining unrelated phase temporaries or adding fabricated values |
| The correct operation graph exists but local/global allocation or reload first changes a value | Inspect the first affected pseudo, uses, conflicts and call crossings in existing RTL | Declaration permutations, broad clobbers or allocation overrides |
| A specific short lifetime still needs the original hard register | Test one initialized fixed-register operand with a truthful empty constraint | Assuming a register declaration reserves the register throughout the function |
| A small original instruction sequence remains after a bounded diagnosis | Consider an explicit, owned mixed island, then verify the entire linked method | Whole-function opcode/ASM blobs, hidden effects or counting a prefix as whole exact |

## Local compilation is a question to test, not the default suspect

The current bounded comparator invokes the same `build_rom.compile_module`
backend and `c_preprocessor_command` as production. A full ROM build is not
needed to decide allocation. This shared path alone does not prove two builds
used identical inputs. Pin the effective module, complete translation unit,
preprocessed bytes, declarations/packing, compiler binary/argv and dependencies.

Reuse existing output first. If context remains a plausible cause, reuse an existing control, or perform an
already-authorized unchanged-source local versus genuine production-equivalent
module comparison within its original clock/budget. This grants no extra cause.
Compare pre-link function instructions and final placement separately. A random
neighbor function or a different header is not a production-context control.
Record a missing control as unknown rather than declaring isolated compilation
universally harmless. Do not change optimization levels or rebuild the ROM.

### Recalled build-context control and unresolved counterexample

A 44-byte whole-exact callback has identical local and production binary hashes;
its production source preprocesses to the same bytes as the frozen local input.
This demonstrates equivalence for that module, not every possible translation
unit. The 264-byte two-cursor near match still has 252/264 same-offset bytes and
no whole-exact credit. Its unchanged diagnostic input reproduces the same binary.
Existing RTL shows cursor initialization order changing in `combine`, before
allocation, and the update order already present in `flow` after loop induction
processing. It is not merely the final hard-register assignment. The selected
production method is still ASM, so a production-C context control for this
method remains unknown. First recover the two actual induction lifetimes/order;
any constraint or mixed-island proposal needs its own supported experiment.

## Three mechanisms, with different accounting

**Ordinary C lifetime repair.** Separate objects that belong to distinct phases;
keep original snapshots and actual call-crossing values. An earlier definition
or missing reload can rotate registers far from the cause. EDS's four-byte
sliding-grid near miss closed by separating row lifetimes in other phases;
forcing only the visibly wrong phase had failed.

**Initialized compiler constraints, zero emitted instructions.** Select the
narrowest actual definition/use interval. An input-only operand can retain an
initialized base after its iterator dies:

```c
/* base is initialized and is the original object base, not a dummy value. */
asm volatile ("" : : "r" (base));
```

For an actual computed full-word result, a read/write operand can preserve a
late register value/normalization boundary:

```c
/* Fragment: compute_result and the low-byte return follow the original ABI. */
register unsigned result asm ("r0") = compute_result();
asm ("" : "+r" (result));
return (unsigned char)result;
```

These are conditional recipes, not universal wrappers. Check the pinned
compiler's constraints and the whole output. A local register binding does not
reserve the register or guarantee every use; calls, frame-pointer conflicts,
reload and loop induction recognition can defeat it. Never manufacture a value
with empty output-only ASM, add fake clobbers, or use a blanket memory barrier
to force register choices. An empty template can still affect compiler length
estimates and branch shortening, so inspect remote branches too.

**Emitted instruction island.** If a truthful short original sequence is the
remaining supported solution, declare its inputs, outputs, tied operands and
actual clobbers; preserve memory/call effects and full original CFG. Account it
as mixed with exact emitted instruction bytes, excluding literal/alignment
and veneer bytes from the ratio. A byte-diff count is not an island size: replacing two
operand bytes can require several complete instructions and change live ranges. The ordinary completion threshold is strictly below 10%;
a builder accepting exactly 10% does not establish completion. Separate
documented low-level exceptions remain lower priority. A full native
match can complete such a mixed method, but does not turn it into pure C.

## Proven project transfers and limits

- A 192-byte shared-result method improved from 177/192 to 192/192 after one
  supported continuation: an initialized late full-word R0 read/write operand
  retained the original low-byte normalization. Zero emitted inline instructions.
- A 60-byte callback method improved from 53/60 to 60/60 in three source causes.
  An R1-only attempt regressed to 56 bytes and 7 same-offset bytes; the final
  initialized first-context R0 operand retained the original R0-to-R2 copy.
  Zero emitted inline instructions. A nearby wrong pin is evidence against
  blanket register forcing, not against truthful constraints.
- A 56-byte payload controller initially saved an extra R5 because its mode
  constant was defined before a call. Moving that real definition after the
  call restored the frame; anchoring the initialized payload address at its
  original phase then closed 56/56. This requires both lifetime and copy timing,
  not just a hard-register name. Zero emitted inline instructions.
- These are recalled complete-range results, not a new speedup experiment or
  proof that any register mismatch has the same cause. Local, peer and integrated
  gates remain separate; a near match receives zero whole-exact credit.

## Primary references

- [Pinned agbcc manual: local register variables and extended ASM](https://github.com/pret/agbcc/blob/da598c1d918402c42c0c0d7128ba14567f3175e9/gcc_arm/extend.texi):
  `Local Reg Vars`, `Extended Asm`, initialized input/read-write operands. This
  manual is in the separate ARM tree; cross-check normal Thumb implementation
  in [`gcc/toplev.c`](https://github.com/pret/agbcc/blob/da598c1d918402c42c0c0d7128ba14567f3175e9/gcc/toplev.c)
  and [`gcc/stmt.c`](https://github.com/pret/agbcc/blob/da598c1d918402c42c0c0d7128ba14567f3175e9/gcc/stmt.c).
  EDS primarily uses `old_agbcc`; its allocation results do not automatically
  transfer to the normal Thumb compiler used here.
- [Pinned EDS matching cases](https://github.com/CosmicScribe64/eds-decomp/blob/857002acd7a2e3ce98afb2992fe9761144308c9a/wiki/concepts/matching-tricks.md):
  sliding-grid lifetime resolution, retained DMA base, failed pins and reload.
- [Existing symptom lookup](vendor-matching-playbook.md) and
  [pipeline diagnosis](asm-to-c-migration.md) for a specific unresolved pass.

Before another effective edit, record one predicted change and reuse the
applicable lookup. Preserve all failures. After a successful whole match, put
the exact conditions, failed transfer and complete-method result in the owned
lesson; do not create another recurring report or benchmark gate.
