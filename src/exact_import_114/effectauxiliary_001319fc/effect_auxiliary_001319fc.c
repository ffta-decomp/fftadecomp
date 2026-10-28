#include "interfaces.h"

u32 ReadEffectSignedBaseLimitedByProperty19(volatile EffectRuleContext *context)
{
    s32 amount;
    u32 magnitude;
    amount = EffectBaseCalculation(context);
    if (amount < 0) amount = 0;
    if ((u8)EffectTargetSignGate(context->target)) amount = (s32)(0u - (u32)amount);
    magnitude = 0;
    {
        u32 property_value = EffectUnitProperty(context->target, 19);
        magnitude = amount < 0 ? 0u - (u32)amount : (u32)amount;
        if (property_value < magnitude) {
        if (amount < 0) amount = (s32)(0u - EffectUnitProperty(context->target, 19));
        else amount = EffectUnitProperty(context->target, 19);
        }
    }
    return amount;
}
