#include "effect_15_exact_types.h"
void RemoveCurrencyForAffectedUnit(EffectContext *context)
{
 u32 blocked_flags = (u16)(context->flags & 16);
 s32 magnitude;
 u32 remaining;
 if (blocked_flags != 0)
  return;
 magnitude = ((AmountView*)context)->values[context->amount_index];
 if (magnitude < 0)
  magnitude = -magnitude;
 if ((u8)InUnitPool(context->affected) == 0)
  return;
 if ((u8)InUnitPool(context->affected) == 0)
  return;
 remaining = RuntimeResources.amount - (u32)magnitude;
 if ((s32)remaining <= 0)
  RuntimeResources.amount = blocked_flags;
 else
  RuntimeResources.amount = remaining;
}
