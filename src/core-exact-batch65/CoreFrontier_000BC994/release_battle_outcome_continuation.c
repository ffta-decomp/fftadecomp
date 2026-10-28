typedef unsigned int u32;
typedef void (*ClearBattleContinuationBytes)(void *, u32);
extern void ReleaseBattleContinuationBytes(void *continuation);
__asm__(".global ReleaseBattleContinuationBytes\n.thumb_set ReleaseBattleContinuationBytes,0x08022855\n"
        ".global _call_via_r2\n.thumb_set _call_via_r2,0x0814224d\n");

void ReleaseBattleOutcomeContinuation(void *continuation)
    __asm__("CoreFrontier_000BC994");

/* The phase controller captures the outcome before clearing this record. */
void ReleaseBattleOutcomeContinuation(void *continuation)
{
    (*(ClearBattleContinuationBytes *)0x0836d4b8)(continuation, 456);
    ReleaseBattleContinuationBytes(continuation);
}
