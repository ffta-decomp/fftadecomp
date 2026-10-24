# Panel mode marker: physical layout with its own call boundary

- `66A8C` uses the same embedded text-at36 panel family as `687D8`, but has its own byte8 mode rule and drawing call. Reuse the physical fields, not a controller CFG.
- Preserve LOW8(mode-5)<=1. Text bytes16/17/18 are column/row/width; X=(column+width)*8-40 and Y=row*8-4 remain full signed working values until the helper call.
- The fixed marker literal and eleven-argument call require seven zero stack words. Do not replace them with a guessed shorter prototype or narrow the coordinates.
- First fixed-O2 source matches68/68 bytes:64 instruction,4 literal,0 alignment,32B full frame. No instruction ASM, empty constraints or trim.
- Its local command takes1.055629s; original qualification-to-freeze takes107.580436s. No CPU bank was rerun; independent peer and production integration are separate gates.
- This supports a small typed-panel rule only. Prior multi-state frame/register failures remain closed under their old budgets.
- Frozen local-proof SHA-256: `a8f706f608782c1303cf9c4f18324cb365785456512672911b025033fc14db6f`.
