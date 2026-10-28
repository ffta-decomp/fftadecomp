#include "effect_46_exact_types.h"
void ApplyStateAndCopyTaskFlag(EffectContext *context)
{
 if ((u8)StateGate(context->affected)!=0) {
  if (context->flags&16) return;
  ClearState(context->affected,0);
  context->flags |=256;
 } else {
  Node *node;
  ApplyKind(context,6);
  if (context->flags&16) return;
  SetState(context->affected,1);
  node=FindNode(CurrentRuntime(),context->affected);
  if (node!=0) {
   if (node->flags&8) WriteNodeState(context->affected,1);
   else WriteNodeState(context->affected,0);
  }
 }
}
