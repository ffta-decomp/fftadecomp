#include "interfaces.h"

/* Both metadata choices precede the single conditional unit update. */
void EffectCallback_00132520(EffectContext *context)
{
    RecordEffectMetadata(context,17);
    RecordEffectMetadata(context,34);
    if (!(context->flags & 0x10))
        SetUnitStateEABit1(context->effect_unit,1);
}
