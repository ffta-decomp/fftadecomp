#include "interfaces.h"

u32 ReadEffectDescriptorPairRateSlot15(volatile EffectRuleContext *context)
{
    void *actor, *target;
    u8 *descriptor;
    u32 value, selector;
    actor = context->actor;
    target = context->target;
    descriptor = context->descriptor;
    value = EffectByte(descriptor, 3);
    selector = EffectByte(descriptor, 2);
    return (u8)ResolutionRule_12D5F4(actor, target, value, selector);
}
