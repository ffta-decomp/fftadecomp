typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef void (*ClearRoutine)(void *,u32);
typedef void (*CopyRoutine)(void *,const void *,u32);
struct BattleStateSnapshot {
    u32 mode;
    u8 operation_state[1144];
    u16 saved_halfword;
    u8 saved_first, saved_second, saved_third, saved_fourth;
    u8 copied_state[512];
};
struct BattleStateView {
    u16 halfword;
    u8 unknown_0002[16];
    volatile u16 first_reset;
    volatile u16 second_reset;
    u8 unknown_0022[52];
    u8 first, second, third, fourth;
};
extern struct BattleStateView gBattleState;
extern u8 gCurrentCopiedState[512];
extern ClearRoutine const gClearRoutine;
extern CopyRoutine const gCopyRoutine;
extern void *AllocateSnapshot(u32 size);
extern void CallClear(void *,u32,ClearRoutine);
extern void CallCopy(void *,const void *,u32,CopyRoutine);
extern void InitializeZeroMode(void *);
extern void InitializeZeroHighMode(void *);
extern void InitializeOtherMode(void *);
extern void InitializeOtherHighMode(void *);
asm(".global gBattleState\n.set gBattleState,0x03000940\n.global gCurrentCopiedState\n.set gCurrentCopiedState,0x03003860\n.global gClearRoutine\n.set gClearRoutine,0x0836d4b8\n.global gCopyRoutine\n.set gCopyRoutine,0x0836d4bc\n.global AllocateSnapshot\n.thumb_set AllocateSnapshot,0x08022841\n.global CallClear\n.thumb_set CallClear,0x0814224d\n.global CallCopy\n.thumb_set CallCopy,0x08142251\n.global InitializeZeroMode\n.thumb_set InitializeZeroMode,0x08090cf9\n.global InitializeZeroHighMode\n.thumb_set InitializeZeroHighMode,0x08090e35\n.global InitializeOtherMode\n.thumb_set InitializeOtherMode,0x08090a81\n.global InitializeOtherHighMode\n.thumb_set InitializeOtherHighMode,0x08090bbd");
struct BattleStateSnapshot *CreateBattleStateSnapshot(u8 mode)
{
    struct BattleStateSnapshot *snapshot = AllocateSnapshot(1748);
    CopyRoutine const *copy_cell;
    CallClear(snapshot,1748,gClearRoutine);
    snapshot->saved_halfword = gBattleState.halfword;
    snapshot->saved_first = gBattleState.first;
    snapshot->saved_second = gBattleState.second;
    snapshot->saved_third = gBattleState.third;
    snapshot->saved_fourth = gBattleState.fourth;
    gBattleState.first_reset = 0;
    gBattleState.second_reset = 0;
    snapshot->mode = mode & ~128u;
    if (snapshot->mode == 0) {
        if (mode & 128)
            InitializeZeroHighMode(snapshot->operation_state);
        else
            InitializeZeroMode(snapshot->operation_state);
    } else {
        if (mode & 128)
            InitializeOtherHighMode(snapshot->operation_state);
        else
            InitializeOtherMode(snapshot->operation_state);
    }
    copy_cell = &gCopyRoutine;
    CallCopy(snapshot->copied_state,gCurrentCopiedState,512,*copy_cell);
    return snapshot;
}
