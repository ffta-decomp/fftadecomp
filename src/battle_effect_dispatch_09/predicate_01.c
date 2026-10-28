#include "interfaces.h"

u32 TestEffectContextValue(volatile EffectRuleContext *context)
{
    if ((u8)EffectTargetField19IsZero(context->target)) return 0;
    return context->field08 != 0;
}
