#include "abi/interfaces/0813091c_bindings.h"

u32 ReadEffectTargetHalfword1E(volatile EffectRuleContext *context)
{
    return EffectHalf(context->target, 30);
}
