typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
typedef struct {void *actor;u8 unknown04[34];u16 flags;} EffectContext;
u32 NextRandom(void) __asm__("RetailCall_08002804");
s32 SignedRemainder(s32,s32) __asm__("IT03_SignedRemainder");
u32 UnitProperty(void*,u32) __asm__("RetailCall_080c7ea4");
typedef char CheckFlags[(u32)&((EffectContext*)0)->flags==38?1:-1];

u32 VaryUnitPropertyAmount(EffectContext *context)
    __asm__("EffectAuxiliary_0013158C");
u32 VaryUnitPropertyAmount(EffectContext *context)
{
    u32 scaled;
    if ((context->flags & 16) == 0) {
        /* The normal-path carrier receives the signed narrowed helper value. */
        register s32 factor __asm__("r4") =
            (s16)SignedRemainder((s16)NextRandom(), 257);
        __asm__("" : "+r" (factor));
        factor += 128;
        {
            /* The original destructive multiply works in the helper's R0
             * result carrier; the shifted output then returns to R4. */
            register u32 product __asm__("r0") =
                UnitProperty(context->actor, 20);
            __asm__("" : "+r" (product));
            product *= (u32)factor;
            factor = product >> 8;
        }
        /* The original shifted result survives in R4 before the R0 return. */
        __asm__("" : "+r" (factor));
        scaled = (u32)factor;
    } else {
        scaled = UnitProperty(context->actor, 20);
    }
    return scaled;
}
