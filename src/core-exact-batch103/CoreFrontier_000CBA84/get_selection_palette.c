typedef unsigned char u8;
typedef unsigned int u32;
struct PaletteVariantStateView {
    u8 unknown[0x2fc2];
    unsigned char variant : 2;
    unsigned char unknown_high_bits : 6;
};
extern struct PaletteVariantStateView gGameState;
extern const u8 gSelectionPalettes[];
extern const u8 gAlternateSelectionPalettes[];
__asm__(".global gGameState\n.set gGameState,0x02000000\n.global gSelectionPalettes\n.set gSelectionPalettes,0x08419f60\n.global gAlternateSelectionPalettes\n.set gAlternateSelectionPalettes,0x0841aa60");
const u8 *GetSelectionPalette(u8 index) __asm__("CoreFrontier_000CBA84");
/* Both tables contain 32-byte records. This accessor leaves bounds to callers. */
const u8 *GetSelectionPalette(u8 index)
{
    u32 positioned_variant = (u32)gGameState.variant << 30;
    /* Preserve the original two-shift extraction before the comparison. */
    __asm__("" : "+r"(positioned_variant));
    if ((positioned_variant >> 30) == 2)
        return gAlternateSelectionPalettes + (u32)index * 32;
    else
        return gSelectionPalettes + (u32)index * 32;
}
