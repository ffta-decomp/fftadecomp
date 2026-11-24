#include "abi/interfaces/08132450_bindings.h"
void EffectCallback_00132450(struct EffectContext *context)
{
    EffectApplicationCall_08131DD4(context,3);
    if(!(context->flags&16)) SetUnitStateE8Bit3(context->unit,1);
}
