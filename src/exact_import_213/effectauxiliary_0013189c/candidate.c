#include "interfaces.h"

u32 CalculateEffectBase(struct EffectOperandContext *context)
{
    void *actor;
    void *target;
    u32 action;
    u32 item;

    actor = context->actor;
    target = context->target;
    action = context->action;
    item = context->item;
    return EffectCalculateBase(actor, target, action, item, 0,
                               (u16)(context->flags & 16) ? 2 : 0);
}
