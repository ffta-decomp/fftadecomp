typedef unsigned char u8;
typedef unsigned short u16;
struct BattleStateSnapshot {
    u8 unknown_0000[1148];
    u16 saved_halfword;
    u8 saved_first;
    u8 saved_second;
    u8 current_first;
    u8 current_second;
};
struct BattleStateView {
    u16 restored_halfword;
    u8 unknown_0002[72];
    volatile u8 restored_first;
    volatile u8 restored_second;
    u8 current_first;
    u8 current_second;
};
extern struct BattleStateView gBattleState;
extern void FreeSnapshot(void *snapshot);
asm(".global gBattleState\n.set gBattleState,0x03000940\n.global FreeSnapshot\n.thumb_set FreeSnapshot,0x08022855");
void ReleaseBattleStateSnapshot(struct BattleStateSnapshot *snapshot)
{
    u8 first;
    u8 second;
    gBattleState.restored_halfword = snapshot->saved_halfword;
    first = snapshot->saved_first;
    gBattleState.restored_first = first;
    second = snapshot->saved_second;
    gBattleState.restored_second = second;
    snapshot->current_first = gBattleState.current_first;
    snapshot->current_second = gBattleState.current_second;
    FreeSnapshot(snapshot);
}
