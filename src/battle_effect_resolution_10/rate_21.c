#include "rate_21_exact_types.h"
u32 ReadEffectConditionalTargetRate(EffectContext *context)
{
 u32 amount = Evaluate(context->actor,context->target,context->descriptor[1]);
 if ((u8)StateGate(context->target) != 0) {
  if ((context->flags & 16) != 0)
   goto zero;
  if (amount != 0)
   return 100;
  goto truncated;
zero:
  return 0;
 }
truncated:
 return (u8)amount;
}
