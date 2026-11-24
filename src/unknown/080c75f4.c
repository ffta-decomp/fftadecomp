typedef unsigned char u8;
typedef unsigned int u32;
extern u8 BattleContinuationStart[], BattleContinuationEnd[];
extern u32 QueryBattleContinuation(const void *start, const void *end);
__asm__(".global BattleContinuationStart\n.set BattleContinuationStart,0x08149a60\n.global BattleContinuationEnd\n.set BattleContinuationEnd,0x08149a68\n.global QueryBattleContinuation\n.thumb_set QueryBattleContinuation,0x08003b1d");
/* Selector52 consumes the low byte, not a normalized full-word predicate. */
u32 QueryBattleContinuationReady(void)
{
    return (u8)QueryBattleContinuation(BattleContinuationStart, BattleContinuationEnd);
}
