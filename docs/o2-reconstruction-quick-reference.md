> Public toolkit edition. Local assignments, evidence and game implementations are not distributed. See [the contributor guide](../CONTRIBUTING.md).

# Fixed-O2 reconstruction: choose a source form from its ASM use

Use this page before the first candidate, then consult the linked frozen lesson
for evidence. Keep `-O2 -mthumb-interwork` fixed. The objective is a complete
readable method with the original behavior and exact output, not a shorter C
expression or a larger count of scattered equal bytes.

The [GBA resource collection](gba-asm-to-c-resources.md) indexes the supplied
47 references and pinned local GitHub corpus. Its
[ISA lookup](gba-asm-to-c-idioms.md) and
[adapted workflow](gba-asm-to-c-workflow.md) support a specific unresolved
question; they add no whole-ROM analysis, installation or compiler-search gate.

For source-family preparation, consult the
[pokeemerald reference study](pokeemerald-reconstruction-reference.md).
Use its feature index for shared object/callback contracts, storage versus
working types, callback-visible reloads and script cursor ownership. These are
external source observations to test against our original ASM, not proven FFTA
recipes. The [EDS discrepancy-driven reference](eds-matching-reference.md) adds
matched-sibling retrieval and first-cause RTL/allocation/reload diagnosis. Its
compiler choices do not change our fixed profile. Documented register/empty-ASM
constraints are allowed under the current compiler-constraint rule in AGENTS.md;
they do not defeat a full native match. Read only the relevant example and use
the existing round record. Older no-forcing cautions in individual cases describe
their unsupported hypotheses, not a blanket prohibition on valid constraints.

For several unresolved branch/source-form alternatives, use the bounded
`tools/jev_analyze.md` (implementation-checkout reference):
extract the relevant blocks/targets locally, supply only applicable rules, and
ask finite choices. Confirm the selected interpretation in source before coding.
This is optional triage, never a new approval or model-vote gate.

## Select by operation, not by a neighboring function's spelling

| Original feature | Source form to test | Counterexample / stop condition | Frozen evidence |
| --- | --- | --- | --- |
| Operations and widths agree; existing local-allocation evidence isolates a slot-base/ordinal register inversion | An initialized fixed-register local plus a documented instruction-free read/write operand can express that exact requirement | Declare all block locals before ASM under C89. A binding alone is not a general guarantee; a changed frame, extra move or remaining mismatch is failure. Do not apply to earlier loop/combine differences | [39 to 44/44 B in one new cause; 173.2 s recall episode](c-recovery-lessons/administrator/initialized-slot-base-constraint.md) |
| Comparisons branch directly to their effect continuations without a numeric predicate result | Keep the strict conditions at their actual control-flow consumer; avoid an unobserved Boolean lifetime | If original ASM materializes 0/1 for a later consumer, preserve that distinct value instead. Helper inlining is not a global rule | [268 B exact and the opposite structural case](c-recovery-lessons/administrator/predicate-uses-and-family-contracts.md) |
| An already narrowed value crosses a call without additional caller shifts | Distinguish the full caller-register value from the bits the callee consumes; use the proven compatible interface | A narrow prototype can introduce shifts absent in the original. Never widen every prototype or change return width globally | [Caller boundaries: 960 B exact](c-recovery-lessons/administrator/call-boundaries-and-small-records.md) |
| A helper result is narrowed before defining a constant, and only its low byte controls a branch | Define the actual narrowed value at that point, separately from the raw helper result and subsequent constant | A cast postponed until the condition left MOV100 before LSL24; moving only a declaration is insufficient. Preserve full-word tests and helper interfaces where observed; no arbitrary casts or register forcing | [Effect feasibility: 98 to 102/102 B](c-recovery-lessons/worker2/EffectDirect_0012D2F0.md) |
| A byte field belongs to an observed two-byte physical record | Assert the actual compiler size/offsets and represent the proven packed stride | agbcc rounded an unpacked two-byte record to four bytes. Field widths alone do not establish stride or producer bounds | [Six residual bytes closed by physical layout](c-recovery-lessons/administrator/call-boundaries-and-small-records.md) |
| Ordinary halfword masks use LDRH/STRH, even for individual low bits | Use the actual u16 field and masks, preserving separate reloads | C bitfields can narrow to byte accesses; packed logical-field extraction is a different case | [Actor-row cleanup:252B exact](c-recovery-lessons/worker2/CoreMutationDependency_000A53E4.md) |
| Shifts extract a logical three-bit value, followed by a masked field update | Model the actual packed field, including its storage size | Do not transfer this form to a branch consuming raw masked bits | [Timer transitions: 370 B exact](c-recovery-lessons/main/mission-queue-timers.md) |
| Successive property reads feed cross-byte shifts and partial-byte RMWs in one packed record | Derive each field's bit start/width and untouched bits first; use the proven packed layout and keep assignment/call order | Ordinary halfword flags still require halfword accesses. Do not replace callback-visible assignments with a buffered generic serializer or assume portable bitfield layout | [Unit snapshot: first-source 306 B exact](c-recovery-lessons/worker3/EffectDirect_0012EBD0.md) |
| Ordered rejection tests converge on one loop increment; finding an eligible record bypasses the post-loop cursor update | Preserve the original ordered tests, shared `continue` edge, early return and complete local pointer array | No switch/table rewrite without original evidence; a cached unit pointer can remove required post-helper reloads | [Scene eligibility: first-source 188 B exact](c-recovery-lessons/sol_b/Scene51_00122A00.md) |
| A stored callable word feeds a native indirect call, with its address surviving another helper | Use the source-proven function-pointer type and actual arguments | An artificial four-argument trampoline changed address/scratch lifetimes. This does not apply to an internal entry with a nonstandard ABI | [Modal transaction: 181 to 216/216 B, second source](c-recovery-lessons/sol_b/SceneRegisteredRoot_00023488.md) |
| Discrete scene IDs form two clustered comparison trees | Preserve the complete enum cases and nested dispatch structure | Replacing cases with range conjunctions changed the tree. Do not turn arbitrary numeric intervals into switches | [Request owner: 306 B exact](c-recovery-lessons/sol_b/SceneRegisteredRoot_0002326C.md) |
| Status results form discrete groups 1/2 and 3/4, with different operation effects | Preserve grouped cases in a nested switch before adjusting comparison constants | A mathematically equivalent range test left `CMP 0; BGT` where retail used `CMP 1; BGE`. This is not a rule for numeric thresholds | [Mission operation: 590 to 592/592 B](c-recovery-lessons/main/grouped-mission-status-cases.md) |
| One byte-loaded phase feeds a signed dispatch and survives calls into differently narrowed arguments | Separate physical byte storage from the promoted captured value; preserve signed `int` use when the original supports it | A u8 local added a copy; u32 removed it but changed dispatch to unsigned. Do not widen all fields or change helper ABI | [Eligible selection: 412 to 404 to 408/408 B](c-recovery-lessons/worker3/SceneRegisteredRoot_0005D784.md) |
| A controller writes an inactive terminal state and materializes an allocation-root cell before Allocate | Retain the source-proven terminal case and that actual cell definition; preserve later callback-visible reloads separately | A sibling can use253 handoff and255 teardown or different child counts; never copy sizes/cases without original evidence | [Five locally exact methods:1490B; two siblings matched on their first source](c-recovery-lessons/administrator/content-flow-family-transfer.md) |
| A destination pointer is captured before a helper, while count/state writes use a post-helper root | Keep the captured destination and live context as distinct values at those exact sites | A uniform cached context or blanket volatile changes the original def-use relationships; inspect each helper boundary | [Cancellation: first-source 204 B exact](c-recovery-lessons/main/mission-cancellation-operation-refresh.md) |
| Source bytes are reloaded after a helper and copied before destination addresses are formed | Keep the observed load-before-address definitions in a distinct post-helper copy value, separate from earlier command operands | A load-order-only change still failed when it reused an earlier command value. Do not move loads across helpers or infer a declaration-order or volatile rule | [Scene coordinate copies: 114 B exact](c-recovery-lessons/main/scene-coordinate-post-helper-copy.md) |
| A physical definition record is selected before a second table lookup | Define that record pointer at the observed point, then access its typed field | Naming alone is insufficient; the definition must change actual evaluation/lifetime boundaries. No speculative loads across helpers | [Request owner: 37 residual bytes closed; transferred from a 364 B constructor](c-recovery-lessons/sol_b/SceneRegisteredRoot_0002326C.md) |
| Argument loads occur after an effect-ID decision; zero follows the original fallthrough | Keep the original field-load sites and use zero-first `if/else` when that reproduces the observed branch | Removing every snapshot is wrong: callbacks can require retained values or fresh reloads at different sites. A ternary added a jump here | [Result feedback: 1001 to 1026 to 1042/1042 B](c-recovery-lessons/sol_c/BattleStateDependency_000A5580.md) |
| A branch tests raw byte bits 2..4 with AND 28 | Keep a raw-byte mask predicate | A logical bitfield introduced shifts and changed the peeled loop | [Record replacement: 260 B exact](c-recovery-lessons/main/mission-record-replacement.md) |
| A scan cursor dies on success while the found record survives unlink/calls | Separate the cursor, found-value snapshot and later scan ordinal at their actual definition points | Renaming two pointers with identical definitions coalesced to the same binary; declaration permutations are not a lifetime fix | [Timer transitions](c-recovery-lessons/main/mission-queue-timers.md), [record replacement](c-recovery-lessons/main/mission-record-replacement.md) |
| A condition loads a previous-node value that is reused on loop exit | Retain that condition snapshot | An extra post-loop load is a different definition, even when the test inputs agree | [Record replacement](c-recovery-lessons/main/mission-record-replacement.md) |
| The original computes a mask, captures a record, then compares the mask | Express those meaningful evaluation boundaries in that order | Two names assigned before the mask did not reproduce the original allocation | [Record replacement](c-recovery-lessons/main/mission-record-replacement.md) |
| A byte comparison and byte-object update have distinct promoted values | Compare and update the actual byte object at the observed store; preserve computed-value versus reload sites | Changing only a local timer's width can be binary-identical. Cached roots or modulo helpers need their own original evidence | [Timer transitions](c-recovery-lessons/main/mission-queue-timers.md), [fee commit](c-recovery-lessons/worker3/CoreFrontier_0005EA0C.md), [category scan](c-recovery-lessons/worker3/Source52_0008D554.md) |
| One post-helper halfword flags RMW accesses ordinary RAM, without an intervening call | Test the typed field RMW at that site, preserving other callback-visible reloads | Explicit volatile snapshot/store forms added reads; operand reversal was identical. No transfer to MMIO or asynchronous state | [Effect 28: 138 B exact](c-recovery-lessons/worker2/EffectCallback_001322B0.md) |
| A runtime outer object supplies a field after a helper | Preserve the actual field access and reload point | An invented field-address local folded base + offset into a different literal | [Record replacement](c-recovery-lessons/main/mission-record-replacement.md) |
| Numeric fixed-RAM pointer arithmetic introduces a new base-plus-offset literal | Declare the actual fixed-address object through verified symbol-only linkage; access its source-proven typed field | A generic inline accessor or equivalent index expression can still fold. No forced register, fabricated object or invented array capacity | [Descriptor root: 228 B exact](c-recovery-lessons/main/effect-descriptor-root.md) |
| An indexed ROM lookup scales the narrowed ID before loading the record base, then accesses a field | Bind the actual ROM object symbol and retain the observed scaled-offset, record-pointer and field definitions | Symbol-only linkage can restore the literal yet leave base-before-scale lifetimes wrong. Preserve the entry narrowing; this is no general operand-order, argument-width or volatile rule | [Item object base](c-recovery-lessons/main/item-sign-rule-object-base.md), [offset before base](c-recovery-lessons/worker2/CoreRegion30_0013413C.md) |
| One physical slot range has word accesses and halfword accesses at word stride; only constant/index association remains wrong | Check the dynamic reference's inferred alignment in pinned `get_inner_reference` / `expand_expr`; a proven overlapping halfword-array view can expose the original expansion | Require actual overlap, stride and extent. Early base locals changed tail sharing; equivalent casts repeated a failed binary. No alignment attributes or invented capacity | [306-byte inventory selection closed in one remaining trial](c-recovery-lessons/administrator/halfword-view-address-expansion.md) |
| Three address instructions associate index + runtime before the field offset, while the original forms the field base first | Use the actual trailing field and its observed element stride | Transfer requires evidence for that object, offset and width; do not add dummy members to steer code generation | [Effect 92: 152 B exact](c-recovery-lessons/main/effect-pool-selection.md) |
| Separate sign-extension chains normalize operands before arithmetic and later result wrapping | Materialize the signed operands at their original definition points before subtracting and narrowing the result | Same-expression casts or changing only result width can disappear in initial RTL; arbitrary extra temporaries can increase pressure | [Unit value classification: 222 B exact](c-recovery-lessons/main/unit-value-classification.md) |
| Several sequential threshold computations reuse one temporary register, while context survives all calls | Give each actual computation its own lifetime and retain callback-visible field reloads | Declaration order or removing a qualifier alone was binary-identical; a named extra intermediate overflowed | [Effect 43: 552 B exact](c-recovery-lessons/worker2/EffectCallback_001326AC.md) |
| A proven fixed-size halfword field is indexed while separate base/offset constants and ordinal uses remain live | Represent that actual physical array field before choosing a cursor abstraction; predict the address-definition change | The20-slot shuffle reached160/160 after this change; a different56-byte scan still failed. No invented field capacity or blanket conversion to indexing | [Physical inventory fields](c-recovery-lessons/administrator/physical-inventory-fields.md) |
| Original clears byte identity, byte flags and a halfword link, then reuses one allocation across calls | Preserve the three typed stores and the captured allocation's lifetime | A generic word clear or fresh pointer reload changes these observed operations; this is not a helper-migration rule | [First-source44-byte discard](c-recovery-lessons/administrator/physical-inventory-fields.md) |
| Original retains a scaled ordinal, but candidate advances a second pointer | Locate induction-variable rewriting in `.loop`; distinguish scan and matched-result uses | Moving a continuation outside the scan grew effect 91 from 152 to 160 B, over its 154 B envelope. This is an unresolved diagnosis, not a fix | [Effect 91: bounded nonexact](c-recovery-lessons/main/effect-pool-reference.md) |
| Ordered bit-priority helper choices feed a zero fallthrough and shared full-word return | Map the actual call/zero/join edges and retain full return widths; reuse a compatible successful source form | The same native branch shape matched both a shared result and ordered early returns in two siblings. Neither spelling is universally required; mask operand order was not isolated | [Two 56 B exact selectors and the failed source form](c-recovery-lessons/administrator/equipment-selector-source-forms.md) |
| Two incoming paths share a halfword return conversion | Preserve the outgoing value and shared conversion | This removed 24 B in reward selection but did not close its whole-function match | [Unresolved reward selection](c-recovery-lessons/main/mission-reward-selection.md) |
| Loop-invariant mask constants are hoisted despite narrowing the snapshot/result | Diagnose the first divergent pass before another source form | Reward selection's `.loop` hoist survived both narrowing attempts; more casts have no supporting evidence | [Unresolved reward selection](c-recovery-lessons/main/mission-reward-selection.md) |
| Several scalar stat blocks have distinct field offsets, helper sequences and no original backward edge | Keep the original per-stat blocks, typed fields and site-specific snapshots/reloads; preserve where quotient/RNG results narrow | Do not replace them with a generic indexed loop or transfer one stat type to another field. The 514 B reduction and 628 B growth have different signedness/clamp rules | [Reduction](c-recovery-lessons/worker2/CoreRegion_00128C3C.md), [growth](c-recovery-lessons/worker2/CoreConsumer_000C9B8C.md) |
| Literal-zero arguments become a branch-known predicate register during first CSE | Use the existing unchanged-input pass evidence to close equivalent width/constant spellings before another candidate | This diagnoses the frozen 126/140 B obstruction; it is not an exact fix or permission for compiler-flag changes | [Measured first-CSE case](o2-throughput-ramp.md#compiler-stage-discriminator-completed-example-no-rerun) |

The timer, record-replacement and effect-28 rules establish observed source-to-
output effects. Their final allocation mechanisms were not all traced through
compiler passes. Do not label an inferred CSE/reload explanation as measured.
The [initializer](c-recovery-lessons/main/initializer.md) and
[queue](c-recovery-lessons/main/queue-acquisition.md) provide separate pass-traced
examples; they do not upgrade other lessons' evidence levels.

## Verified transfer: byte objects and opposite loop directions

Three additional complete methods reproduced their original spans on the first
source formulation under fixed O2: the156-byte mission fee commit and the two
104-byte inventory category scans,364 bytes total, now mechanically verified and
integrated. The common form is the observed byte field mutation, with its actual
wrapping and mutable-root reload sites. The fee method preserves its fifth stack
argument and delayed currency transaction; the scans preserve the entry snapshot,
count test and post-sound reload. These obligations remain method-specific.

The [forward scan](c-recovery-lessons/worker3/Source52_0008D554.md) increments
categories at most4 and wraps otherwise to0. The
[reverse scan](c-recovery-lessons/worker3/Source52_0008D5BC.md) decrements nonzero
categories and wraps zero to5. Reuse the physical record and helper interfaces,
then independently map the actual branch direction and updates. Preserve the
original all-empty behavior; do not invent a guard or generic modulo helper.

Claim-to-exact decisions were96.885,87.347 and35.347seconds respectively. Reverse
ASM preparation partly occurred during the forward method and is charged there;
35.347seconds is not a stand-alone family speedup. These are observed outputs,
not traced compiler passes. Transfer to an asynchronous object, a cached root or
a different narrowing/reload site remains unproved.

## First-candidate preparation

For a proven family, use the [compact transfer and closeout record](c-recovery-lessons/administrator/family-closeout.md). Reuse the physical layout and execution pipeline, then record each method's own guard, call order, reloads and native boundary. Keep local gate submission immediate and preserve complete method clocks; short paperwork is not permission to omit evidence.

For mission-operation controllers, consult the [bounded family result](c-recovery-lessons/administrator/mission-controller-source-forms.md).
Map discrete status groups, physical field widths versus promoted local values,
and pre-call captures versus post-call root reloads before writing. These are
three separate questions; a common context structure does not answer them.

For a related script cohort, reuse the verified descriptor/dispatcher and helper
contract once, then map each method's own decision, reloads and return/pool
boundary. The [eight-method script cohort](c-recovery-lessons/administrator/nested-script-family-preparation.md)
reached 762 locally exact bytes: three first recorded attempts were exact, and
five first C formulations matched after setup/alignment corrections. Those are
different measurements. Preserve the dispatcher's independent PC advance,
unsigned-guard/signed-index use chain and separate selected-padding ownership.

For a branch into a shared tail, record the exact target instruction and the
value definitions it executes before the store. Do not merge a target that
defines a result with the following store. In the frozen688-byte
[selection continuation](c-recovery-lessons/sol_b/CoreFrontier_0005D23C.md), four
branches enter `MOV r1,2` at0805D4D4; treating them as entering the following store
missed a shared state assignment. Whole-method mapping recovered that obligation
before the final exact result. This is a CFG-writing lesson, not permission to
infer semantics from a high scattered-byte score.

For residual definition-order or second-mask differences, consult the
[1,860-byte continuation lesson](c-recovery-lessons/administrator/field-definition-and-mask-lifetimes.md).
It distinguishes a verified field-address-before-zero change from a traced
promoted-halfword/regmove obstruction. Preserve mutation/reload boundaries and
the actual one-load output; neither rule justifies blanket casts or reordered
declarations.

Record one compact source map: ABI and call linkage; physical object sizes and
widths; CFG joins; snapshot versus reload obligations; evaluation order and
phase-specific lifetimes. For each transferred rule, name its original ASM
precondition and predicted emitted change. An applicable counterexample wins
over similarity of function names or fields.

Choose the recovered data representation and control-flow structure before
translating individual instructions. The 306-byte packed snapshot used six
logical fields of widths 10/10/11/11/11/11; its generated masks, cross-byte stores
and register reuse followed from that physical layout. The 188-byte scene scan
used the observed ordered rejection/continue chain and an early return, retaining
the original shared tail. Both matched on their first source formulation under
fixed O2. These are source-shape examples, not proof that packed structs or early
returns improve unrelated methods. Consult the complete frozen lessons and keep
helper ABI, aliasing and width obligations separate from a copied spelling.

Before editing an otherwise identical body to remove two trailing bytes, inspect
the existing ELF function extent and section alignment. In the packed snapshot,
306 original instruction bytes already matched inside a 308-byte section; only
the verified two-byte post-function alignment needed existing output metadata.
This does not authorize trimming a live epilogue, literal pool, original alignment
or an unexplained difference. Final full-span identity and provenance still gate
delivery; the extra metadata/build time stays in the method clock.

The implementer checks copied declarations and included interfaces as well as
new code. Inherited forced-register bindings, fabricated volatile accesses or
opaque instruction bodies do not become eligible merely because a whole span
matches. G41 redirect reached 200 exact bytes, but the independent peer recorded
inherited `r1`/`r8` bindings forbidden by that assignment; policy-clean acceptance
remains zero. This is an admission lesson, not a new administrator C review.
Keep declaration-only verified helper symbol linkage distinct from register
bindings or instruction-bearing ASM.

Reconcile every original call site's arguments and return width before tuning
the first instruction difference. One recent 620-byte draft spent three trials
on prologue order before its owner found a missing third helper argument. The
source-order gains did not make that draft valid. Repair a demonstrated contract
error before further allocation work; retain the failed costs and use the
[correctness-repair distinction](c-recovery-throughput.md#correctness-repairs-before-matching-trials)
rather than treating an exhausted spelling budget as a reason to preserve a
known wrong call.

Preserve size/offset assertions for physical layouts. A fitting binary is not a
reason to weaken them. Signedness must follow the original comparison, including
intermediate promotion and truncation, before interpreting allocation differences.

Use assertion syntax already accepted by the pinned old compiler. A host
preprocessor accepting a modern builtin does not make agbcc accept it: effect 91
lost its first compile to `__builtin_offsetof`. Retain the physical-layout guard
when repairing its syntax. Reuse the proven executor environment and adapter
invocation as well; a missing Unicorn environment is a setup failure, not a C
behavior result.

Reconcile the original full envelope with the selected production C prefix
before the first build. A shorter historical prefix is not the original method
boundary. If reclaiming a retained suffix is needed, use an isolated proposal
that validates the full partition and neighboring entries. Never silently expand
the selected production range or trim live original code to pass a size check.

## Reject redundant retries before compiling

Keep one row per hypothesis in the existing method record:
`original site | cause class | predicted instruction/dataflow change | binary hash | result | closed class`.
Reuse that row after context recovery; do not reconstruct a failed search from chat.
Check earlier hashes and the applicable counterexample before each next edit.

- A new binary is useful only if the predicted operation changed. More same-offset bytes alone do not validate the cause.
- When two source forms produce the same binary, close that specific equivalence class. A third spelling needs new original-site or compiler-pass evidence; a new variable name is insufficient.
- Check the complete binary hash before describing a generated-instruction change. Keep source corrections and machine-code changes distinct: an ABI declaration, layout assertion or clearer expression can be necessary while producing identical output. If an earlier narrative claimed an emitted improvement that its frozen hash disproves, append a measurement correction; preserve both rounds and do not rebuild merely to rewrite the explanation.
- After three unsuccessful effective source hypotheses, stop editing and reconcile the causes. Above 70% full-original-range matching permits at most three further supported trials (six total), not automatic retries. At least 95% matching or at most 16 unmatched original bytes requires the [whole-method plateau diagnosis](c-recovery-throughput.md#near-exact-plateau-whole-method-diagnosis-before-another-edit): reread all original ASM, candidate C and generated ASM, map every residual to its cause, then predict one change. Preserve length differences, failed classes and the original clock. Six unsuccessful trials require a frozen, explicitly assigned handoff; do not automatically change models or restart the budget.
- Preserve the distinction between unnecessary source-shape repetition and necessary ABI/layout repairs or a final naming identity check. The latter remain valid even when the binary is unchanged.
- Record the failed prediction immediately. Do not add a new report service, repeat a runtime bank for unchanged inputs, or reopen a frozen cause just because context was compacted.

## Two questions from the exact 188-byte snapshot controller

The frozen `RemainingCore48_000649A4` result reached 188/188 original bytes
under fixed O2 after a whole-method checkpoint. Use these as bounded questions,
not general source-order rules:

- Does the original materialize a pointer before loading its value as a call
  argument? At `080649A6..080649B4`, separate snapshot and options-pointer value
  definitions reproduce the address order while the options dereference remains
  argument four. Existing initial RTL already exposed the earlier wrong order;
  final output also restored the dependent literal-pool order. Naming the ROM
  word alone had failed. Do not move a mutable load across a helper or assume
  this fixes loop induction ordering.
- After a narrowing store, does the original reuse the computed narrow value or
  reload the field? At `08064A0C..08064A26`, the computed decremented `u16` supplies
  both index uses. Preserve wrapping, normalization and alias boundaries. An
  intervening helper or alias write can require the original reload instead.

The failed-best-to-checkpoint interval included diagnosis and recording; its
review-only duration was not isolated. One successful method does not establish
an overall speedup or a compiler-pass rule.

## One useful iteration

1. State the first differing operation and one source-backed cause. When the
   responsible pass is unknown, say so; use a bounded trace when it can distinguish
   competing causes, rather than requiring a new trace for every expression.
2. Make one cause-specific change and compile only the method. Compare complete
   output identity before execution. For complete exact output use the source-bound mechanical path; no new
   runtime bank is required solely to prove identical instructions. Nonexact
   semantic-delivery candidates retain relevant independent execution checks.
3. If equivalent spellings yield the same binary, close that hypothesis class.
   Preserve the failure and move to a distinct cause or the next owned ready
   method. Do not turn byte-score improvements into whole-function credit.
4. On success, update the owned lesson with the gate, failed transfer boundaries
   and next application. Publish the frozen packet and continue the owned queue;
   complete-exact packages receive mechanical provenance/range verification;
   nonexact packages retain independent semantic acceptance.

Read the [recent attempt patterns](o2-rewrite-attempt-patterns.md) for measured
successful transfers and failed classes. Separate a known visible instruction
cause from an unknown compiler-pass cause: do not make an RTL dump a mandatory
extra step when a small source-backed difference is already localized.

## Record time without hiding preparation or publication

Use explicit UTC boundaries for claim, each decision, local exact decision and
frozen packet publication. `decision_to_decision_seconds` is the difference from
the preceding decision, not elapsed time since claim. Preserve failed commands,
fixture fixes, recovery and inter-method gaps. Initial preparation and the time
after the latest decision remain visible separately and in gross throughput.

Effect 28 illustrates why both completion boundaries matter: local evidence was
ready after 1,389.735 s; its frozen package was published after 1,491.181 s. The
additional 101.446 s belongs to delivery. Do not sum concurrent actors' wall
times to obtain team elapsed time. Report local exact, independent acceptance
and integration separately, with original instruction/literal/alignment spans.

### Keep diagnostic output bounded

Persist full assembly, RTL and comparison reports in the owned output directory. Print the first divergent block and the relevant compiler-pass excerpt, together with complete-span match counts and report paths. Do not dump full allocation tables into the session. After context recovery, consume the saved decision and hashes before any repeated build. Context recovery is charged to the original method clock; output reduction has no claimed speed benefit until measured.

## Evidence-driven decision loop

Use [the REA-informed GBA workflow](rea-gba-workflow.md) for question/evidence/source-plan/discriminator/result/transfer. It includes measured task-feature cohorts and the current raw-provider limitation. Reuse the existing method map and ledger; no new mandatory report or engine setup.

## Large dispatchers: transfer layout and joins, not size assumptions

The frozen [1292-byte ability assignment controller](c-recovery-lessons/sol_b/CoreScene34_0007DDB8.md) matched its first source in 287.83 seconds gross. Its owner mapped both row loops, distinguished backward timer branches to shared exits, preserved separate signed timer tests/raw byte updates and original case-owned reloads before writing. This demonstrates one successful complete shape, not a rule that switches or large functions are easy. No compiler-pass attribution was measured.

The subsequent 3704-byte parent transfer closed without an exact result after
496.68 seconds. Physical slots, the child ABI and signed timers transferred;
the parent's complete control-flow shape did not. Its final source was 3724 B,
20 B over the original envelope. A successful child is evidence for its actual
interfaces and layouts, not permission to assume the parent has the same shape
or to omit the parent's complete CFG map. Preserve this failed transfer when
selecting another member of the family.

## Small residuals can still have global allocation consequences

A bounded104-byte item-policy closure reproduced its original lower-bound predicate with a4-byte mixed island but changed two surrounding value/register lifetimes:97/104 equal versus the preserved pure-C102/104. Its second formulation emitted identical bytes. The two-trial closure stopped with zero credit. This is a counterexample to assuming that a tiny local opcode difference can be locked without changing the rest of the method; compare full binary identity before claiming a local improvement, and close identical-output hypotheses immediately.
