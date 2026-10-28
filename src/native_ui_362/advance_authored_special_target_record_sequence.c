typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
typedef struct TaskNode TaskNode;
struct SequenceEvent {u16 phase,unknown02;void *actor;u8 unknown08[12];s16 definition;u16 variant;u8 unknown18[4];};
struct ChildEvent {u32 unknown00;void *record;u8 unknown08[12];u16 selector,ordinal;u8 unknown18[4];};
struct SequenceWork {u8 selector,variant,count,ordinal,delay,special,ready,unknown07;void *record;TaskNode *motion;void *actor;TaskNode *children[2],*opening;};
typedef char EventSize[sizeof(struct SequenceEvent)==28?1:-1];
typedef char ChildSize[sizeof(struct ChildEvent)==28?1:-1];
typedef char WorkSize[sizeof(struct SequenceWork)==32?1:-1];
/* The fourth incoming word is physically full width; the callee consumes LOW8.
 * The two source branches define its only actual values, 0 and 1. */
extern TaskNode *CreateDefinitionEffectTask(void *,const void *,u8,u32,const void *,TaskNode *);
extern void FinishDefinitionSequence(void);
extern TaskNode *PollDefinitionEffectTask(TaskNode *);
extern u32 TestDefinitionActor(void *);
extern TaskNode *CreateRecordMotion(void *,void **,u16,u8,u8 *,const void *,u16,u32,TaskNode *);
extern u32 QueryRecordBoundary(void *);
extern u32 QueryDefinitionReadiness(void);
extern u32 CountDefinitionTargets(void *,u16);
extern u32 PollDefinitionTaskArray(TaskNode **,u16);
extern void *GetDefinitionTargetRecord(void *,u8);
extern TaskNode *CreateDefinitionTask(const void *,u16,const void *,TaskNode *);
extern u32 PollDefinitionRecord(void *);
extern const u8 gOpeningCounts[],gMotionSequence[],gSpawnDelays[],gChildEntry[];
extern const void *const gOpeningSequences[];
__asm__(
 ".global CreateDefinitionEffectTask\n.thumb_set CreateDefinitionEffectTask,0x80e03f9\n"
 ".global FinishDefinitionSequence\n.thumb_set FinishDefinitionSequence,0x80d38b5\n"
 ".global PollDefinitionEffectTask\n.thumb_set PollDefinitionEffectTask,0x80e05dd\n"
 ".global TestDefinitionActor\n.thumb_set TestDefinitionActor,0x80d3b55\n"
 ".global CreateRecordMotion\n.thumb_set CreateRecordMotion,0x80ddf69\n"
 ".global QueryRecordBoundary\n.thumb_set QueryRecordBoundary,0x80d8cd5\n"
 ".global QueryDefinitionReadiness\n.thumb_set QueryDefinitionReadiness,0x80d8b4d\n"
 ".global CountDefinitionTargets\n.thumb_set CountDefinitionTargets,0x80d8859\n"
 ".global PollDefinitionTaskArray\n.thumb_set PollDefinitionTaskArray,0x80e0571\n"
 ".global GetDefinitionTargetRecord\n.thumb_set GetDefinitionTargetRecord,0x80dd4a5\n"
 ".global CreateDefinitionTask\n.thumb_set CreateDefinitionTask,0x8005b6d\n"
 ".global PollDefinitionRecord\n.thumb_set PollDefinitionRecord,0x80de1f1\n"
 ".global gOpeningCounts\n.set gOpeningCounts,0x8397e50\n"
 ".global gOpeningSequences\n.set gOpeningSequences,0x8397e44\n"
 ".global gMotionSequence\n.set gMotionSequence,0x8397f90\n"
 ".global gSpawnDelays\n.set gSpawnDelays,0x8397f72\n"
 ".global gChildEntry\n.set gChildEntry,0x80e8159\n"
);
s32 AdvanceAuthoredSpecialTargetRecordSequence(TaskNode *,struct SequenceEvent *,struct SequenceWork *) __asm__("OriginalActionCallback_000E8384");
s32 AdvanceAuthoredSpecialTargetRecordSequence(TaskNode *input_parent,struct SequenceEvent *input_event,struct SequenceWork *input_work)
{
 register TaskNode *parent __asm__("r8")=input_parent;
 struct SequenceEvent *event=input_event;
 struct SequenceWork *work=input_work;
 register s32 phase __asm__("r1");
 struct ChildEvent child;
 /* Capture every incoming value before the phase uses the old R1 home. */
 __asm__("" : "+r"(parent), "+r"(event), "+r"(work));
 phase=event->phase;
 __asm__("" : "+r"(phase));
 switch(phase) {
 case 0: {
  register u32 raw_definition __asm__("r2");
  s32 signed_definition;
  u32 mode,variant,selector,address;
  u8 count;void *actor;
  register const u8 *counts_base __asm__("r0");
  const void *sequence;
  raw_definition=(u16)event->definition;
  /* The original unsigned snapshot precedes a distinct signed memory read. */
  __asm__("" : "+r"(raw_definition));
  signed_definition=event->definition;
  if(signed_definition!=232) {
   register u32 selector_working __asm__("r0")=raw_definition;
   /* This native working copy dies at the byte store, before ABI setup. */
   __asm__("" : "+r"(selector_working));
   selector_working-=27;
   work->selector=selector_working;work->special=phase;mode=1;
  } else {
   work->selector=phase;work->special=1;mode=0;
  }
  variant=event->variant;work->variant=variant;
  actor=event->actor;work->actor=actor;
  counts_base=gOpeningCounts;
  __asm__("" : : "r"(counts_base));
  selector=work->selector;address=selector+(u32)counts_base;
  count=*(const u8 *)address;
  if((u8)variant!=0)count=0;
  sequence=gOpeningSequences[selector];
  /* This full pointer is an ordinary second ABI argument. No extra
   * observer is needed at the already explicit load/call boundary. */
  work->opening=CreateDefinitionEffectTask(actor,sequence,count,mode,0,parent);
  break;
 }
 case 1:FinishDefinitionSequence();break;
 case 256: {
  TaskNode *opening;
  opening=PollDefinitionEffectTask(work->opening);work->opening=opening;
  if(opening!=0)break;
  if(work->special!=0) {
   register u32 rejected __asm__("r4")=(u8)TestDefinitionActor(work->actor);
   if(rejected!=0){event->phase=2;break;}
   /* The actual captured LOW8 zero supplies the full eighth motion word. */
   __asm__("" : "+r"(rejected));
   work->motion=CreateRecordMotion(work->actor,&work->record,0x8007,2,&work->ready,gMotionSequence,5,rejected,parent);
   ++event->phase;
  } else event->phase=259;
  break;
 }
 case 257:
  if(work->ready==0)break;
  QueryRecordBoundary(work->actor);work->ordinal=4;++event->phase;
  break;
 case 258:
  if(work->ordinal!=0 && --work->ordinal!=0)break;
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
  child.selector=work->selector;child.ordinal=work->ordinal;
  child.record=GetDefinitionTargetRecord(work->actor,work->ordinal);
  created=CreateDefinitionTask(gChildEntry,52,&child,parent);
  offset=slot<<2;
  __asm__("" : "+r"(offset));
  *(TaskNode **)((u8 *)children+offset)=created;
  work->delay=gSpawnDelays[work->selector];
  raw_ordinal=work->ordinal+1;work->ordinal=raw_ordinal;
  shifted_ordinal=raw_ordinal<<24;
  __asm__("" : "+r"(shifted_ordinal));
  ordinal=shifted_ordinal>>24;
  if(ordinal==work->count)++event->phase;
  break;
 }
 case 261:
  if(work->special!=0 && (u8)PollDefinitionRecord(work->record)==0)break;
  if((u8)PollDefinitionTaskArray(work->children,2)==0)break;
  event->phase=2;
  break;
 }
 return 0;
}
