#include "interfaces.h"
void EffectCallback_00132040(struct EffectContext *context)
{
    EffectApplicationCall_08131DD4(context,16);
    if(!(context->flags&16)) SetUnitStateEABit0(context->unit,1);
}
