#include "effect_matching.h"

u32 TestEffectMatchingProperty(struct EffectPair *context)
{
    u32 actor_property;
    if ((u8)UnitField19IsZero(context->target) != 0)
        return 0;
    actor_property = (u8)UnitStatusBit15(context->actor);
    /* Reload the target after the actor query, as at 08130ce4. */
    return (u8)UnitStatusBit15(context->target) == actor_property;
}
