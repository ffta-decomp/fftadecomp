#include "interfaces.h"
u32 EffectUnitsHaveDifferentProperty(struct EffectPredicateContext *context) __asm__("EffectAuxiliary_00130C44");
u32 EffectUnitsHaveDifferentProperty(struct EffectPredicateContext *context)
{
    u8 actor_property;
    if ((u8)QueryTargetUnitGate(context->target) != 0)
        return 0;
    actor_property = (u8)ReadUnitComparisonProperty(context->actor);
    return actor_property != (u8)ReadUnitComparisonProperty(context->target);
}
