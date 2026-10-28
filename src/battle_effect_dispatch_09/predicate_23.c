#include "interfaces.h"

u32 TestEffectInverseSecondaryGate(volatile EffectRuleContext *context)
{
    if ((u8)EffectTargetField19IsZero(context->target)) return 0;
    /* The nested rule repeats the first gate; it may observe changed context. */
    return (u8)EffectPredicateTargetGate(context) == 0;
}
