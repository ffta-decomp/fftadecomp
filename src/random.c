#include "random.h"

#define RANDOM_SEED (*(volatile u32 *)0x030034b0)

u32 NextRandom15(void)
{
    /* The retail routine is the upper 15 bits of a 32-bit LCG update. */
    u32 next = RANDOM_SEED * 0x41c64e6d + 0x3039;
    RANDOM_SEED = next;
    return (next << 1) >> 17;
}

void SeedRandom(u32 seed)
{
    RANDOM_SEED = seed;
}

volatile u32 *GetRandomSeedAddress(void)
{
    return (volatile u32 *)0x030034b0;
}
