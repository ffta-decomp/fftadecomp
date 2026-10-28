#include "interfaces.h"

/* Metadata records selection even when the unit update is suppressed. */
void EffectCallback_00133458(EffectContext *context)
{
    RecordEffectMetadata(context,39);
    if (!(context->flags & 0x10))
        SetUnitStateECBit7(context->effect_unit,1);
}
