#include "interfaces.h"

u32 ReadEffectHalvedBase(volatile EffectRuleContext *context)
{
    s32 amount, magnitude;
    amount = EffectBaseCalculation(context);
    magnitude = amount < 0 ? (s32)(0u - (u32)amount) : amount;
    if (magnitude > 1) amount >>= 1;
    if (amount < -999) amount = -999;
    if (amount > 999) amount = 999;
    return amount;
}
