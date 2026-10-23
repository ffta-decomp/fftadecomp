> Public toolkit edition. Local assignments, evidence and game implementations are not distributed. See [the contributor guide](../../../CONTRIBUTING.md).

# Equipment selectors: source syntax is not a unique CFG inverse

Two frozen 56-byte equipment-stat selectors reproduced their complete original
spans under fixed O2/interwork. Both normalize selector/include to low bytes,
prioritize bit0 over bit1, retain the full helper return word and otherwise return
zero. Their original instruction/branch shapes are identical after rebasing
local targets and distinguishing their two actual helper targets. This is a
source-shape comparison, not an assertion that the stat helpers are identical.

The [stat20/24 selector](../worker3/SelectUnitEquippedStat20Or24.md) first produced
43/56 equal bytes with its early-return source. A nested three-arm selection into
one outgoing `selected_stat`, with zero before the second helper, reproduced
56/56. Its owner recorded two source formulations,96.458 seconds to exact and
131.917 seconds through frozen closeout.

The [stat22/26 selector](../worker2/SelectUnitEquippedStat22Or26.md) matched56/56
on its first source using ordered early returns and mask-first conditions.
Its frozen closeout charged139.333 seconds. These are concurrent different
methods, not a measured transfer saving or a controlled operand-order experiment.

Do not promote the first result into "shared return is required", or the second
into "always use early return". Several readable C forms can produce one native
shape, and equivalent source forms can produce different shapes. Map the bit
priority, actual zero fallthrough, call edges, full-word return and common exit
first. Reuse a successful form only with compatible widths, interfaces and
value definitions; compare the first generated branch divergence before another
source change. Keep failed formulations attached to their original method.

Both results are local whole-function exact observations. Independent mechanical
and production gates are recorded separately. No compiler pass was traced here,
no new behavior test or compiler invocation was run for this lesson, and no
universal syntax or speedup claim follows from these two outcomes.
