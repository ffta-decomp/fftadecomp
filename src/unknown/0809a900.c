typedef unsigned char u8;
typedef unsigned int u32;
struct BattleChoiceView {
    u8 prefix[150];
    u8 choice;
};
extern struct BattleChoiceView gBattleChoiceView;
__asm__(".global gBattleChoiceView\n.set gBattleChoiceView, 0x0200f390");
/* The caller passes a value, but the original entry consumes no arguments. */
u32 ReadBattleContinuationChoice(void)
{
    return gBattleChoiceView.choice;
}
