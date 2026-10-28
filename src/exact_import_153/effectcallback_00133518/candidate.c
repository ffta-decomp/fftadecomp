#include "contract.h"

void EffectCallback_00133518(EffectContext *context)
{
    RecordEffectMetadata(context, 41);
    if ((context->flags & 0x10) == 0)
        SetUnitStateEDBit1(context->unit, 1);
}
