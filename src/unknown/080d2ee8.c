/* Original 0x080D2EE8: choose the state-12 stage reward amount.
 * Keep the legacy export; proposed name: ChooseStageRewardAmount.
 * The RNG result is signed low16 before signed remainder, and the result
 * is returned as a zero-extended halfword. Existing helpers are reused. */
typedef unsigned short u16;
typedef signed short s16;
extern int RetailCall_08002804(void);
extern int RetailCall_08142950(int dividend, int divisor);
unsigned int CoreDependency29_000D2EE8(void)
{
    int sample = (s16)RetailCall_08002804();
    int amount = RetailCall_08142950(sample, 2000);
    return (u16)(amount + 1000);
}
