#include "interfaces.h"

u32 ReadEffectDescriptorRateDA0C(volatile EffectRuleContext *context)
{
    void *actor, *target;
    u32 code;
    actor = context->actor;
    target = context->target;
    code = EffectByte(context->descriptor, 1);
    return (u8)ResolutionRule_12DA0C(actor, target, code);
}
