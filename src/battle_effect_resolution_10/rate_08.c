#include "interfaces.h"

u32 ReadEffectContextByteRate(volatile EffectRuleContext *context)
{
    void *actor, *target;
    u32 value;
    actor = context->actor;
    target = context->target;
    value = EffectByte(context, 36);
    return (u8)ResolutionRule_12D398(actor, target, value);
}
