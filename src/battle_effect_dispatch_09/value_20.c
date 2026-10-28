#include "interfaces.h"

u32 ReadEffectTargetMaximum(volatile EffectRuleContext *context)
{
    if ((u8)EffectTargetGateCDA4C(context->target)) return 0;
    return EffectHalf(context->target, 26);
}
