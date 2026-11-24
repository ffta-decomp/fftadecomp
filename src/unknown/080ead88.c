typedef unsigned char u8;typedef unsigned short u16;typedef signed int s32;typedef unsigned int u32;typedef struct TaskNode TaskNode;
struct SequenceEvent {u16 phase,unknown02;void *owner;u8 unknown08[12];u16 definition,variant;u8 unknown18[4];};
struct SequenceWork {u16 timer;u8 variant,unknown03;TaskNode *child,*second_child,*auxiliary,*palette,*control;void *owner;TaskNode *followup,*opening,*stage,*fade;};
extern TaskNode * CreateDefinitionEffectTask(void *,const void *,u8,u32,const void *,TaskNode *);
extern void FinishDefinitionSequence(void);
extern TaskNode * PollDefinitionEffectTask(TaskNode *);
extern TaskNode * CreateDefinitionFadeTask(u8,u16,TaskNode *);
extern TaskNode * PollDefinitionFadeTask(TaskNode *);
extern void PlaceDefinitionResource(const void *,u32,u32,s32,s32,u32);
extern TaskNode * CreateDefinitionAuxiliaryTask(const void *,TaskNode *);
extern TaskNode * CreateDefinitionPaletteTask(const void *,TaskNode *);
extern TaskNode * CreateDefinitionControlTask(u8,u16,u16,u16,const void *,TaskNode *);
extern TaskNode * CreateDefinitionTask(const void *,u16,const void *,TaskNode *);
extern TaskNode * CreateDefinitionStageTask(const void *,u8,u16,u8,TaskNode *);
extern void ClearRelatedRecordFlags(void *);
extern TaskNode * PollDefinitionAuxiliary(TaskNode *);
extern TaskNode * PollDefinitionPalette(TaskNode *);
extern void BeginDefinitionControlRelease(TaskNode *);
extern u32 ReadDisplayHighMaskWord(u8);
extern void RemoveCurrentGroupTask(TaskNode *);
extern void RemoveDefinitionControlTask(TaskNode *);
extern u32 CountDefinitionTargets(void *,u16);
extern TaskNode * CreateActionEffectChild(void *,u8,TaskNode *);
extern TaskNode * PollAndReleaseActionEffectChild(TaskNode *);
extern const u8 gOpeningSequence[],gStageSequence[],gFirstChildEntry[],gSecondChildEntry[],gResource[],gPaletteSequence[],gAuxiliarySequence[],gControlSequence[];
__asm__(
 ".global CreateDefinitionEffectTask\n.thumb_set CreateDefinitionEffectTask,0x80e03f9\n"
 ".global FinishDefinitionSequence\n.thumb_set FinishDefinitionSequence,0x80d38b5\n"
 ".global PollDefinitionEffectTask\n.thumb_set PollDefinitionEffectTask,0x80e05dd\n"
 ".global CreateDefinitionFadeTask\n.thumb_set CreateDefinitionFadeTask,0x80dfd69\n"
 ".global PollDefinitionFadeTask\n.thumb_set PollDefinitionFadeTask,0x80dfed9\n"
 ".global PlaceDefinitionResource\n.thumb_set PlaceDefinitionResource,0x80d7221\n"
 ".global CreateDefinitionAuxiliaryTask\n.thumb_set CreateDefinitionAuxiliaryTask,0x80d3e9d\n"
 ".global CreateDefinitionPaletteTask\n.thumb_set CreateDefinitionPaletteTask,0x80d4705\n"
 ".global CreateDefinitionControlTask\n.thumb_set CreateDefinitionControlTask,0x80d98d5\n"
 ".global CreateDefinitionTask\n.thumb_set CreateDefinitionTask,0x8005b6d\n"
 ".global CreateDefinitionStageTask\n.thumb_set CreateDefinitionStageTask,0x80dfd8d\n"
 ".global ClearRelatedRecordFlags\n.thumb_set ClearRelatedRecordFlags,0x80edb81\n"
 ".global PollDefinitionAuxiliary\n.thumb_set PollDefinitionAuxiliary,0x80d3f09\n"
 ".global PollDefinitionPalette\n.thumb_set PollDefinitionPalette,0x80d4775\n"
 ".global BeginDefinitionControlRelease\n.thumb_set BeginDefinitionControlRelease,0x80d9b39\n"
 ".global ReadDisplayHighMaskWord\n.thumb_set ReadDisplayHighMaskWord,0x80035a9\n"
 ".global RemoveCurrentGroupTask\n.thumb_set RemoveCurrentGroupTask,0x8005b59\n"
 ".global RemoveDefinitionControlTask\n.thumb_set RemoveDefinitionControlTask,0x80d9b59\n"
 ".global CountDefinitionTargets\n.thumb_set CountDefinitionTargets,0x80d8859\n"
 ".global CreateActionEffectChild\n.thumb_set CreateActionEffectChild,0x80edb99\n"
 ".global PollAndReleaseActionEffectChild\n.thumb_set PollAndReleaseActionEffectChild,0x80edbdd\n"
 ".global gOpeningSequence\n.set gOpeningSequence,0x8398c30\n"
 ".global gStageSequence\n.set gStageSequence,0x8398db0\n"
 ".global gFirstChildEntry\n.set gFirstChildEntry,0x80eab35\n"
 ".global gSecondChildEntry\n.set gSecondChildEntry,0x80eabe1\n"
 ".global gResource\n.set gResource,0x88f4d34\n"
 ".global gPaletteSequence\n.set gPaletteSequence,0x8948ff4\n"
 ".global gAuxiliarySequence\n.set gAuxiliarySequence,0x894d69c\n"
 ".global gControlSequence\n.set gControlSequence,0x8398d88\n"
);
typedef char WorkSize[sizeof(struct SequenceWork)==44?1:-1];
s32 AdvanceAuthoredPairedChildOwnerFlags(TaskNode *,struct SequenceEvent *,struct SequenceWork *) __asm__("OriginalActionCallback_000EAD88");
s32 AdvanceAuthoredPairedChildOwnerFlags(TaskNode *input_parent,struct SequenceEvent *input_event,struct SequenceWork *input_work)
{
 TaskNode *parent=input_parent;
 struct SequenceEvent *event=input_event;
 struct SequenceWork *work=input_work;
 register s32 phase __asm__("r1");
 u8 child_event[28];
 __asm__("" : "+r"(parent), "+r"(event), "+r"(work));
 phase=event->phase;__asm__("" : "+r"(phase));
 switch(phase){
 case 0:{
  u16 captured_variant=event->variant;
  void *owner;
  register u32 variant __asm__("r0");
  work->variant=captured_variant;owner=event->owner;work->owner=owner;
  variant=(u8)captured_variant;__asm__("" : "+r"(variant));
  if(variant!=0)break;
  work->opening=CreateDefinitionEffectTask(owner,gOpeningSequence,6,4,(const void *)variant,parent);
  break;
 }
 case 1:FinishDefinitionSequence();break;
 case 256:
  if(work->variant!=0){
   work->opening=PollDefinitionEffectTask(work->opening);if(work->opening!=0)break;
   event->phase=261;
  }else{work->fade=CreateDefinitionFadeTask(1,30,parent);++event->phase;}
  break;
 case 257:
  work->opening=PollDefinitionEffectTask(work->opening);if(work->opening!=0)break;
  work->fade=PollDefinitionFadeTask(work->fade);if(work->fade!=0)break;
  work->stage=CreateDefinitionStageTask(gStageSequence,2,4,0,parent);
  /* Both children receive the same untouched event storage, distinct payloads. */
  work->child=CreateDefinitionTask(gFirstChildEntry,20,child_event,parent);
  work->second_child=CreateDefinitionTask(gSecondChildEntry,728,child_event,parent);
  work->timer=120;++event->phase;break;
 case 258:{
  register u32 working __asm__("r0");
  register u32 remaining __asm__("r1");
  working=work->timer-1;__asm__("" : "+r"(working));
  work->timer=working;remaining=(u16)working;__asm__("" : "+r"(remaining));
  if(remaining!=0)break;
  PlaceDefinitionResource(gResource,0,2,0,(s32)remaining,remaining);
  work->palette=CreateDefinitionPaletteTask(gPaletteSequence,parent);
  work->auxiliary=CreateDefinitionAuxiliaryTask(gAuxiliarySequence,parent);
  work->control=CreateDefinitionControlTask(2,0,0,0,gControlSequence,parent);
  work->timer=240;++event->phase;break;
 }
 case 259:
  if(work->timer!=0){
   register u32 working __asm__("r0");
   register u32 remaining __asm__("r5");
   working=work->timer-1;__asm__("" : "+r"(working));
   work->timer=working;remaining=(u16)working;__asm__("" : "+r"(remaining));
   if(remaining==0){
    u32 mask;u16 *shadow;
    register u32 previous __asm__("r1");
    mask=ReadDisplayHighMaskWord(3);shadow=(u16 *)0x03000940;
    previous=*shadow;__asm__("" : "+r"(previous));*shadow=previous&~mask;
    RemoveCurrentGroupTask(work->child);work->child=(TaskNode *)remaining;
    RemoveCurrentGroupTask(work->second_child);work->second_child=(TaskNode *)remaining;
    work->fade=CreateDefinitionFadeTask(0,30,parent);
    ClearRelatedRecordFlags(work->owner);
   }
  }
  /* These polls short-circuit in the original, unlike the EA4A0 three-poll set. */
  work->auxiliary=PollDefinitionAuxiliary(work->auxiliary);if(work->auxiliary!=0)break;
  work->palette=PollDefinitionPalette(work->palette);if(work->palette!=0)break;
  BeginDefinitionControlRelease(work->control);++event->phase;break;
 case 260:
  work->fade=PollDefinitionFadeTask(work->fade);if(work->fade!=0)break;
  RemoveDefinitionControlTask(work->control);
  if((u8)CountDefinitionTargets(work->owner,0)==0)event->phase=2;else ++event->phase;
  break;
 case 261:
  work->followup=CreateActionEffectChild(work->owner,2,parent);++event->phase;break;
 case 262:
  work->followup=PollAndReleaseActionEffectChild(work->followup);if(work->followup==0)event->phase=2;
  break;
 }
 return 0;
}
