typedef unsigned int u32;

/* The real continuation retains its implicit context and delegated effects. */
extern u32 PollBattleActionContinuation(void *record);
__asm__(".global PollBattleActionContinuation\n.thumb_set PollBattleActionContinuation,0x080a5b99\n");

u32 PollBattleActionRecord(void *record)
{
    return PollBattleActionContinuation(record);
}
