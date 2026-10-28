#include "interfaces.h"
int EvaluateFlagSelectedEffect(EffectContext *context) asm("EffectAuxiliary_001319C4");
int EvaluateFlagSelectedEffect(EffectContext *context)
{
    void *actor = context->actor;
    void *target = context->target;
    u16 parameter12 = context->parameter12;
    u16 parameter14 = context->parameter14;
    u16 masked_mode;
    return EvaluateEffectFormula(actor, target, parameter12, parameter14, 0,
                                 (masked_mode = context->flags & 16) ? 2 : masked_mode);
}
