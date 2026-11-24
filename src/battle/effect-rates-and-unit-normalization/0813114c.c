#include "battle/effect-rates-and-unit-normalization/interfaces/0813107c_bindings.h"

u32 ReadEffectPairRateF068(volatile EffectRuleContext *context)
{
    void *actor, *target;
    actor = context->actor;
    target = context->target;
    return (u8)ResolutionRule_12F068(actor, target);
}
