#include "interfaces.h"

/* Metadata records selection even when the unit update is suppressed. */
void EffectCallback_00132498(EffectContext *context)
{
    RecordEffectMetadata(context,2);
    if (!(context->flags & 0x10))
        SetUnitStateE8Bit2(context->effect_unit,1);
}
