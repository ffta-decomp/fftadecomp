> Public toolkit edition. Local assignments, evidence and game implementations are not distributed. See [the contributor guide](../CONTRIBUTING.md).

# REA-informed GBA matching workflow

The methodology reference is the MIT-licensed [hitsmaxft/rea fork](https://github.com/hitsmaxft/rea),
initially checked out at `3d472bde23b70f9aa7bcf0d28a0cd10e469545e9`
under [vendor/rea](https://github.com/hitsmaxft/rea/tree/baddb76f09da3c10b0057e489473232da6f285c8). Its local
[GBA reconstruction chapter](https://github.com/hitsmaxft/rea/blob/baddb76f09da3c10b0057e489473232da6f285c8/docs/gba-reconstruction.md) applies
REA's question-driven, evidence-reusing workflow to this project's ARM7TDMI work.
The dependency is for analysis guidance, not the ROM build or a new runtime.
No REA engine/provider execution has been validated here. Its current generic
ARMv7 raw profile is not a verified GBA Thumb/ARMv4T decoder.

## The worker's short decision loop

Read this once at the next method boundary. Reuse the existing method map,
ledger and artifacts; do not create a parallel reporting system.

1. **Question:** state the complete method's decision or transaction and the
   exact unknown that prevents writing its original structure.
2. **Evidence:** read the pinned original method, necessary caller/helper ABI,
   physical objects and shared exits. Reuse existing source-hash-bound results.
   Expand only the unresolved dependency, not the entire call graph.
3. **Source plan:** map definitions, calls, reloads, branch joins and live values.
   A backward branch requires checking the actual cycle/exit graph; it may
   instead reach an earlier shared tail. For a loop, record initial value,
   test, update order, retained exit value and ordinal versus cursor use.
4. **Discriminator:** write one sentence in the existing round record:
   `observed difference -> cause -> predicted emitted change -> rejecting result`.
   Resolve entry/schema/linkage errors before interpreting them as source failure.
5. **Local result:** fixed O2, method-only build, full original envelope. Reuse
   identical binary checks. Examine compiler passes only for an unresolved
   transformation; stop equivalent spelling retries.
6. **Transfer:** after exact success, record one source-shape lesson and its
   counterexample/limits. Name a ready same-contract successor where one exists;
   related addresses or API names alone do not establish a reusable family.

At the near-exact plateau, use the existing whole-method diagnosis and trial
budget. A small proven mixed island follows the explicit mixed policy; it does
not become pure C. Pure-C-only selection tooling does not validate mixed input.
Use the established mixed provenance/range route and retain any unsupported
validator result. Credit only after the applicable checks, never before them.

## Observed fast-task features

A metadata-only cohort taken on 2026-10-22 covers 199 methods first claimed
from 12:00 UTC: 195 closed and four still open. It joins the existing ledger to
hash-verified original ASM; it does not inspect candidate C. First claim to
first nonrevoked local exact gate includes preparation, retries and gaps.
Failed methods end at their final finish; open attempts remain censored.

| Original span | Closed methods | Local exact | Exact success | Matched B / summed actor-hour, including failures |
| --- | ---: | ---: | ---: | ---: |
| At most128 B | 50 | 40 | 80.0% | 1,730 |
| 129–512 B | 113 | 55 | 48.7% | 2,065 |
| 513–1024 B | 21 | 4 | 19.0% | 1,232 |
| Above1024 B | 11 | 2 | 18.2% | 1,278 |

Small functions finish reliably, but the middle group delivered more bytes per
summed actor-hour. Do not turn the table into a tiny-function quota, exclude
large core dependencies, or mistake summed actor-hours for team wall time.

Within the129–512 B group, methods without an explicit backward branch were
exact in37/61 closed attempts (60.7%), versus18/52 (34.6%) with one. Median
closed time was129 versus211seconds. This is a static branch-direction proxy,
not a proven loop classifier. Across the cohort, methods using high registers
were exact in13/67 attempts versus88/128 without them; size, actor and task
selection remain confounders. These features trigger better preparation, not
permission to skip difficult core code.

The next writing improvement is therefore specific: map cyclic/shared-exit
control flow and values live across calls **before the first candidate** for
these methods. Prefer known physical layouts and proven source forms within
an already-prioritized core chain. A large dispatcher with repeated independent
arms may be easier than a smaller coupled loop; inspect the actual structure.

Methods with a recorded compile/setup failure had a371-second median closed
cycle, versus143seconds without one. This association does not measure the
causal cost of setup: method difficulty differs. It justifies reusing a working
candidate schema, existing symbol-only helper bindings and the correct pure-C
or mixed validation route, rather than copying an incompatible old runner.

## Bounded adoption and hourly feedback

Mark the next method's existing source map or round summary `rea-gba-79`.
At the next hourly check compare original-span and backward-branch strata:
first-pass exact success, full method time, setup failures, and original matched
bytes per summed actor-hour plus the existing team wall-hour delivery metric.
Retain failures, open methods and actual models. Same-family transfer remains
an unmeasured hypothesis until the owner records a concrete transfer outcome.
Change the guide when a transfer succeeds or a counterexample invalidates it;
do not claim a speedup from publishing this document or importing REA.
