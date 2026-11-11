typedef unsigned char u8;typedef signed char s8;typedef unsigned short u16;typedef signed short s16;typedef unsigned int u32;typedef signed int s32;typedef struct TaskNode TaskNode;
struct SequenceEvent {u16 phase,unknown02;void *record;u8 unknown08[12];s16 definition;u16 variant;u8 unknown18[4];};
struct ChildEvent {u32 unknown00;void *record;u8 unknown08[12];u16 kind,unknown16;u8 unknown18[4];};
struct SequenceWork {u8 kind,delay,variant,record_flag;u32 unknown04;s16 x,y;TaskNode *child;void *object;u32 unknown14;TaskNode *positioned;void *extra_object;TaskNode *extra_positioned,*palette0,*palette1,*palette2,*auxiliary,*motion,*opening;void *owner;TaskNode *stage;};
extern TaskNode *CreateDefinitionEffectTask(void *,const void *,u8,u32,const void *,TaskNode *);
extern void FinishDefinitionSequence(void);
extern TaskNode *PollDefinitionEffectTask(TaskNode *);
extern void *FillSequenceBytes(void *,s32,u32);
extern u32 CountDefinitionTargets(void *,u16);
extern void *GetDefinitionTargetRecord(void *,u32);
extern void *ReadOptionalDefinitionObjectCell(const void *);
extern void ProjectDefinitionRecordPosition(const void *,s16 *,s16 *);
extern TaskNode *CreatePositionedDefinitionTask(s32,s32,s32,u8,u32,void *,const void *,TaskNode *);
extern TaskNode *CreateDefinitionRecordMotion(void *,const void *,u8,u16,u16,TaskNode *,u16);
extern TaskNode *CreateDefinitionTask(const void *,u16,const void *,TaskNode *);
extern u32 TestEquipmentRecordFlag7(const void *);
extern TaskNode *CreateDefinitionStageTask(const void *,u8,u16,u8,TaskNode *);
extern TaskNode *CreateDefinitionPaletteTask(const void *,TaskNode *);
extern void SetDefinitionPaletteOption(TaskNode *,u8);
extern TaskNode *CreateDefinitionAuxiliaryTask(const void *,TaskNode *);
extern TaskNode *PollDefinitionAuxiliary(TaskNode *);
extern TaskNode *PollDefinitionPalette(TaskNode *);
extern void ReleasePositionedDefinitionTask(TaskNode *);
extern void RemoveCurrentGroupTask(TaskNode *);
extern u32 ReadDefinitionObjectOrderState(void *);
extern void SetDefinitionObjectSortKey(void *,s16);
extern void ReleaseDefinitionPalette(TaskNode *);
extern TaskNode *PollAndReleasePositionedDefinitionTask(TaskNode *);
extern TaskNode *PollAndReleaseDefinitionMotion(TaskNode *);
extern TaskNode *PollAndReleaseDefinitionChild(TaskNode *);
extern const u8 gOpeningSequence[],gChildEntry[],gPalette0Normal[],gPalette0Kind2[],gPalette1[],gAuxiliary0[],gPaletteTransition[],gAuxiliary1[],gExtraSequence[];
extern const void *const gPositionSequences0[];
extern const void *const gPositionSequences1[];
extern const void *const gFlaggedPaletteSequences[];
extern const u8 gMotionSequences[][20],gStageSequences[][8];
__asm__(
 ".global CreateDefinitionEffectTask\n.thumb_set CreateDefinitionEffectTask,0x80e03f9\n"
 ".global FinishDefinitionSequence\n.thumb_set FinishDefinitionSequence,0x80d38b5\n"
 ".global PollDefinitionEffectTask\n.thumb_set PollDefinitionEffectTask,0x80e05dd\n"
 ".global FillSequenceBytes\n.thumb_set FillSequenceBytes,0x8144461\n"
 ".global CountDefinitionTargets\n.thumb_set CountDefinitionTargets,0x80d8859\n"
 ".global GetDefinitionTargetRecord\n.thumb_set GetDefinitionTargetRecord,0x80dd4a5\n"
 ".global ReadOptionalDefinitionObjectCell\n.thumb_set ReadOptionalDefinitionObjectCell,0x80dd4c5\n"
 ".global ProjectDefinitionRecordPosition\n.thumb_set ProjectDefinitionRecordPosition,0x80dbdc9\n"
 ".global CreatePositionedDefinitionTask\n.thumb_set CreatePositionedDefinitionTask,0x80d6099\n"
 ".global CreateDefinitionRecordMotion\n.thumb_set CreateDefinitionRecordMotion,0x80dcfe5\n"
 ".global CreateDefinitionTask\n.thumb_set CreateDefinitionTask,0x8005b6d\n"
 ".global TestEquipmentRecordFlag7\n.thumb_set TestEquipmentRecordFlag7,0x80dd581\n"
 ".global CreateDefinitionStageTask\n.thumb_set CreateDefinitionStageTask,0x80dfd8d\n"
 ".global CreateDefinitionPaletteTask\n.thumb_set CreateDefinitionPaletteTask,0x80d4705\n"
 ".global SetDefinitionPaletteOption\n.thumb_set SetDefinitionPaletteOption,0x80d47a1\n"
 ".global CreateDefinitionAuxiliaryTask\n.thumb_set CreateDefinitionAuxiliaryTask,0x80d3e9d\n"
 ".global PollDefinitionAuxiliary\n.thumb_set PollDefinitionAuxiliary,0x80d3f09\n"
 ".global PollDefinitionPalette\n.thumb_set PollDefinitionPalette,0x80d4775\n"
 ".global ReleasePositionedDefinitionTask\n.thumb_set ReleasePositionedDefinitionTask,0x80d6129\n"
 ".global RemoveCurrentGroupTask\n.thumb_set RemoveCurrentGroupTask,0x8005b59\n"
 ".global ReadDefinitionObjectOrderState\n.thumb_set ReadDefinitionObjectOrderState,0x80110cd\n"
 ".global SetDefinitionObjectSortKey\n.thumb_set SetDefinitionObjectSortKey,0x8011059\n"
 ".global ReleaseDefinitionPalette\n.thumb_set ReleaseDefinitionPalette,0x80d4769\n"
 ".global PollAndReleasePositionedDefinitionTask\n.thumb_set PollAndReleasePositionedDefinitionTask,0x80d6135\n"
 ".global PollAndReleaseDefinitionMotion\n.thumb_set PollAndReleaseDefinitionMotion,0x80dba5d\n"
 ".global PollAndReleaseDefinitionChild\n.thumb_set PollAndReleaseDefinitionChild,0x80e051d\n"
 ".global gOpeningSequence\n.set gOpeningSequence,0x8398740\n"
 ".global gChildEntry\n.set gChildEntry,0x80e9bdd\n"
 ".global gPalette0Normal\n.set gPalette0Normal,0x8949294\n"
 ".global gPalette0Kind2\n.set gPalette0Kind2,0x8949db0\n"
 ".global gPalette1\n.set gPalette1,0x89492bc\n"
 ".global gAuxiliary0\n.set gAuxiliary0,0x894d768\n"
 ".global gPaletteTransition\n.set gPaletteTransition,0x89492cc\n"
 ".global gAuxiliary1\n.set gAuxiliary1,0x894d778\n"
 ".global gExtraSequence\n.set gExtraSequence,0x839880c\n"
 ".global gPositionSequences0\n.set gPositionSequences0,0x83987f4\n"
 ".global gPositionSequences1\n.set gPositionSequences1,0x8398800\n"
 ".global gFlaggedPaletteSequences\n.set gFlaggedPaletteSequences,0x8398824\n"
 ".global gMotionSequences\n.set gMotionSequences,0x8398888\n"
 ".global gStageSequences\n.set gStageSequences,0x83988b0\n"
);
typedef char WorkSize[sizeof(struct SequenceWork)==68?1:-1];
typedef char ChildSize[sizeof(struct ChildEvent)==28?1:-1];
s32 AdvanceAuthoredProjectedTargetSequence(TaskNode *,struct SequenceEvent *,struct SequenceWork *) __asm__("OriginalActionCallback_000E9E28");
s32 AdvanceAuthoredProjectedTargetSequence(TaskNode *input_parent,struct SequenceEvent *input_event,struct SequenceWork *input_work)
{
 TaskNode *parent=input_parent;
 register struct SequenceEvent *event __asm__("r6")=input_event;
 struct SequenceWork *work=input_work;
 register s32 phase __asm__("r1");
 struct ChildEvent child;
 s8 offsets[3];
 __asm__("" : "+r"(parent), "+r"(event), "+r"(work));
 phase=event->phase;__asm__("" : "+r"(phase));
 switch(phase) {
 case 0: {
  register u32 raw_definition __asm__("r1");
  register s32 definition __asm__("r0");
  u32 kind,count;u16 variant;void *owner;
  /* Distinct original unsigned snapshot, signed predicate, and branch-local working copy. */
  raw_definition=(u16)event->definition;__asm__("" : "+r"(raw_definition));
  definition=event->definition;__asm__("" : "+r"(definition));
  if(definition==84)kind=2;
  else {
   register u32 working __asm__("r0")=raw_definition;
   __asm__("" : "+r"(working));kind=working-39;
  }
  work->kind=kind;
  variant=event->variant;work->variant=variant;
  owner=event->record;work->owner=owner;
  count=3;if((u8)variant!=0)count=0;
  work->opening=CreateDefinitionEffectTask(owner,gOpeningSequence,count,1,0,parent);
  break;
 }
 case 1:FinishDefinitionSequence();break;
 case 256: {
  s8 *fill=offsets;
  register u32 offsets_base __asm__("r9")=(u32)fill;
  TaskNode *opening;
  register u32 opening_snapshot __asm__("r8");
  void *record;u32 kind,motion_index,stage_index,flag;s32 motion_parameter,x,y;
  __asm__("" : "+r"(offsets_base));
  FillSequenceBytes(fill,0,3);
  opening=PollDefinitionEffectTask(work->opening);
  opening_snapshot=(u32)opening;__asm__("" : "+r"(opening_snapshot));
  work->opening=opening;if(opening!=0)break;
  if((u8)CountDefinitionTargets(work->owner,0)==0){event->phase=2;break;}
  record=GetDefinitionTargetRecord(work->owner,0);
  ProjectDefinitionRecordPosition(ReadOptionalDefinitionObjectCell(record),&work->x,&work->y);
  x=work->x;y=(s16)((s8)*(u8 *)(offsets_base+work->kind)+(u16)work->y);
  work->positioned=CreatePositionedDefinitionTask(x,y,0,1,2,&work->object,gPositionSequences0[work->kind],parent);
  motion_parameter=220;kind=work->kind;if(kind==1)motion_parameter+=68;
  motion_index=0;if(kind==2)motion_index=1;
  work->motion=CreateDefinitionRecordMotion(record,gMotionSequences[motion_index],12,motion_parameter,4,parent,120);
  child.kind=work->kind;if(work->kind==2)child.kind=opening_snapshot;
  child.record=record;
  work->child=CreateDefinitionTask(gChildEntry,80,&child,parent);
  flag=TestEquipmentRecordFlag7(record);work->record_flag=flag;
  stage_index=work->kind;if(stage_index==2)stage_index=0;
  if((u8)flag==0)stage_index=2;
  work->stage=CreateDefinitionStageTask(gStageSequences[stage_index],1,4,0,parent);
  work->delay=20;++event->phase;
  break;
 }
 case 257: {
  register const void *sequence __asm__("r0");
  if(--work->delay!=0)break;
  /* Each native arm defines the actual first argument after its condition. */
  if(work->kind!=2){sequence=gPalette0Normal;__asm__("" : "+r"(sequence));}
  else {sequence=gPalette0Kind2;__asm__("" : "+r"(sequence));}
  work->palette0=CreateDefinitionPaletteTask(sequence,parent);
  work->palette1=CreateDefinitionPaletteTask(gPalette1,parent);
  SetDefinitionPaletteOption(work->palette1,1);
  work->auxiliary=CreateDefinitionAuxiliaryTask(gAuxiliary0,parent);
  work->delay=160;if(work->kind==1)work->delay=228;
  if(work->record_flag==0)work->delay=60;
  ++event->phase;break;
 }
 case 258:
  work->auxiliary=PollDefinitionAuxiliary(work->auxiliary);
  work->palette0=PollDefinitionPalette(work->palette0);
  if(--work->delay!=0)break;
  work->palette0=CreateDefinitionPaletteTask(gPaletteTransition,parent);
  if(work->record_flag!=0)work->palette2=CreateDefinitionPaletteTask(gFlaggedPaletteSequences[work->kind],parent);
  work->auxiliary=CreateDefinitionAuxiliaryTask(gAuxiliary1,parent);
  work->delay=10;++event->phase;break;
 case 259: {
  register u32 offsets_address __asm__("r2")=(u32)offsets;
  register u32 offsets_base __asm__("r8");
  register TaskNode *cleared __asm__("r5");
  s32 x,y;
  __asm__("" : "+r"(offsets_address));
  offsets_base=offsets_address;__asm__("" : "+r"(offsets_base));
  FillSequenceBytes((void *)offsets_base,0,3);
  if(work->delay!=0 && --work->delay!=0)break;
  work->auxiliary=PollDefinitionAuxiliary(work->auxiliary);if(work->auxiliary!=0)break;
  work->palette0=PollDefinitionPalette(work->palette0);if(work->palette0!=0)break;
  cleared=PollDefinitionPalette(work->palette2);__asm__("" : "+r"(cleared));
  work->palette2=cleared;if(cleared!=0)break;
  ReleasePositionedDefinitionTask(work->positioned);work->positioned=cleared;
  {
   register s32 loaded_x __asm__("r0");
   register u32 x_offset __asm__("r1");
   /* Bounded original signed-H8 read: both outputs are instruction-defined.
      The memory input declares exactly this fresh two-byte work-field read. */
   __asm__("mov %1,#8\n\tldrsh %0,[%2,%1]"
           : "=&r"(loaded_x), "=&r"(x_offset)
           : "r"(work), "m"(work->x) : "cc");
   x=loaded_x;
  }
  y=(s16)((s8)*(u8 *)(offsets_base+work->kind)+(u16)work->y);
  work->positioned=CreatePositionedDefinitionTask(x,y,0,1,1,&work->object,gPositionSequences1[work->kind],parent);
  RemoveCurrentGroupTask(work->child);work->child=cleared;
  work->delay=10;++event->phase;break;
 }
 case 260:
  if(--work->delay!=0)break;
  if(work->record_flag!=0)work->extra_positioned=CreatePositionedDefinitionTask(work->x,work->y,0,1,1,&work->extra_object,gExtraSequence,parent);
  ++event->phase;break;
 case 261:
  if((u16)ReadDefinitionObjectOrderState(work->extra_object)==0)SetDefinitionObjectSortKey(work->extra_object,-1);
  if(work->palette1!=0){ReleaseDefinitionPalette(work->palette1);work->palette1=0;}
  work->positioned=PollAndReleasePositionedDefinitionTask(work->positioned);if(work->positioned!=0)break;
  work->extra_positioned=PollAndReleasePositionedDefinitionTask(work->extra_positioned);if(work->extra_positioned!=0)break;
  work->motion=PollAndReleaseDefinitionMotion(work->motion);if(work->motion!=0)break;
  work->child=PollAndReleaseDefinitionChild(work->child);if(work->child!=0)break;
  event->phase=2;break;
 }
 return 0;
}
