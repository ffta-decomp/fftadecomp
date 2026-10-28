#include "interfaces.h"
u32 ReadEffectFlagOneRate(struct EffectRateContext *context) __asm__("EffectAuxiliary_0013109C");
u32 ReadEffectFlagOneRate(struct EffectRateContext *context)
{
    if ((context->flags & 1) == 0)
        return 0;
    return 100;
}
