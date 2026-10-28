#include "interfaces.h"

/* Metadata is recorded even when the unit-state write is suppressed. */
void EffectCallback_00132C94(struct EffectContext *context)
{
    EffectApplicationCall_08131DD4(context, 0xF);
    if (!(context->flags & 0x10)) {
        SetUnitStateE9Bit7(context->affected_unit, 1);
    }
}
