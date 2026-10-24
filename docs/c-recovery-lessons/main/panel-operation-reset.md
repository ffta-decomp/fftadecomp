# Panel operation reset: embedded objects and callback result

- `687D8` is a menu panel reset continuation reached after callers clear their flag40; retain the existing helpers. Exact callback meaning remains unknown.
- Read byte28 for the text subobject at36, call the child at112 with0, then clear byte14. Do not move the clear before those opaque calls.
- Register literal Thumb callback `08066E09` with the same full panel pointer; store only the LOW8 result at byte9. The function returns void through its saved LR.
- Separate physical byte fields and the embedded36/112 object views reproduce all48 native bytes on the first fixed-O2 source:42 instruction,4 literal,2 alignment. No instruction ASM, empty constraints or terminal trim.
- Local compilation takes2.317119s; qualification-to-freeze takes177.388417s, including source/contract, registration, checks and orchestration. No whole-workflow speed claim follows.
- Full equality is a local gate; independent peer and batch integration remain distinct. This simple ordering rule does not imply matching of another multistate controller.
- Frozen local-proof SHA-256: `06e14757aa99cebb05ee250792a7705a28004a359118a9fc670da75b7058ebdc`.
