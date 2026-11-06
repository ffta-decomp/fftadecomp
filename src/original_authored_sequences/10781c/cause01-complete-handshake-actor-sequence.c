#include "handshake_actor.h"
u32 AdvanceHandshakeActorSequence(TaskNode *,HandshakeEvent *,HandshakeActorWork *)
 __asm__("OriginalRegisteredActionQuestion_0010781C");
u32 AdvanceHandshakeActorSequence(TaskNode *parent,HandshakeEvent *event,HandshakeActorWork *work)
{
 HandshakeEvent child_event;
 int state=event->state;
 switch(state) {
 case 0: {
  u16 mode=event->mode;
  u32 parameter;
  work->mode=mode;
  work->source=event->source;
  parameter=4;
  if((u8)mode!=0) parameter=0;
  /* The original only sets this byte on the true path; no invented else write. */
  if(event->flags&2) work->variant=1;
  work->initial=CreateInitialSequence(work->source,InitialSequenceData,parameter,0,state,parent);
  break;
 }
 case 1:
  AdvanceCurrentSequenceState();
  break;
 case 256: {
  TaskNode *child=PollInitialSequence(work->initial);
  u32 parameter;
  work->initial=child;
  if(child!=0) break;
  if((u8)ReadSourceUnavailable(work->source)!=0) {event->state=2;break;}
  parameter=84;
  if(work->variant!=0) parameter=52;
  else work->secondary=CreateSecondarySequence(SecondaryStartData,3,4,0,parent);
  work->ready_child=CreateActorReadySequence(work->source,&work->actor_context,parameter,
                  ReadyParameters[work->variant],&work->ready,
                  ReadySequences[work->variant],0,0,parent);
  /* Only these three fields belong to the original partial event preparation. */
  child_event.selector=work->variant;
  child_event.source=work->source;
  child_event.signal=&work->signal;
  work->handshake=CreateOppositePhaseTask(HandshakeActorCallback,412,&child_event,parent);
  event->state++;
  break;
 }
 case 257:
  if(work->ready==0) break;
  if(work->signal!=1) break;
  work->signal=2;
  event->state++;
  break;
 case 258: {
  void *target;
  u32 mask;
  register u32 flags __asm__("r1");
  if(work->signal!=3) break;
  if((u8)CheckSourceStage(work->source,0)==0) {event->state=259;break;}
  target=ReadSequenceTarget(work->source,0);
  work->target=target;
  work->projection=ProjectActorWithDefaultTransition(target,&work->x,&work->y,0);
  if((u8)QueryProjectedActorAdjustment()!=0) work->y-=8;
  work->positioned=CreatePositionedDefinitionTask((s16)work->x,(s16)work->y,0,1,
                           1,&work->positioned_output,PositionedSequence,parent);
  /* Coordinates are freshly read after the positioned-task call. */
  ConfigureDefinitionCoordinates(0,2,0,(s16)work->x,(s16)work->y);
  work->resource=CreateDefinitionResource(0,DisplayResource,964,6);
  mask=ReadDisplayHighBitMask(2);
  flags=DisplayShadowControl;
  flags|=mask;
  /* Proven actual mask result / halfword-store interval; no instruction emitted. */
  __asm__("" : "+r"(flags));
  DisplayShadowControl=flags;
  work->authored=CreateAuthoredSequence(AuthoredSequence,parent);
  work->target_sequence=CreateTargetSequence(work->target,TargetSequenceData,12,90,10,parent,90);
  work->secondary=CreateSecondarySequence(SecondaryImpactData,1,4,0,parent);
  event->state++;
  break;
 }
 case 259: {
  TaskNode *child=PollAuthoredSequence(work->authored);
  void *resource;
  u32 mask,flags;
  work->authored=child;
  if(child!=0) break;
  resource=PollDefinitionResource(work->resource,0);
  work->resource=resource;
  if(resource!=0) break;
  mask=ReadDisplayHighBitMask(2);
  flags=DisplayShadowControl;
  flags&=~mask;
  DisplayShadowControl=flags;
  child=PollAndReleaseChild(work->handshake);
  work->handshake=child;
  if(child!=0) break;
  child=PollPositionedDefinition(work->positioned);
  work->positioned=child;
  if(child!=0) break;
  resource=PollTargetSequence(work->target_sequence);
  work->target_sequence=resource;
  if(resource!=0) break;
  event->state=2;
  break;
 }
 }
 return 0;
}
__asm__(
 ".global CreateInitialSequence\n.thumb_set CreateInitialSequence,0x080E03F9\n"
 ".global AdvanceCurrentSequenceState\n.thumb_set AdvanceCurrentSequenceState,0x080D38B5\n"
 ".global PollInitialSequence\n.thumb_set PollInitialSequence,0x080E05DD\n"
 ".global ReadSourceUnavailable\n.thumb_set ReadSourceUnavailable,0x080D3B55\n"
 ".global CreateSecondarySequence\n.thumb_set CreateSecondarySequence,0x080DFD8D\n"
 ".global CreateActorReadySequence\n.thumb_set CreateActorReadySequence,0x080DDF69\n"
 ".global CreateOppositePhaseTask\n.thumb_set CreateOppositePhaseTask,0x08005B6D\n"
 ".global CheckSourceStage\n.thumb_set CheckSourceStage,0x080D8859\n"
 ".global ReadSequenceTarget\n.thumb_set ReadSequenceTarget,0x080DD4A5\n"
 ".global ProjectActorWithDefaultTransition\n.thumb_set ProjectActorWithDefaultTransition,0x080DD749\n"
 ".global QueryProjectedActorAdjustment\n.thumb_set QueryProjectedActorAdjustment,0x080DD73D\n"
 ".global CreatePositionedDefinitionTask\n.thumb_set CreatePositionedDefinitionTask,0x080D6099\n"
 ".global ConfigureDefinitionCoordinates\n.thumb_set ConfigureDefinitionCoordinates,0x080D49FD\n"
 ".global CreateDefinitionResource\n.thumb_set CreateDefinitionResource,0x080D4B65\n"
 ".global ReadDisplayHighBitMask\n.thumb_set ReadDisplayHighBitMask,0x080035A9\n"
 ".global CreateAuthoredSequence\n.thumb_set CreateAuthoredSequence,0x080D3E9D\n"
 ".global CreateTargetSequence\n.thumb_set CreateTargetSequence,0x080DCFE5\n"
 ".global PollAuthoredSequence\n.thumb_set PollAuthoredSequence,0x080D3F09\n"
 ".global PollDefinitionResource\n.thumb_set PollDefinitionResource,0x080D4D2D\n"
 ".global PollAndReleaseChild\n.thumb_set PollAndReleaseChild,0x080E051D\n"
 ".global PollPositionedDefinition\n.thumb_set PollPositionedDefinition,0x080D6135\n"
 ".global PollTargetSequence\n.thumb_set PollTargetSequence,0x080DBA5D\n"
 ".global InitialSequenceData\n.set InitialSequenceData,0x083A0C94\n"
 ".global SecondaryStartData\n.set SecondaryStartData,0x083A0D08\n"
 ".global ReadyParameters\n.set ReadyParameters,0x083A0CF0\n"
 ".global ReadySequences\n.set ReadySequences,0x083A0CE8\n"
 ".global PositionedSequence\n.set PositionedSequence,0x083A0CC4\n"
 ".global DisplayResource\n.set DisplayResource,0x088EEB54\n"
 ".global AuthoredSequence\n.set AuthoredSequence,0x0894D844\n"
 ".global TargetSequenceData\n.set TargetSequenceData,0x083A0CF4\n"
 ".global SecondaryImpactData\n.set SecondaryImpactData,0x083A0D28\n"
 ".global DisplayShadowControl\n.set DisplayShadowControl,0x03000940\n"
 ".global HandshakeActorCallback\n.thumb_set HandshakeActorCallback,0x081074D9\n"
);
