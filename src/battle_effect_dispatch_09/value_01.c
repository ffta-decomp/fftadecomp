#include "value_01_exact_types.h"
u32 ReadEffectProperty38Limit(EffectContext *context)
{
 if (context->descriptor[1] == 90) {
  u32 amount = UnitProperty(context->actor,38) >> 1;
  if ((UnitProperty(context->actor,38) & 1) != 0)
   amount++;
  return amount;
 }
 {
  u32 target_amount;
  if (UnitProperty(context->target,38) > 1)
   target_amount = 2;
  else
   target_amount = UnitProperty(context->target,38);
  return target_amount;
 }
}
