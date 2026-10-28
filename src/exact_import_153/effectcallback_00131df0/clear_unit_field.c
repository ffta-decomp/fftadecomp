#include "effect_context.h"

/* Clear the unit halfword only when context flag 0x10 is absent. */
void EffectCallback_00131DF0(EffectContext *context)
{
    u16 suppression = context->flags & 0x10;
    if (suppression == 0)
        context->unit->field_d0 = suppression;
}
