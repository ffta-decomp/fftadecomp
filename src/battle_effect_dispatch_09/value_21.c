#include "interfaces.h"

u32 ReadEffectCurrentLessTenth(volatile EffectRuleContext *context)
{
    void *target;

    if ((u8)EffectTargetGateCDA4C(context->target)) return 0;

    target = context->target;
    if (EffectHalf(target, 24) <= 1) return 1;

    {
        /* Retail loads this zero-extended value across the divide helper in r4. */
        register u32 current __asm__("r4");
        u16 tenth;

        current = EffectHalf(target, 24);
        tenth = (u16)EffectUnsignedQuotient(current, 10);
        if (tenth == 0) tenth = 1;
        return current - tenth;
    }
}
