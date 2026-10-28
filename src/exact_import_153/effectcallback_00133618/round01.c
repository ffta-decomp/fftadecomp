#include "interfaces.h"

/* Metadata records selection even when the unit update is suppressed. */
void EffectCallback_00133618(EffectContext *context)
{
    RecordEffectMetadata(context,13);
    if (!(context->flags & 0x10))
        SetUnitStateE9Bit5(context->effect_unit,1);
}
