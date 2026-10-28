#include "effect_context.h"

void EffectCallback_00133724(EffectContext *context)
{
    u32 amount;
    if ((context->flags & 0x10) == 0) {
        amount = (u32)RetailCall_08131b20();
        context->actor->counter_d6 += amount;
        /* The actor and target may differ: only the target is capped. */
        if (context->target->counter_d6 > 10)
            context->target->counter_d6 = 10;
    }
}
