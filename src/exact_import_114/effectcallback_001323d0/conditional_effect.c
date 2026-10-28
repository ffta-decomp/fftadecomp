#include "interfaces.h"
void EffectCallback_001323D0(EffectContext *context)
{
 if ((u8)StateGate(context->affected)==0) {
  s16 effect;
  u16 threshold=(s16)EvaluateEffect(context->actor,context->affected,0,&effect)*10;
  s32 roll=Remainder((s16)RandomWord(),1001);
  if ((s16)threshold >= (s16)roll) {
   EffectDescriptors[effect].apply(context);
   return;
  }
 } else ClearState(context->affected,0);
 context->flags |=256;
}
