#include "interfaces.h"
void EffectCallback_001336B8(EffectContext *context)
{
 if (context->flags&16) return;
 if ((u8)StateGate(context->affected)!=0) {
  ClearState(context->affected,0);
  context->flags |=256;
 } else {
  ApplyFirst(context);
  if ((context->flags&272)==0) WriteFirstCounter(context->affected,3);
  ApplySecond(context);
  if ((context->flags&272)==0) WriteSecondCounter(context->affected,3);
 }
}
