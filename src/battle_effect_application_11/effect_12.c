#include "interfaces.h"

void ApplyOrReplaceUnitStatusSlot12(volatile ApplicationContext *context)
{
    /* The Thumb test shifts the helper result left by 24, so it tests low-byte nonzero. */
    if ((u8)EffectResolutionCall_080CD8FC(context->affected)) {
        if (context->flags & 16) return;
        SetUnitStateE8Bit4(context->affected, 0);
        ((ApplicationContext *)(void *)context)->flags |= 256;
    } else {
        EffectApplicationCall_08131DD4(context, 8);
        if (context->flags & 16) return;
        SetUnitStateE9Bit0(context->affected, 1);
    }
}
