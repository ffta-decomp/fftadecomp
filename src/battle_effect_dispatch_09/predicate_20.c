#include "interfaces.h"

u32 TestEffectTargetSecondaryGate(volatile EffectRuleContext *context)
{
    if ((u8)EffectTargetField19IsZero(context->target)) return 0;
    return (u8)EffectTargetGateC8384(context->target) == 0;
}
