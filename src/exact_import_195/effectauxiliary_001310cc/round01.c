#include "interfaces.h"
u32 ReadEffectSlotSixFlagOneRate(struct EffectRateContext *context) __asm__("EffectAuxiliary_001310CC");
u32 ReadEffectSlotSixFlagOneRate(struct EffectRateContext *context)
{
    if ((context->flags & 1) == 0)
        return 0;
    return 100;
}
