#include "predicate_13_exact_types.h"
u32 TestEffectIneligibleRemainderFiveZero(EffectContext *context)
{
 u32 accepted;
 if ((u8)UnitField19IsZero(context->unit) != 0)
  return 0;
 if ((u8)IsReactionAllowed(context->unit) == 0)
  return 0;
 accepted = 0;
 if ((u8)UnsignedRemainder(context->unit->selector, 5) == 0)
  accepted = 1;
 return accepted;
}
