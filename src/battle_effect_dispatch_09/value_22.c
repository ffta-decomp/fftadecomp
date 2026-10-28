#include "interfaces.h"

u32 ReadEffectTargetHalfword1E(volatile EffectRuleContext *context)
{
    return EffectHalf(context->target, 30);
}
