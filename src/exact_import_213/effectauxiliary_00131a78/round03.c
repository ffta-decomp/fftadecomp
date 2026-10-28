#include "interfaces.h"
u32 ReadQuarterAbsoluteEffectMagnitude(struct EffectMagnitudeContext *context) __asm__("EffectAuxiliary_00131A78");
u32 ReadQuarterAbsoluteEffectMagnitude(struct EffectMagnitudeContext *context)
{
    s32 quarter;
    s32 magnitude = context->amount;
    if (magnitude < 0)
        magnitude = -magnitude;
    quarter = magnitude / 4;
    if (quarter == 0)
        quarter = 1;
    return quarter;
}
