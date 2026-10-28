#include "effect_63_exact_types.h"
void ApplyOrReplaceUnitStatusSlot63(EffectContext *context)
{
 if ((u8)StateGate(context->affected) != 0) {
  ClearState(context->affected,0);
  context->flags |= 256;
 } else {
  ApplyKind(context,11);
  if ((context->flags & 16) == 0)
   SetState(context->affected,1);
 }
}
