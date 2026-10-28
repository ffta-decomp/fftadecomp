#include "effect_24_exact_types.h"
void ApplyOrReplaceUnitStatusSlot24(EffectContext *context)
{
 if ((u8)StateGate(context->affected) != 0) {
  ClearState(context->affected,0);
  context->flags |= 256;
 } else {
  ApplyKind(context,30);
  if ((context->flags & 16) == 0) {
   SetState(context->affected,1);
   WriteCounter(context->affected,3);
  }
 }
}
