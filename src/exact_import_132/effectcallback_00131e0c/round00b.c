#include "interfaces.h"
void EffectCallback_00131E0C(struct EffectContext *context)
{
    EffectApplicationCall_08131DD4(context,1);
    if(!(context->flags&16)) SetUnitStateE8Bit1(context->unit,1);
}
