#include "interfaces.h"
u32 ReadEffectBaseTenthWithRandomOffset(struct EffectRuleContext *context) __asm__("EffectAuxiliary_001318F8");
u32 ReadEffectBaseTenthWithRandomOffset(struct EffectRuleContext *context)
{
    s32 final_amount;
    s32 amount = CalculateEffectBase(context);
    s32 random_value = NextEffectRandom();
    amount = DivideEffectSigned(amount, 10);
    final_amount = (s32)((u32)amount + (u32)(s16)RemainderEffectSigned((s16)random_value, 11));
    if (final_amount <= 0)
        final_amount = 1;
    return final_amount;
}
