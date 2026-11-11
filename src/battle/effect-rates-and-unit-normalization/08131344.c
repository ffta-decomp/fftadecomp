#include "battle/effect-rates-and-unit-normalization/interfaces/0813107c_bindings.h"

u32 ReadEffectUnsuppressedZeroArgumentRate(volatile EffectRuleContext *context)
{
    void *actor, *target;
    if ((u8)ResolutionRule_12F1CC(context->target)) return 0;
    actor = context->actor;
    target = context->target;
    if ((u8)EffectSuppressionGate(actor, target)) return 0;
    return (u8)ResolutionZeroRule(context);
}
