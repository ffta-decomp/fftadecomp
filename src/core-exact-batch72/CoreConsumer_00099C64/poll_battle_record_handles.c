typedef unsigned char u8;
typedef unsigned int u32;
struct BattleHandleContext { u8 unaccessed[68]; void *primary; u32 unaccessed_state; void *secondary[2]; };
extern u32 QueryBattleHandleProgress(const void *handle);
u32 PollBattleRecordHandles(struct BattleHandleContext *context)
{
    void *handle = context->primary;
    void **slot;
    int ordinal;
    if (handle != 0 && QueryBattleHandleProgress(handle) == 0)
        return 0;
    ordinal = 0;
    slot = context->secondary;
    do {
        handle = *slot;
        if (handle != 0 && QueryBattleHandleProgress(handle) == 0)
            return 0;
        slot++;
        ordinal++;
    } while (ordinal <= 1);
    return 1;
}
asm(".global QueryBattleHandleProgress\n.thumb_set QueryBattleHandleProgress,0x08021C5D\n");
