typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
struct BattleTransitionHalfwordView {
    u32 unknown_00;
    u16 unknown_04;
    s16 reference_second;
    u16 current_first;
    u16 current_second;
    u16 saved_first;
    u16 saved_second;
    u8 flags;
};
extern struct BattleTransitionHalfwordView gBattleTransition;
asm(".global gBattleTransition\n.set gBattleTransition,0x0200ffc8");

void BeginBattleTransition(void)
{
    if (gBattleTransition.flags & 1) {
        gBattleTransition.saved_first = gBattleTransition.current_first;
        gBattleTransition.saved_second = gBattleTransition.current_second;
        if (gBattleTransition.reference_second <= 4) {
            gBattleTransition.current_first = 192;
            gBattleTransition.current_second = (u16)-32;
        } else {
            gBattleTransition.current_first = 192;
            gBattleTransition.current_second = 160;
        }
        gBattleTransition.flags = 5;
    }
}
