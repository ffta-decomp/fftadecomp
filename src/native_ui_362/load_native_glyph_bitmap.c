/* Original game glyph data and width mode; generic copy stays native. */
typedef unsigned char u8;
typedef signed short s16;
typedef unsigned int u32;
typedef void *(*NativeGlyphCopy)(void *destination, const void *source, u32 bytes);
struct NativeTextRuntime {
    u8 prefix[19];
    u8 fixed_width_mode;
};
extern const u8 NativeGlyphBitmaps[];
extern const u8 NativeGlyphWidths[];
extern struct NativeTextRuntime NativeTextState;
extern NativeGlyphCopy NativeGlyphCopySlot;

u32 LoadNativeGlyphBitmap(void *destination, s16 glyph_index)
{
    const u8 *glyph = NativeGlyphBitmaps + glyph_index * 128;
    NativeGlyphCopy copy = NativeGlyphCopySlot;
    copy(destination, glyph, 128);
    if (NativeTextState.fixed_width_mode != 0)
        return 16;
    return NativeGlyphWidths[glyph_index];
}

/* Actual original object bases and Thumb R3 trampoline, no instructions. */
asm(".global NativeGlyphBitmaps\n.set NativeGlyphBitmaps, 0x08433330\n"
    ".global NativeGlyphWidths\n.set NativeGlyphWidths, 0x084966b0\n"
    ".global NativeTextState\n.set NativeTextState, 0x020020d0\n"
    ".global NativeGlyphCopySlot\n.set NativeGlyphCopySlot, 0x0836d4bc\n"
    ".global _call_via_r3\n.thumb_set _call_via_r3, 0x08142251");
