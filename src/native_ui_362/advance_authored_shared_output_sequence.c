typedef unsigned char u8;typedef unsigned short u16;typedef signed short s16;typedef unsigned int u32;typedef signed int s32;typedef struct TaskNode TaskNode;typedef void (*TaskCallback)(TaskNode *,void *,void *);
struct SequenceEvent {u16 phase,unknown02;void *owner;u8 unknown08[12];s16 definition;u16 variant;u8 unknown18[4];};
struct PartialEvent {u32 untouched00;void *output;u8 untouched08[20];};
struct SequenceWork {u16 timer;u8 variant,unknown03;TaskNode *first,*second,*palette,*auxiliary;u8 output[320];void *owner;TaskNode *opening,*followup,*fade;};
extern TaskNode * CreateDefinitionEffectTask(void *,const void *,u32,u32,const void *,TaskNode *);
extern void FinishDefinitionSequence(void);
extern TaskNode * PollDefinitionEffectTask(TaskNode *);
extern TaskNode * CreateDefinitionFadeTask(u8,u16,TaskNode *);
extern TaskNode * PollDefinitionFadeTask(TaskNode *);
extern void ConfigureDefinitionRecordResource(const void *,u8,u8,s32,u32,u32);
extern TaskNode * CreateDefinitionPaletteTask(const void *,TaskNode *);
extern void SetDefinitionPaletteEnabled(TaskNode *,u8);
extern TaskNode * CreateDefinitionAuxiliaryTask(const void *,TaskNode *);
extern TaskNode * CreateTaskInCurrentGroup(TaskCallback,u16,const void *,TaskNode *);
extern TaskNode * PollDefinitionAuxiliary(TaskNode *);
extern u32 IsTaskStateTwo(const TaskNode *);
extern void RemoveCurrentGroupTask(TaskNode *);
extern void RemoveDefinitionPaletteTask(TaskNode *);
extern void ClearRelatedRecordFlags(void *);
extern u32 CheckDefinitionOwnerReadiness(void *,u16);
extern TaskNode * CreateAuthoredFollowup(void *,u32,TaskNode *);
extern TaskNode * PollAndReleaseActionEffectChild(TaskNode *);
extern const u8 gOpeningSequence[],gResourceRecord[],gPaletteSequence[],gAuxiliarySequence[],gEndingSequence[];
extern void AdvanceFirstAuthoredChild(TaskNode *,void *,void *);
extern void AdvanceSecondAuthoredChild(TaskNode *,void *,void *);
__asm__(
 ".global CreateDefinitionEffectTask\n.thumb_set CreateDefinitionEffectTask,0x80e03f9\n"
 ".global FinishDefinitionSequence\n.thumb_set FinishDefinitionSequence,0x80d38b5\n"
 ".global PollDefinitionEffectTask\n.thumb_set PollDefinitionEffectTask,0x80e05dd\n"
 ".global CreateDefinitionFadeTask\n.thumb_set CreateDefinitionFadeTask,0x80dfd69\n"
 ".global PollDefinitionFadeTask\n.thumb_set PollDefinitionFadeTask,0x80dfed9\n"
 ".global ConfigureDefinitionRecordResource\n.thumb_set ConfigureDefinitionRecordResource,0x80d7221\n"
 ".global CreateDefinitionPaletteTask\n.thumb_set CreateDefinitionPaletteTask,0x80d4705\n"
 ".global SetDefinitionPaletteEnabled\n.thumb_set SetDefinitionPaletteEnabled,0x80d47a1\n"
 ".global CreateDefinitionAuxiliaryTask\n.thumb_set CreateDefinitionAuxiliaryTask,0x80d3e9d\n"
 ".global CreateTaskInCurrentGroup\n.thumb_set CreateTaskInCurrentGroup,0x8005b6d\n"
 ".global PollDefinitionAuxiliary\n.thumb_set PollDefinitionAuxiliary,0x80d3f09\n"
 ".global IsTaskStateTwo\n.thumb_set IsTaskStateTwo,0x8005bb1\n"
 ".global RemoveCurrentGroupTask\n.thumb_set RemoveCurrentGroupTask,0x8005b59\n"
 ".global RemoveDefinitionPaletteTask\n.thumb_set RemoveDefinitionPaletteTask,0x80d4769\n"
 ".global ClearRelatedRecordFlags\n.thumb_set ClearRelatedRecordFlags,0x80edb81\n"
 ".global CheckDefinitionOwnerReadiness\n.thumb_set CheckDefinitionOwnerReadiness,0x80d8859\n"
 ".global CreateAuthoredFollowup\n.thumb_set CreateAuthoredFollowup,0x80edb99\n"
 ".global PollAndReleaseActionEffectChild\n.thumb_set PollAndReleaseActionEffectChild,0x80edbdd\n"
 ".global gOpeningSequence\n.set gOpeningSequence,0x8399288\n"
 ".global gResourceRecord\n.set gResourceRecord,0x88f4d7c\n"
 ".global gPaletteSequence\n.set gPaletteSequence,0x894904c\n"
 ".global gAuxiliarySequence\n.set gAuxiliarySequence,0x894d69c\n"
 ".global gEndingSequence\n.set gEndingSequence,0x894d720\n"
 ".global AdvanceFirstAuthoredChild\n.thumb_set AdvanceFirstAuthoredChild,0x80ed4e9\n"
 ".global AdvanceSecondAuthoredChild\n.thumb_set AdvanceSecondAuthoredChild,0x80ed045\n"
);
typedef char WorkSize[sizeof(struct SequenceWork)==356?1:-1];
typedef char PartialEventSize[sizeof(struct PartialEvent)==28?1:-1];
s32 AdvanceAuthoredSharedOutputSequence(TaskNode *,struct SequenceEvent *,struct SequenceWork *) __asm__("OriginalActionCallback_000ED7B0");
s32 AdvanceAuthoredSharedOutputSequence(TaskNode *input_parent,struct SequenceEvent *input_event,struct SequenceWork *input_work)
{
 struct PartialEvent partial;
 TaskNode *parent=input_parent;
 register struct SequenceEvent *event __asm__("r6")=input_event;
 struct SequenceWork *work=input_work;
 register u32 phase __asm__("r1");
 __asm__("" : "+r"(parent), "+r"(event), "+r"(work));
 phase=event->phase;__asm__("" : "+r"(phase));
 switch((s32)phase){
 case 0:{
  void *owner;
  void **owner_cell;
  register u32 variant __asm__("r0");
  work->variant=event->variant;
  owner_cell=&work->owner;__asm__("" : : "r"(owner_cell));
  owner=event->owner;*owner_cell=owner;
  variant=work->variant;if(variant!=0)break;
  __asm__("" : "+r"(variant));
  work->opening=CreateDefinitionEffectTask(owner,gOpeningSequence,4,4,(const void *)variant,parent);
  break;
 }
 case 1:FinishDefinitionSequence();break;
 case 256:
  if(work->variant!=0){work->opening=PollDefinitionEffectTask(work->opening);if(work->opening==0)event->phase=261;}
  else{work->fade=CreateDefinitionFadeTask(1,30,parent);++event->phase;}
  break;
 case 257:{
  register TaskNode *fade __asm__("r1");
  TaskNode *palette;
  work->opening=PollDefinitionEffectTask(work->opening);if(work->opening!=0)break;
  fade=PollDefinitionFadeTask(work->fade);__asm__("" : "+r"(fade));work->fade=fade;if(fade!=0)break;
  ConfigureDefinitionRecordResource(gResourceRecord,0,2,120,(u32)fade,(u32)fade);
  palette=CreateDefinitionPaletteTask(gPaletteSequence,parent);work->palette=palette;SetDefinitionPaletteEnabled(palette,1);
  work->auxiliary=CreateDefinitionAuxiliaryTask(gAuxiliarySequence,parent);
  partial.output=work->output;
  work->first=CreateTaskInCurrentGroup(AdvanceFirstAuthoredChild,484,&partial,parent);
  work->second=CreateTaskInCurrentGroup(AdvanceSecondAuthoredChild,188,&partial,parent);
  ++event->phase;break;
 }
 case 258:
  /* Auxiliary polling is unconditional here; only the first child's state gates progress. */
  work->auxiliary=PollDefinitionAuxiliary(work->auxiliary);
  if(IsTaskStateTwo(work->first)==0)break;
  work->auxiliary=CreateDefinitionAuxiliaryTask(gEndingSequence,parent);work->timer=30;++event->phase;
  break;
 case 259:{
  register u32 next __asm__("r0");
  register u32 zero __asm__("r4");
  next=work->timer-1;__asm__("" : "+r"(next));work->timer=next;
  zero=(u16)next;__asm__("" : "+r"(zero));if(zero!=0)break;
  RemoveCurrentGroupTask(work->first);work->first=(TaskNode *)zero;
  RemoveCurrentGroupTask(work->second);work->second=(TaskNode *)zero;
  RemoveDefinitionPaletteTask(work->palette);
  work->fade=CreateDefinitionFadeTask(0,30,parent);ClearRelatedRecordFlags(work->owner);
  ++event->phase;break;
 }
 case 260:
  work->auxiliary=PollDefinitionAuxiliary(work->auxiliary);if(work->auxiliary!=0)break;
  work->fade=PollDefinitionFadeTask(work->fade);if(work->fade!=0)break;
  if((u8)CheckDefinitionOwnerReadiness(work->owner,0)!=0)++event->phase;else event->phase=2;
  break;
 case 261:
  work->followup=CreateAuthoredFollowup(work->owner,7,parent);++event->phase;break;
 case 262:
  work->followup=PollAndReleaseActionEffectChild(work->followup);if(work->followup==0)event->phase=2;
  break;
 }
 return 0;
}
