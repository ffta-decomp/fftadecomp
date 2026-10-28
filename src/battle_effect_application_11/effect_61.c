#include "effect_61_exact_types.h"
void ApplyOrReplaceUnitStatusSlot61(EffectContext *context)
{
 if ((u8)StateGate(context->affected) != 0) {
  if ((context->flags & 16) != 0)
   return;
  ClearState(context->affected,0);
  context->flags |= 256;
 } else {
  ApplyKind(context,9);
  if ((context->flags & 16) == 0)
   SetState(context->affected,1);
 }
}
