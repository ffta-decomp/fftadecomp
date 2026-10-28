#include "interfaces.h"

u32 ReadEffectHalfTargetProperty20(volatile EffectRuleContext *context)
{
    s32 amount;
    amount = (s32)(EffectUnitProperty(context->target, 20) >> 1);
    if (amount <= 0)
        return 1;
    return (u32)amount;
}
