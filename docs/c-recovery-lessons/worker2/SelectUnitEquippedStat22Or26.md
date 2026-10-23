> Public toolkit edition. Local assignments, evidence and game implementations are not distributed. See [the contributor guide](../../../CONTRIBUTING.md).

# Equipped-stat selector: normalize inputs, preserve bit priority and full return

`CONVERGE205-CA478` restores56/56 original bytes of
`SelectUnitEquippedStat22Or26` on its first fixed-O2 native source. The existing
C01 semantic implementation, original clocks and source/header evidence remain
preserved; this convergence adds no repeated semantic credit.

The complete original normalizes selector and include to u8 before dispatch.
Bit0 selects the existing22-stat helper even when bit1 is also set. Otherwise
bit1 selects the26-stat helper; no selected bit returns fullword0. Include is
forwarded as a zero-extended word, and the complete helper return word passes
through without another byte or halfword truncation. The helpers may return a
negative signed16-derived result; the wrapper must retain its full32-bit pattern.
Their low-byte include consumption and their five live equipment reads are
existing contracts, not new bodies recovered by this selector.

The source retains two ordered mask-first early-return tests, matching the
original first-helper/shared-exit and second zero-before-helper branch layout.
Ordinary unit pointers need no blanket volatile or invented null guards. This
first-source observation does not isolate mask operand order from the historical
O1 profile difference. Do not transfer the early-return spelling to a method
whose original has one numeric result definition and a different shared join.

Native function/text are56B, with no literal/alignment/compiler trim or retained
retail suffix. Full retail/ELF identity, actual source/header/preprocessor closure,
tool/artifact hashes and strict selection passed. No old semantic bank or full-ROM
build was rerun; independent frozen peer and production remain separate gates.
