> Public toolkit edition. Local assignments, evidence and game implementations are not distributed. See [the contributor guide](../CONTRIBUTING.md).

# Source patterns supported by exact C matches

For the shortest route from an original operation to a supported C form, use the
[fixed-O2 lookup and counterexamples](o2-reconstruction-quick-reference.md).
The [lesson index](c-recovery-lessons.md#evidence-index) tracks later acceptance
receipts; this study does not perform live candidate acceptance.

## Current focus: fixed O2

Current matching work and new transfer experiments use only
`-O2 -mthumb-interwork`. Prioritize the four verified O2 successes below,
totaling 1,056 whole-method envelope bytes. The selected-record and collector
O1 examples later in this document are historical evidence; their instruction
selection/allocation must not be presented as established O2 behavior.

| O2 success | Complete span | Proven useful representation | First relevant mechanism |
| --- | ---: | --- | --- |
| Sort | 316 B | Explicit callback and priority-address evaluation boundaries | Initial RTL expression order; two independent4-byte corrections |
| Derived flags | 572 B | Typed ordinary RAM, ordered flag effects and correct direct helper linkage | Call/width contract; direct binding removes12 excess bytes |
| Acquisition queue | 112 B | Keep branch-only field addresses separate from loop-lived row base | Initial expression, loop hoisting and live-range/allocation effects |
| Acquisition initializer | 56 B | Separate fullword zero snapshot from mutable signed ordinal | Local quantity order, then same-mode redundant-zero elimination during global allocation/reload |

The initializer is an exact result with 46 candidate lifecycle
invocations passing; worker2 subsequently accepted its frozen evidence together
with the 112-byte queue package. Production integration remains pending. Its source and all
56 disassembly bytes were checked against the frozen report and retail range.
The O2 corpus receipt is `o2-main-pool-42/o2-success-corpus.json` in external
evidence. Sort/derived flags are integrated; queue/initializer have independent
acceptance. None of these observations authorizes an optimization-level search.

Subsequent fixed-O2 work produced three more locally exact methods: mission timer
transitions (370 B), mission record replacement (260 B), and effect 28 (138 B).
Their 768 envelope bytes remain a separate local-results cohort, with peer
acceptance pending in the cited receipts. The strongest new transfer lesson is
conditional: logical field extraction reproduced the timer method, while raw
mask consumption reproduced record replacement. Copying the bitfield expression
between these consumers failed. See the lookup for both sides of this result.

The initializer's crucial distinction is that an immutable cleared value and a
mutable loop ordinal can originate from the same fullword zero without being
one source variable. A narrow zero representation changed allocation but left a
redundant initialization; matching the fullword value mode allowed its removal.
This follows actual store/loop uses, not an unused variable inserted to force a
register. See the [numerical allocation lesson](c-recovery-lessons/main/initializer.md).

Apply the O2 rules by original feature and actual pass evidence. Source brevity,
fewer temporaries and merged address expressions are not optimization goals.
Whole-function equality and delivery time remain the measured outcomes.

## Historical five-method study

The strongest common property of this sample is preservation of the original
object, evaluation and lifetime structure. Formatting, naming style and shorter
expressions do not explain its exactness. Use the patterns below as hypotheses
with explicit preconditions, not a universal template for all game functions.

This study reads frozen successful C, its generated disassembly, the historical
controlled changes and acceptance metadata. It does not review live candidates
or create new behavior acceptance. The five frozen binaries were compared again
with their complete corresponding ranges in the identified US retail ROM; all
five are equal. No compilation, behavior rerun or full-ROM build was needed.

## Corpus and limits

| Complete method | Original/generated envelope | Historical profile | Acceptance status |
| --- | ---: | --- | --- |
| `SortBattleUnitTurnOrder_08099A70` | 316/316 B | O2 | Integrated in EXACT-C-INTEGRATION-25 |
| `ProcessSelectedBattleTurnRecords_0809F850` | 156/156 B | O1 | Integrated in EXACT-C-INTEGRATION-25 |
| `CollectBattleTurnUnitPointers_0809F78C` | 100/100 B | O1 | Integrated in EXACT-C-INTEGRATION-25 |
| `CoreConsumer_00098130` | 572/572 B | O2 | Integrated in EXACT-C-INTEGRATION-25 |
| `CoreRegion_00038858` | 112/112 B | O2 | Subsequently independently accepted; integration pending |

These are five selected successes totaling 1,256 envelope bytes, including
literals/alignment. They are not a representative sample for an overall success
rate. The integrated subset is four functions/1,144 bytes. The O2 subset is three
functions/1,000 bytes; the O1 subset is two/256 bytes. Historical O1 observations
do not establish the same instruction output under current fixed O2. Do not
rerun optimization-level comparisons or change the normal profile.

The frozen source hashes match their build reports. The four integrated source
files currently equal the corresponding frozen source files. Hashes, original
offsets and report/disassembly references are retained in the external
`matching-lessons-41/success-style-corpus.json` receipt.

## 1. Model conversion time, not only the final type

The collector captures the request's low 16 bits before allocation, then
interprets the saved value as signed after initialization:

```c
u16 saved_count = requested_count;
/* allocation and initialization */
remaining = (s16)saved_count;
```

Generated sites `0x0809F792`/`0x0809F794` truncate before the allocation call;
`0x0809F7A4`/`0x0809F7A6` sign-extend after initialization. Moving the snapshot
before allocation improved the historical comparison from 15/100 to 92/100.
The remaining address changes, not more type spelling, closed the function.

The queue writer's `u16 item, u8 category, u16 quantity` arguments reproduce
the distinct entry shift pairs at `0x0803885A` through `0x08038864`. Signed
ordinal comparison and the negative full-queue return are separately preserved.

**Apply when:** ASM shows truncation before a call and signed use later.
Do not replace this with one early signed cast without checking the live range.
The collector result is historical O1; its semantic conversion obligation still
applies under O2, but its exact allocation must be established independently.

## 2. Use intermediates for observed evaluation boundaries

The sort retains separate callback context objects and materializes the callback
value before storing its argument. Its generated `0x08099A80` load precedes the
`0x08099A82` argument store. Inside the comparison loop, the first priority address
is formed at `0x08099B36`, before loading the second node at `0x08099B38`.

The two isolated corrections each changed 308/316 to 312/316 in disjoint ranges;
together they produced 316/316. Initial RTL already contained the differing order.
This is direct evidence for expression-expansion order, not a speculative late
instruction-scheduling explanation.

**Apply when:** an original address or callback value is materialized before
another load/store. Give that value a meaningful local name at the observed
boundary. Do not add a C temporary for every machine register or permute all
declarations: allocation can combine or remove equivalent values.

## 3. Preserve address-expression structure and branch-local lifetimes

The queue writer keeps `workspace + ordinal * 8` separate from the conditional
item address. Category and quantity field addresses are formed only after a
free slot is found. Generated sites `0x0803887C`, `0x08038880`, `0x0803888C`
and `0x08038892` preserve those distinct calculations.

A cached row-field address in the first candidate kept a constant live across
the loop and generated 116 bytes. Reconstructing the branch-local address uses
produced 112/112 exact bytes in the next candidate. The frozen cause follows
initial RTL through `.loop` hoisting and `.greg` register materialization.

The selected-record method independently shows the limit of common-expression
reuse. It forms the node-table base, then adds the scaled index; after the callback
it retains a separate value-table expression. Reusing one source offset for both
calculations repaired one pair but introduced seven other differing bytes.
Restoring the independent expression closed the method under its historical O1.

**Apply when:** ASM has separate address uses or a field is only needed in one
branch. Reconstruct its def-use graph before introducing a shared row/field
pointer. Equivalent arithmetic and fewer C expressions do not imply equal code.

## 4. Distinguish snapshots, repeated reads and callback-visible objects

In the sort, collected count is captured after the visitor returns and used as
one snapshot. Signed priorities and marker tests use ordinary signed halfword
reads under the established access contract. Distinct visitor objects preserve
their stack layout and lifetimes.

In selected records, the copy callback can change the selected slot and count.
The generated code reloads the slot after the call at `0x0809F89E` and count at
`0x0809F8B4`. Its return node is loaded before freeing the workspace. The exact
source uses narrowly expressed callback-visible accesses; that is not evidence
for making all RAM volatile.

In derived flags, ordinary typed RAM plus opaque helper calls produces the
required reloads. The final flags snapshot follows the last helper. The first
status test and later snapshot remain separate, matching `0x08098336` and
`0x08098346`.

**Apply when:** reconstructing a memory access, label it as an original snapshot,
ordinary repeated read, callback-visible reload or hardware access. Preserve the
contract before diagnosing code shape. Neither blanket volatile nor blanket
load caching is supported by these successes.

## 5. Preserve branch topology and ordered effects

Derived flags keeps the original sequence of helper predicates and flag updates.
It does not accumulate a private mask and commit once after all calls. Its last
three status writes are independent conditions in source order: later writes can
override earlier ones. Replacing them with an `else if` chain changes behavior.
The `u8` helper return declarations also reproduce the observed low-byte tests.

The selected/collector sources retain the original entry guards, loop bodies,
continuation tests and values saved across calls. The sort retains distinct
callback records rather than merging equal-looking object lifetimes.

**Apply when:** two paths converge, determine the state and effects arriving at
the join before making a shared helper, Boolean temporary or common return.
There is no general preference for one return, early returns or `goto`; the
original incoming edges and live values decide.

## 6. Match call linkage before blaming source shape

The derived-flags O2 candidate was 584 bytes before two missing helper aliases
were bound to verified direct Thumb call addresses. With the same O2 profile,
declaration-only symbol bindings yielded 572/572 exact bytes. No instruction
assembly was added. Generated sites `0x080982F6` and `0x08098302` are direct BLs.

This improvement is an ABI/linkage correction, not evidence that a different
Boolean spelling improved allocation. First verify target, mode, prototype and
direct/indirect call form. Prefer existing verified symbols; an absolute binding
requires exact revision-bound evidence and must not replace a helper body.

## What explains these successes

The controlled changes support a specific explanation: widths, object identity,
evaluation points, CFG edges and lifetimes became close enough to the original
compiler input for the pinned backend to reproduce its complete output. Type
names and C syntax alone were insufficient. Exact equality demonstrates that the
toolchain can reproduce these particular methods; it does not identify every
original compilation unit's compiler/version/flags.

The successful methods also had bounded interfaces and reusable checks before
the final matching changes. That reduces semantic uncertainty, but this selected
corpus does not measure how much time the preparation saved. Queue closure took
214.999510 seconds and two candidate builds; there is no comparable control run,
so no speedup factor is assigned.

Use a five-part source map before coding: physical object/field widths;
conversion points; CFG and ordered effects; snapshot/reload obligations; and
address/value live ranges. For a mismatch, compare the first different operation
and its first divergent compiler pass. Record one predicted consequence before
one source change. Stop repeating a spelling class once it produces the same
binary. Successful transfer or counterevidence belongs in the
[method lesson](c-recovery-lessons.md), with the actual profile and elapsed time.

## Source references

- `src/battle_turn_selection_21/sort_order.c` (implementation-checkout reference).
- `src/battle_turn_selection_21/process_selected_records.c` (implementation-checkout reference).
- `src/battle_turn_selection_21/collect_unit_pointers.c` (implementation-checkout reference).
- `src/battle_unit_derived_flags_25/refresh_derived_flags.c` (implementation-checkout reference)
  and `src/battle_unit_derived_flags_25/derived_flags.h` (implementation-checkout reference).
- [Queue lifetime lesson](c-recovery-lessons/main/queue-acquisition.md), with local
  acceptance limits; its candidate remains outside the production source tree.
- [Pinned compiler mechanics](agbcc-o2-matching.md).
