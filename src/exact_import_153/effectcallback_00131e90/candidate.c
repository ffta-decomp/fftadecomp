#include "contract.h"

void EffectCallback_00131E90(EffectContext *context)
{
    u32 property = GetUnitProperty(context->unit, 38);
    s32 amount = (s32)(property + (u32)context->amounts[context->selected_index]);
    if (amount > 10)
        amount = 10;
    *(u16 *)(context->unit + 0xd6) = amount;
}
