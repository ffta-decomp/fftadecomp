> Public toolkit edition. Local assignments, evidence and game implementations are not distributed. See [the contributor guide](../CONTRIBUTING.md).

# Reusable C recovery lessons

Every successful method rewrite must update its reusable lesson before the
implementer takes the next method. This is part of the measured delivery cycle,
not a separate review queue. A successful semantic rewrite, a locally exact
candidate, independent acceptance and production integration are distinct gates.
Record the actual gate; never upgrade it from a passing build alone.
Submit the reached local gate before writing the lesson. Lesson completion is
required before the next method, but must never hide a completed function until
an hourly report. Record its elapsed cost on the same method clock.

Main owns `docs/c-recovery-lessons/main/`; worker2 owns
`docs/c-recovery-lessons/worker2/`; worker3 owns
`docs/c-recovery-lessons/worker3/`. Each writes one English Markdown record per
method and updates that record when a later gate is reached. The administrator
maintains this index and transferable compiler rules without reviewing game C.
Keep private paths and extracted game content out of these records; retain
hash-bound detailed receipts in the existing external evidence directory.

Start with the [O2 operation-to-source lookup](o2-reconstruction-quick-reference.md),
then consult [the source-style study](matched-c-source-style.md) for
verified examples and historical-profile limits before applying a lesson.
The [recent attempt synthesis](o2-rewrite-attempt-patterns.md) pairs successful
object/lifetime transfers with failed expression and loop hypotheses.
Prioritize its current O2 corpus. Label historical O1 observations explicitly;
do not use them as proof of current O2 instruction selection or allocation.

Each record contains:

- The stable task/module identity and descriptive function name, with the
  evidence-based naming outcome and unresolved interpretations from the
  [naming closeout](c-recovery-naming.md). Keep the existing lesson filename.

- Method, original envelope, instruction/literal/alignment counts and acceptance
  gate; source/header/compiler/binary hashes or stable evidence identifiers.
- Original ASM feature and the source representation that reproduced it.
- The first compiler pass where the change mattered and the observed result.
  Separate a verified mechanism from an inference.
- Before/after generated size, whole-function equality, relevant case outcomes,
  failed hypotheses and unchanged-binary reuse.
- Full elapsed time and candidate attempts. Record measured time/iteration
  savings only against comparable work; otherwise savings remain unknown.
- Preconditions, counterexamples and one concrete next application. A rule from
  one method is provisional until transferred successfully to another method.
- Evidence level: `observed_output`, `pass_traced`, or `hypothesis`. Record
  local-decision and frozen-publication timestamps separately; do not label
  cumulative method time as a decision interval. Later acceptance receipts
  supplement frozen history instead of silently rewriting its earlier gate.

Before a new method, consult matching lessons by ASM feature, not just function
name. Record which rule is applicable or why none applies. After applying a rule,
record transfer success or failure and time to decision. A failed transfer narrows
the rule; it does not justify blind permutations. Reuse an unchanged lesson at
later acceptance gates rather than writing duplicate success records.

## Evidence index

Gate reconciliation below is dated 2026-10-22. The external peer receipts are
authoritative; a queue label alone cannot establish independent acceptance.

| Lesson | Observed gate | Transfer status |
| --- | --- | --- |
| [Conditional field-address lifetimes](c-recovery-lessons/main/queue-acquisition.md) | 112-byte exact; independently accepted, integration pending | Pass-traced; cross-method time saving unproved |
| [Fullword zero and mutable ordinal](c-recovery-lessons/main/initializer.md) | 56-byte exact O2; independently accepted, integration pending | Pass-traced; requires matching value modes and def-use |
| [Timer transitions](c-recovery-lessons/main/mission-queue-timers.md) | 370-byte local exact; peer pending | Packed status and separate scan/output roles; final timer mechanism inferred |
| [Record replacement](c-recovery-lessons/main/mission-record-replacement.md) | 260-byte local exact; peer pending | Observed output; raw-mask counterexample narrows packed-field transfer |
| [Effect 28 flags update](c-recovery-lessons/worker2/EffectCallback_001322B0.md) | 138-byte local exact; independent receipt recorded at 03:39 UTC, integration pending | Observed output; ordinary-RAM RMW at one proven site only |
| [Effect 43 thresholds](c-recovery-lessons/worker2/EffectCallback_001326AC.md) | 552-byte local exact; peer pending | Separate real computation lifetimes; declaration order alone failed |
| [Unit value classification](c-recovery-lessons/main/unit-value-classification.md) | 222-byte local exact; peer pending | Pass-traced operand sign extensions and shared result blocks |
| [Descriptor root](c-recovery-lessons/main/effect-descriptor-root.md) | 228-byte local exact; peer pending | Pass-traced CSE address fold; typed tail restores the final index form |
| [Effect 92 selection](c-recovery-lessons/main/effect-pool-selection.md) | 152-byte local exact; peer pending | Successful object/field transfer in two candidate compilations; internal pass not claimed |
| [Effect 91 pool reference](c-recovery-lessons/main/effect-pool-reference.md) | 152/154-byte bounded candidate; zero whole-exact credit | `.loop` induction rewrite diagnosed; continuation extraction overflowed |
| [Reward selection](c-recovery-lessons/main/mission-reward-selection.md) | Fitting bounded candidate, zero whole-exact credit | Failed narrowing transfer; `.loop` hoist traced; not a success template |
| [G41 redirect](c-recovery-lessons/worker2/BattleStateDependency_000A4274.md) | 200 machine-exact bytes; policy-clean acceptance blocked | Peer found inherited forced-register bindings; exclude from unconstrained C success corpus |

Queue/initializer acceptance comes from the frozen `peer-checks-main-frozen.json`
receipt in the O2 worker pool. Redirect's policy disposition comes from main's
`redirect-g41-review.json`. Earlier owner lessons retain their historical gates.
Effect 28's later independent gate comes from main's `effect28-acceptance.json`,
not the earlier worker receipt for queue/initializer. Ledger registration may
lag those frozen receipts; preserve actual occurrence times when backfilling.

The matching objective remains newly independently accepted whole-function exact
C bytes/hour. Lesson count, trial count and scattered equal bytes are not output.
