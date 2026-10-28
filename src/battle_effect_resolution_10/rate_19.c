#include "interfaces.h"

u32 ReadEffectTargetByteRate(volatile EffectRuleContext *context)
{
    void *target;
    u32 value;
    target = context->target;
    value = EffectByte(context, 36);
    return (u8)ResolutionRule_12D99C(target, value);
}
