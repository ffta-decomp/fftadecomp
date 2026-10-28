#include "effect_92_exact_types.h"

void AttachRandomRecordAndIncrementByte103(EffectContext *context)
{
 EffectRuntime *runtime;
 u8 *count;
 u32 unit_slot;
 s32 selected;
 if (context->flags & 0x10)
  return;
 runtime = &Runtime;
 count = &runtime->choice_count;
 if (*count == 0) {
  context->flags |= 0x100;
  return;
 }
 context->previous->flags28 |= 0x40;
 unit_slot = context->previous->slot104;
 selected = (s16)RandomWord();
 selected = SignedRemainder(selected, *count);
 SetChoice(unit_slot, runtime->choice_bytes[selected * 2], 0);
 if (context->previous->counter103 <= 8) {
  if ((u8)ReadProgression(13) != 1)
   ++context->previous->counter103;
 }
}
