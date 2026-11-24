#include "battle/effect-rates-and-unit-normalization/interfaces/0813107c_bindings.h"

u32 ReadEffectPairRate(volatile EffectRuleContext *context)
{
    void *actor, *target;
    actor = context->actor;
    target = context->target;
    return (u8)ResolutionRule_12DAB8(actor, target);
}
