#include "interfaces.h"
void EffectCallback_00132138(struct EffectContext *context)
{
    EffectApplicationCall_08131DD4(context,34);
    if(!(context->flags&16)) SetUnitStateECBit2(context->unit,1);
}
