> Public toolkit edition. Local assignments, evidence and game implementations are not distributed. See [the contributor guide](../../../CONTRIBUTING.md).

# Mission record replacement: snapshots and separate scan objects

`CoreFrontier_000CEDC8`, entry `0x080CEDC9`, original 260 bytes:
109 Thumb instructions / 224 instruction bytes, 32 literal bytes, 4 alignment
bytes. Fixed O2/interwork; agbcc
`da598c1d918402c42c0c0d7128ba14567f3175e9`. Round06 reproduces the complete
original span with no padding trim, mixed code, forced register or relocation.

## ASM-driven writing decisions

Keep the previous-node value read in the search condition as the value used
on loop exit. A separate post-loop load changes its definition and loses the
original shared value, even if ordinary inputs produce the same result.

The status condition here tests raw byte bits 2..4 with `& 28`. The logical
three-bit field used by the related timer switch is not the same source shape:
it emitted two shifts, whereas the raw mask restored the original peeled loop.
This is a concrete failed transfer boundary for packed-field expressions.

The original computes the mask, then saves the candidate record pointer, then
tests the mask. Preserve those expression and snapshot roles in that order.
Two pointer names assigned before the mask coalesced to identical code; computing
the actual mask before the output snapshot retained the r2 candidate / r6 saved
record distinction and restored the original search/unlink sequence.

Read the runtime head through its actual outer-object field after clear/copy.
An invented local pointer to that field folded the original outer base + large
field offset into one literal. Direct field reads restored the original 8 bytes
of address formation and literal layout while preserving repeated live loads.
Finally, record-pool and node-pool searches have separate ordinal objects. One
shared ordinal emitted r3 for both; the second phase's own ordinal emitted r2,
closing the final three differing instruction-register bytes.

These source-to-final-code effects are verified by retained reports and exact
comparison. Initial-RTL lifetime/coalescing explanations are inferred here;
no new instrumented compiler trace is claimed for this method.

## Acceptance and failed classes

Source SHA-256 and all included-header/toolchain pins are in the round06 native
local report. Binary SHA-256:
`eace02887840b1c74023b8c3e79146dd0fdbddf9fc8219d7a9ab448303f7244f`.
Two existing independent cases pass with expected whole observed memory, full
return and declared helper-call trace preserved. The real IWRAM clear/copy paths
execute. Independent code acceptance and production integration remain pending;
there is zero new semantic-byte credit and no natural-gameplay claim.

Seven candidates generated 232, 228, 248, 248, 252, 260 and 260 bytes. The second
248-byte binary was identical and reused the preceding execution evidence.
No optimizer-level, flag, name or register permutation was performed. The
unsuccessful pointer-naming-only hypothesis remains frozen.

## Transfer preconditions

Use the raw-mask form only when the original branch consumes raw bits, not an
extracted switch value. Preserve mask-before-snapshot and post-helper reloads
only where original def-use supports them. Separate scan ordinals only for
actually distinct objects/phases; declaration shuffling is not a register rule.
Null-head / full-pool invariants remain unknown and original failure behavior is
retained. Next mission-offer reconstruction should check its own status/quantity
bit domains and post-helper global reads before transferring these lessons.

Full gross elapsed through exact decision: 459.538 seconds (2036.829 local exact
original bytes/hour); peer-accepted/integrated rates remain zero. Required
freeze/lesson work is included before claiming the next method. Savings against
comparable earlier work are unknown.
