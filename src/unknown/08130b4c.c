#include "abi/interfaces/08130b4c_effect_remainder.h"

u32 TestEffectTargetRemainderThreeZero(struct EffectPair *context)
{
    u32 passes;
    if ((u8)UnitField19IsZero(context->target) != 0)
        return 0;
    passes = 0;
    if ((u8)UnsignedEffectRemainder(context->target->field_09, 3) == 0)
        passes = 1;
    return passes;
}
