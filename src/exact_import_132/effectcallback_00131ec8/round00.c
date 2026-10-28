#include "interfaces.h"
void EffectCallback_00131EC8(struct EffectContext *context)
{
    EffectApplicationCall_08131DD4(context,4);
    if(!(context->flags&16)) SetUnitStateE8Bit4(context->unit,1);
}
