#include "interfaces.h"

u32 ReadEffectDescriptorCodeRate(volatile EffectRuleContext *context)
{
    void *actor, *target;
    u32 code;
    actor = context->actor;
    target = context->target;
    code = EffectByte(context->descriptor, 1);
    return (u8)ResolutionRule_12DAEC(actor, target, code);
}
