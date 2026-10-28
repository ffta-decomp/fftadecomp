#include "interfaces.h"

void ApplyOrReplaceUnitStatusSlot22(volatile ApplicationContext *context)
{
    if ((u8)EffectResolutionCall_080CD8FC(context->affected)) {
        SetUnitStateE8Bit4(context->affected, 0);
        ((ApplicationContext *)(void *)context)->flags |= 256;
    } else {
        EffectApplicationCall_08131DD4(context, 31);
        if (context->flags & 16) return;
        SetUnitStateEBBit7(context->affected, 1);
        WriteUnitCounterE4(context->affected, 3);
    }
}
