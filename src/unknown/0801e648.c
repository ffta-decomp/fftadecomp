typedef unsigned char u8;
typedef unsigned int u32;
struct PreviousChannels { u8 first; u8 second; };
extern struct PreviousChannels gPreviousChannels;
__asm__(".global gPreviousChannels\n.set gPreviousChannels,0x02007f40");
u32 IsPreviousChannel0Available(void) __asm__("CoreFrontier_0001E648");
u32 IsPreviousChannel0Available(void)
{
    return (gPreviousChannels.first >> 7) ^ 1;
}
