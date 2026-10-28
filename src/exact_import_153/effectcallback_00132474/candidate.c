#include "contract.h"

void EffectCallback_00132474(EffectContext *context)
{
    RecordEffectMetadata(context, 5);
    if ((context->flags & 0x10) == 0)
        SetUnitStateE8Bit5(context->unit, 1);
}
