#include "battle/effect-rates-and-unit-normalization/interfaces/0813107c_bindings.h"

u32 ReadEffectPairRateD388(volatile EffectRuleContext *context)
{
    void *actor, *target;
    actor = context->actor;
    target = context->target;
    return (u8)ResolutionRule_12D388(actor, target);
}
