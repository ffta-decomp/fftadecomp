#include "abi/interfaces/081334f4_bindings.h"

void EffectCallback_001334F4(EffectContext *context)
{
    RecordEffectMetadata(context, 42);
    if ((context->flags & 0x10) == 0)
        SetUnitStateEDBit2(context->unit, 1);
}
