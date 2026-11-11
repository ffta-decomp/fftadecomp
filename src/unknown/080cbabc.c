typedef unsigned char u8;
typedef unsigned int u32;

struct PairPaletteVariantView {
    u8 unknown_00[0x2fc2];
    unsigned char variant : 2;
    unsigned char unknown_high_bits : 6;
};
extern struct PairPaletteVariantView PairPaletteGameState;
extern const u8 PairVariantTwoPalettesLow[];
extern const u8 PairVariantTwoPalettesHigh[];
extern const u8 PairVariantOnePalettesLow[];
extern const u8 PairVariantOnePalettesHigh[];
extern const u8 PairDefaultPalettesLow[];
extern const u8 PairDefaultPalettesHigh[];

const u8 *GetUnitPairPalette(u8 index)
{
    u32 positioned_variant = (u32)PairPaletteGameState.variant << 30;
    /* Retain the retail two-shift extraction before the variant dispatch. */
    asm("" : "+r" (positioned_variant));
    switch (positioned_variant >> 30) {
    case 2:
        if (index <= 15)
            return PairVariantTwoPalettesLow + (u32)index * 32;
        return PairVariantTwoPalettesHigh + (u32)(index - 16) * 32;
    case 1:
        if (index <= 15)
            return PairVariantOnePalettesLow + (u32)index * 32;
        return PairVariantOnePalettesHigh + (u32)(index - 16) * 32;
    default:
        if (index <= 15)
            return PairDefaultPalettesLow + (u32)index * 32;
        else
            return PairDefaultPalettesHigh + (u32)(index - 16) * 32;
    }
}

asm(".global PairPaletteGameState\n.set PairPaletteGameState, 0x02000000\n"
    ".global PairVariantTwoPalettesLow\n.set PairVariantTwoPalettesLow, 0x0841ac60\n"
    ".global PairVariantTwoPalettesHigh\n.set PairVariantTwoPalettesHigh, 0x0841ae60\n"
    ".global PairVariantOnePalettesLow\n.set PairVariantOnePalettesLow, 0x0841b740\n"
    ".global PairVariantOnePalettesHigh\n.set PairVariantOnePalettesHigh, 0x0841b940\n"
    ".global PairDefaultPalettesLow\n.set PairDefaultPalettesLow, 0x0841a160\n"
    ".global PairDefaultPalettesHigh\n.set PairDefaultPalettesHigh, 0x0841a360\n");
