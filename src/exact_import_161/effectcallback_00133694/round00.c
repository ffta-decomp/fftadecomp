#include "interfaces.h"

/* The preceding effect can set the second suppression bit, 0x100. */
void EffectCallback_00133694(struct EffectContext *context)
{
    EffectApplicationCall_081320E8(context);
    if (!(context->flags & 0x110)) {
        WriteUnitCounterDC(context->unit_at_8, 1);
    }
}
