#include "abi/interfaces/0813091c_bindings.h"

u32 ReadEffectBaseLimitedByProperty21(volatile EffectRuleContext *context)
{
    s32 amount;
    amount = EffectBaseCalculation(context);
    if ((s32)(EffectUnitProperty(context->target, 21) - (u32)amount) < 0)
    amount = EffectUnitProperty(context->target, 21);
    return amount;
}
