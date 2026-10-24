# Selection text: reuse operation shape, preserve actual ownership

- `5C3D4` reuses the clear/text-call shape of `6FFAC`, with full text/data pointers, LOW8 signed row and LOW8 glyph. Preserve its own24-byte frame and pointer lifetimes.
- Existing `17B9C` C returns a tile offset after clamping/modulo/width arithmetic, not a row ordinal. The complete caller uses LOW16 result shifted5.
- Its destination base is word16 of workspace `03000990`; do not substitute `6FFAC`'s different workspace at `030008B0`. Clear count is twice data byte21; the existing helper clears32 bytes per width unit.
- Load root `0200F428` after the clear, then pass the embedded context at root+1184. It is not a pointer loaded from word1184. Hold the destination across the call.
- The first fixed-O2 source matches96/96 bytes:84 instruction,12 literal,0 alignment. No constraints, instruction ASM or terminal trim; helper implementations remain unchanged.
- The command takes1.076963s; source-qualification-to-freeze is427.128746s, including production-batch waiting and source/interface work. Original clock is retained, not restarted after integration.
- Local whole-native identity is distinct from independent peer and production acceptance; no capacity/natural path or generic engine completion claim.
- Frozen local-proof SHA-256: `ec44f175673e9e8602305d47c3604ae64f5f5d19dfb640efcaa038bdf4dc33a8`.
