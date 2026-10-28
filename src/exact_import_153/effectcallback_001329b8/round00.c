#include "interfaces.h"

/* Record the paired effect choices even when unit-state mutation is suppressed. */
void EffectCallback_001329B8(struct EffectContext *context)
{
    EffectApplicationCall_08131DD4(context, 0x28);
    EffectApplicationCall_08131DD4(context, 0x2A);
    if (!(context->flags & 0x10)) {
        SetUnitStateEDBit0(context->affected_unit, 1);
        SetUnitStateEDBit2(context->affected_unit, 1);
    }
}
