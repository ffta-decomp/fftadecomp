#include "interfaces.h"
u32 CalculateEffectResponseWithModePolicy(struct EffectResponseContext *context) __asm__("EffectAuxiliary_00131960");
u32 CalculateEffectResponseWithModePolicy(struct EffectResponseContext *context)
{
    void *actor = context->actor;
    void *target = context->target;
    u32 action = context->action;
    u16 masked_flags = context->flags & 16;
    u32 mode = masked_flags ? 2 : 0;
    return CalculateUnitEffectResponse(actor, target, action, mode);
}
