#include "interfaces.h"

u32 ReadEffectPairBaseRate(volatile EffectRuleContext *context)
{
    void *actor, *target;
    actor = context->actor;
    target = context->target;
    return (u8)ResolutionRule_12F054(actor, target);
}
