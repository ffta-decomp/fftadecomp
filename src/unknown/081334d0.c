#include "abi/interfaces/081334d0_bindings.h"

void EffectCallback_001334D0(EffectContext *context)
{
    RecordEffectMetadata(context, 38);
    if ((context->flags & 0x10) == 0)
        SetUnitStateECBit6(context->unit, 1);
}
