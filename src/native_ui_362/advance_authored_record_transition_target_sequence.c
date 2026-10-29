typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
typedef struct TaskNode TaskNode;
struct SequenceEvent {u16 phase,unknown02;void *actor;u8 unknown08[12];s16 definition;u16 variant;u8 unknown18[4];};
struct ChildEvent {u32 unknown00;void *record;u8 unknown08[12];u16 definition,ordinal;u8 unknown18[4];};
struct SequenceWork {u8 kind,variant,count,ordinal,delay,transition,completion,unknown07;void *record;TaskNode *transition_task;void *actor;TaskNode *children[2],*opening;};
typedef char EventSize[sizeof(struct SequenceEvent)==28?1:-1];
typedef char ChildSize[sizeof(struct ChildEvent)==28?1:-1];
typedef char WorkSize[sizeof(struct SequenceWork)==32?1:-1];
/* Physical fullword R3 transport at this site: branch definitions prove0/1. */
extern TaskNode *CreateDefinitionEffectTaskWordMode(void *,const void *,u8,u32,const void *,TaskNode *);
extern void FinishDefinitionSequence(void);
extern TaskNode *PollDefinitionEffectTask(TaskNode *);
extern u32 ReadSceneBlocked(void *);
extern TaskNode *CreateRecordPhaseTask(void *,void **,u32,u32,u8 *,const void *,u32,u32,TaskNode *);
extern u32 QueryRecordPositionBoundary(void *);
extern u32 QueryDefinitionReadiness(void);
extern u32 CountDefinitionTargets(void *,u16);
extern u32 PollDefinitionTaskArray(TaskNode **,u16);
extern void *GetDefinitionTargetRecord(void *,u8);
extern TaskNode *CreateDefinitionTask(const void *,u16,const void *,TaskNode *);
extern u32 PollDefinitionRecordHandles(void *);
extern const u8 gOpeningCounts[],gChildDelays[],gRecordPhaseSequence[],gChildEntry[];
extern const void *const gOpeningSequences[];
__asm__(
 ".global CreateDefinitionEffectTaskWordMode\n.thumb_set CreateDefinitionEffectTaskWordMode,0x80e03f9\n"
 ".global FinishDefinitionSequence\n.thumb_set FinishDefinitionSequence,0x80d38b5\n"
 ".global PollDefinitionEffectTask\n.thumb_set PollDefinitionEffectTask,0x80e05dd\n"
 ".global ReadSceneBlocked\n.thumb_set ReadSceneBlocked,0x80d3b55\n"
 ".global CreateRecordPhaseTask\n.thumb_set CreateRecordPhaseTask,0x80ddf69\n"
 ".global QueryRecordPositionBoundary\n.thumb_set QueryRecordPositionBoundary,0x80d8cd5\n"
 ".global QueryDefinitionReadiness\n.thumb_set QueryDefinitionReadiness,0x80d8b4d\n"
 ".global CountDefinitionTargets\n.thumb_set CountDefinitionTargets,0x80d8859\n"
 ".global PollDefinitionTaskArray\n.thumb_set PollDefinitionTaskArray,0x80e0571\n"
 ".global GetDefinitionTargetRecord\n.thumb_set GetDefinitionTargetRecord,0x80dd4a5\n"
 ".global CreateDefinitionTask\n.thumb_set CreateDefinitionTask,0x8005b6d\n"
 ".global PollDefinitionRecordHandles\n.thumb_set PollDefinitionRecordHandles,0x80de1f1\n"
 ".global gOpeningCounts\n.set gOpeningCounts,0x8397c00\n"
 ".global gOpeningSequences\n.set gOpeningSequences,0x8397bf4\n"
 ".global gRecordPhaseSequence\n.set gRecordPhaseSequence,0x8397cfc\n"
 ".global gChildDelays\n.set gChildDelays,0x8397ce0\n"
 ".global gChildEntry\n.set gChildEntry,0x80e7d21\n"
);
s32 AdvanceAuthoredRecordTransitionTargetSequence(TaskNode *,struct SequenceEvent *,struct SequenceWork *) __asm__("OriginalActionCallback_000E7F4C");
s32 AdvanceAuthoredRecordTransitionTargetSequence(TaskNode *parent,struct SequenceEvent *event,struct SequenceWork *work)
{
 struct ChildEvent child;
 register s32 phase __asm__("r1")=event->phase;
 __asm__("" : "+r"(phase));
 switch(phase) {
 case 0: {
  register u32 raw_definition __asm__("r2")=(u16)event->definition;
  register u32 flags __asm__("r3");
  register void *actor __asm__("r6");
  register u32 kind __asm__("r4");
  u32 variant;u8 count;
  __asm__("" : "+r"(raw_definition), "+r"(event));
  {
  register s32 signed_definition __asm__("r0")=event->definition;
  __asm__("" : "+r"(signed_definition));
  if(signed_definition!=231) {
   register u32 index __asm__("r0")=raw_definition;
   index-=24;work->kind=index;work->transition=phase;
   flags=1;
  } else {
   work->kind=phase;work->transition=1;flags=0;
  }
  }
  /* Actual branch-defined fullword0/1 is transported to the same R3 ABI. */
  variant=event->variant;work->variant=variant;
  actor=event->actor;
  work->actor=actor;
  {
   register const u8 *counts __asm__("r0")=gOpeningCounts;
   u32 address;
   kind=work->kind;
   address=(u32)kind+(u32)counts;
   count=*(const u8 *)address;
  }
  if((u8)variant!=0)count=0;
  {
   register const void *const *sequences __asm__("r1")=gOpeningSequences;
   register u32 index __asm__("r0");
   register const void *sequence __asm__("r1");
   index=kind<<2;
   index+=(u32)sequences;
   /* Consume the address before R0 takes the actor/stack argument roles.
    * The original full pointer result now lives in the actual R1 input. */
   sequence=*(const void **)index;
   __asm__("" : : "r"(sequence));
   work->opening=CreateDefinitionEffectTaskWordMode(actor,sequence,count,flags,0,parent);
  }
  break;
 }
 case 1:FinishDefinitionSequence();break;
 case 256: {
  register u32 blocked __asm__("r4");
  work->opening=PollDefinitionEffectTask(work->opening);
  if(work->opening!=0)break;
  if(work->transition!=0) {
   blocked=(u8)ReadSceneBlocked(work->actor);
   if(blocked!=0){event->phase=2;break;}
   /* Actual zero-extended LOW8 result supplies the later full outgoing word. */
   __asm__("" : "+r"(blocked));
   work->transition_task=CreateRecordPhaseTask(work->actor,&work->record,0x8007,2,&work->completion,gRecordPhaseSequence,5,blocked,parent);
   ++event->phase;
  } else event->phase=259;
  break;
 }
 case 257:
  if(work->completion==0)break;
  QueryRecordPositionBoundary(work->actor);
  work->ordinal=4;
  ++event->phase;
  break;
 case 258:
  if(work->ordinal!=0) {
   --work->ordinal;
   if(work->ordinal!=0)break;
  }
  if((u8)QueryDefinitionReadiness()!=0)break;
  ++event->phase;
  break;
 case 259: {
  u32 count=CountDefinitionTargets(work->actor,0);work->count=count;
  if((u8)count==0)event->phase=2;
  else {work->delay=1;++event->phase;}
  break;
 }
 case 260: {
  TaskNode **children=work->children;
  u32 pointer_snapshot,slot,raw_ordinal,shifted_ordinal,ordinal;
  register u32 offset __asm__("r4");
  TaskNode *created;
  PollDefinitionTaskArray(children,2);
  if(--work->delay!=0)break;
  pointer_snapshot=(u32)work->children[0];
  slot=((0U-pointer_snapshot)|pointer_snapshot)>>31;
  /* Unlike the earlier sibling, both scalar fields precede the query. */
  child.definition=work->kind;
  child.ordinal=work->ordinal;
  child.record=GetDefinitionTargetRecord(work->actor,work->ordinal);
  created=CreateDefinitionTask(gChildEntry,52,&child,parent);
  offset=slot<<2;
  __asm__("" : "+r"(offset));
  *(TaskNode **)((u8 *)children+offset)=created;
  work->delay=gChildDelays[work->kind];
  raw_ordinal=work->ordinal+1;work->ordinal=raw_ordinal;
  shifted_ordinal=raw_ordinal<<24;
  __asm__("" : "+r"(shifted_ordinal));
  ordinal=shifted_ordinal>>24;
  if(ordinal==work->count)++event->phase;
  break;
 }
 case 261:
  if(work->transition!=0 && (u8)PollDefinitionRecordHandles(work->record)==0)break;
  if((u8)PollDefinitionTaskArray(work->children,2)!=0)event->phase=2;
  break;
 }
 return 0;
}
