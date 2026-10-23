> Public toolkit edition. Local assignments, evidence and game implementations are not distributed. See [the contributor guide](../../../CONTRIBUTING.md).

# Mission reward selection: retain the shared halfword-return continuation

`CoreFrontier_000D21A8`, entry `0x080D21A9`, original 344 bytes.
Fixed O2/interwork. The local round02 candidate fits 344 bytes and passes six
existing independent cases. It is not whole-function exact and has no new
semantic, independently accepted or integrated byte credit.

The original has a halfword reward table (20 entries per 40-byte row), 16-byte
property records with flags in the halfword at +2, and a signed-low16 random
value passed to fullword signed remainder. Preserve all six low8 flag queries
and their override order. A negative remainder is not narrowed to unsigned.

Two source returns share the original halfword-cast continuation: base reward
171 + group and the flag40 result ID + 85. Expressing separate cast returns
caused O2 to carry a shifted base-reward induction through the loop. Restoring
one outgoing result and shared cast reduced 368 to 344 bytes without changing
the ABI or test input. Moving that join into its original flag40 location
restored block topology but generated 356 bytes; it remains a structural-stage
artifact, not a more accepted candidate. Separate phase-local entry cursors
then produced the original first-pass cursor/weight/counter register roles and
352 bytes; the former shared cursor was one user pseudo in both phases.

The unchanged-source diagnostic generated identical assembly. Initial RTL
materializes first-pass mask constants as SI values; `.loop` moves them outside
the loop (insns 174/184 become 468/470). The generated masks occupy preserved
registers, whereas original masks are materialized locally. Narrowing either
the flags snapshot or masked-result width did not remove that hoist. These are
failed transfer classes, not instructions to try more equivalent casts. A new
source-backed cause or reduced compiler proof is needed. Do not invent volatile
ROM, force registers, change flags, or use the old semantic C as a template.

Seven candidate attempts include the failed textual cursor edit and its syntax
repair; no oversized output was executed. All original raw-result obligations
are retained and retail cases were reused. This bounded result is not natural
reward-domain coverage. Next related mission-record replacement should reuse
only actual width/object/shared-tail evidence; the mask-hoist problem remains
open. Exact/peer/integrated output rate for this method is zero.

Measured gross through this checkpoint: 696.403 seconds, including frozen peer
review, setup, all failures and reporting. No measured savings are claimed.
