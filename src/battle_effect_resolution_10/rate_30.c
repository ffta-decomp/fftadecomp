#include "interfaces.h"

u32 ReadEffectPointDependentRate(volatile EffectRuleContext *context)
{
    void *target;
    s32 x, y;
    target = context->target;
    x = (s8)EffectByte(target, 246);
    y = (s8)EffectByte(target, 247);
    if (!(u8)ResolutionPointGate(target, x, y)) return 0;
    return (u8)ResolutionCommonRule(context);
}
