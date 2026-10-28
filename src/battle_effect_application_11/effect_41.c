#include "effect_41_exact_types.h"
void ApplyOrReplaceUnitStatusSlot41(EffectContext *context)
{
 if ((u8)StateGate(context->affected) != 0) {
  if ((context->flags & 16) != 0)
   return;
  ClearState(context->affected,0);
  context->flags |= 256;
 } else {
  ApplyKind(context,28);
  if ((context->flags & 16) == 0) {
   SetState(context->affected,1);
   WriteCounter(context->affected,3);
  }
 }
}
