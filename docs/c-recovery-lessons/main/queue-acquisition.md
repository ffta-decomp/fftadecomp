> Public toolkit edition. Local assignments, evidence and game implementations are not distributed. See [the contributor guide](../../../CONTRIBUTING.md).

# Conditional field-address lifetimes

Method: `CoreRegion_00038858`, acquisition queue writer. Fixed profile:
`-O2 -mthumb-interwork`, agbcc revision
`da598c1d918402c42c0c0d7128ba14567f3175e9`.

This record summarizes the implementer's frozen G38-APPLY-QUEUE decision and
round01 cause record. It is not a new administrator C review or acceptance.

## Result

The first candidate generated116 bytes and exceeded the112-byte envelope. One
source-structure correction produced112/112 equal bytes:94 instruction bytes,
16 literal bytes and2 alignment bytes. Fourteen development cases passed.
Independent peer acceptance and integration remain pending. The binary SHA-256 is
`238c55666c0b4f7f992f8189c2572e2f09511b9450a7b9c556b00a0684366339`.

## Reusable mechanism

Original ASM keeps the workspace plus ordinal-times-eight value separate from
the conditional item-field address, and derives later field addresses on the
successful insertion path. A cached row-field address in the first formulation
kept an offset live across the loop. The implementer observed its expression in
initial RTL, hoisting in `.loop`, and high-register materialization in `.greg`.

Reconstructing those distinct address lifetimes reproduced the original field
constants and register allocation without flag changes or assembly. Do not
generalize this to removing every row pointer: the original def-use chain and
branch-specific uses must support the separation, and helper reload obligations
must remain intact.

## Cost and transfer

Full observed method time was214.999510 seconds, with two candidate builds and
one diagnostic dump from the unchanged source. The first build took1.519571
seconds. There is no comparable control workflow, so saved time and speedup are
unknown. This is one successful method, not a validated cross-method template.

Next application: before an inventory-related loop rewrite, check whether field
addresses are formed inside the selected branch or kept live across the loop.
Predict the affected RTL pass before editing; preserve widths, store ordering
and reload behavior. Record success or a counterexample in the next method's
lesson.
