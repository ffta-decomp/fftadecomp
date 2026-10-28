#include "interfaces.h"

u32 ReadEffectHalvedConditionalRate(struct EffectRuleContext *context)
{
    s32 rate;

    rate = (u8)ResolutionCommonRule(context);
    if (rate <= 99)
        rate /= 2;
    return rate;
}
