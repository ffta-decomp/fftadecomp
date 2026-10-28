#include "interfaces.h"

/* Symbol-only binding for the descriptor table address loaded by the original. */
extern const ApplicationDescriptor gEffectApplicationDescriptors[]
    __asm__("gEffectApplicationDescriptors");
__asm__(".global gEffectApplicationDescriptors\n.set gEffectApplicationDescriptors, 0x083a87b0");

void EffectCallback_0013233C(ApplicationContext *context)
{
    union { u32 frame_word; s16 value; } effect_output;
    u16 threshold;
    s32 roll;
    u32 random_word;
    u32 comparison_threshold;
    u32 comparison_roll;
    s32 selected_effect;

    if ((u8)EffectResolutionCall_080CD8FC(context->affected) != 0) {
        SetUnitStateE8Bit4(context->affected, 0);
        goto mark_rejected;
    }

    random_word = EffectApplicationCall_0812D7FC(
        context->actor, context->affected, 0, &effect_output.value);
    threshold = (u16)((s16)random_word * 10);
    roll = (s16)IT03_SignedRemainder((s16)IP03_RandomWord(), 1001);
    comparison_threshold = (u32)threshold << 16;
    comparison_roll = (u32)(u16)roll << 16;
    if ((s32)comparison_threshold < (s32)comparison_roll) {
        goto mark_rejected;
    }

    /* Original signed stack-read scratch operation; surrounding logic stays C. */
    __asm__("movs r3, #0\n\tldrsh %0, [%1, r3]"
            : "=l"(selected_effect)
            : "l"(&effect_output.value), "m"(effect_output.value)
            : "r3", "cc");
    if (selected_effect <= 0) {
        ApplicationHalf(context->affected, 24) = 1;
        return;
    }

    {
        gEffectApplicationDescriptors[effect_output.value].apply(context);
    }
    return;

mark_rejected:
    {
        ApplicationContext *ram_context;
        ram_context = (ApplicationContext *)(void *)context;
        ram_context->flags = (u16)(0x0100 | ram_context->flags);
    }
}
