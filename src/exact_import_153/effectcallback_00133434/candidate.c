#include "contract.h"

void EffectCallback_00133434(EffectContext *context)
{
    RecordEffectMetadata(context, 40);
    if ((context->flags & 0x10) == 0)
        SetUnitStateEDBit0(context->unit, 1);
}
