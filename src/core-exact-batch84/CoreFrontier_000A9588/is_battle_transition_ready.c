typedef unsigned char u8;
typedef unsigned int u32;
struct BattleTransitionView {
    u32 unknown_00;
    u32 reference_value;
    u32 current_value;
    u32 unknown_0c;
    u8 flags;
};
extern struct BattleTransitionView gBattleTransition;
asm(".global gBattleTransition\n.set gBattleTransition,0x0200ffc8");

u32 IsBattleTransitionReady(void)
{
    if ((gBattleTransition.flags & 1) != 0 &&
        gBattleTransition.current_value != gBattleTransition.reference_value)
        return 0;
    return 1;
}
