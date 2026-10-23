> Public toolkit edition. Local assignments, evidence and game implementations are not distributed. See [the contributor guide](../CONTRIBUTING.md).

# ASM-to-C migration and local verification

The active workstream is systematic migration of selected source ASM to readable
C. Remaining original-byte dependencies are a separate backlog. Preserve exact
ASM for unresolved boundaries. Preserve observed compiler structure in the first
readable C implementation, and measure semantic acceptance and whole-function
exact matching separately. Game priorities remain in
[the system plan](game-recovery-priorities.md); active preparation, iteration,
handoff and delivery measurement follow [the execution rules](c-recovery-throughput.md).

## What currently slows migration

The repository has 174 `probe_*.c` files and 63 `check_*.py` files at baseline
`34c5a94`. Many contain their own setup and comparison logic. Repeating that
work increases review cost and allows width, literal, helper and observation
contracts to drift. Existing full-ROM builds already cache modules, but the
entry point still walks the selected manifest and resource dependencies. Local
iteration should reuse its compiler rather than run that whole path.

The supported responsibility index also covers less than the full ASM inventory.
Rebuildable instructions do not automatically provide a C signature or game
semantics. Recent review corrections involved a low-byte test mistaken for a
single-bit test, decimal/hex offsets, a clear-function pointer mistaken for copy
data, and an incidental return-address register mistaken for a meaningful return.
These must become task-contract checks rather than be rediscovered after coding.

## Two classification axes

Separate source-backed game-policy/content/engine ownership from compiler and
contract readiness. Names, addresses, API affinity and table membership are
shortlisting hints. Establish the actual state/data owner or necessary core
consumer for the claimed method; do not classify the whole project first.

Reuse existing hash-bound inventories, current selected modules, ledger history
and exclusions before source qualification. A full inventory rebuild is not a
per-method prerequisite. The old selected-ASM counts and zero-C snapshot were
historical measurements, not current status; use the runtime ledger and current
source-bound progress data for current totals.

A source-contract-ready method is eligible without an existing successful lesson.
An applicable frozen compiler/source family raises priority. Fixtures are needed
for nonexact semantic acceptance, not to begin exact-directed reconstruction or
to duplicate full native proof. Complete shared-frame/indirect-call contracts
remain the implementation owner's responsibility, with uncertainty explicit.

## Diagnose structural differences before chasing exact bytes

Do not reshape game logic solely to satisfy a tooling limitation. First separate
business-contract uncertainty from compiler output, placement and comparison
artifacts. Preserve the current accepted candidate while investigating one
measured cause outside the shared source tree.

| Suspected cause | First local evidence | Bounded response |
| --- | --- | --- |
| Indexed ASM dispatch became an if/goto chain | Original dispatch/table, C selection shape, generated ASM | Test a switch preserving all arms, shared tails and one-dispatch behavior; do not assume smaller output |
| Allocated sections rejected or omitted | ELF sections, compiler labels and incoming references | Fix the narrow verified tool limitation; never disable section checks or silently discard data |
| Repeated RAM access or poor allocation | Per-field load/store order, alias/callback effects, volatile qualifiers | Define partial proven layouts and snapshot/reload contracts; no blanket volatile removal |
| Ordinary fields made volatile during rewriting | Compare access-qualified variants with the same source, flags and header dependencies | Recover access semantics first; unknown field meaning does not justify blanket volatile, and MMIO/required reloads stay explicit |
| Wrong or uncertain helper interface | Caller/callee register and memory evidence | Resolve widths, argument count, OUT capacity and effects before matching experiments |
| Relocated code compares against unrelated bytes | Original-entry mapping, generated placement and veneers | Compare corresponding function structure separately; relocation-normalized similarity is not exact matching |
| Existing fixtures pass but natural input bounds are unknown | Producer evidence and adversarial input domain | Keep the limitation explicit; do not reinterpret fixture success as unrestricted equivalence |

A controller experiment found that a compiler-emitted, unused four-byte switch
pointer caused a linear dispatch workaround. Restoring a switch increased the
unlinked text size from 9,880 to 10,452 bytes but increased same-offset matches
from 339 to 961 over the same 13,080-byte reference envelope. Three controlled
cases passed. This demonstrates a structural/tooling opportunity, not complete
behavioral equivalence, a speed benchmark, or a generally superior optimization
level. See the opt-in `tools/compiler_data_policy.md` (implementation-checkout reference).

### Write C from the observed structure

Prepare an access and control-flow map before choosing C expressions. A readable
implementation can still lose the original structure through premature factoring,
implicit integer promotions or incorrect aggregate layout. Use the fixed O2
profile and distinguish established rules from individual matching hypotheses.

| Original evidence | C writing guidance | Required check |
| --- | --- | --- |
| Indexed records use a fixed stride | Describe the proven fields and preserve unknown bytes; use packing only where the observed layout requires it | Assert aggregate size and relevant field offsets; inspect the generated address calculation |
| Byte/halfword loads, extensions and truncations | Preserve signedness and the point of narrowing, including arithmetic before a comparison or helper call | Inspect load/extension instructions and test width/sign boundaries |
| A value survives a helper, or memory is loaded again afterward | Use an explicit snapshot for the former and a fresh field access for the latter | Exercise helper mutation and alias-visible writes; do not add blanket volatile |
| Similar arms reach different copy, eviction or failure continuations | Keep those arms distinct until the actual common tail | Check each incoming guard and effect before factoring shared C |
| A comparison produces a numeric 0/1 before a later branch | Record the predicate as an expression-level result; test a named predicate or inline helper only as a bounded source hypothesis | Verify whether the compiler preserves that result; do not force it with volatile, padding or assembly |
| Ordinal and byte offset advance separately | Preserve both meanings in the initial draft | Check induction and lifetime output; an explicit pointer may cause strength reduction instead |
| Packed fields use different extraction sequences | Choose each field representation independently from its loads and masks | A successful bitfield example does not justify converting every mask into a bitfield |

For a concrete layout failure, an inferred 70-byte mission definition acquired a
72-byte stride under the pinned compiler. Packing with a size assertion corrected
eight failing cases. This is verified layout guidance. In contrast, the mission
selection range test materializes a boolean in retail while the initial candidate
branches directly. A pure inline predicate with explicit numeric returns restored
that boundary at both sites under fixed O2; all 13 relevant cases passed. Output
grew from 560 to 576 bytes within the 596-byte envelope, while same-offset equal
bytes changed from 75 to 74. The result supports this local source formulation,
not whole-function matching or a general rule about original inline helpers.

Predict the instruction-level change before each edit. Check the corresponding
block, not just the first unequal absolute byte: earlier size changes shift later
code. Separate opcode, register, branch topology and literal-address differences.
Retain a behavior-checked candidate that restores an observed structural feature
even when scattered same-offset equality decreases. Keep the best byte-comparison
baseline separately. Later matching work may depend on the restored feature;
greedily keeping only the largest scattered count can discard useful progress.
Do not reorder declarations or rename temporaries without an identified compiler
cause. If the binary is unchanged, reuse its exact evidence and reject that cause.
If a local change improves the intended structure, validate the complete affected
method before treating it as a reusable rule. Whole-function equality remains the
exact-match gate.

### Repeatable experiment and acceptance sequence

1. Freeze reference revision, source AND included-header hashes, manifest,
   toolchain, original span and generated entry mapping; pin a bank where semantic
   acceptance requires it.
   Keep active work untouched; stale snapshots are experiments, not replacements.
2. Extract calls, branches, table entries, literals, ELF sections and relocations
   mechanically. Classify the suspected difference before changing C. Preserve
   shared frames, default-tail effects, nonreturning states and repeated reads.
3. Change one cause at a time: dispatch expression, one proven field/interface,
   or a narrowly reviewed compiler policy. Start with one representative module
   using the fixed O2 candidate configuration. Do not try other optimization
   levels or a flag matrix.
4. Compare generated span, actual source/section changes, original-entry-aligned
   instructions, stack layout, and byte differences. Separate shorter output,
   structural similarity, exact bytes and behavioral evidence. Do not accept a
   match increase that changes reads, effects, ABI or supported inputs.
5. Complete source-bound native exact uses independent mechanical full-range
   verification. For nonexact semantic acceptance, reuse independent custom
   oracles and execute meaningful branches/dependencies after binary changes.
   Unchanged evidence requires matching relevant hashes; spot checks do not
   close an entire controller.
6. Promote a reusable rule only after its positive and negative cases pass. For
   tooling, share local/full-build behavior and validate cache audit/invalidation.
   Reapply the proven transformation to the latest implementation, then run the
   relevant semantic bank when required, then join a coherent integration batch.
   Do not overwrite newer fixes or require a full build per method.

Record baseline/candidate hashes, hypothesis, sole change, compile/verification
cost, generated and matching bytes, case-domain coverage, retained suffixes,
failed hypotheses and decision. Failed experiments are useful reusable evidence;
keep them off the selected manifest and out of recovery counts.

### Jev-assisted mismatch triage

Use `tools/jev_analyze.md` (implementation-checkout reference) to rank finite hypotheses across **selected
active-family** excerpts, not to rediscover exact addresses or rewrite code.
The reusable questions are in
`tools/jev_migration_questions.json` (implementation-checkout reference).

For each record provide bounded original ASM, current C, generated ASM, and a
machine-generated summary of sections/calls/differences. Include enough control
flow to cover the relevant join; missing context must yield `unknown`. Keep
record files, source excerpts, model outputs and private evidence outside Git.

```sh
python3 tools/jev_analyze.py --records "$PRIVATE_RECORDS" \
  --questions tools/jev_migration_questions.json \
  --output "$PRIVATE_OUTPUT/triage.jsonl" --dry-run
# Review the bounded inputs, then remove --dry-run to submit them.
```

The first pass ranks dispatch shape, memory qualifiers/layout, interface/domain,
placement, compiler configuration, or unknown. Group the results by likely
shared cause and work unlocked. For a shortlisted group, a second Jev pass may
rank explicit counterhypotheses or select a missing test obligation from a new
question file. Do not supply the first answer as a fact. Keep the same frozen
source hashes; changed questions must invalidate the cached decision. Agreement
between two calls to the same model is correlated screening, not independent
validation. Disagreement or uncertain context goes to review, not a tie-breaking
majority vote.

Scripts establish exact structure and hashes; Jev reduces hypothesis-reading
cost. The owning implementer resolves contracts and chooses/applies the source
experiment; a different actor supplies required independent acceptance. Main
alone publishes production integration. Jev must not authorize removal of volatile accesses or sections, infer
ABI/buffer bounds as fact, drop failing oracles, declare semantic equivalence,
or change progress counts. Screen only when it can reduce measured work; skip
model calls for facts already established by local tools.

## Minimal reusable pipeline

1. The claiming implementer establishes the family contract: exact envelopes, callable entries, normal
   versus internal ABI, widths/overflow, writable fields, direct/indirect helper
   interfaces, branch obligations and explicit unknowns. Pool words and global
   constants come from checked data, not hand-transcribed hexadecimal strings.
2. The implementation owner writes independent C using observed-role names and necessary comments.
   Numeric field names remain neutral where meaning is unknown. Keep existing
   external calls stable; do not recursively rewrite engine dependencies.
3. Run [module-only compilation](local-module-migration.md). It reuses the pinned
   compiler/linker, checks entry placement and reports code size, exact byte
   differences and timings. Oversized output is a failed placement trial, not
   permission to overwrite adjacent modules. Shorter output leaves an explicit
   retail tail; it does not recover that tail automatically.
4. Run the shared bounded CPU case bank with a pinned dependency environment:

   ```sh
   uv run --no-project --with unicorn==2.1.4 python tools/run_module_cases.py \
     --retail "$RETAIL_ROM" --build-report "$LOCAL_BUILD_REPORT" \
     --cases "$CASE_BANK" --output "$PAIRED_REPORT"
   ```

   Compare meaningful returns, callee-saved registers/SP, declared RAM and helper
   call arguments/order. Require independent oracle values where available.
   Execution outside declared contracts, undeclared writes, faults and bounded
   step exhaustion fail. A helper stub is explicit controlled evidence. Budget
   long loops from their proven input size, and permit the candidate's entire
   fixed module envelope rather than freezing old instruction/literal positions.
5. Integrate a coherent family through `tools/build_rom.py` once local checks
   pass. Preserve entry addresses, record differences and retained ASM/tails,
   update status/progress and perform only relevant replay. CPU-local tests are
   not a substitute for selected-ROM integration or natural/hardware validation.

## Task packets and capacity

Battle/action/turn, missions/story, jobs/abilities, items/equipment and save-image
transactions lead. Menus/input/map support follows core dependencies; renderer,
audio, generic scheduling, compiler/runtime and transport interiors stay later.
Scene/effect descriptor families are useful migration groups after per-handler
contracts; table membership alone does not establish the handler ABI.

Each claimed method has one owner, a source/manifest baseline, complete native
boundaries, typed dependency interfaces, existing local commands and explicit
acceptance/stop conditions. A new case bank is required for nonexact semantic
acceptance, not for complete source-bound native exact proof. Keep one active
implementation claim per actor; actors self-select disjoint successors. Complex
shared frames and indirect-call inference stay with the owning implementer. Within the active core family, bounded
exact-match work follows the execution rules and preserves semantic gates.
Broad renaming and residual-resource cleanup must not displace core delivery.

Measure accepted migrated functions/spans, local compile and execution latency,
the number of necessary full builds, and reasons for rework. Test tool changes
with deliberate bad returns, bad memory writes, ABI clobbering, bad revisions,
overlaps, timeouts and stale contracts. No “pass” may silently ignore these.

## Pinned O2 compiler behavior

Use [the measured agbcc O2 guide](agbcc-o2-matching.md) to distinguish initial
RTL expansion, CSE, loop transformation, combine, allocation/reload and final
jump/literal placement. The linked synthetic corpus demonstrates specific
source-shape effects; it does not establish original-ROM compiler provenance
or count as matched game C.
