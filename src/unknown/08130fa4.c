#include "abi/interfaces/08130fa4_bindings.h"

u32 TestEffectTargetGateSet(volatile EffectRuleContext *context)
{
    if ((u8)EffectTargetGateC8298(context->target) != 0)
        return 1;
    return 0;
}
