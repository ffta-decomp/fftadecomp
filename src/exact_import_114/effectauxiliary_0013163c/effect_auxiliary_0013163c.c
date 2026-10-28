#include "interfaces.h"

u32 ReadEffectRandomizedBase(volatile EffectRuleContext *context)
{
    s32 amount, base, factor;
    base = EffectBaseCalculation(context);
    if (context->flags & 16) goto return_base;
    factor = (s16)EffectSignedRemainder((s16)EffectNextRandom(), 257) + 128;
    amount = base;
    base = (s32)((u32)base * (u32)factor) >> 8;
    if (base == 0) base = amount;
    if (base < -999) base = -999;
    if (base > 999) base = 999;
    return base;
return_base:
    return base;
}
