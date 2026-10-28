#include "interfaces.h"

u32 TestEffectSameUnit(volatile EffectRuleContext *context)
{
    if ((u8)EffectTargetField19IsZero(context->target)) return 0;
    return context->actor == context->target;
}
