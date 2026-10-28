#include "interfaces.h"

/* The original reloads both unit pointers after the state setter. */
void EffectCallback_0013363C(struct EffectContext *context)
{
    if (!(context->flags & 0x10)) {
        SetUnitStateEDBit3(context->unit_at_0, 1);
        WriteUnitCounterE6(context->unit_at_0, context->unit_at_8->byte104);
    }
}
