#include "effect_80_exact_types.h"
void ApplyStatusAndThreeCountSlot80(EffectContext *context)
{
 if ((u8)StateGate(context->affected) != 0) {
  if ((context->flags & 16) != 0)
   return;
  ClearState(context->affected,0);
  context->flags |= 256;
 } else {
  ApplyKind(context,29);
  if ((context->flags & 16) == 0) {
   SetState(context->affected,1);
   WriteCounter(context->affected,3);
  }
 }
}
