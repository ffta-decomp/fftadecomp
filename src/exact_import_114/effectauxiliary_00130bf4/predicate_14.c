#include "interfaces.h"

extern volatile u8 gEwramBase[];

u32 TestEffectGlobalMatchingResidue10(volatile EffectRuleContext *context)
{
    u8 global_residue;
    u8 target_residue;

    if ((u8)EffectTargetField19IsZero(context->target) != 0)
        return 0;

    global_residue = (u8)EffectUnsignedResidue(
        gEwramBase[0x2fbb], 10);
    target_residue = (u8)EffectUnsignedResidue(
        EffectByte(context->target, 9), 10);
    return global_residue == target_residue;
}
