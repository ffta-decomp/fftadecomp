#include "interfaces.h"

u32 ReadEffectDescriptorRateD2F0(volatile EffectRuleContext *context)
{
    void *actor, *target;
    u32 code;
    actor = context->actor;
    target = context->target;
    code = EffectByte(context->descriptor, 1);
    return (u8)ResolutionRule_12D2F0(actor, target, code);
}
