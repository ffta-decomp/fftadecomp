#include "interfaces.h"

u32 ReadEffectFlaggedConditionalRateSlot24(struct EffectRateContext *context)
{
    u32 result;

    if (1 & context->flags)
        result = (u8)ResolutionCommonRule(context);
    else
        result = 0;
    return result;
}
