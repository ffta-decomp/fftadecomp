#include "interfaces.h"

u32 TestEffectIneligibleMatchingResidue10(volatile EffectRuleContext *context)
{
    u8 actor_residue;
    u8 target_residue;

    if ((u8)EffectTargetField19IsZero(context->target) != 0)
        return 0;
    if ((u8)EffectTargetGate1308F4(context->target) == 0)
        return 0;

    actor_residue = (u8)EffectUnsignedResidue(
        EffectByte(context->actor, 9), 10);
    target_residue = (u8)EffectUnsignedResidue(
        EffectByte(context->target, 9), 10);
    return actor_residue == target_residue;
}
