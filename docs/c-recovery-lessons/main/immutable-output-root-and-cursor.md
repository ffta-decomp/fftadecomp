# Immutable output root and advancing cursor

- Original `C9208` keeps the three-byte output root in R5 and advances a separate R4 cursor. Both remain live across the mapped-selection helper; sentinel zeroing uses root plus ordinal.
- After four ordinary CFG/address/width causes, the full 232-byte output matched 209 bytes. Original and generated def-use chains isolated the remaining 23 differing bytes to the root/cursor register exchange, with frame, branches, tables and order already matching.
- One initialized `register u8 *output asm("r5") = destination` plus a truthful empty `+r` operand at its definition restored 232/232 bytes. No cursor binding, fake input, clobber or inline instruction was added.
- `gcc_arm/extend.texi` requires an actual operand use for a local register binding; the existing repeated-field/counter lesson supplied the narrow transfer. This is not a universal R5 rule.
- Counterconditions: no real root/cursor lifetime, an incoming argument overwritten by a forced register, or unresolved CFG/frame/width differences. Such cases do not inherit this result.
- Total 5 source causes/5 compiler starts and the original method clock remain charged. Local5297 and independent5298 are reused; production preprocessing and complete-image equality close integration.
- The actual consumer establishes command eligibility/selection, not job learning. The historical C/export names remain frozen; no naming-only compiler run or natural-gameplay claim.
- Checker feedback remains an uncovered def-use/operand-exchange pattern, requiring a proven full-span comparison; a lexical register suggestion alone cannot establish it or authorize an automatic rewrite.
