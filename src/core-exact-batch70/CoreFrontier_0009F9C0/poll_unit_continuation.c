typedef unsigned char u8;
typedef unsigned int u32;

/* The real continuation retains all unit-state and callback effects. */
extern u32 AdvanceUnitContinuation(void *continuation);
__asm__(".global AdvanceUnitContinuation\n.thumb_set AdvanceUnitContinuation,0x0809ed39\n");

u8 PollBattleUnitContinuationByte(void *continuation)
{
    return (u8)AdvanceUnitContinuation(continuation);
}
