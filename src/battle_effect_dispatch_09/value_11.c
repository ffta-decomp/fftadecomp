#include "interfaces.h"

u32 ReadEffectRandomCurrentQuarter(volatile EffectRuleContext *context)
{
    u32 quarter;
    s32 twice_quarter;

    if ((u8)EffectTargetGateCDA4C(context->target)) return 0;

    quarter = EffectHalf(context->target, 24) >> 2;
    twice_quarter = quarter << 1;
    if (context->flags & 16) return quarter + (twice_quarter >> 1);

    return (u32)EffectSignedRemainder((s16)EffectNextRandom(),
                                      twice_quarter + 1) + quarter;
}
