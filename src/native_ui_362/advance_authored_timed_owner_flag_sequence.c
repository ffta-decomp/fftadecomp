typedef unsigned char u8;typedef unsigned short u16;typedef signed int s32;typedef unsigned int u32;typedef struct TaskNode TaskNode;
struct SequenceEvent {u16 phase,unknown02;void *owner;u8 unknown08[12];u16 definition,variant;u8 unknown18[4];};
struct SequenceWork {TaskNode *child;u8 variant,unknown05[3];u16 timer,unknown0a;void *owner;TaskNode *positioned;u8 output[32];TaskNode *auxiliary,*palette,*control,*opening,*followup,*stage,*fade;};
extern TaskNode * CreateDefinitionEffectTask(void *,const void *,u8,u32,const void *,TaskNode *);
extern void FinishDefinitionSequence(void);
extern TaskNode * PollDefinitionEffectTask(TaskNode *);
extern TaskNode * CreateDefinitionFadeTask(u8,u16,TaskNode *);
extern TaskNode * PollDefinitionFadeTask(TaskNode *);
extern void PlaceDefinitionResource(const void *,u32,u32,s32,s32,u32);
extern TaskNode * CreatePositionedDefinitionTask(s32,s32,s32,u8,u32,void *,const void *,TaskNode *);
extern TaskNode * CreateDefinitionAuxiliaryTask(const void *,TaskNode *);
extern TaskNode * CreateDefinitionPaletteTask(const void *,TaskNode *);
extern TaskNode * CreateDefinitionControlTask(u8,u8,u8,const void *,TaskNode *);
extern void SetDefinitionControlPair(TaskNode *,u8,u8,u8);
extern TaskNode * CreateDefinitionTask(const void *,u16,const void *,TaskNode *);
extern TaskNode * CreateDefinitionStageTask(const void *,u8,u16,u8,TaskNode *);
extern void ClearRelatedRecordFlags(void *);
extern TaskNode * PollAndReleasePositionedDefinitionTask(TaskNode *);
extern TaskNode * PollDefinitionAuxiliary(TaskNode *);
extern TaskNode * PollDefinitionPalette(TaskNode *);
extern void BeginDefinitionControlRelease(TaskNode *);
extern u32 ReadDisplayHighMaskWord(u8);
extern void RemoveCurrentGroupTask(TaskNode *);
extern void RemoveDefinitionControlTask(TaskNode *);
extern u32 CountDefinitionTargets(void *,u16);
extern TaskNode * CreateActionEffectChild(void *,u8,TaskNode *);
extern TaskNode * PollAndReleaseActionEffectChild(TaskNode *);
extern const u8 gOpeningSequence[],gResource[],gPositionSequence[],gAuxiliarySequence[],gPaletteSequence[],gControlSequence[],gChildEntry[],gStageSequence[];
__asm__(
 ".global CreateDefinitionEffectTask\n.thumb_set CreateDefinitionEffectTask,0x80e03f9\n"
 ".global FinishDefinitionSequence\n.thumb_set FinishDefinitionSequence,0x80d38b5\n"
 ".global PollDefinitionEffectTask\n.thumb_set PollDefinitionEffectTask,0x80e05dd\n"
 ".global CreateDefinitionFadeTask\n.thumb_set CreateDefinitionFadeTask,0x80dfd69\n"
 ".global PollDefinitionFadeTask\n.thumb_set PollDefinitionFadeTask,0x80dfed9\n"
 ".global PlaceDefinitionResource\n.thumb_set PlaceDefinitionResource,0x80d7221\n"
 ".global CreatePositionedDefinitionTask\n.thumb_set CreatePositionedDefinitionTask,0x80d6099\n"
 ".global CreateDefinitionAuxiliaryTask\n.thumb_set CreateDefinitionAuxiliaryTask,0x80d3e9d\n"
 ".global CreateDefinitionPaletteTask\n.thumb_set CreateDefinitionPaletteTask,0x80d4705\n"
 ".global CreateDefinitionControlTask\n.thumb_set CreateDefinitionControlTask,0x80d979d\n"
 ".global SetDefinitionControlPair\n.thumb_set SetDefinitionControlPair,0x80d984d\n"
 ".global CreateDefinitionTask\n.thumb_set CreateDefinitionTask,0x8005b6d\n"
 ".global CreateDefinitionStageTask\n.thumb_set CreateDefinitionStageTask,0x80dfd8d\n"
 ".global ClearRelatedRecordFlags\n.thumb_set ClearRelatedRecordFlags,0x80edb81\n"
 ".global PollAndReleasePositionedDefinitionTask\n.thumb_set PollAndReleasePositionedDefinitionTask,0x80d6135\n"
 ".global PollDefinitionAuxiliary\n.thumb_set PollDefinitionAuxiliary,0x80d3f09\n"
 ".global PollDefinitionPalette\n.thumb_set PollDefinitionPalette,0x80d4775\n"
 ".global BeginDefinitionControlRelease\n.thumb_set BeginDefinitionControlRelease,0x80d9b39\n"
 ".global ReadDisplayHighMaskWord\n.thumb_set ReadDisplayHighMaskWord,0x80035a9\n"
 ".global RemoveCurrentGroupTask\n.thumb_set RemoveCurrentGroupTask,0x8005b59\n"
 ".global RemoveDefinitionControlTask\n.thumb_set RemoveDefinitionControlTask,0x80d9b59\n"
 ".global CountDefinitionTargets\n.thumb_set CountDefinitionTargets,0x80d8859\n"
 ".global CreateActionEffectChild\n.thumb_set CreateActionEffectChild,0x80edb99\n"
 ".global PollAndReleaseActionEffectChild\n.thumb_set PollAndReleaseActionEffectChild,0x80edbdd\n"
 ".global gOpeningSequence\n.set gOpeningSequence,0x8398988\n"
 ".global gResource\n.set gResource,0x88f46fc\n"
 ".global gPositionSequence\n.set gPositionSequence,0x83989b8\n"
 ".global gAuxiliarySequence\n.set gAuxiliarySequence,0x894d69c\n"
 ".global gPaletteSequence\n.set gPaletteSequence,0x8948da8\n"
 ".global gControlSequence\n.set gControlSequence,0x8398a78\n"
 ".global gChildEntry\n.set gChildEntry,0x80ea3e9\n"
 ".global gStageSequence\n.set gStageSequence,0x8398a90\n"
);
typedef char WorkSize[sizeof(struct SequenceWork)==80?1:-1];
s32 AdvanceAuthoredTimedOwnerFlagSequence(TaskNode *,struct SequenceEvent *,struct SequenceWork *) __asm__("OriginalActionCallback_000EA4A0");
s32 AdvanceAuthoredTimedOwnerFlagSequence(TaskNode *input_parent,struct SequenceEvent *input_event,struct SequenceWork *input_work)
{
 TaskNode *parent=input_parent;
 struct SequenceEvent *event=input_event;
 struct SequenceWork *work=input_work;
 register s32 phase __asm__("r1");
 u8 child_event[28];
 __asm__("" : "+r"(parent), "+r"(event), "+r"(work));
 phase=event->phase;__asm__("" : "+r"(phase));
 switch(phase) {
 case 0: {
  u16 captured_variant=event->variant;
  void *owner;
  register u32 variant __asm__("r0");
  work->variant=captured_variant;owner=event->owner;work->owner=owner;
  variant=(u8)captured_variant;__asm__("" : "+r"(variant));
  if(variant!=0)break;
  work->opening=CreateDefinitionEffectTask(owner,gOpeningSequence,4,4,(const void *)variant,parent);
  break;
 }
 case 1:FinishDefinitionSequence();break;
 case 256:
  /* Both variant branches follow their actual native handle policy, even
     though phase0 left opening untouched in the nonzero-variant arm. */
  if(work->variant!=0){
   work->opening=PollDefinitionEffectTask(work->opening);if(work->opening!=0)break;
   event->phase=260;
  }else{work->fade=CreateDefinitionFadeTask(1,30,parent);++event->phase;}
  break;
 case 257: {
  register TaskNode *cleared __asm__("r1");
  TaskNode *control;
  work->opening=PollDefinitionEffectTask(work->opening);if(work->opening!=0)break;
  cleared=PollDefinitionFadeTask(work->fade);__asm__("" : "+r"(cleared));
  work->fade=cleared;if(cleared!=0)break;
  /* The actual full NULL result supplies the fifth and sixth stack words. */
  PlaceDefinitionResource(gResource,0,2,0,(s32)cleared,(u32)cleared);
  work->positioned=CreatePositionedDefinitionTask(0,0,0,0,8,work->output,gPositionSequence,parent);
  work->auxiliary=CreateDefinitionAuxiliaryTask(gAuxiliarySequence,parent);
  work->palette=CreateDefinitionPaletteTask(gPaletteSequence,parent);
  control=CreateDefinitionControlTask(1,2,0,gControlSequence,parent);work->control=control;
  SetDefinitionControlPair(control,0,4,155);
  SetDefinitionControlPair(work->control,1,64,111);
  /* Native passes this independent event storage without initializing it. */
  work->child=CreateDefinitionTask(gChildEntry,8,child_event,parent);
  work->stage=CreateDefinitionStageTask(gStageSequence,10,4,0,parent);
  work->timer=301;++event->phase;
  break;
 }
 case 258: {
  u32 ready=1,mask;u16 *shadow;
  register u32 previous __asm__("r1");
  register u32 clear_zero __asm__("r4");
  if(work->timer!=0 && --work->timer==0){
   work->fade=CreateDefinitionFadeTask(0,30,parent);
   ClearRelatedRecordFlags(work->owner);
  }
  work->positioned=PollAndReleasePositionedDefinitionTask(work->positioned);if(work->positioned!=0)ready=0;
  work->auxiliary=PollDefinitionAuxiliary(work->auxiliary);if(work->auxiliary!=0)ready=0;
  work->palette=PollDefinitionPalette(work->palette);if(work->palette!=0)ready=0;
  if(ready==0)break;
  BeginDefinitionControlRelease(work->control);
  mask=ReadDisplayHighMaskWord(2);shadow=(u16 *)0x03000940;
  previous=*shadow;__asm__("" : "+r"(previous));previous&=~mask;
  clear_zero=0;__asm__("" : "+r"(clear_zero));*shadow=previous;
  RemoveCurrentGroupTask(work->child);work->child=(TaskNode *)clear_zero;
  ++event->phase;break;
 }
 case 259:
  work->fade=PollDefinitionFadeTask(work->fade);if(work->fade!=0)break;
  RemoveDefinitionControlTask(work->control);
  if((u8)CountDefinitionTargets(work->owner,0)==0)event->phase=2;else ++event->phase;
  break;
 case 260:
  work->followup=CreateActionEffectChild(work->owner,0,parent);++event->phase;break;
 case 261:
  work->followup=PollAndReleaseActionEffectChild(work->followup);if(work->followup==0)event->phase=2;
  break;
 }
 return 0;
}
