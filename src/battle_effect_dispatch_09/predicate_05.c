#include "interfaces.h"

u32 ReadEffectTargetGateAfterTypeCheck(volatile EffectRuleContext *context)
{
    if ((u8)EffectTargetGate1308F4(context->target)) return 0;
    return (u8)EffectTargetField19IsZero(context->target);
}
