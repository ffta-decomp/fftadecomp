#include "interfaces.h"

u32 ReadEffectPairRateD388(volatile EffectRuleContext *context)
{
    void *actor, *target;
    actor = context->actor;
    target = context->target;
    return (u8)ResolutionRule_12D388(actor, target);
}
