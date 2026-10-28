#include "interfaces.h"

u32 ReadEffectDoubleBase(volatile EffectRuleContext *context)
{
    s32 amount;
    amount = (s32)((u32)EffectBaseCalculation(context) << 1);
    if (amount < -999) amount = -999;
    if (amount > 999) amount = 999;
    return amount;
}
