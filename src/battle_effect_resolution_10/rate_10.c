#include "interfaces.h"

u32 ReadEffectZeroArgumentRate(volatile EffectRuleContext *context)
{
    void *actor, *target;
    actor = context->actor;
    target = context->target;
    return (u8)ResolutionRule_12EF94(actor, target, 0, 0, 0);
}
