typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct EffectRateContext { u8 unknown_00[38]; u16 flags; };
typedef char FlagsOffset[((u32)&((struct EffectRateContext *)0)->flags == 38) ? 1 : -1];

u32 ReadEffectFlagRateSlot7(struct EffectRateContext *context)
    __asm__("EffectAuxiliary_001310E4");
u32 ReadEffectFlagRateSlot7(struct EffectRateContext *context)
{
    register u32 rate __asm__("r0");
    if (context->flags & 2)
        rate = 100;
    else
        rate = 0;
    /* Both paths define the physical return carrier before the shared join. */
    __asm__("" : "+r" (rate));
    return rate;
}
