#include "interfaces.h"
u32 ReadEffectFlagTwoConditionalRate(struct EffectRateContext *context) __asm__("EffectAuxiliary_001312B0");
u32 ReadEffectFlagTwoConditionalRate(struct EffectRateContext *context)
{
    if ((context->flags & 2) == 0)
        return 0;
    return (u8)CalculateExistingEffectRate(context);
}
