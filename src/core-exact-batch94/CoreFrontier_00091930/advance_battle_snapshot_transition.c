typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef void (*CopyRoutine)(void *, const void *, u32);
struct BattleTransitionSnapshot {
    u32 mode;
    u8 operation_state[1144];
    u16 saved_halfword;
    u8 saved_bytes[4];
    u16 saved_first_range[112];
    u16 saved_second_range[144];
    u8 unknown_1666[2];
    void *first_token;
    void *second_token;
    u16 transition_state;
};
extern u32 AdvanceOtherSnapshotMode(void *operation);
extern u32 AdvanceZeroSnapshotMode(void *operation);
extern void *BeginConstantRangeTransition(u16 start, u16 count, u16 duration,
                                         u16 first, u16 second, u16 third);
extern void *BeginSavedRangeTransition(u16 start, u16 count, u16 duration,
                                      const u16 *saved);
extern u32 IsTransitionTokenComplete(const void *token);
extern void *ReleaseTransitionToken(void *token);
extern u8 gLiveCopiedState[512];
extern CopyRoutine const gCopyRoutine;
extern void CallCopy(void *destination, const void *source, u32 length,
                     CopyRoutine routine);
asm(".global AdvanceOtherSnapshotMode\n.thumb_set AdvanceOtherSnapshotMode,0x080902cd\n.global AdvanceZeroSnapshotMode\n.thumb_set AdvanceZeroSnapshotMode,0x08090f71\n.global BeginConstantRangeTransition\n.thumb_set BeginConstantRangeTransition,0x081473e5\n.global BeginSavedRangeTransition\n.thumb_set BeginSavedRangeTransition,0x08147d2d\n.global IsTransitionTokenComplete\n.thumb_set IsTransitionTokenComplete,0x081485d5\n.global ReleaseTransitionToken\n.thumb_set ReleaseTransitionToken,0x081484cd\n.global gLiveCopiedState\n.set gLiveCopiedState,0x03003860\n.global gCopyRoutine\n.set gCopyRoutine,0x0836d4bc\n.global CallCopy\n.thumb_set CallCopy,0x08142251");
u8 AdvanceBattleSnapshotTransition(struct BattleTransitionSnapshot *snapshot)
{
    if (snapshot->mode != 0)
        return (u8)AdvanceOtherSnapshotMode(snapshot->operation_state);
    switch (snapshot->transition_state) {
    case 0:
        snapshot->first_token = BeginConstantRangeTransition(0, 96, 16,
                                                             217, 217, 217);
        snapshot->second_token = BeginConstantRangeTransition(112, 144, 16,
                                                              217, 217, 217);
        snapshot->transition_state = 1;
        break;
    case 1: {
        void **first = &snapshot->first_token;
        void **second;
        if (IsTransitionTokenComplete(*first) == 0)
            break;
        second = &snapshot->second_token;
        if (IsTransitionTokenComplete(*second) == 0)
            break;
        ReleaseTransitionToken(*first);
        ReleaseTransitionToken(*second);
        snapshot->transition_state = 2;
        break;
    }
    case 2: {
        u8 pending;
        if (snapshot->mode == 0)
            pending = (u8)AdvanceZeroSnapshotMode(snapshot->operation_state);
        else
            pending = (u8)AdvanceOtherSnapshotMode(snapshot->operation_state);
        if (pending != 0)
            break;
        snapshot->first_token = BeginSavedRangeTransition(0, 96, 16,
                                                         snapshot->saved_first_range);
        snapshot->second_token = BeginSavedRangeTransition(112, 144, 16,
                                                          snapshot->saved_second_range);
        snapshot->transition_state = 3;
        break;
    }
    case 3: {
        CopyRoutine const *copy_cell;
        void **first = &snapshot->first_token;
        void **second;
        if (IsTransitionTokenComplete(*first) == 0)
            break;
        second = &snapshot->second_token;
        if (IsTransitionTokenComplete(*second) == 0)
            break;
        ReleaseTransitionToken(*first);
        ReleaseTransitionToken(*second);
        /* The native copy-cell address is materialized before copy arguments. */
        copy_cell = &gCopyRoutine;
        CallCopy(gLiveCopiedState, snapshot->saved_first_range, 512, *copy_cell);
        snapshot->transition_state = 4;
        break;
    }
    case 4:
        return 0;
    }
    return 1;
}
