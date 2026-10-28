#include "effect_74_exact_types.h"
void ApplyCode74SideEffects(EffectContext *context)
{
 if ((context->flags & 16) != 0)
  return;
 context->flags |= 64;
 if ((u8)ActorInUnitPool(context->actor) != 0) {
  void *destination = FindSnapshotDestination(context->affected);
  EncodeUnitSnapshot(destination,context->affected);
  RemoveItem((u16)ResolveUnitItem(context->affected),1);
 }
 SetFlag(1451,1);
}
