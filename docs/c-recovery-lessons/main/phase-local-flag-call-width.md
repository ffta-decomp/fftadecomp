# Phase-local flag call constants

- Original `09FF8` reads flag 543 and clears it only when the LOW8 result is nonzero; the flag meaning remains unknown. Each helper gets a fresh R0 definition.
- Keeping the constant across calls retained R4 and grew the method to 36/32 bytes. Separate initialized input-only R0 operands removed R4, but `u16` working values still added copies.
- Using `unsigned int` for those known constants, with the original `u8 Get(u16)` / `void Set(u16,u16)` interfaces unchanged, produced 32/32 exact bytes: 26 instruction, 4 literal and 2 alignment bytes.
- Vendor `thumb.h` `PROMOTE_MODE` promotes narrow integer working modes to SI; `calls.c` performs argument-mode conversion. This supports a working-width cause, not an earliest-RTL-pass claim.
- There are no incoming arguments. Do not transfer this rule to an overlapping live formal (the `130200` counterexample), or a narrow readwrite output (`1312EC` needs real normalization shifts). No instructions or unknown readwrite values were introduced.
- Three original source causes/compiler starts remain charged. Local 5293 and independent peer 5294 are reused; production preprocessing and complete-image equality close integration. No flag-role, natural-gameplay or hardware claim follows.
