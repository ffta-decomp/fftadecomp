typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
typedef struct {u8 unknown[26];u16 amount;} Unit;
typedef struct {Unit *actor;Unit *previous;void *affected;u8 unknown12[26];u16 flags;} EffectContext;
u32 RandomWord(void) __asm__("RetailCall_08002804");
s32 Remainder(s32,s32) __asm__("RetailCall_08142950");

s32 ScaleTwoStageEffectAmount(EffectContext *context)
    __asm__("EffectAuxiliary_00131694");
s32 ScaleTwoStageEffectAmount(EffectContext *context)
{
    s32 ratio, amount;
    if (context->flags & 16)
        return context->previous->amount;
    {
        /* Normalize the actual helper return in its R0 working carrier. */
        register s32 normalized __asm__("r0") =
            (s16)Remainder((s16)RandomWord(), 257);
        __asm__("" : "+r" (normalized));
        ratio = normalized;
    }
    ratio += 128;
    amount = context->actor->amount;
    if (context->flags & 16)
        return amount;
    {
        /* Copy before the destructive modulo32 multiply, then signed shift. */
        register u32 product __asm__("r0") = (u32)amount;
        __asm__("" : "+r" (product));
        product *= (u32)ratio;
        amount = (s32)product >> 8;
    }
    if (amount < -999)
        amount = -999;
    if (amount > 999)
        amount = 999;
    {
        register u32 product __asm__("r0") = (u32)ratio;
        __asm__("" : "+r" (product));
        product *= (u32)amount;
        return (s32)product >> 8;
    }
}
