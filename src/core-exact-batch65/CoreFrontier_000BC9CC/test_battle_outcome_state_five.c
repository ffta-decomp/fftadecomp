typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

u32 IsBattleOutcomeStateFive(const u8 *continuation)
    __asm__("CoreFrontier_000BC9CC");

/* Selector24 waits for this exact observed state before advancing its continuation. */
u32 IsBattleOutcomeStateFive(const u8 *continuation)
{
    if (*(const u16 *)(continuation + 384) == 5)
        return 1;
    return 0;
}
