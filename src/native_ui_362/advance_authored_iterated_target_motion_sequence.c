typedef unsigned char u8;typedef unsigned short u16;typedef signed short s16;typedef unsigned int u32;typedef signed int s32;typedef struct TaskNode TaskNode;typedef void (*TaskCallback)(TaskNode *,void *,void *);
struct SequenceEvent {u16 phase,unknown02;void *owner;u8 unknown08[12];s16 definition;u16 variant;u8 unknown18[4];};
struct PartialEvent {u8 untouched[28];};
struct SequenceWork {u16 timer;u8 ordinal,count,variant;u8 untouched05[7];TaskNode *child;u32 untouched16;void *record;TaskNode *auxiliary,*palette,*opening;void *owner;TaskNode *motions[4],*stage;};
extern TaskNode * CreateDefinitionEffectTask(void *,const void *,u32,u32,const void *,TaskNode *);
extern u32 ReadDefinitionTargetRowCount(const void *);
extern void * GetSelectedDefinitionRecord(void *,u32);
extern void RefreshActorCurrentDirection(void *);
extern void FinishDefinitionSequence(void);
extern TaskNode * PollDefinitionEffectTask(TaskNode *);
extern void ConfigureDefinitionRecordResource(const void *,u8,u8,s32,u32,u32);
extern TaskNode * CreateDefinitionAuxiliaryTask(const void *,TaskNode *);
extern TaskNode * CreateDefinitionPaletteTask(const void *,TaskNode *);
extern TaskNode * CreateDefinitionStageTask(const void *,u8,u16,u8,TaskNode *);
extern TaskNode * CreateTaskInCurrentGroup(TaskCallback,u16,const void *,TaskNode *);
extern TaskNode * PollDefinitionAuxiliary(TaskNode *);
extern u32 ReadDisplayHighMaskWord(u8);
extern TaskNode * PollDefinitionPalette(TaskNode *);
extern TaskNode * PollAndReleaseDefinitionChild(TaskNode *);
extern void * GetDefinitionTargetRecord(void *,u32);
extern void * ReadOptionalDefinitionObjectCell(const void *);
extern u32 ApplyDefinitionCoordinateRectangle(const void *);
extern u32 ReadDefinitionReadiness(void);
extern u32 PollAndReleaseChildArray(TaskNode **,u32);
extern TaskNode * CreateDefinitionMotionTask(void *,const void *,u8,u16,u32,TaskNode *,u16);
extern const u8 gOpeningSequence[],gResourceRecord[],gAuxiliarySequence[],gPaletteSequence[],gStageSequence[],gMotionRow[];
extern void AdvanceUninitializedPartialChild(TaskNode *,void *,void *);
__asm__(
 ".global CreateDefinitionEffectTask\n.thumb_set CreateDefinitionEffectTask,0x80e03f9\n"
 ".global ReadDefinitionTargetRowCount\n.thumb_set ReadDefinitionTargetRowCount,0x80dd495\n"
 ".global GetSelectedDefinitionRecord\n.thumb_set GetSelectedDefinitionRecord,0x80dd4b5\n"
 ".global RefreshActorCurrentDirection\n.thumb_set RefreshActorCurrentDirection,0x80de269\n"
 ".global FinishDefinitionSequence\n.thumb_set FinishDefinitionSequence,0x80d38b5\n"
 ".global PollDefinitionEffectTask\n.thumb_set PollDefinitionEffectTask,0x80e05dd\n"
 ".global ConfigureDefinitionRecordResource\n.thumb_set ConfigureDefinitionRecordResource,0x80d7221\n"
 ".global CreateDefinitionAuxiliaryTask\n.thumb_set CreateDefinitionAuxiliaryTask,0x80d3e9d\n"
 ".global CreateDefinitionPaletteTask\n.thumb_set CreateDefinitionPaletteTask,0x80d4705\n"
 ".global CreateDefinitionStageTask\n.thumb_set CreateDefinitionStageTask,0x80dfd8d\n"
 ".global CreateTaskInCurrentGroup\n.thumb_set CreateTaskInCurrentGroup,0x8005b6d\n"
 ".global PollDefinitionAuxiliary\n.thumb_set PollDefinitionAuxiliary,0x80d3f09\n"
 ".global ReadDisplayHighMaskWord\n.thumb_set ReadDisplayHighMaskWord,0x80035a9\n"
 ".global PollDefinitionPalette\n.thumb_set PollDefinitionPalette,0x80d4775\n"
 ".global PollAndReleaseDefinitionChild\n.thumb_set PollAndReleaseDefinitionChild,0x80e051d\n"
 ".global GetDefinitionTargetRecord\n.thumb_set GetDefinitionTargetRecord,0x80dd4a5\n"
 ".global ReadOptionalDefinitionObjectCell\n.thumb_set ReadOptionalDefinitionObjectCell,0x80dd4c5\n"
 ".global ApplyDefinitionCoordinateRectangle\n.thumb_set ApplyDefinitionCoordinateRectangle,0x80db839\n"
 ".global ReadDefinitionReadiness\n.thumb_set ReadDefinitionReadiness,0x80d8b4d\n"
 ".global PollAndReleaseChildArray\n.thumb_set PollAndReleaseChildArray,0x80dbab9\n"
 ".global CreateDefinitionMotionTask\n.thumb_set CreateDefinitionMotionTask,0x80dcfe5\n"
 ".global gOpeningSequence\n.set gOpeningSequence,0x83a3e34\n"
 ".global gResourceRecord\n.set gResourceRecord,0x88f63d8\n"
 ".global gAuxiliarySequence\n.set gAuxiliarySequence,0x894dce4\n"
 ".global gPaletteSequence\n.set gPaletteSequence,0x894c474\n"
 ".global gStageSequence\n.set gStageSequence,0x83a4c78\n"
 ".global gMotionRow\n.set gMotionRow,0x83a4c64\n"
 ".global AdvanceUninitializedPartialChild\n.thumb_set AdvanceUninitializedPartialChild,0x8116515\n"
);
typedef char WorkSize[sizeof(struct SequenceWork)==60?1:-1];
typedef char PartialEventSize[sizeof(struct PartialEvent)==28?1:-1];
s32 AdvanceAuthoredIteratedTargetMotionSequence(TaskNode *,struct SequenceEvent *,struct SequenceWork *) __asm__("OriginalActionCallback_001168B4");
s32 AdvanceAuthoredIteratedTargetMotionSequence(TaskNode *input_parent,struct SequenceEvent *input_event,struct SequenceWork *input_work)
{
 struct PartialEvent partial;
 TaskNode *parent=input_parent;
 register struct SequenceEvent *event __asm__("r6")=input_event;
 struct SequenceWork *work=input_work;
 register u32 phase __asm__("r3");
 __asm__("" : "+r"(parent), "+r"(event), "+r"(work));
 phase=event->phase;__asm__("" : "+r"(phase));
 switch((s32)phase){
 case 0:{
  u16 variant=event->variant;
  register void *owner __asm__("r4");
  register u32 nonzero __asm__("r0");
  register u32 ordinal __asm__("r4");
  register u32 advanced __asm__("r0");
  u32 count;
  work->variant=variant;owner=event->owner;__asm__("" : "+r"(owner));work->owner=owner;
  count=4;if((u8)variant!=0)count=0;
  work->opening=CreateDefinitionEffectTask(owner,gOpeningSequence,count,7,(const void *)phase,parent);
  nonzero=ReadDefinitionTargetRowCount(work->owner);work->count=nonzero;
  nonzero<<=24;__asm__("" : : "r"(nonzero));
  ordinal=0;__asm__("" : "+r"(ordinal));
  if(nonzero!=0){
   do{
    RefreshActorCurrentDirection(GetSelectedDefinitionRecord(work->owner,ordinal));
    advanced=ordinal+1;__asm__("" : "+r"(advanced));ordinal=(u8)advanced;
   }while(ordinal<work->count);
  }
  break;
 }
 case 1:FinishDefinitionSequence();break;
 case 256:{
  register TaskNode *opening __asm__("r1");
  opening=PollDefinitionEffectTask(work->opening);__asm__("" : "+r"(opening));work->opening=opening;
  if(opening!=0)break;
  ConfigureDefinitionRecordResource(gResourceRecord,0,2,0,(u32)opening,(u32)opening);
  work->auxiliary=CreateDefinitionAuxiliaryTask(gAuxiliarySequence,parent);
  work->palette=CreateDefinitionPaletteTask(gPaletteSequence,parent);
  work->stage=CreateDefinitionStageTask(gStageSequence,2,4,0,parent);
  work->timer=60;++event->phase;break;
 }
 case 257:
  if(--work->timer!=0)break;
  /* All fields of this original partial event remain unwritten. */
  work->child=CreateTaskInCurrentGroup(AdvanceUninitializedPartialChild,364,&partial,parent);
  ++event->phase;break;
 case 258:{
  u32 mask;u16 *shadow;
  register u32 previous __asm__("r1");
  work->auxiliary=PollDefinitionAuxiliary(work->auxiliary);if(work->auxiliary!=0)break;
  mask=ReadDisplayHighMaskWord(2);shadow=(u16 *)0x03000940;
  previous=*shadow;__asm__("" : "+r"(previous));*shadow=previous&~mask;
  work->palette=PollDefinitionPalette(work->palette);if(work->palette!=0)break;
  work->child=PollAndReleaseDefinitionChild(work->child);if(work->child!=0)break;
  work->timer=1;++event->phase;break;
 }
 case 259:{
  void *record;
  if(--work->timer!=0)break;
  record=GetDefinitionTargetRecord(work->owner,work->ordinal);work->record=record;
  ApplyDefinitionCoordinateRectangle(ReadOptionalDefinitionObjectCell(record));
  ++event->phase;
  /* The original continues into readiness and motion creation in the same call. */
 }
 case 260:{
  register TaskNode **children __asm__("r8");
  register u32 ordinal __asm__("r2");
  register u32 odd __asm__("r0");
  register u32 flags __asm__("r4");
  register u32 next __asm__("r0");
  TaskNode *created;
  if((u8)ReadDefinitionReadiness()!=0)break;
  children=work->motions;__asm__("" : : "r"(children));
  PollAndReleaseChildArray(children,4);
  ordinal=work->ordinal;__asm__("" : : "r"(ordinal));
  odd=ordinal&1;__asm__("" : : "r"(odd));
  flags=2;__asm__("" : "+r"(flags));if(odd!=0)flags=4;
  created=CreateDefinitionMotionTask(work->record,gMotionRow,(u8)(12-(ordinal&6)),10,({ flags|=8;__asm__("" : "+r"(flags));flags; }),parent,10);
  /* The constructor can mutate the payload: select the destination from a fresh ordinal. */
  children[work->ordinal&3]=created;
  next=work->ordinal+1;__asm__("" : "+r"(next));work->ordinal=next;
  next=(u8)next;__asm__("" : "+r"(next));
  if(next==work->count)++event->phase;
  else{work->timer=40;event->phase=259;}
  break;
 }
 case 261:
  if((u8)PollAndReleaseChildArray(work->motions,4)!=0)event->phase=2;
  break;
 }
 return 0;
}
