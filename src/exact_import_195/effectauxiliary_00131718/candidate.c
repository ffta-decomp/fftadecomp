#include "interfaces.h"
u32 ReadEffectRandomTargetByte10(struct EffectRandomContext *context)
{
    s32 random_value;
    u32 bound;
    if (16 & context->flags)
        return context->target->value;
    if (context->target->value == 0)
        return 0;
    random_value = (s16)EffectNextRandom();
    /* RNG is opaque at this boundary: reload the target and its bound. */
    bound = context->target->value;
    return (u32)EffectSignedRemainder(random_value, bound) + 1u;
}
