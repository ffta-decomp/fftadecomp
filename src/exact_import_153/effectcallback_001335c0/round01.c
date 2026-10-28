#include "interfaces.h"

/* The counter update reloads the unit after the state setter. */
void EffectCallback_001335C0(EffectContext *context)
{
    RecordEffectMetadata(context,25);
    if (!(context->flags & 0x10)) {
        SetUnitStateEBBit1(context->effect_unit,1);
        WriteUnitCounterDE(context->effect_unit,3);
    }
}
