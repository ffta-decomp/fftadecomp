#include "interfaces.h"

void ApplyOrReplaceUnitStatusSlot35(volatile ApplicationContext *context)
{
    if ((u8)EffectResolutionCall_080CD8FC(context->affected)) {
        if (context->flags & 16) return;
        SetUnitStateE8Bit4(context->affected, 0);
        ((ApplicationContext *)(void *)context)->flags |= 256;
    } else {
        EffectApplicationCall_08131DD4(context, 10);
        if (context->flags & 16) return;
        SetUnitStateE9Bit2(context->affected, 1);
    }
}
