#include "interfaces.h"
u32 QuantizeEffectTargetQuantity(struct EffectQuantityContext *context) __asm__("EffectAuxiliary_0013156C");
u32 QuantizeEffectTargetQuantity(struct EffectQuantityContext *context)
{
    if (context->target->quantity != 0)
        return 1;
    return 0;
}
