#include "interfaces.h"

u32 ReadEffectQuarterCurrent(volatile EffectRuleContext *context)
{
    s32 amount;
    if ((u8)EffectTargetGateCDA4C(context->target)) return 0;
    amount = EffectHalf(context->target, 24) >> 2;
    if (amount > 0)
        return amount;
    return 1;
}
