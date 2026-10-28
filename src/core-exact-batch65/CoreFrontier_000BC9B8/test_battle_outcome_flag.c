typedef unsigned char u8;
typedef unsigned int u32;

u32 IsBattleOutcomeFlagSet(const u8 *continuation)
    __asm__("CoreFrontier_000BC9B8");

/* The phase controller consumes only the zero/nonzero outcome of this byte. */
u32 IsBattleOutcomeFlagSet(const u8 *continuation)
{
    return continuation[369] != 0;
}
