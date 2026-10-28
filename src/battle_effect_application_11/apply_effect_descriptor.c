#include "apply_effect_descriptor_exact_types.h"

void ApplyBattleEffectDescriptor(void)
{
 EffectContext *context = &BattleEffectContext;
 const EffectDescriptor *descriptors;
 u32 effect;
 context->flags &= 0xffdf;
 if ((u8)Compatible(context->affected, context->descriptor[1]) == 0)
  return;
 descriptors = (const EffectDescriptor *)0x083a87b0;
 descriptors[context->descriptor[1]].apply(context);
 /* The callback may replace the descriptor and affected unit. */
 if (context->descriptor[1] == 70)
  context->flags |= 0x200;
 if (!(context->flags & 0x100)) {
  if ((u8)GetKind() == 1 || (u8)GetKind() == 2) {
   if (((AmountView *)context)->selected_amount[context->amount_index] > 0) {
    ApplyEffect(context->descriptor[1], context->affected);
   } else {
    effect = context->descriptor[1];
    if (descriptors[effect].metadata < 0)
     ApplyEffect(effect, context->affected);
   }
  } else {
   ApplyEffect(context->descriptor[1], context->affected);
  }
  NotifyItem(context->item, context->action, context->affected);
 }
 Normalize(context->affected);
 Refresh(context->affected);
 Refresh(context->actor);
}
