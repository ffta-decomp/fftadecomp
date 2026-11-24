#include "abi/interfaces/0813091c_bindings.h"

u32 TestEffectInverseTypeNine(volatile EffectRuleContext *context)
{
    if ((u8)EffectTargetField19IsZero(context->target)) return 0;
    return (u8)EffectPredicateNotTypeNine(context) == 0;
}
