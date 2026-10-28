#include "predicate_09_exact_types.h"
u32 TestEffectEligibleMatchingResidue10(EffectContext *context)
{
 u32 actor_remainder;
 u32 target_remainder;
 u32 same;
 if ((u8)UnitField19IsZero(context->target) != 0)
  return 0;
 if ((u8)CounterCondition(context->target) != 0)
  return 0;
 actor_remainder = (u8)UnsignedRemainder(context->actor->selector,10);
 target_remainder = (u8)UnsignedRemainder(context->target->selector,10);
 same = 0;
 if (actor_remainder == target_remainder)
  same = 1;
 return same;
}
