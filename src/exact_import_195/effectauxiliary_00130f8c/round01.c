#include "interfaces.h"
u32 IsEffectTargetEligibilityGateClear(struct EffectPredicateContext *context) __asm__("EffectAuxiliary_00130F8C");
u32 IsEffectTargetEligibilityGateClear(struct EffectPredicateContext *context)
{
    if ((u8)QueryTargetEligibilityGate(context->target) != 0)
        return 0;
    return 1;
}
