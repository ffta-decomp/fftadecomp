typedef unsigned char u8;
typedef signed short s16;
typedef unsigned int u32;
struct BattleSelectionValue { u8 unknown00[18]; s16 selection_value; };
extern struct BattleSelectionValue *gBattleSelection;
asm(".global gBattleSelection\n.set gBattleSelection,0x0200f438\n");

/* Store the low halfword; the physical return retains the complete input. */
u32 CoreFrontier_000294F0(u32 value)
{
    gBattleSelection->selection_value = (s16)value;
    return value;
}
