#include "interfaces.h"
u32 IsEffectTargetGateClear(struct EffectPredicateContext *context) __asm__("EffectAuxiliary_00130A94");
u32 IsEffectTargetGateClear(struct EffectPredicateContext *context)
{
    if ((u8)QueryTargetUnitGate(context->target) != 0)
        return 0;
    return 1;
}
