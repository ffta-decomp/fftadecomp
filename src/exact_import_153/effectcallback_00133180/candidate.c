#include "contract.h"

void EffectCallback_00133180(EffectContext *context)
{
    RecordEffectMetadata(context, 12);
    if ((context->flags & 0x10) == 0)
        SetUnitStateE9Bit4(context->unit, 1);
}
