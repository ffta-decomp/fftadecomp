# Worker strategy: reconstruct fixed-O2 GBA C from ASM

Read this page before the first candidate and after context recovery. During
later methods, reuse it and open only the row matching the current discrepancy.
It brings the useful source-writing rules next to the execution entry; do not
read the entire reference collection for every function. Current ownership,
original clocks, source history and cause budgets remain authoritative.

Start from the existing task/source contract, its frozen helper/type bindings and
one applicable lesson. Link those identities and record only method-specific
differences and unknowns; do not write a second ABI report or reread every helper
body. Confirm the new function's actual complete body/boundary and each unknown
use site. After the first local build, reuse its reference/generated disassembly
and diff rather than extracting unchanged originals again. This reuses existing
artifacts, not a new global index or an unverified decompiler pipeline.

Keep routine tool output small: select the current metrics, artifact paths,
errors and changed block windows instead of printing entire manifests, reports,
untracked-file inventories or an unchanged whole disassembly each round. Keep
the detailed evidence on disk. Read the complete original at qualification and
perform the required complete original/C/generated-ASM plateau reread; those
obligations are not replaced by a truncated diff. Reuse unchanged guidance and
contracts after loading them rather than repeatedly filling the context with
historical text.

## Optional first draft for a nontrivial CFG or stack

At a new owned method, the existing m2c `gba-gcc-c` target can supply block and
stack-layout hypotheses before hand drafting. See [the short recipe](m2c-gba-first-draft.md).
Use proven caller/type context and original ASM; inferred ABI/OUT widths remain
unverified. Fixed O2, whole-native gates and old cause budgets remain unchanged.
Skip the tool for tiny wrappers and reuse its output rather than generating it
every round. Measure complete source-to-local time and first-pass yield, not
just tool execution time.

## Keep these facts beside the current method

1. Pin the **complete** native entry/mode/span, including all returns, literals,
   jump tables and alignment. Never shorten a span or remove a live epilogue to
   make a candidate fit. A shifted comparison is not proof of a local defect.
2. Map arguments/returns and stack arguments from real callers; distinguish
   full pointers, low-byte results and signed/unsigned halfword values.
3. Map actual objects: size/stride, field widths, independently addressed OUT
   objects, and each pre-call snapshot versus post-call reload.
4. Map basic blocks, branch polarity, loop entry/test/update, shared tails and
   the live value entering every join. Recover operations, not a new algorithm.
5. Use the pinned normal **O2** method build. Write one source-backed prediction,
   compare full output, then update the existing round. No O1/O2 search. After a
   syntax or constraint error, use rule19 before another compiler attempt.
6. First mismatch in a **new class**: inspect the relevant rule below and one
   local/vendor case before another effective edit. Reuse an unchanged search.
   No supported new cause means stop; a reference does not reset the budget.
7. Submit a reached local gate immediately. Update the owned lesson before the
   next method: source feature, reference, failed transfer, actual result/time
   and applicability. Then continue an eligible dependency or consumer.

The [execution rules](c-recovery-throughput.md) own claims, gates, budgets and
measurement. This page is the source-writing strategy. Detailed provenance,
pass experiments and counterexamples remain in the linked references.

## Read the source type from its use, not one instruction

### 1. Storage, working value, call ABI and return width are separate

A signed byte loaded with `LDRSB` can become a 32-bit signed working value,
later be stored with `STRH`, and finally be passed as LOW8. One `s16` local for
all three roles can insert unwanted extensions. Conversely, a real wrapping
halfword update needs its observed truncation. Trace definition, extension,
arithmetic, store and call consumption separately.

An unused helper result is not permission to change its prototype. A caller
may preserve full R0, test only LOW8, normalize LOW16, or ignore it. A pointer
whose low byte is zero is still non-NULL. Do not invent guards, mask domains or
void/nonvoid changes merely to get a preferred epilogue. Check existing ABI
contracts and real call sites first.

Project examples include a 50-byte method whose signed working value removed
unwanted extensions, and a 36-byte LOW16 predicate. For the latter, the observed
`NEG; LSR31` corresponds to `(0u - (u32)(u16)value) >> 31`; its restricted
0..65535 domain matters. That is not a replacement for arbitrary full-word
nonzero tests. See the [operation lookup](o2-reconstruction-quick-reference.md).

### 2. Recover the physical record before choosing array syntax

Derive stride from actual index/address arithmetic and consumers. This agbcc
fork can round an ordinary structure to a four-byte boundary: a record believed
to be 70 bytes can become 72 without source-backed packing. A correct layout
must also give the right access widths; size alone is insufficient. Use the
existing target-compatible size/offset assertions for established fields.

Packed halfword fields can retain two underlying byte loads that explicit
byte-composition arithmetic loses when one part becomes dead. This is a measured
source/output observation, not a universal rule to mark records packed. Do not
create fake members/capacities or violate alignment/aliasing to shape addresses.
Check the actual preprocessed type and the original object.

### 3. OUT scalars and arrays are different stack objects

Six independently passed halfword addresses are not necessarily two arrays of
three. An aggregate changes object alignment, stack grouping, address escape and
which address stays live across a call. Reconstruct the actual objects and their
uses rather than trying declaration permutations first.

The project has a 292-byte whole-exact transfer where replacing two OUT arrays
with six scalars reduced local storage from 56 to 52 bytes and grew generated
code from 288 to the correct 292 bytes. A later 100-byte success additionally
needed the computed Y value retained for a later argument. Scalarization alone
was not enough. Local storage and register-save bytes must be counted separately:
in the latter case, 24 local + 8 saved became 20 local + 12 saved, still 32 total.

For real indexed/contiguous buffers, keep the actual array. When equal-sized
objects are truly independent, source order can affect their placement; an
upstream probe found that unequal-sized objects followed size rather than simple
declaration order. Treat that probe as a hypothesis, not a target-independent
stack-layout promise. See [stack cases and limits](vendor-matching-playbook.md).
Recover only source-backed object relationships and access bounds. Never add
unused locals, oversized arrays, out-of-bounds subobjects or dummy padding to
obtain a desired frame. Account separately for outgoing arguments and ABI
alignment as well as saved registers and local storage.

## Preserve the operation graph and the observed objects

### 4. A computed value is different from a reread of its stored truncation

If ASM computes Y, stores its low halfword, then passes the surviving working
value, do not replace that value with a new halfword load. The reverse also
matters: an original reread after a callback cannot be replaced by a pre-call
snapshot. Preserve each definition's width and lifetime, including possible
alias writes to OUT arguments and callback-visible objects.

Use the original sequence to decide which root, record pointer, count, phase,
delay or flag gets reloaded. Ordinary RAM, alias/callback-visible RAM and MMIO
are different contracts. Do not use blanket `volatile`, `restrict`, or invented
memory barriers to compensate for an unknown object relationship.

### 5. Preserve destructive arithmetic and narrowing points

When a multiply updates a component and a following shift consumes that update,
the two source assignments can matter even if an algebraic expression looks
equivalent. Preserve the actual unsigned wrapping/working width and saturation
order. A project 104-byte match closed by retaining successive multiply/shift
definitions; this does not prove every such spelling survives optimization.

Recover signed versus logical shifts, sign extensions, byte/halfword wrapping,
sentinels and overflow domains before changing expression form. Integer
promotions can make `~mask` different from a narrowed unsigned complement. Do
not introduce signed overflow or assume only tested table rows can occur.

### 6. Materialized predicates are not interchangeable with control edges

Direct branches to effects need not produce a Boolean temporary. If the original
instead constructs 0/1 and later tests or passes it, preserve that separate
value and its definition point. Rewriting an interval into a Boolean chain,
switch or ternary can change both operation topology and allocation.

Equivalent parentheses, casts and Boolean expressions may emit identical bytes.
Record that result and close that spelling class. A numeric-result inline helper
is a testable hypothesis only when the original shows that representation; it
is not a global anti-optimization wrapper. Never remove a side-effecting call
because its return value can be predicted on a narrow fixture.

### 7. Real objects and symbols preserve address structure

An integer-address macro can fold a base plus field offset during expansion.
A linker-bound object/table symbol can preserve a different address expression.
Use the actual RAM/ROM object and its physical fields when source evidence
establishes it; do not invent an opaque accessor or alias merely to hide folding.

Check each site independently: a read can use split base+offset while a write
uses the final constant address. Match the real association of base, index,
stride and trailing field. Signed Thumb loads use register-offset encodings
even for zero/constant fields; seeing `LDRSH`/`LDRSB` is not proof of an array.
An IWRAM execution address requires its actual ROM copy mapping, not subtraction
of a guessed base or a negative ROM offset.

## Reconstruct control flow before tuning allocation

### 8. Shared tails need exact incoming definitions

Record whether a branch targets a value definition, a store, a call or an
epilogue. Entering `result = 2` is not the same as entering the following store.
Do not merge arms merely because their last source statements look alike.

Original fallthrough, source case order, explicit empty cases, return location
and guard polarity can select different block layout or cross-jump survivors.
Per-case returns, a shared result and a forward label all have successful cases;
none is a universal preferred style. Duplicate source tails can be merged by
the compiler later. A visually unused saved register can be a consequence of
that earlier structure, not evidence for a dummy source variable.

### 9. Preserve the loop's induction value and continuation

Identify top/bottom tests, zero-iteration behavior, signedness, the increment or
decrement point, and the value used after exit. A wrapping U16 ordinal and a
full pointer induction variable are not interchangeable. A loop shared with a
matched-result path may keep different values live from a scan-only loop.

Structured loops carry optimization notes in this old compiler; goto loops can
change invariant motion and block layout. Earlier CSE/GCSE can still reuse values,
so goto is not a universal way to suppress hoisting. Inspect the first changed
operation and relevant `.loop` evidence when the source alone cannot decide.
Do not try every loop spelling or delete a real invariant to obtain a register.

### 10. Separate different phase lifetimes before pinning registers

One function-scope temporary can join values that the original treats as
different per-phase objects. Conversely, an original value live across calls
must not become several unrelated reloads. Derive definitions, uses, call
crossings and address escapes from the complete function, including remote
branches; the last few wrong bytes may originate far earlier.

EDS's four-byte sliding-grid case was solved with separate row lifetimes in two
other phases. Fixing only the visibly wrong phase and forcing registers failed.
Its original-base/iterator example solved a different lifetime requirement with
an initialized input-only constraint. Read failed forms and preconditions before
transferring either example. External success does not reopen a closed budget.

### 11. The first reload difference matters more than later register rotation

For a tiny register or cursor-order remainder, use the
[near-match decision card](register-allocation-near-match.md): input equivalence,
first pre-allocation difference, truthful constraints and mixed fallback.

Wrong registers can arise from different operations, overlapping lifetimes,
global allocation priority, local allocation, call clobbers or reload choices.
Do not call all of these scheduling. This compiler has no standalone instruction
scheduling pass in the audited pipeline. First ask whether the operation graph,
widths and CFG already differ; allocation tuning cannot repair those defects.

When existing output cannot distinguish the causes, use one unchanged-input
diagnostic dump. Follow the actual value across passes, not file modification
times or a whole dump hash. A missing reload early in the function can rotate
later scratch choices. Upstream allocation-priority formulas and regoracle
output are investigative aids, not a guarantee for our actual compiler binary.
Do not bootstrap its patched compiler or accept bytes from allocation overrides.

The pinned normal compiler's `global.c:allocno_compare` ranks live allocnos using
`floor_log2(weighted_refs) * weighted_refs / live_length * 10000 * allocno_size`,
converted to an integer priority; ties use the lower allocno number. `flow.c`
weights references using loop depth derived from loop notes. This explains why
real definition/use sites, cross-block lifetime and loop structure can matter
even when declarations look similar. It is not an invitation to add dummy uses,
nor a substitute for checking conflicts, local allocation and reload first.

### 12. Constraints must express an actual initialized value requirement

Fixed-register locals and empty ASM with truthful inputs/read-write operands
can express a concrete lifetime/allocation requirement. The C still has to
express all real logic; an empty output-only operand does not create a value.
A register binding alone is not a guarantee. Check frame, hard-register conflicts,
save/restore and every affected use, not only the improved byte offsets.

Keep C89 declaration rules and complete compiler provenance. Do not fabricate
dead values, claim an argument is initialized when it is not, or clobber a live
call/stack value. If real instructions are emitted, use mixed accounting and
the existing instruction-ratio rule; zero emitted instructions are a different
case. A full match never proves historical source authenticity by itself.

An empty template can also have a **nonzero estimated length** inside this
compiler, despite emitting no machine instruction. The pinned `gcc/final.c`
`asm_insn_count` starts at one; ASM length calculations multiply that count by
the default length. Adding such an annotation can therefore alter a remote
branch-shortening decision. Inspect the actual final branch displacement and
estimates before another constraint. Do not count estimated bytes as emitted
inline ASM, or conclude that zero inline instructions means no layout effect.

## Other source details that repeatedly decide a match

### 13. A descending ASM counter can be compiler-generated

Distinguish a physical cursor, a business ordinal and an induction counter used
only to terminate a fixed traversal. The source can traverse forward while O2
generates a countdown. A project 1080-byte method closed after recovering the
real forward traversal and definition order; merely spelling a descending
for/do loop differently had produced the same binary. Never reverse an ordinal
whose value is actually observed. Check initial RTL and `.loop` when this
distinction is unresolved.

### 14. Outgoing argument preparation has phases, not a C left-to-right rule

R0-R3 and later stack arguments must agree with the actual call convention;
incoming stack offsets include this function's real saved registers and local
frame. Internal/shared-frame entries may not be ordinary callable C functions.
Map them before inventing a prototype or splitting a function.

An eager temporary can move a later argument's calculation ahead of an earlier
stack store. One project 54-byte case required preserving the mode calculation
at its observed phase while retaining the earlier argument snapshots. **C does
not guarantee left-to-right evaluation of function arguments.** Do not encode
side-effect-dependent argument expressions or generalize a compiler observation
into a language guarantee. Use compatible prototypes and one source-backed
test of the actual preparation graph.

### 15. Preserve the actual container and fields that are left untouched

A bitfield read can use an underlying word container, a packed halfword view or
independent byte fields; the same physical object need not use one access view
at every site. Derive the container from loads, masks, shifts, stores and callers,
including preserved bits and truncation. Validate the target layout, not host
bitfield assumptions. Switch use of a field can generate a different extract
from an in-place comparison.

Do not replace several typed stores with a word clear, aggregate initializer or
`memset` unless the original writes those bytes with the same effects. A startup
record can deliberately leave reserved bytes or a later child pointer untouched.
Unwritten bytes are not permission to read an indeterminate C value: trace every
actual later consumer and the real defining helper first. A stack reservation
alone does not prove the identity or initialization of a guessed C object.

### 16. One hardware sample and two hardware reads are different effects

For proven MMIO, record the access width and number/order of volatile reads.
If the original samples once for two uses, capture that real sample; if it polls
or resamples, retain each read. This is deliberately different from the ordinary
RAM post-callback reload rule. DMA write/readback/wait sequences are effect
contracts; a vendor driver is a reference, not permission to migrate a driver
outside the active core scope.

### 17. Match constants and arithmetic interpretation before their pool slots

An 8-bit shifted constant, a small signed negative and a full literal have
different construction opportunities. The intermediate type can change whether
a complement is synthesized or loaded as a halfword constant. Trace the original
signedness, narrowing point and use; do not force every value into U16 merely
because it eventually reaches a halfword store.

Similarly, signed division truncates toward zero; an arithmetic right shift is
not an interchangeable replacement for negative inputs. Account for the native
bias/shift sequence if present. Equivalent mask/XOR spelling can canonicalize
identically; another identical binary closes that spelling class. Literal-pool
offsets often move because of an earlier operation or branch change.

### 18. Fix call linkage and placement before rewriting matching source

A real direct BL, an indirect callback through the existing interworking thunk,
a Thumb function pointer and an ARM entry have different contracts. Preserve the
callee, mode bit, arguments and caller-visible effects. Do not replace an opaque
helper with a stub, fabricate a return, or change a prototype just to change a
branch/epilogue. Resolve verified helper aliases and relocations through the
existing build path; a zero-instruction alias is not a recovered helper body.

Check entry placement, allocated sections, literal/table extent and native
alignment. A linker veneer is separate provenance/accounting, not game C bytes.
Never discard a section or crop live instructions because another comparator
ignores a trailing pad. Frozen source that already produces the expected bytes
needs the correct linkage/metadata, not another source formulation.

### 19. Read the pinned compiler manual after a syntax failure

After the first syntax, unsupported-extension or ASM-constraint diagnostic,
inspect the exact error and retained preprocessed `.i`, then read the applicable
manual section **before another compiler attempt**. Do not guess successive
spellings or assume that a modern GCC extension exists in this fork. If the
manual does not resolve the question, inspect the current front-end grammar or
constraint implementation and state what remains unknown.

The bundled language-extension reference is
`vendor/agbcc/gcc_arm/extend.texi`; verify fork-specific behavior against the
active Thumb sources under `vendor/agbcc/gcc/`. In particular, its
`c-parse.in` compound-statement grammar separates declarations from statements:
put block declarations before assignments and `asm`, or introduce a real nested
block when a later local is needed. Preserve the intended value lifetimes.

Record the diagnostic, manual section/source reference, supported repair and
outcome in the existing round. Retain and charge failed invocations. A syntax
repair remains within its original hypothesis; consulting a manual does not
reset a terminal budget, change fixed O2 or require rebuilding frozen results.

For a remaining entry-copy mismatch, distinguish parameter setup from local
assignments in the function body. A fixed-register local can delay the desired
copy; an initialized ordinary pointer with a read/write operand restored the
original two-copy order in the [602-byte name controller](c-recovery-lessons/worker3/CoreRegion_0012A5BC.md).
That is one measured transfer, not a universal constraint or alignment recipe.

## Use the compiler pipeline as a diagnostic map

The ordinary pipeline is host preprocessing, pinned normal agbcc O2, ARM7TDMI
assembly/linking at the original location, then extraction/full comparison.
Inspect the `.i` when a header/type is unexpected: the host preprocessor's
64-bit macros are not the target's 32-bit pointer/word ABI.
The active binary is normal agbcc, **not old_agbcc**. Many EDS examples and its
oracle use old_agbcc; matching version banners or O2 labels do not establish
identical binaries, passes or allocation. Transfer their hypotheses through our
normal pipeline rather than importing their compiler selection.

| First suspicious artifact | Look for | Do not infer |
| --- | --- | --- |
| `.i`, initial `.rtl` | Prototype/type/packing, constants, expression association | An identical source-looking header means identical preprocessed input |
| `.cse`, `.gcse` | Folded addresses, shared predicates, merged value definitions | Another cast/parenthesis is a new useful source cause |
| `.loop`, `.cse2` | Hoisted bases/masks, induction changes, loop-exit layout | Every loop spelling suppresses the same optimizations |
| `.flow`, `.combine` | Live ranges and width operations removed or combined | A later final difference was caused by combine without tracing the value |
| `.lreg`, `.greg`, reload | Conflicts, priorities, call crossings, first changed reload | Reordering all locals will repair a structural mismatch |
| `.jump2`, `.mach`, ELF | Cross-jumped tails, Thumb pools, branches, sections/placement | A literal offset or veneer is a C statement-order defect |

The [compiler guide](agbcc-o2-matching.md) contains the measured pipeline and
synthetic corpus. Diagnostic `-da` dumps retain the fixed profile; they are not
an alternative optimization search. Reuse existing dumps unless a new distinction
requires one diagnostic command.

## Turn a mismatch into one decision

Classify the first causal difference as boundary/ABI, object/width,
operation/CFG, lifetime/reload, or placement. Use the corresponding section
above, the [feature lookup](o2-reconstruction-quick-reference.md) and the
[vendor case table](vendor-matching-playbook.md). Search only that class, normally
well under the roughly two-minute initial lookup bound; reuse its result until
the discrepancy or input corpus changes.

Write the existing round entry as:

`original feature -> reference/preconditions -> one source cause -> predicted
instruction/frame/edge change -> actual full result and elapsed time`.

After three unsuccessful source causes, preserve the budget rules. A strictly
above70% full-range result permits at most three supported additional causes;
the near-exact checkpoint requires a complete original/C/generated-ASM reread
before another edit. At a terminal boundary freeze failures and the best version;
do not reset clocks or return under another method name. A smaller residual,
matching prefix or fit alone creates no exact credit.

On whole exact, submit provenance immediately, then update the owned lesson
and continue. State `observed_output`, `pass_traced` or `hypothesis`; distinguish
upstream reports from a demonstrated project transfer. Keep failed transfers
as counterexamples. Prefer complete dependency-ready consumers in the active
game group. Preserve confirmed SDK/compiler-runtime/driver exclusions even when
called by battle code; expose their real interfaces without rewriting bodies.
Other complex engine implementations follow explicitly authorized scope, not
automatic migration because a caller reaches them.

## Evidence and deeper references

### Keep closeout small without losing the gates

The ledger and one frozen evidence package are authoritative. Preserve one
required round per actual decision, immediate local submission, independent
verification and integration as separate gates. Do not add a `progress` event
solely to repeat the adjacent round/gate/finish, or reproduce the same full
hash/ABI/result table in several summaries, queues and chat messages.

A same-family method lesson can be compact: identity/gate and frozen evidence
reference; original feature; actual change; reused case and method-specific
delta; failed form/countercondition; elapsed/attempts. Reference immutable reports
for detailed hashes/counts rather than manually copying them again. A new cause
needs its explanation, not an arbitrary page quota. New blockers and changes to
ownership or evidence still require their real records. Never postpone a local
gate until the lesson, an hourly summary or a batch is complete.
An unchanged-family entry normally needs six to ten concise lines and its
evidence reference, not a new multi-page case study.

Ledger round-to-credit delay measures only the interval after the round was
written. It does not measure comparison-finish-to-round analysis or all reporting
effort. Keep that earlier interval unknown unless a real tool completion receipt
timestamps it. Do not claim that fast SQLite writes prove closeout is free, or
that every gap between methods is idle or narrative work.

- [O2 compiler and probe guide](agbcc-o2-matching.md): pinned pipeline,
  source-output corpus, target layout, Thumb addressing and diagnostic limits.
- [Feature-to-source lookup](o2-reconstruction-quick-reference.md) and
  [attempt synthesis](o2-rewrite-attempt-patterns.md): successful project examples
  beside failed/identical forms; historical O1 results are explicitly separate.
- [Vendor matching playbook](vendor-matching-playbook.md): pinned EDS, Klonoa,
  pokeemerald, m2c and compiler-source references, with retrieval/transfer limits.
- [Owned lesson protocol](c-recovery-lessons.md): original/generated spans,
  gate/provenance, failed causes, lookup/iteration/full elapsed cost and next
  application. A source-writing tip is not recovered-byte credit or a measured
  throughput improvement until the actual complete method and clocks show it.

### Traceable historical and upstream basis

The historical project synthesis inspected 15 lesson snapshots committed during
2026-10-23 in Shanghai time. Their underlying experiments can be older; the
commit date is not the experiment date. Today's OUT/phase transfers are recorded
separately. Useful source-feature entries include generated countdowns,
post-helper coordinate copies, branch-only versus numeric predicates, physical
case layout, mixed-width address views and outgoing-argument phases. Consult the
named lesson through the feature lookup instead of loading the historical corpus.

Compiler-source checks use pret/agbcc
`da598c1d918402c42c0c0d7128ba14567f3175e9`: `gcc/thumb.h` for target layout,
`gcc/flow.c` and `gcc/global.c` for loop weighting/allocation,
`gcc/reload1.c` for spill selection, `gcc/jump.c` for cross-jumping, and
[`gcc/final.c`](https://github.com/pret/agbcc/blob/da598c1d918402c42c0c0d7128ba14567f3175e9/gcc/final.c#L1063-L1080)
for ASM length estimation. Source confirms a possible mechanism; only tracing
the actual target value establishes the cause of a particular mismatch.

Read upstream source alongside prose. At EDS revision
`857002acd7a2e3ce98afb2992fe9761144308c9a`, one catalog description calls a
0x14-byte stack example a genuine object, but its source explicitly marks an
unused object as `FAKEMATCH`. The original reservation proves its size, not that
the guessed C object is authentic. Do not transfer that unused-object padding.
Likewise, contradictory upstream claims that barriers are always or never
removable are not adopted. Truthful constraints remain permitted by this
project's policy; unsupported source fabrication does not become a rule.

These rules synthesize existing project observations and attributed upstream
research. They do not change the normal toolchain, safety of C operations,
original acceptance envelope or ownership rules.
