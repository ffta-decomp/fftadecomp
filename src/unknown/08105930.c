#include "abi/interfaces/08105930_repeated_actor.h"
u32 AdvanceRepeatedActorSequence(TaskNode *,ActorEvent *,RepeatedActorWork *)
 __asm__("OriginalRegisteredActionQuestion_00105930");
u32 AdvanceRepeatedActorSequence(TaskNode *parent,ActorEvent *event,RepeatedActorWork *work)
{
 u16 selectors[4];
 ActorEvent leading_event;
 ActorEvent repeated_event;
 int state=event->state;
 switch(state) {
 case 0: {
  u16 mode;
  void *source;
  u32 parameter,enabled;
  const u8 *record;
  register const u8 *palette __asm__("r0");
  register const u8 *selector_base __asm__("r2");
  u32 selector_offset;
  const u8 *selector_address;
  work->variant=(u8)event->selector+17;
  mode=event->mode;
  work->mode=mode;
  source=event->source;
  work->source=source;
  parameter=4;
  if((u8)mode!=0) parameter=0;
  work->initial=CreateInitialSequence(source,InitialSequenceData,parameter,0,state,parent);
  record=VariantPaletteRecords[work->variant];
  enabled=1;
  CopyCountedPaletteGroupsToShadow(record,6,0,0,enabled);
  if(work->variant!=6) palette=DefaultObjectPalette;
  else palette=SpecialObjectPalette;
  /* Actual initialized first argument remains R0 through the fresh selector load. */
  __asm__("" : "+r"(palette));
  selector_base=PaletteSelectors;
  /* Original ROM base is defined before the fresh byte index; dies at the load. */
  __asm__("" : "+r"(selector_base));
  selector_offset=work->variant;
  selector_address=(const u8 *)(selector_offset+(u32)selector_base);
  CopyCountedPaletteGroupsToShadow(palette,8,1,*selector_address,enabled);
  break;
 }
 case 1:
  AdvanceCurrentSequenceState();
  break;
 case 256: {
  TaskNode *child=PollInitialSequence(work->initial);
  work->initial=child;
  if(child!=0) break;
  {
   void *source=work->source;
   u32 variant=work->variant;
   u32 twice=variant<<1;
   u32 four=variant<<2;
   u32 row_offset=(four+twice)<<2;
   work->initial=CreateInitialSequence(source,FollowupSequences+row_offset,
                                      2,7,(u32)child,parent);
  }
  event->state++;
  break;
 }
 case 257: {
  TaskNode *child=PollInitialSequence(work->initial);
  u8 mode;
  void *nested;
  work->initial=child;
  if(child!=0) break;
  mode=work->mode;
  if(mode!=0) {
   work->count=CountSourceTargets(work->source);
   work->ready=1;
   event->state=263;
   break;
  }
  nested=GetRecordNestedPointer(work->source);
  work->nested=nested;
  ConfigureNestedTransition(nested,60);
  work->ready_child=CreateReadyTransition(work->nested,&work->ready,2,-1,mode,mode,mode,parent);
  event->state++;
  break;
 }
 case 258:
  if(work->ready==0) break;
  ReadNestedCoordinates(work->nested,&work->x,&work->y);
  work->positioned=CreatePositionedDefinitionTask((s16)work->x,(s16)work->y,0,1,
                           3,&work->sprite,PositionedData,parent);
  work->secondary=CreateSecondarySequence(SecondaryData,2,4,0,parent);
  event->state++;
  break;
 case 259: {
  TaskNode *child;
  u8 variant;
  u16 value;
  SequenceDescriptor *descriptor;
  u16 *code;
  register u32 code_value __asm__("r0");
  CopyBytes(selectors,DescriptorSelectors,8);
  child=PollPositionedDefinition(work->positioned);
  work->positioned=child;
  if(child!=0) break;
  variant=4;
  work->property_flag=(u32)child;
  if((u8)ReadSourceProperty(work->source,16)!=0) {
   variant=3;
   work->property_flag=1;
  }
  value=ReadUnitField(ReadNestedUnitIndex(work->nested),21);
  descriptor=&work->descriptor;
  code=&work->descriptor.code;
  while(value>10) value-=10;
  if(value==3 || value==5 || value==7) variant+=2;
  work->sprite=CreateSpriteDefinition(SpriteResource,variant,(s16)work->x,(s16)work->y,
                                      0x37F,6,1,0);
  InitializeDescriptor(descriptor,8);
  descriptor->selector=selectors[variant-3];
  code_value=298;
  /* This initialized value is immediately consumed by the real halfword store. */
  __asm__("" : "+r"(code_value));
  *code=code_value;
  work->descriptor_sequence=CreateSecondarySequence(descriptor,1,4,0,parent);
  if((u8)(variant-5)<=1)
   work->optional_secondary=CreateSecondarySequence(OptionalSecondaryData,5,4,0,parent);
  event->state++;
  break;
 }
 case 260: {
  void *sprite=PollSpriteDefinition(work->sprite);
  work->sprite=sprite;
  if(sprite!=0) break;
  if(work->property_flag==0) SetDefinitionMode(2,0);
  else SetDefinitionMode(1,0);
  event->state++;
  break;
 }
 case 261: {
  u8 readiness=QueryDefinitionReadiness();
  if(readiness!=0) break;
  /* Only the original selector field is written in this distinct event. */
  leading_event.selector=work->variant;
  work->leading=CreateOppositePhaseTask(LeadingActorCallback,24,&leading_event,parent);
  ReleaseReadyTransition(work->ready_child);
  work->ready_child=(void *)(u32)readiness;
  work->counter=120;
  event->state++;
  break;
 }
 case 262: {
  u32 remaining=work->counter-1;
  work->counter=remaining;
  if((u16)remaining!=0) break;
  work->ready=1;
  {
   u32 count=CheckSourceStage(work->source,4);
   work->count=count;
   if((u8)count==0) event->state=264;
   else event->state++;
  }
  break;
 }
 case 263: {
  TaskNode **children=work->children;
  int ready;
  u32 slot,occupied;
  u16 counter;
  PollAndReleaseSequenceArray(children,2);
  ready=0;
  if(work->ready!=0) {work->ready=0;ready=1;}
  if(!ready) break;
  occupied=(u32)children[0];
  /* Native unsigned nonzero normalization has no conditional CFG edge. */
  slot=((0U-occupied)|occupied)>>31;
  repeated_event.selector=work->variant;
  counter=work->counter;
  repeated_event.mode=counter;
  repeated_event.source=ReadSequenceTarget(work->source,(u8)counter);
  repeated_event.output=&work->ready;
  children[slot]=CreateOppositePhaseTask(RepeatedActorCallback,64,&repeated_event,parent);
  {
   u32 next=work->counter+1;
   work->counter=next;
   if((u16)next==work->count) event->state++;
  }
  break;
 }
 case 264: {
  TaskNode *child=PollAndReleaseChild(work->leading);
  work->leading=child;
  if(child!=0) break;
  if((u8)PollAndReleaseSequenceArray(work->children,2)!=0) event->state=2;
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
 ".global CountSourceTargets\n.thumb_set CountSourceTargets,0x080DD495\n"
 ".global GetRecordNestedPointer\n.thumb_set GetRecordNestedPointer,0x080DD47D\n"
 ".global ConfigureNestedTransition\n.thumb_set ConfigureNestedTransition,0x080DE10D\n"
 ".global CreateReadyTransition\n.thumb_set CreateReadyTransition,0x080DE4B1\n"
 ".global ReadNestedCoordinates\n.thumb_set ReadNestedCoordinates,0x080DBDC9\n"
 ".global CreatePositionedDefinitionTask\n.thumb_set CreatePositionedDefinitionTask,0x080D6099\n"
 ".global CreateSecondarySequence\n.thumb_set CreateSecondarySequence,0x080DFD8D\n"
 ".global PollPositionedDefinition\n.thumb_set PollPositionedDefinition,0x080D6135\n"
 ".global ReadSourceProperty\n.thumb_set ReadSourceProperty,0x080DD699\n"
 ".global ReadNestedUnitIndex\n.thumb_set ReadNestedUnitIndex,0x080DD479\n"
 ".global ReadUnitField\n.thumb_set ReadUnitField,0x080C7EA5\n"
 ".global CreateSpriteDefinition\n.thumb_set CreateSpriteDefinition,0x080D5CC1\n"
 ".global PollSpriteDefinition\n.thumb_set PollSpriteDefinition,0x08011485\n"
 ".global SetDefinitionMode\n.thumb_set SetDefinitionMode,0x080DB945\n"
 ".global QueryDefinitionReadiness\n.thumb_set QueryDefinitionReadiness,0x080D8B4D\n"
 ".global CreateOppositePhaseTask\n.thumb_set CreateOppositePhaseTask,0x08005B6D\n"
 ".global ReleaseReadyTransition\n.thumb_set ReleaseReadyTransition,0x080DBA51\n"
 ".global CheckSourceStage\n.thumb_set CheckSourceStage,0x080D8859\n"
 ".global PollAndReleaseSequenceArray\n.thumb_set PollAndReleaseSequenceArray,0x080E0571\n"
 ".global ReadSequenceTarget\n.thumb_set ReadSequenceTarget,0x080DD4A5\n"
 ".global PollAndReleaseChild\n.thumb_set PollAndReleaseChild,0x080E051D\n"
 ".global InitialSequenceData\n.set InitialSequenceData,0x0839FBD8\n"
 ".global FollowupSequences\n.set FollowupSequences,0x0839FC08\n"
 ".global VariantPaletteRecords\n.set VariantPaletteRecords,0x0839FD64\n"
 ".global DefaultObjectPalette\n.set DefaultObjectPalette,0x088E9C70\n"
 ".global SpecialObjectPalette\n.set SpecialObjectPalette,0x088EA81C\n"
 ".global PaletteSelectors\n.set PaletteSelectors,0x0839FD84\n"
 ".global PositionedData\n.set PositionedData,0x0839FCC8\n"
 ".global SecondaryData\n.set SecondaryData,0x0839FDD0\n"
 ".global OptionalSecondaryData\n.set OptionalSecondaryData,0x0839FDF0\n"
 ".global SpriteResource\n.set SpriteResource,0x084FE428\n"
 ".global DescriptorSelectors\n.set DescriptorSelectors,0x08149E54\n"
 ".global InitializeDescriptor\n.set InitializeDescriptor,0x0836D4B8\n"
 ".global LeadingActorCallback\n.thumb_set LeadingActorCallback,0x08105685\n"
 ".global RepeatedActorCallback\n.thumb_set RepeatedActorCallback,0x0810578D\n"
);

/* Existing original typed interwork trampoline; no emitted instructions. */
__asm__(".global _call_via_r2\n.thumb_set _call_via_r2,0x0814224D\n");
