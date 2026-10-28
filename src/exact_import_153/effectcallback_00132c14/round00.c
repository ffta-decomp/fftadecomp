#include "interfaces.h"

/* Metadata is recorded even when the unit-state write is suppressed. */
void EffectCallback_00132C14(struct EffectContext *context)
{
    EffectApplicationCall_08131DD4(context, 0x21);
    if (!(context->flags & 0x10)) {
        SetUnitStateECBit1(context->affected_unit, 1);
    }
}
