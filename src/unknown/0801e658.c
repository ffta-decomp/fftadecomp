typedef unsigned char u8;
typedef unsigned int u32;
struct PreviousChannels { u8 first; u8 second; };
extern struct PreviousChannels gPreviousChannels;
__asm__(".global gPreviousChannels\n.set gPreviousChannels,0x02007f40");
u32 IsPreviousChannel1Available(void) __asm__("CoreFrontier_0001E658");
u32 IsPreviousChannel1Available(void)
{
    return (gPreviousChannels.second >> 7) ^ 1;
}
