#include "abi/interfaces/08133394_bindings.h"
void EffectCallback_00133394(struct EffectContext *context)
{
    EffectApplicationCall_08131DD4(context,36);
    if(!(context->flags&16)) SetUnitStateECBit4(context->unit,1);
}
