#include "interfaces.h"

u32 ReadEffectPairRateF068(volatile EffectRuleContext *context)
{
    void *actor, *target;
    actor = context->actor;
    target = context->target;
    return (u8)ResolutionRule_12F068(actor, target);
}
