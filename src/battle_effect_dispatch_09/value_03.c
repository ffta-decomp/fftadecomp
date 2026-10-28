#include "interfaces.h"

u32 ReadEffectMaximumUnlessExcluded(volatile EffectRuleContext *context)
{
    if ((u8)EffectTargetGateCDA4C(context->target)) return 0;
    return 999;
}
