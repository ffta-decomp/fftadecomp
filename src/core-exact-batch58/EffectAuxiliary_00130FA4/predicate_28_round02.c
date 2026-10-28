#include "interfaces.h"

u32 TestEffectTargetGateSet(volatile EffectRuleContext *context)
{
    if ((u8)EffectTargetGateC8298(context->target) != 0)
        return 1;
    return 0;
}
