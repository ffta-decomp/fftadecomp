#include "effect_26_exact_types.h"
void MoveAffectedUnitToProducedPoint(EffectContext *context)
{
 ReferenceNode *node;
 void *reference;
 u8 x,y;
 if ((context->flags&16)!=0) return;
 node=FindNode(CurrentRuntime(),context->previous);
 reference=0;
 if (node!=0) reference=node->reference;
 if (ProducePoint(CurrentRuntime(),context->actor,context->previous,reference,&x,&y)!=0) {
  context->flags |=8;
  context->affected->x=x;
  context->affected->y=y;
 }
}
