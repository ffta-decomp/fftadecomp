# Menu text row: fixed workspace and post-clear reload

- Native `6FFAC` binds a caption row for the `6FABC` item/related-caption consumer; its complex text helpers remain existing C/ASM.
- Preserve both full pointers and the LOW16 row argument. Workspace word16 supplies the base; row addressing is `base + (row << 5)`.
- Clear first, then load the live panel word124 before the five-argument text call. Keep the destination argument even though the selected text implementation ignores it.
- The clear helper receives24, which it converts to192 halfwords/384 bytes; this is not a24-byte clear. Do not infer a full row capacity from the stride.
- The first fixed-O2 typed-object source matches all56 bytes:50 instruction,4 literal,2 alignment. No instruction ASM, register constraints, private header or terminal trim is used.
- One compiler invocation takes1.099486s; the277.524239s qualification-to-freeze clock also includes an occupied-slot refusal, source/interface work and result handling. Unclassified time is not compiler time.
- This is local whole-native equality, not natural-path coverage. Independent peer and production integration are separate gates; layout reuse does not prove another multistate CFG will match.
- Frozen local-proof SHA-256: `d4849290cebadb8edd1a2b5cb444fbae02f80e3218d56c809578e4f199cb2849`.
