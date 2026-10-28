#include "interfaces.h"

u32 ReadEffectTenfoldProperty57(volatile EffectRuleContext *context)
{
    s32 amount;
    if ((u8)EffectTargetGateCDA4C(context->target)) return 0;
    amount = (s32)(EffectUnitProperty(context->target, 57) * 10u);
    if (amount < -999) amount = -999;
    if (amount > 999) amount = 999;
    return amount;
}
