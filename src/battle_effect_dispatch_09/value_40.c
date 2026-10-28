#include "interfaces.h"

u32 ReadEffectTargetProperty20(volatile EffectRuleContext *context)
{
    return EffectUnitProperty(context->target, 20);
}
