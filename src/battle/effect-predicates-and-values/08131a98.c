#include "abi/interfaces/0813091c_bindings.h"

u32 ReadEffectTripleBase(volatile EffectRuleContext *context)
{
    s32 amount;
    amount = (s32)((u32)EffectBaseCalculation(context) * 3u);
    if (amount < -999) amount = -999;
    if (amount > 999) amount = 999;
    return amount;
}
