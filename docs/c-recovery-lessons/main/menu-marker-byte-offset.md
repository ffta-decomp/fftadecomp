# Menu marker: byte offset and live tilemap identity

- `70170` preserves the complete76B fixed two-row marker, not its generic writer. The full panel/map pointers and LOW8 relative row produce a LOW16 tile index, then one doubled byte-offset snapshot retained across both calls.
- Actual objects: panel bytes19/20 are column/row; map byte12 is stride and word20 is tile-buffer base. Physical prefix types assert only these accesses, without a buffer-capacity claim.
- Existing`2ACA0` consumes `(destination,u16 first_tile,u8 palette,u16 count)`. Here13 is the palette and2 is the halfword count, not a13-by2 rectangle. First row uses329/330 and the next331/332.
- After the first writer, reload map word20 and byte12; the same byte offset plus twice the fresh stride locates the next row. Preserve potential alias effects instead of caching the original destination and stride.
- The first fixedO2 source matches76/76:66 instruction,8 literal,2 alignment,12B frame. No initialized constraints, instruction ASM, trim, helper migration or compiler option changes.
- One local command takes1.079417s; original qualification-to-freeze is120.813768s. Reuse the established row/object lessons; this first-pass result establishes no general compiler-pass or throughput gain.
- Whole-native local identity is separate from independent peer, production acceptance, natural coordinates/capacity and complete menu behavior.
- Frozen proof SHA-256:`52ffcf6e3ae12eb44cdd5992fc0d6e1875ddff5a35529e48ae2a1ff37ddd584f`.
