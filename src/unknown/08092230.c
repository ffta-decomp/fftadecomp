typedef unsigned char u8;
typedef unsigned int u32;
struct BattleSavedState {
    u32 unknown_0000;
    void *owned_allocation;
    u8 unknown_0008[64];
    u8 saved_first, saved_second, saved_third, saved_fourth;
};
struct RestoredBattleBytes {
    u8 unknown_0000[74];
    volatile u8 first, second, third, fourth;
};
extern struct RestoredBattleBytes gBattleState;
extern void FreeSavedState(void *memory);
asm(".global gBattleState\n.set gBattleState,0x03000940\n.global FreeSavedState\n.thumb_set FreeSavedState,0x08022855");
void ReleaseBattleSavedState(struct BattleSavedState *state)
{
    if (state->owned_allocation != 0)
        FreeSavedState(state->owned_allocation);
    gBattleState.first = state->saved_first;
    gBattleState.second = state->saved_second;
    gBattleState.third = state->saved_third;
    gBattleState.fourth = state->saved_fourth;
    FreeSavedState(state);
}
