#include "interfaces.h"

u32 ReadEffectQuadrupleBase(volatile EffectRuleContext *context)
{
    s32 amount;
    amount = (s32)((u32)EffectBaseCalculation(context) << 2);
    if (amount < -999) amount = -999;
    if (amount > 999) amount = 999;
    return amount;
}
