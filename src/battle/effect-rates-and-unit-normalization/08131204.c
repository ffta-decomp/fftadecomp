#include "battle/effect-rates-and-unit-normalization/interfaces/0813107c_bindings.h"

u32 ReadEffectTargetByteRate(volatile EffectRuleContext *context)
{
    void *target;
    u32 value;
    target = context->target;
    value = EffectByte(context, 36);
    return (u8)ResolutionRule_12D99C(target, value);
}
