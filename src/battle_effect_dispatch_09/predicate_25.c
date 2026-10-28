#include "interfaces.h"

u32 TestEffectMatchingPropertyAfterStatusGate(volatile EffectRuleContext *context)
{
    if ((u8)EffectTargetGateCDBCC(context->target)) return 0;
    return (u8)EffectPredicateSameProperty(context);
}
