#include "interfaces.h"
u32 CalculateEffectOperandWithVariancePolicy(struct EffectOperandContext *context) __asm__("EffectAuxiliary_00131804");
u32 CalculateEffectOperandWithVariancePolicy(struct EffectOperandContext *context)
{
    void *actor = context->actor;
    void *target = context->target;
    u32 action = context->action;
    u32 item = context->item;
    u16 mode = context->flags & 16;
    if (mode != 0)
        mode = 2;
    return CalculateUnitEffectOperand(actor, target, action, item, mode);
}
