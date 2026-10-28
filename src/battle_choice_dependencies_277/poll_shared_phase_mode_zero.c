typedef unsigned char u8;
typedef unsigned int u32;
extern u32 AdvanceSharedPhase(void *context, u8 mode);
__asm__(".global AdvanceSharedPhase\n.thumb_set AdvanceSharedPhase,0x080c7079");

/* Preserve the actual shared context, mode and low-byte polling result. */
u32 PollSharedPhaseModeZero(void)
{
    return (u8)AdvanceSharedPhase((void *)0x020158b0, 0);
}
