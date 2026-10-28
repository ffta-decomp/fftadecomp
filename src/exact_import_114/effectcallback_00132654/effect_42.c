#include "interfaces.h"

void EffectCallback_00132654(volatile ApplicationContext *context)
{
    u16 prior_flags;
    if ((u8)EffectResolutionCall_080CD8FC(context->affected)) {
        if (context->flags & 16) return;
        SetUnitStateE8Bit4(context->affected, 0);
        ((ApplicationContext *)context)->flags |= 256;
    } else {
        EffectApplicationCall_08131DD4(context, 20);
        if (context->flags & 16) return;
        SetUnitStateEABit4(context->affected, 1);
        WriteUnitCounterD9(context->affected, 3);
    }
}
