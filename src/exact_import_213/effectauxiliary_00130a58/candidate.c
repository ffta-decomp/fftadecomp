#include "interfaces.h"

u32 TestEffectSameUnitProperty(struct EffectPairContext *context)
{
    u32 actor_property;
    u32 target_property;
    u32 result;

    if ((u8)EffectTargetField19IsZero(context->target))
        return 0;

    actor_property = (u8)EffectUnitStatusBit15(context->actor);
    target_property = (u8)EffectUnitStatusBit15(context->target);
    result = 0;
    if (actor_property == target_property)
        result = 1;
    return result;
}
