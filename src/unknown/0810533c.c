#include "abi/interfaces/0810533c_target_palette.h"

u32 AdvanceTargetPropertyPaletteSequence(TaskNode *,PaletteSequenceEvent *,TargetPaletteWork *)
 __asm__("OriginalRegisteredActionQuestion_0010533C");

u32 AdvanceTargetPropertyPaletteSequence(TaskNode *parent,PaletteSequenceEvent *event,
                                       TargetPaletteWork *work)
{
 u8 parameters[5];
 u16 state=event->state;
 switch(state) {
 case 0: {
  u16 mode;
  void *source;
  u32 parameter,enabled;
  const u8 *const *records;
  const u8 *record;
  CopyBytes(parameters,InitialGroupParameters,5);
  work->variant=event->selector_low+22;
  mode=event->mode;
  work->mode=mode;
  source=event->source;
  work->source=source;
  parameter=2;
  if((u8)mode!=0) parameter=0;
  work->initial=CreateInitialSequence(source,InitialSequenceData,parameter,0,state,parent);
  records=VariantPaletteRecords;
  record=records[work->variant];
  enabled=1;
  CopyCountedPaletteGroupsToShadow(record,6,0,0,enabled);
  CopyCountedPaletteGroupsToShadow(records[work->variant],7,0,0,enabled);
  CopyCountedPaletteGroupsToShadow(records[work->variant],8,0,0,enabled);
  CopyCountedPaletteGroupsToShadow(FixedObjectPaletteRecord,6,1,
                                 parameters[work->variant],enabled);
  break;
 }
 case 1:
  AdvanceCurrentSequenceState();
  break;
 case 256: {
  TaskNode *child=PollInitialSequence(work->initial);
  u8 unavailable;
  work->initial=child;
  if(child!=0) break;
  unavailable=ReadSourceUnavailable(work->source);
  if(unavailable!=0) {event->state=2;break;}
  work->ready_sequence=CreateActorReadySequence(work->source,&work->actor_context,
                  0x8007,2,&work->ready,ReadySequenceData,5,unavailable,parent);
  event->state++;
  break;
 }
 case 257:
  if(work->ready==0) break;
  QueryRecordPositionBoundary(work->source);
  work->timer=24;
  event->state++;
  /* Original returns here; the countdown starts on the next invocation. */
  break;
 case 258: {
  void *target;
  u32 mask;
  register u32 flags __asm__("r1");
  u8 index;
  TaskNode **children;
  const void *const *palette_rows;
  if(work->timer!=0) {
   u32 remaining=work->timer-1;
   work->timer=remaining;
   if((u16)remaining!=0) break;
  }
  if((u8)QueryDefinitionReadiness()!=0) break;
  if((u8)CheckSourceStage(work->source,0)==0) {event->state=2;break;}
  target=ReadSequenceTarget(work->source,0);
  work->target=target;
  /* This return intentionally replaces the earlier ready OUT in the same slot. */
  work->actor_context=ProjectActorWithDefaultTransition(target,&work->x,&work->y,0);
  ConfigureDefinitionCoordinates(0,2,0,(s16)work->x,(s16)work->y);
  work->display_resource=CreateDefinitionResource(0,DisplayResourceRecord,0x3CB,6);
  mask=ReadDisplayHighBitMask(2);
  flags=DisplayShadowControl;
  flags|=mask;
  __asm__("" : "+r"(flags));
  DisplayShadowControl=flags;
  work->authored=CreateAuthoredSequence(AuthoredSequenceData,parent);
  index=0;
  children=work->palettes;
  palette_rows=VariantPaletteSequences;
  do {
   u32 byte_offset=(u32)index*4;
   u32 row_offset=(u32)work->variant*12;
   const void *sequence=*(const void *const *)((const u8 *)palette_rows+
                                            (byte_offset+row_offset));
   TaskNode *palette=CreateDefinitionPaletteTask(sequence,parent);
   /* The numeric offset survives the call; the destination address is formed now. */
   *(TaskNode **)((u8 *)children+byte_offset)=palette;
   index++;
  } while(index<=2);
  work->secondary=CreateSecondarySequence(SecondaryStartData,1,4,0,parent);
  event->state++;
  break;
 }
 case 259: {
  TaskNode *authored;
  void *resource;
  u32 mask,duration;
  u32 flags;
  CopyBytes(parameters,PropertySelectors,5);
  authored=PollAuthoredSequence(work->authored);
  work->authored=authored;
  if(authored!=0) break;
  if((u8)PollStageHandleArray(work->palettes,3)==0) break;
  resource=PollDefinitionResource(work->display_resource,0);
  work->display_resource=resource;
  if(resource!=0) break;
  mask=ReadDisplayHighBitMask(2);
  flags=DisplayShadowControl;
  flags&=~mask;
  DisplayShadowControl=flags;
  duration=0;
  if((u8)ReadRecordPropertyLowByte(work->target,parameters[work->variant])!=0) {
   duration=40;
   work->positioned=CreatePositionedDefinitionTask((s16)work->x,(s16)work->y,0,1,
                 1,&work->positioned_output,PositionedSequences[work->variant],parent);
   work->secondary=CreateSecondarySequence(SecondaryImpactData,1,4,0,parent);
  }
  work->target_sequence=CreateTargetSequence(work->target,
                  TargetSequences+20*work->variant,12,duration,12,parent,duration);
  event->state++;
  break;
 }
 case 260: {
  TaskNode *child=PollPositionedDefinition(work->positioned);
  void *target;
  work->positioned=child;
  if(child!=0) break;
  target=PollTargetSequence(work->target_sequence);
  work->target_sequence=target;
  if(target!=0) break;
  event->state=2;
  break;
 }
 }
 return 0;
}

__asm__(
 ".global CopyBytes\n.thumb_set CopyBytes,0x081443FD\n"
 ".global CreateInitialSequence\n.thumb_set CreateInitialSequence,0x080E03F9\n"
 ".global CopyCountedPaletteGroupsToShadow\n.thumb_set CopyCountedPaletteGroupsToShadow,0x080D45D1\n"
 ".global AdvanceCurrentSequenceState\n.thumb_set AdvanceCurrentSequenceState,0x080D38B5\n"
 ".global PollInitialSequence\n.thumb_set PollInitialSequence,0x080E05DD\n"
 ".global ReadSourceUnavailable\n.thumb_set ReadSourceUnavailable,0x080D3B55\n"
 ".global CreateActorReadySequence\n.thumb_set CreateActorReadySequence,0x080DDF69\n"
 ".global QueryRecordPositionBoundary\n.thumb_set QueryRecordPositionBoundary,0x080D8CD5\n"
 ".global QueryDefinitionReadiness\n.thumb_set QueryDefinitionReadiness,0x080D8B4D\n"
 ".global CheckSourceStage\n.thumb_set CheckSourceStage,0x080D8859\n"
 ".global ReadSequenceTarget\n.thumb_set ReadSequenceTarget,0x080DD4A5\n"
 ".global ProjectActorWithDefaultTransition\n.thumb_set ProjectActorWithDefaultTransition,0x080DD749\n"
 ".global ConfigureDefinitionCoordinates\n.thumb_set ConfigureDefinitionCoordinates,0x080D49FD\n"
 ".global CreateDefinitionResource\n.thumb_set CreateDefinitionResource,0x080D4B65\n"
 ".global ReadDisplayHighBitMask\n.thumb_set ReadDisplayHighBitMask,0x080035A9\n"
 ".global CreateAuthoredSequence\n.thumb_set CreateAuthoredSequence,0x080D3E9D\n"
 ".global CreateDefinitionPaletteTask\n.thumb_set CreateDefinitionPaletteTask,0x080D4705\n"
 ".global CreateSecondarySequence\n.thumb_set CreateSecondarySequence,0x080DFD8D\n"
 ".global PollAuthoredSequence\n.thumb_set PollAuthoredSequence,0x080D3F09\n"
 ".global PollStageHandleArray\n.thumb_set PollStageHandleArray,0x080D48DD\n"
 ".global PollDefinitionResource\n.thumb_set PollDefinitionResource,0x080D4D2D\n"
 ".global ReadRecordPropertyLowByte\n.thumb_set ReadRecordPropertyLowByte,0x080DD671\n"
 ".global CreatePositionedDefinitionTask\n.thumb_set CreatePositionedDefinitionTask,0x080D6099\n"
 ".global CreateTargetSequence\n.thumb_set CreateTargetSequence,0x080DCFE5\n"
 ".global PollPositionedDefinition\n.thumb_set PollPositionedDefinition,0x080D6135\n"
 ".global PollTargetSequence\n.thumb_set PollTargetSequence,0x080DBA5D\n"
 ".global InitialGroupParameters\n.set InitialGroupParameters,0x08149E38\n"
 ".global PropertySelectors\n.set PropertySelectors,0x08149E3D\n"
 ".global InitialSequenceData\n.set InitialSequenceData,0x0839F9C0\n"
 ".global VariantPaletteRecords\n.set VariantPaletteRecords,0x0839FA64\n"
 ".global FixedObjectPaletteRecord\n.set FixedObjectPaletteRecord,0x088E9C70\n"
 ".global ReadySequenceData\n.set ReadySequenceData,0x0839FB18\n"
 ".global DisplayResourceRecord\n.set DisplayResourceRecord,0x088EDC04\n"
 ".global AuthoredSequenceData\n.set AuthoredSequenceData,0x0894D7E4\n"
 ".global VariantPaletteSequences\n.set VariantPaletteSequences,0x0839FA78\n"
 ".global SecondaryStartData\n.set SecondaryStartData,0x0839FB20\n"
 ".global PositionedSequences\n.set PositionedSequences,0x0839FA50\n"
 ".global SecondaryImpactData\n.set SecondaryImpactData,0x0839FB28\n"
 ".global TargetSequences\n.set TargetSequences,0x0839FAB4\n"
 ".global DisplayShadowControl\n.set DisplayShadowControl,0x03000940\n"
);
