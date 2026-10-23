> Public toolkit edition. Local assignments, evidence and game implementations are not distributed. See [the contributor guide](../../../CONTRIBUTING.md).

# Unit value application: materialize signed operands before wrapping

`ActionDependency_000A2210`, entry `0x080A2211`, original 222 instruction
bytes, no literals or internal alignment. Fixed O2/interwork, agbcc
`da598c1d918402c42c0c0d7128ba14567f3175e9`. Round05a is wholly exact.
A separate two-byte compiler NOP after the final BX is outside the original
span and is excluded by the existing trailing-alignment guard.

## Original behavior and source boundaries

The low16 incoming delta is interpreted as signed16, as is a newly queried
field19. Their difference wraps to u16 before its signed16 negativity test.
The maximum comparison is unsigned/full32; if it clamps, field20 is queried
again and that second return supplies the stored halfword. Classification uses
full32 properties and low8 gate results, both before and after the unit write.
These stages must not be merged into a generic saturating subtraction.

The two classification guards share actual class2 and class3 blocks, then one
result join. Expressing those shared exits in the small readable inline
classifier reproduced the original branch structure and result snapshot.
Duplicated if/else assignments had encouraged speculative default values;
a single joined local alone did not recover all shared blocks.

The remaining eight executable bytes were separate sign extensions for the two
operands. Same-expression casts in `u16_result = (s16)query() - (s16)delta` were
already represented as HI subregister operands in initial RTL. This happened
before allocation; changing result width or overwriting the parameter did not
restore them. The bounded unchanged-source dump identifies insns91/93 as HI
subregs followed by minus94, without the original sign-extension statements.

Instead, materialize the actual signed values at their observed definition
points: `s32 current_signed = (s16)query();`, then
`s32 delta_signed = (s16)delta;`, then assign their difference to the wrapped
result. New initial RTL contains the two LSL/ASR conversion chains before the
minus, and final output reproduces the original instructions. Both observational
compiles reproduce their unchanged normal assembly; no backend modification,
flag variation, artificial volatile, register binding or dummy use was involved.

## Acceptance and transfer limits

Seven frozen independent cases pass, retaining expected memory/full return,
the complete frozen declared trace and the custom `expected_helper_calls`
oracle. The candidate byte SHA-256 is
`e8bc5d7b9748d1f71990b7fd7b5913a92e8759e2b682d3dce229d7e11717d293`.
Native reports pin source, included declarations and the complete toolchain.
Independent code acceptance and production integration remain pending. Existing
semantic recovery is not credited again; natural combat is not established.

Seven candidate commands include the final verified terminal-NOP metadata
repair. The u32-result-only trial was binary-identical and reused its prior
cases. The unsupported mutable-parameter trial is retained. Two diagnostics
located the front-end boundary and verified the corrected initial RTL.

Transfer only when original ASM separately normalizes operands before arithmetic
and wraps at the later result boundary. Splitting arbitrary expressions or
adding unused locals is not this rule. Preserve signedness and opaque helper
order; a whole-function match here does not justify a global signed-width rule.
Next descriptor application should first identify its own repeated-query and
post-callback reload joins rather than importing the subtraction pattern.

Full elapsed through local exact/freeze preparation: 740.592 seconds; 1079.137 local
whole-exact original bytes/hour for this method. Independent/integrated credit
remains zero; no measured cross-method saving or fivefold claim is made.
