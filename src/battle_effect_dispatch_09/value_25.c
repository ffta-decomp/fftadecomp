#include "interfaces.h"

u32 ReadEffectActorCurrentUnlessExcluded(volatile EffectRuleContext *context)
{
    if ((u8)EffectTargetGateCDA4C(context->target)) {
        u32 tag = EffectByte(context->descriptor, 1);
        if (tag == 21 || tag == 8 || tag == 15) return 0;
    }
    return EffectHalf(context->actor, 24);
}
