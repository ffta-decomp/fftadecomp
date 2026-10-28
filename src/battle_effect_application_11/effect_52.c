#include "effect_52_exact_types.h"
void ApplyState21AndIncreaseCounterD9(EffectContext *context)
{
 s32 next_counter;
 ApplyKind(context,21);
 if ((context->flags & 16) != 0)
  return;
 SetState(context->affected,1);
 next_counter = (u8)ReadCounter(context->affected) + 3;
 if ((next_counter & 128) != 0)
  return;
 if (next_counter > 5)
  next_counter = 6;
 WriteCounter(context->affected,(u8)next_counter);
}
