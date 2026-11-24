typedef unsigned char u8;
typedef unsigned int u32;
extern u32 PollUnitProgressContext(void *result);
__asm__(".global PollUnitProgressContext\n.thumb_set PollUnitProgressContext,0x080a7219\n");
u8 PollUnitProgressResults(void *result) __asm__("CoreFrontier_000A8958");

/* The battle continuation observes the low byte of the real stateful poll. */
u8 PollUnitProgressResults(void *result)
{
    return (u8)PollUnitProgressContext(result);
}
