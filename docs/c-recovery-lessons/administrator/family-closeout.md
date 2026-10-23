> Public toolkit edition. Local assignments, evidence and game implementations are not distributed. See [the contributor guide](../../../CONTRIBUTING.md).

# Keep family reuse and per-method closeout small

A successful family transfer preserves each method's original operations while
reusing established physical layouts, helper contracts and validation commands.
It does not copy a sibling's constants, guards, call count or alignment.

## Measured delivery cost

Six first-source fixed-O2 methods were observed on 2026-10-22. The intervals
below include ledger, provenance, naming, lesson and handoff work where it fell
between these timestamps; they are not compiler timings.

| Original method | Original bytes | Claim to finish (s) | Exact decision to local credit (s) | Exact decision to finish (s) |
| --- | ---: | ---: | ---: | ---: |
| 1329B8 | 50 | 175.045 | 10.928 | 65.054 |
| 132C14 | 34 | 116.521 | 13.072 | 47.180 |
| 132C94 | 34 | 95.263 | 9.592 | 42.914 |
| 133394 | 34 | 31.480 | 0.291 | 0.678 |
| 1333B8 | 34 | 17.347 | 0.286 | 0.658 |
| 132520 | 42 | 59.178 | 0.986 | 19.823 |

The first three spent 155.147 of 386.830 seconds after the recorded exact
decision. Their measured strict-preflight commands total 2.228 seconds. Remaining
time is not fully attributed: do not call it all paperwork or claim it can all
be eliminated. The next two used a composed build/preflight before recording the
decision; their 5.636 seconds of combined pipeline work remains in the total
clock. Different methods and prior preparation prevent a causal actor/model
comparison. Savings from the recommendations below remain unmeasured.

## Reuse execution, preserve the checks

Use the existing `tools/build_function.py` composed method pipeline when its
inputs cover the task. Inspect its comparison and strict native result before
submitting credit. Reuse valid dependency-bound evidence; a summary or an
unchanged function name is not a cache key. Do not run another compiler or bank
merely to obtain a different report layout.

Prepare meaningful names and method-specific lesson fields during the original
source map. Fill in results only after the actual gate. Keep record, immediate
local credit, immutable packet publication, lesson and finish adjacent in the
existing actor workflow. An actor-specific finalizer is not a generic validator;
do not copy its claim or assumptions into another lane. Failed commands and
work before the first decision stay in the method clock.

## Compact family-transfer record

Each method still owns a lesson. Link the frozen family rule once, then record
only its own obligations and result in a small table or short paragraphs:

| Field | Required method-specific content |
| --- | --- |
| Identity | Stable task/module, descriptive name, original full span and instruction/literal/alignment split |
| Original discriminator | Ordered selectors/calls, physical objects, widths, guards, snapshots/reloads and actual native end |
| Transfer | Linked frozen rule, confirmed preconditions and any counterexample or changed operation |
| Evidence | Actual gate and stable source/header/compiler/binary/provenance receipt identities |
| Result | Generated/full-equal spans, attempts, failed hypotheses, relevant cases or justified unchanged reuse |
| Mechanism | Measured pass if available; otherwise `observed_output` or `hypothesis` |
| Cost | Original start, decision and frozen-publication timestamps; complete elapsed and known step costs |
| Next use | One applicable next pattern and the condition that would invalidate transfer |

Do not replace source obligations with a generic template. For example, 1329B8
has two setters and a fresh unit-pointer load after the first setter; a
single-setter sibling cannot inherit that call sequence. A method may also use a
different guard or end directly at the next live instruction. Compiler terminal
normalization and original outside alignment require separate evidence.

Attach any additional closeout timing to the existing finish receipt, rather
than starting another reporting cycle. Compare complete claim-to-finish time
alongside decision-to-credit latency on subsequent methods. Moving checks before
the recorded decision can shorten one interval without improving delivery.
