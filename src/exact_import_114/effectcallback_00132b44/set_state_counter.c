#include "interfaces.h"
void EffectCallback_00132B44(EffectContext *context)
{
 if ((u8)StateGate(context->affected)!=0) {
  if (context->flags&16) return;
  ClearState(context->affected,0);
  context->flags|=256;
 } else {
  u16 blocked_flags;
  s32 counter;
  ApplyKind(context,22);
  blocked_flags=context->flags&16;
  if (blocked_flags!=0) return;
  SetState(context->affected,1);
  context->affected->field212=blocked_flags;
  counter=(u8)ReadCounter(context->affected);
  if ((counter&128)==0) {
   counter+=3;
   if (counter>6) counter=6;
   WriteCounter(context->affected,(u8)counter);
  }
 }
}
