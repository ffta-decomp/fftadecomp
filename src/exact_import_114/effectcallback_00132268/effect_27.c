#include "interfaces.h"

void ApplyOrReplaceUnitStatusSlot27(volatile ApplicationContext *context)
{
    /* Retail loads flags in r1, then merges into r0; these bindings preserve that live pair. */
    register u16 previous_flags __asm__("r1");
    register u16 updated_flags __asm__("r0");
    u16 *flags_field;

    /* Retail reads context+0x26 once after the helper, then writes it without another call. */
    flags_field = (u16 *)(void *)&context->flags;

    if ((u8)EffectResolutionCall_080CD8FC(context->affected)) {
        SetUnitStateE8Bit4(context->affected, 0);
        previous_flags = *flags_field;
        updated_flags = 256 | previous_flags;
        *flags_field = updated_flags;
    } else {
        EffectApplicationCall_08131DD4(context, 7);
        if (context->flags & 16) return;
        SetUnitStateE8Bit7(context->affected, 1);
    }
}
