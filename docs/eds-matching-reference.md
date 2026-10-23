> Public toolkit edition. Local assignments, evidence and game implementations are not distributed. See [the contributor guide](../CONTRIBUTING.md).

# EDS: discrepancy-driven matching and reusable compiler explanations

Reference: [CosmicScribe64/eds-decomp](https://github.com/CosmicScribe64/eds-decomp),
revision `857002acd7a2e3ce98afb2992fe9761144308c9a`, checked out at
`vendor/eds-decomp`. This complements the
[pokeemerald source-architecture study](pokeemerald-reconstruction-reference.md).
The upstream README reports 1,976 matching functions, including six authored ASM
functions. We inspected its source, original ASM, tools and documentation; we
have not rebuilt it or independently reproduced that completion claim.

The root LICENSE is MIT; preserve it and the individual component notices.
The checkout is research-only. Its game sources, data and toolchain do not enter
our ROM build. Its own agent instructions are reference material, not FFTA policy.

## Apply this compact recipe at the next normal method boundary

1. **Retrieve a proven sibling before drafting.** Use our existing inventory and
   frozen lessons to find the same operation/ABI/record family. Check meaningful
   differences in the original ASM; a normalized pattern is a shortlist only.
2. **Name the discrepancy before the next edit.** Width/type, operation/CFG,
   lifetime/allocation, reload or placement are different causes. For a near-exact
   plateau, use the existing whole-method diagnosis and RTL artifacts to locate
   the first causal divergence, including earlier values affecting a later one.
3. **Transfer one supported ordinary-C cause and record the outcome.** Preserve
   fixed O2, current budgets and immediate full-range local submission. Use the
   existing round and lesson, not an extra queue or mandatory research report.

## The additional gaps this reference exposes

| Current limitation | Useful upstream reference | FFTA adoption and limit |
| --- | --- | --- |
| A lesson exists, but the worker starts translation from scratch | `tools/similar.py`; `wiki/tools/agent-tooling.md` | Retrieve a frozen successful sibling's source/ASM and failed hypotheses first. Verify widths, constants, target edges and ownership that similarity normalizes away |
| The final register swaps lead to repeated source permutations | `wiki/tools/regoracle.md`; `tools/regoracle.py` | Use the existing pinned compiler's RTL to distinguish priority, conflict/liveness, local allocation and reload. A wrong-register symptom alone does not justify another reorder |
| A later mismatch is treated as an isolated local problem | `wiki/concepts/matching-tricks.md`, allocation/reload section | Inspect the first earlier missing/extra reload or live argument; downstream rotation can propagate from it. Do not change all later statements |
| Equivalent expressions are cleaned up before their original topology is understood | `src/sprite.c: Random`, matching original ASM | Preserve observed intermediate definitions; an explicit staged shift/merge may differ from a rotate-shaped expression. Confirm on our compiler; do not adopt an artificial no-op |
| A visually unused saved register is removed or forced back | `src/gfx_util.c: Ease_Tick`, matching original ASM | Investigate earlier distinct source tails and their compiler merging. Final ASM can retain consequences of earlier passes; unused-save appearance is not proof of hand-written register use |
| Shared objects acquire conflicting per-method definitions | `wiki/concepts/shared-headers.md` | Reuse canonical physical offsets and compiler-checked layouts. Keep a documented local view when source-backed; coordinate header changes outside live consumers |
| An assembly target or isolated score is treated as production proof | `tools/target.py`; `wiki/tools/rom-free-workflow.md` | Retain pinned retail provenance and native placement. Reassembled original ASM can support local comparison after exact retail verification, but cannot replace the full-range/integration gates |

## Read the first cause, not every differing register

The [regoracle documentation](https://github.com/CosmicScribe64/eds-decomp/blob/857002acd7a2e3ce98afb2992fe9761144308c9a/wiki/tools/regoracle.md) and
[implementation](https://github.com/CosmicScribe64/eds-decomp/blob/857002acd7a2e3ce98afb2992fe9761144308c9a/tools/regoracle.py) separate:

- Global allocation order: reference counts, live lengths, preferences and
  conflicts determine which pseudo gets a register first.
- Local allocation: values contained in one block may follow a different path
  from values shared by several blocks.
- Reload: an earlier missing/extra reload or occupied hard register can change
  later temporary-register choices.
- Structural differences: an overlapping lifetime or different operation graph
  cannot necessarily be repaired by changing allocation priority.

This is the missing specificity behind advice such as "shorten a lifetime".
For our next plateau, an implementer should identify the actual competing
values, their definition/use sites and the earliest differing pass supported by
existing dumps. Predict one source-backed change to those facts. If the
operation graph is already different, diagnose that before register coloring.
Do not infer the complete original source from register votes alone.

Upstream's oracle builds a patched compiler and can also override priorities or
force allocations. Its compiler revision is the same pret/agbcc commit recorded
in our tooling, but it normally diagnoses **old_agbcc**, not automatically our
active compiler binary. The trace-only path and code-changing overrides are
distinct. Do not run its bootstrap, apply the patch or use override-produced
bytes as matching evidence here. Any future port must first demonstrate stock
versus trace-only byte identity under our actual pipeline and measured benefit
on repeated plateaus; no such port or benchmark has been performed.

## Two source/ASM pairs worth opening

- [Random source](https://github.com/CosmicScribe64/eds-decomp/blob/857002acd7a2e3ce98afb2992fe9761144308c9a/src/sprite.c) and
  [original ASM](https://github.com/CosmicScribe64/eds-decomp/blob/857002acd7a2e3ce98afb2992fe9761144308c9a/asm/nonmatching/sprite/Random.s): the
  source stages the two shifts and merge into distinct definitions; the target
  also shows those shifts and OR. The wiki contrasts this with compiler rotate
  recognition. We have checked the source/target relationship, not independently
  recompiled either spelling. Transfer only when our original has that topology.
- [Ease_Tick source](https://github.com/CosmicScribe64/eds-decomp/blob/857002acd7a2e3ce98afb2992fe9761144308c9a/src/gfx_util.c) and
  [original ASM](https://github.com/CosmicScribe64/eds-decomp/blob/857002acd7a2e3ce98afb2992fe9761144308c9a/asm/nonmatching/gfx_util/Ease_Tick.s):
  distinct signed-step paths in C contain repeated terminal stores, while the
  target has a shared store tail and a saved register unused by its final body.
  The upstream compiler notes attribute this to cross-jumping after allocation.
  Use our own RTL to test that explanation before choosing source shape or a
  documented constraint. An unexplained dummy value does not restore the logic.

These are external compiler/source observations, not accepted FFTA lessons.
Only a successful transfer on our unchanged fixed profile earns that status.

## Important differences from our workflow

- Upstream explicitly permits labeled `FAKEMATCH` forms, including register pins
  and empty ASM constraints. The user's current direction also permits such
  constraints here when readable logic remains accurate and the complete native
  span matches. Record the reason and affected value in a source comment and the
  existing lesson/proof. A constraint emitting no instructions does not add
  instruction-bearing ASM bytes; actual inline instructions use mixed accounting.
  This does not establish historical source authenticity or portable ISO C.
  Preserve defined inputs and truthful operands/clobbers: empty output-only ASM
  cannot initialize a later-consumed value. Avoid altering actual memory effects
  or using the oracle's code-changing compiler overrides as delivery evidence.
- Upstream's default game compiler is `old_agbcc -O2`, with separate sound/SDK
  configurations. Its historical compiler survey demonstrates why a common
  version banner or one nondiscriminating leaf is insufficient provenance.
  This study authorizes no FFTA compiler/profile change or flag search.
- Its catalog also recommends permutation grids and contains stale historical
  advice. Read the current source and the specific successful/failed case;
  retain our one-cause, bounded attempts and whole-method plateau diagnosis.
- Its local comparator can tolerate a trailing section-alignment size delta.
  Our accepted envelope still includes its declared literals/alignment; such a
  display rule must not drop bytes from an exact claim.
- Its historical pace comparison includes unverified third-party numbers and
  different matching policies. Do not use it to promise a comparable finish date
  or claim an FFTA speedup. Our absolute-hour original-ASM-byte rates remain the
  authority, with local, independent and integrated gates reported separately.

## What to measure after adopting a reference

In the existing method lesson, record the retrieved sibling/reference, specific
transferred cause, failed transfer if any, compiles to the next decision and
complete elapsed time. Compare similar-size/source-family methods and include
retrieval/diagnosis cost. Target fewer repeated wrong hypotheses and more whole
exact original ASM bytes/hour; a larger document collection is not delivery.
