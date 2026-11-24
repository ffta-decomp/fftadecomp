#include "abi/interfaces/0813091c_bindings.h"

u32 ReadEffectTargetProperty20(volatile EffectRuleContext *context)
{
    return EffectUnitProperty(context->target, 20);
}
