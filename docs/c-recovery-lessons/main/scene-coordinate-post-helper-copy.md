> Public toolkit edition. Local assignments, evidence and game implementations are not distributed. See [the contributor guide](../../../CONTRIBUTING.md).

# Scene coordinate copies: separate source and destination phases

The complete command entry at `0x08122598` has 114 instruction bytes. Its prior
104-byte C selection and ten-byte original companion are parts of one function;
the companion is not a second entry or an unknown boundary.

Read the command axes before the shared tail. A byte value of 255 independently
selects the entity's signed halfword at +8 or +12, arithmetic shift by five, then
byte narrowing. The position helper receives signed bytes reloaded from the live
unit, not the earlier command operands. Preserve byte-store aliasing and the
entity-to-unit reloads before and after that helper.

For the final copies, the original loads the source byte before constructing its
destination address. A direct assignment computed the destination first. Explicit
source snapshots restored that order but reusing the earlier command `x` local
kept its old register identity. One separately named post-helper coordinate-copy
value restored both original copy sequences. Three source formulations under the
same fixed O2/interwork configuration reached 114/114 native bytes; two compiler
NOP bytes after the original return are separately trimmed by existing metadata.

This is a phase-lifetime and evaluation-order result, not permission to force
registers or mark ordinary RAM volatile. Exact local native identity establishes
no new natural gameplay coverage. Production promotion must absorb only the
proven same-parent companion and preserve adjacent alignment.
