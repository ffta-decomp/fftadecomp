#include "interfaces.h"

u32 TestEffectEligibleRemainderFiveZero(volatile EffectRuleContext *context)
{
    u32 eligible;

    if ((u8)EffectTargetField19IsZero(context->target)) return 0;
    if ((u8)EffectTargetGate1308F4(context->target)) return 0;

    eligible = 0;
    if ((u8)EffectUnsignedResidue(EffectByte(context->target, 9), 5) == 0) {
        eligible = 1;
    }
    return eligible;
}
