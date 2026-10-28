#include "value_dispatch_exact_types.h"
s32 EvaluateBattleEffectValue(void)
{
 EffectContext *context=(EffectContext *)0x0200f3f0;
 s32 amount;
 if (context->actor==0 || context->target==0) return 0;
 amount=EffectValueCallbacks[context->descriptor->value_selector](context);
 amount=(s32)((u32)amount*(u32)EffectMultiplier());
 switch ((u8)EffectKind()) {
 case 1: case 2: case 4: case 5:
  if ((u8)PairGate(context->actor,context->target)!=0) amount=0;
  break;
 case 3:
  if ((u8)PairGate(context->actor,context->target)!=0) amount=0;
  else if (amount<=1) amount=2;
  break;
 }
 return amount;
}
