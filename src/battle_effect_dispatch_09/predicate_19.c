#include "interfaces.h"

u32 TestEffectEligibleTarget(volatile EffectRuleContext *context)
{
    if ((u8)EffectTargetField19IsZero(context->target)) return 0;
    return (u8)EffectTargetGate1308F4(context->target) == 0;
}
