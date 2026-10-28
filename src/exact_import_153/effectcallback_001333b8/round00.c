#include "interfaces.h"
void EffectCallback_001333B8(struct EffectContext *context)
{
    EffectApplicationCall_08131DD4(context,14);
    if(!(context->flags&16)) SetUnitStateE9Bit6(context->unit,1);
}
