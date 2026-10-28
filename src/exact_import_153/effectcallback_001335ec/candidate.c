#include "contract.h"

void EffectCallback_001335EC(EffectContext *context)
{
    RecordEffectMetadata(context, 24);
    if ((context->flags & 0x10) == 0) {
        SetUnitStateEBBit0(context->unit, 1);
        WriteUnitByteDD(context->unit, 3);
    }
}
