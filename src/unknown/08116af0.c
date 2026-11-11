typedef unsigned char u8;typedef unsigned short u16;typedef signed short s16;typedef unsigned int u32;typedef signed int s32;typedef struct TaskNode TaskNode;typedef void (*TaskCallback)(TaskNode *,void *,void *);
struct SequenceEvent {u16 phase,unknown02;void *owner;u8 unknown08[12];s16 definition;u16 variant;u8 unknown18[4];};
struct PartialEvent {u32 untouched00;void *owner;u32 zero,one;u8 untouched16[4];u16 definition,variant;u32 untouched24;};
struct SequenceWork {s16 x,y;u8 variant,count;u16 timer;TaskNode *child,*palette;void *resource;TaskNode *auxiliary;void *owner;TaskNode *opening,*stage;};
extern TaskNode * CreateDefinitionEffectTask(void *,const void *,u32,u32,const void *,TaskNode *);
extern void FinishDefinitionSequence(void);
extern TaskNode * PollDefinitionEffectTask(TaskNode *);
extern u32 ReadDefinitionTargetRowCount(const void *);
extern void ReadDefinitionOwnerCoordinates(void *,u16 *,u16 *);
extern void ConfigureDefinitionResourceCoordinates(u8,u8,u16,s16,s16);
extern void * CreateDefinitionResource(u8,const void *,u16,u8);
extern u32 ReadDisplayHighMaskWord(u8);
extern TaskNode * CreateDefinitionAuxiliaryTask(const void *,TaskNode *);
extern TaskNode * CreateDefinitionPaletteTask(const void *,TaskNode *);
extern TaskNode * CreateDefinitionStageTask(const void *,u8,u16,u8,TaskNode *);
extern u32 StartDefinitionOwnerResponse(void *,u16,u16,TaskNode *);
extern TaskNode * CreateTaskInCurrentGroup(TaskCallback,u16,const void *,TaskNode *);
extern void * PollAndReleaseDefinitionResource(void *,u8);
extern TaskNode * PollDefinitionAuxiliary(TaskNode *);
extern TaskNode * PollDefinitionPalette(TaskNode *);
extern TaskNode * PollAndReleaseDefinitionChild(TaskNode *);
extern const u8 gOpeningSequence[],gResourceRecord[],gAuxiliarySequence[],gPaletteSequence[],gStageSequence[];
extern void AdvanceNestedDefinitionChild(TaskNode *,void *,void *);
__asm__(
 ".global CreateDefinitionEffectTask\n.thumb_set CreateDefinitionEffectTask,0x80e03f9\n"
 ".global FinishDefinitionSequence\n.thumb_set FinishDefinitionSequence,0x80d38b5\n"
 ".global PollDefinitionEffectTask\n.thumb_set PollDefinitionEffectTask,0x80e05dd\n"
 ".global ReadDefinitionTargetRowCount\n.thumb_set ReadDefinitionTargetRowCount,0x80dd495\n"
 ".global ReadDefinitionOwnerCoordinates\n.thumb_set ReadDefinitionOwnerCoordinates,0x80d8c59\n"
 ".global ConfigureDefinitionResourceCoordinates\n.thumb_set ConfigureDefinitionResourceCoordinates,0x80d49fd\n"
 ".global CreateDefinitionResource\n.thumb_set CreateDefinitionResource,0x80d4b65\n"
 ".global ReadDisplayHighMaskWord\n.thumb_set ReadDisplayHighMaskWord,0x80035a9\n"
 ".global CreateDefinitionAuxiliaryTask\n.thumb_set CreateDefinitionAuxiliaryTask,0x80d3e9d\n"
 ".global CreateDefinitionPaletteTask\n.thumb_set CreateDefinitionPaletteTask,0x80d4705\n"
 ".global CreateDefinitionStageTask\n.thumb_set CreateDefinitionStageTask,0x80dfd8d\n"
 ".global StartDefinitionOwnerResponse\n.thumb_set StartDefinitionOwnerResponse,0x80d8925\n"
 ".global CreateTaskInCurrentGroup\n.thumb_set CreateTaskInCurrentGroup,0x8005b6d\n"
 ".global PollAndReleaseDefinitionResource\n.thumb_set PollAndReleaseDefinitionResource,0x80d4d2d\n"
 ".global PollDefinitionAuxiliary\n.thumb_set PollDefinitionAuxiliary,0x80d3f09\n"
 ".global PollDefinitionPalette\n.thumb_set PollDefinitionPalette,0x80d4775\n"
 ".global PollAndReleaseDefinitionChild\n.thumb_set PollAndReleaseDefinitionChild,0x80e051d\n"
 ".global gOpeningSequence\n.set gOpeningSequence,0x83a4cb0\n"
 ".global gResourceRecord\n.set gResourceRecord,0x88f06b0\n"
 ".global gAuxiliarySequence\n.set gAuxiliarySequence,0x894daa0\n"
 ".global gPaletteSequence\n.set gPaletteSequence,0x894ab50\n"
 ".global gStageSequence\n.set gStageSequence,0x83a4cd4\n"
 ".global AdvanceNestedDefinitionChild\n.thumb_set AdvanceNestedDefinitionChild,0x80e7c05\n"
);
typedef char WorkSize[sizeof(struct SequenceWork)==36?1:-1];
typedef char PartialEventSize[sizeof(struct PartialEvent)==28?1:-1];
s32 AdvanceAuthoredCountedNestedDefinitionSequence(TaskNode *,struct SequenceEvent *,struct SequenceWork *) __asm__("OriginalActionCallback_00116AF0");
s32 AdvanceAuthoredCountedNestedDefinitionSequence(TaskNode *input_parent,struct SequenceEvent *input_event,struct SequenceWork *input_work)
{
 struct PartialEvent partial;
 TaskNode *parent=input_parent;
 struct SequenceEvent *event=input_event;
 struct SequenceWork *work=input_work;
 register u32 phase __asm__("r3");
 __asm__("" : "+r"(parent), "+r"(event), "+r"(work));
 phase=event->phase;__asm__("" : "+r"(phase));
 switch((s32)phase){
 case 0:{
  u16 variant=event->variant;
  void *owner;
  register u32 count __asm__("r5");
  work->variant=variant;owner=event->owner;work->owner=owner;
  count=3;__asm__("" : "+r"(count));if((u8)variant!=0)count=0;
  work->opening=CreateDefinitionEffectTask(owner,gOpeningSequence,count,1,(const void *)phase,parent);
  break;
 }
 case 1:FinishDefinitionSequence();break;
 case 256:
  work->opening=PollDefinitionEffectTask(work->opening);if(work->opening!=0)break;
  if(work->variant!=0){work->count=ReadDefinitionTargetRowCount(work->owner);event->phase=258;}
  else ++event->phase;
  break;
 case 257:{
  u32 mask,count;u16 *shadow;
  register u32 previous __asm__("r1");
  ReadDefinitionOwnerCoordinates(work->owner,(u16 *)&work->x,(u16 *)&work->y);
  ConfigureDefinitionResourceCoordinates(0,2,0,work->x,work->y);
  work->resource=CreateDefinitionResource(0,gResourceRecord,800,6);
  mask=ReadDisplayHighMaskWord(2);shadow=(u16 *)0x03000940;
  previous=*shadow;__asm__("" : "+r"(previous));
  previous|=mask;__asm__("" : "+r"(previous));*shadow=previous;
  work->auxiliary=CreateDefinitionAuxiliaryTask(gAuxiliarySequence,parent);
  work->palette=CreateDefinitionPaletteTask(gPaletteSequence,parent);
  work->stage=CreateDefinitionStageTask(gStageSequence,1,4,0,parent);
  count=StartDefinitionOwnerResponse(work->owner,0,30,parent);work->count=count;
  if((u8)count==0)event->phase=259;
  else{work->timer=38;++event->phase;}
  break;
 }
 case 258:{
  register u32 next __asm__("r0");
  register u32 zero __asm__("r2");
  next=work->timer-1;__asm__("" : "+r"(next));work->timer=next;
  zero=(u16)next;__asm__("" : "+r"(zero));if(zero!=0)break;
  partial.definition=316;partial.variant=work->variant;partial.owner=work->owner;
  partial.zero=zero;partial.one=1;
  work->child=CreateTaskInCurrentGroup(AdvanceNestedDefinitionChild,20,&partial,parent);
  ++event->phase;break;
 }
 case 259:{
  u32 mask;u16 *shadow;
  register u32 previous __asm__("r1");
  work->resource=PollAndReleaseDefinitionResource(work->resource,0);if(work->resource!=0)break;
  mask=ReadDisplayHighMaskWord(2);shadow=(u16 *)0x03000940;
  previous=*shadow;__asm__("" : "+r"(previous));*shadow=previous&~mask;
  work->auxiliary=PollDefinitionAuxiliary(work->auxiliary);if(work->auxiliary!=0)break;
  work->palette=PollDefinitionPalette(work->palette);if(work->palette!=0)break;
  work->child=PollAndReleaseDefinitionChild(work->child);if(work->child==0)event->phase=2;
  break;
 }
 }
 return 0;
}
