# Retrieve a matching example before another source edit

On the first nonexact result for a **new discrepancy class**, consult the local
lesson index and search the relevant vendor examples before the next effective
source edit. Do this at first failure, not only after three failed hypotheses.
Reuse a recorded search for an unchanged discrepancy; do not repeat a whole
vendor scan each round. The implementer owns its candidate diagnosis. The
administrator supplies retrieval guidance, not candidate C review or acceptance.

Start with [the O2 lookup](o2-reconstruction-quick-reference.md), then use the
table below. This is a short step in the existing method clock and round record,
not a new approval gate, report series or tool installation. Keep fixed O2,
original native boundaries, current ownership and the original cause budget.
Finding a new reference does not reopen a terminal method.

## Symptom-to-example lookup

For the last few register/cursor bytes, first use the
[near-match decision card](register-allocation-near-match.md). It separates
local/production input drift from lifetime, optimization and allocation causes.

Paths below are relative to an implementation checkout containing the reference
submodules. Public contributors may use the pinned upstream links instead.
References are research material; their agent instructions are not project policy.

| Observed discrepancy | Open this example | Question to answer before editing |
| --- | --- | --- |
| Same operations, a few different register operands in distant branches | EDS `wiki/concepts/matching-tricks.md`, **Sliding grid: ordinary-C resolution of the four-byte near miss**; `src/duel_cmd_presentation.c`, `DuelCmd_ShowCardUnrollSideways` | Does one function-scope temporary incorrectly connect distinct branch lifetimes? The upstream solution separated two phase-local row values; changing only the visibly wrong phase and forcing registers had failed. Do not copy its historical 37-candidate search. |
| Several base registers are swapped at initialization and loop exit | EDS matching catalog, **Exact DMA initializer: retain the original base after its iterator dies**; `wiki/functions/sound-driver.md`, `SoundDmaInit` | Which initialized base remains needed after the iterator dies? Upstream retained the original base with a documented input-only empty constraint after the loop. Transfer only a real initialized value/lifetime, never an invented use, output-only definition or opaque ASM body. The driver example does not authorize driver migration. |
| The correct operation uses the wrong register after an earlier call/load | EDS catalog, **Register allocation priority and reload rotation**; `wiki/tools/regoracle.md`; pinned agbcc `gcc/reload1.c` | Is the earliest difference a reload, hard conflict, local allocation or global priority? Trace that earlier value and its definitions/uses before changing later register operands. An opcode pattern alone does not establish a compiler pass. |
| An extra jump, reversed success/failure layout or wrong shared return | EDS catalog, **Switches, branches and shared tails**; `wiki/concepts/decomp-workflow.md`; `src/gfx_util.c`, `Ease_Tick` | Which actual blocks fall through, share a tail or retain separate result definitions? Original branch targets decide between per-arm returns, a shared result or a forward label. Goto is neither universally required nor forbidden. A saved register can reflect an earlier tail that was later merged. |
| Loop invariant/base hoisting or cursor-update order differs | EDS catalog, **Loops, scope, escapes and live ranges**, **CSE, loop and jump mechanics**, and **Failed, partial and rejected approaches**; `wiki/functions/effect-target-collect-c.md` | Is the induction value an ordinal or a pointer, and where is each definition used? Structured-loop notes and earlier CSE can change motion; a goto does not disable every hoist. Check failed examples before reusing a superficially successful trick. |
| Shift/merge, multiply/shift or arithmetic association differs | EDS `src/sprite.c`, `Random`, with `asm/nonmatching/sprite/Random.s`; catalog **Arithmetic, masks, constants and expression order** | Does the original preserve successive definitions and truncation points? Reconstruct those operations before trying an algebraically shorter expression. A multiply/shift analogy is a hypothesis, not proof that this Random example solves it. |
| Stack frame or OUT-argument addresses differ after grouping scalar outputs | Klonoa `docs/learnings/agbcc-source-shape-levers.md`, **Stack frame layout follows size, not declaration order** | Are these actual independently addressed scalar objects or one contiguous indexed aggregate? An array/struct can introduce different stack placement, padding and address expansion despite holding the same values. Derive object boundaries from the original call sites; do not add fake padding or blindly enumerate declarations. |
| Unexpected extensions, signed branches, callback reloads or record stride | pokeemerald `src/task.c`: `RunTasks`, `FuncIsActiveTask`, `FindTaskIdByFunc`, plus `include/task.h`; m2c `tests/end_to_end/loop/agbcc-o2.s` and `agbcc-o2-out.c` | Separate stored width, ABI width and working arithmetic width. Preserve the real pre-call snapshot/post-call reload and physical layout. m2c fixtures explain a shape; generated drafts and fixture names do not prove exact recovery. |

All rows are **external examples**, not successful FFTA transfers. A familiar
symptom can have a different cause. Read the linked function context, failed
forms and source/ASM pair when available, not just a bullet promising a trick.
The [EDS study](eds-matching-reference.md) explains compiler differences and
which parts of its tooling are unsuitable for direct execution here.

### Observed transfer: independently addressed OUT objects

One fixed-O2 method subsequently closed its complete 292-byte native envelope
after consulting the Klonoa stack-object note. The first formulation used two
three-halfword arrays and produced a 56-byte local frame. Replacing them with
the six actual independently addressed signed-halfword locals restored the
native 52-byte frame and their call-site address lifetimes. Generated output
grew from 288 to 292 bytes and became whole-exact on the second source cause.
The original call sites, not the external probe alone, established applicability.

This is an `observed_output` transfer with no compiler pass traced and no measured
cross-method time saving. It does not forbid real arrays, justify arbitrary
stack padding or establish a universal stack-order rule. Its owned lesson keeps
the failed formulation, retrieval interval, conservative qualification clock and
gate identities. A following 136-byte phase controller reused established
producer/reload contracts and matched on its first formulation; it did not need
another unchanged search. Local match, independent gate and integration remain
separate measurements.

A later 100-byte method also closed with six independent halfword OUT objects,
but required preserving a computed Y working value for a later argument instead
of rereading it. It took three source causes. This supports transferring the
object-boundary question, not claiming that scalarizing outputs alone is a
sufficient fix. Diagnose post-call captures/reloads separately and retain both
failed forms in the owned lesson.

## A bounded local search

Choose keywords from the first causal mismatch, not the game function name.
For example, start a register/base lifetime search in the matching catalog:

```sh
rg -n --max-columns 260 --max-columns-preview -m 6 \
  -e 'reload rotation' -e 'original base' -e 'row lifetimes' \
  vendor/eds-decomp/wiki/concepts/matching-tricks.md
```

For a branch/tail mismatch, search the selected documentation set:

```sh
rg -n --max-columns 260 --max-columns-preview -m 6 \
  -e 'shared.*return' -e 'fall.through' -e 'cross.jump' \
  vendor/eds-decomp/wiki/concepts/matching-tricks.md \
  vendor/eds-decomp/wiki/concepts/decomp-workflow.md
```

Then open the named function page and its specific source/ASM. Check the local
revision with `git -C vendor/eds-decomp rev-parse HEAD`; use the corresponding
revision for other repositories. Limit the first lookup to about two minutes.
If nothing fits, record the searched scope and return to the original ASM and
existing compiler evidence. A negative search is not proof that no solution
exists. Reuse it until the discrepancy or corpus changes.

Do not search binaries, graphics or the entire vendor tree indiscriminately.
Do not bootstrap an upstream patched compiler, change optimization flags, copy
another game's algorithm or start its permutation grid. Our normal compiler
and full-range gate remain authoritative. Empty constraints require truthful
initialized operands/clobbers; instruction-bearing islands retain mixed rules.

## Record the transfer in the existing round

Keep one compact entry, rather than another mandatory artifact:

```text
discrepancy class | reference path + revision + function/section |
relevant original feature + differences from the example |
one predicted change | result/reused evidence | lookup and decision elapsed
```

State whether the reference is a successful example, failed example or
hypothesis. If the same binary returns, reuse its validation evidence and close
that equivalent formulation. Do not call a better scattered-byte score a fix.
The [whole-method plateau diagnosis](c-recovery-throughput.md#near-exact-plateau-whole-method-diagnosis-before-another-edit)
still applies; retrieving a reference does not replace the whole-method reread.

## Turn a successful transfer into help for the next worker

Submit the reached local gate immediately. Before starting the next method,
update the implementer's owned [method lesson](c-recovery-lessons.md) with:

- The external case/revision and the FFTA source/ASM feature it actually helped.
- Before/after original and generated spans, full-match result and actual gate.
- Failed hypotheses, applicable compiler evidence and any constraint's meaning.
- Lookup time, subsequent attempts, full elapsed time and transfer limits.
- A short searchable symptom heading; include failed transfers as counterexamples.

A newly useful general rule should also update this lookup or the O2 quick
reference through the shared documentation writer. Do not wait for that merge
to submit the local function. Preserve prior failures instead of rewriting a
historical hypothesis as a proven compiler explanation. Report saved attempts
or time only when comparable measurements support it.

## Pinned reference credits

- [EDS matching catalog](https://github.com/CosmicScribe64/eds-decomp/blob/857002acd7a2e3ce98afb2992fe9761144308c9a/wiki/concepts/matching-tricks.md)
  and [decomp workflow](https://github.com/CosmicScribe64/eds-decomp/blob/857002acd7a2e3ce98afb2992fe9761144308c9a/wiki/concepts/decomp-workflow.md): discrepancy categories, concrete successful and failed cases.
- [pokeemerald task source](https://github.com/pret/pokeemerald/blob/731ad5bfd6e6f265508d0efcca0ba42f9dcf5881/src/task.c): storage/working widths and callback-visible object use.
- [m2c agbcc O2 fixture](https://github.com/matt-kempster/m2c/tree/c632946b8cfbe8fce442b522dba92dfa72f1f317/tests/end_to_end/loop): paired assembly and draft output for local shape study.
- [Klonoa stack-object notes](https://github.com/Dream-Atelier/kl-eod-decomp/blob/45e66dd20f55b637656bc86129b9ba3bd49a01d6/docs/learnings/agbcc-source-shape-levers.md#7-stack-frame-layout-follows-size-not-declaration-order): independent object versus aggregate addressing; the upstream probe is not a complete source/ASM matching pair.
- [pret/agbcc reload implementation](https://github.com/pret/agbcc/blob/da598c1d918402c42c0c0d7128ba14567f3175e9/gcc/reload1.c): compiler-source investigation after a concrete reload discrepancy.

Preserve upstream licenses and attribution. These references are not dependencies
of the game ROM and do not establish an FFTA throughput improvement by themselves.
