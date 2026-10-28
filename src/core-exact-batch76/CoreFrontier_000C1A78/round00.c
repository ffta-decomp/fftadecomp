typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
/* Partial live record view. The zero-length tail asserts no natural capacity. */
struct BattleRecordedTargets {
    u8 prefix[0x54b0];
    u8 first_x;
    u8 first_y;
    u8 second_x;
    u8 second_y;
    u8 intervening[14];
    u16 actions[0];
};
typedef char FirstOffset[(u32)&((struct BattleRecordedTargets *)0)->first_x == 0x54b0 ? 1 : -1];
typedef char SecondOffset[(u32)&((struct BattleRecordedTargets *)0)->second_x == 0x54b2 ? 1 : -1];
typedef char ActionsOffset[(u32)&((struct BattleRecordedTargets *)0)->actions == 0x54c2 ? 1 : -1];
extern struct BattleRecordedTargets gBattleRecordedTargets;
__asm__(".global gBattleRecordedTargets\n.set gBattleRecordedTargets,0x020101f8");
u32 ReadBattleRecordedTarget(u8 slot, u8 *x_out, u8 *y_out)
{
    if (slot == 0) {
        *x_out = gBattleRecordedTargets.second_x;
        *y_out = gBattleRecordedTargets.second_y;
    } else {
        *x_out = gBattleRecordedTargets.first_x;
        *y_out = gBattleRecordedTargets.first_y;
    }
    return gBattleRecordedTargets.actions[slot];
}
