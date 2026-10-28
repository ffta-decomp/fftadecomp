typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
typedef struct TaskNode TaskNode;
struct SequenceEvent {u16 phase,unknown02;void *actor;u32 unknown08,flags;u8 unknown10[6];u16 variant;u8 unknown18[4];};
struct ChildEvent {u32 unknown00;void *record;u8 unknown08[12];u16 ordinal;u8 unknown16[6];};
struct SequenceWork {u8 count,ordinal,delay,variant;TaskNode *children[2],*opening;void *actor;};
typedef char EventSize[sizeof(struct SequenceEvent)==28?1:-1];
typedef char ChildSize[sizeof(struct ChildEvent)==28?1:-1];
typedef char WorkSize[sizeof(struct SequenceWork)==20?1:-1];
extern TaskNode *CreateDefinitionEffectTask(void *,const void *,u8,u8,const void *,TaskNode *);
extern void FinishDefinitionSequence(void);
extern TaskNode *PollDefinitionEffectTask(TaskNode *);
extern u32 CountDefinitionTargets(void *,u16);
extern u32 PollDefinitionTaskArray(TaskNode **,u16);
extern void *GetDefinitionTargetRecord(void *,u8);
extern TaskNode *CreateDefinitionTask(const void *,u16,const void *,TaskNode *);
extern const u8 gOpeningSequence[],gChildEntry[];
__asm__(
 ".global CreateDefinitionEffectTask\n.thumb_set CreateDefinitionEffectTask,0x80e03f9\n"
 ".global FinishDefinitionSequence\n.thumb_set FinishDefinitionSequence,0x80d38b5\n"
 ".global PollDefinitionEffectTask\n.thumb_set PollDefinitionEffectTask,0x80e05dd\n"
 ".global CountDefinitionTargets\n.thumb_set CountDefinitionTargets,0x80d8859\n"
 ".global PollDefinitionTaskArray\n.thumb_set PollDefinitionTaskArray,0x80e0571\n"
 ".global GetDefinitionTargetRecord\n.thumb_set GetDefinitionTargetRecord,0x80dd4a5\n"
 ".global CreateDefinitionTask\n.thumb_set CreateDefinitionTask,0x8005b6d\n"
 ".global gOpeningSequence\n.set gOpeningSequence,0x8397a50\n"
 ".global gChildEntry\n.set gChildEntry,0x80e7b05\n"
);
s32 AdvanceAuthoredTwoSlotTargetSequence(TaskNode *,struct SequenceEvent *,struct SequenceWork *) __asm__("OriginalActionCallback_000E7C04");
s32 AdvanceAuthoredTwoSlotTargetSequence(TaskNode *parent,struct SequenceEvent *event,struct SequenceWork *work)
{
 struct ChildEvent child;
 register s32 phase __asm__("r3")=event->phase;
 /* The actual full phase snapshot supplies phase0's zero fifth argument. */
 __asm__("" : "+r"(phase));
 switch(phase) {
 case 0: {
  u32 variant=event->variant;
  void *actor;
  u8 count;
  work->variant=variant;
  actor=event->actor;work->actor=actor;
  count=2;
  if((u8)variant!=0)count=0;
  if((event->flags&1)!=0)count=0;
  work->opening=CreateDefinitionEffectTask(actor,gOpeningSequence,count,1,(const void *)phase,parent);
  break;
 }
 case 1:FinishDefinitionSequence();break;
 case 256: {
  u32 count;
  work->opening=PollDefinitionEffectTask(work->opening);
  if(work->opening!=0)break;
  count=CountDefinitionTargets(work->actor,0);work->count=count;
  if((u8)count==0)event->phase=2;
  else {work->delay=1;++event->phase;}
  break;
 }
 case 257: {
  TaskNode **children=work->children;
  u32 pointer_snapshot,slot,raw_ordinal,shifted_ordinal,ordinal;
  register u32 offset __asm__("r4");
  TaskNode *created;
  PollDefinitionTaskArray(children,2);
  if(--work->delay!=0)break;
  pointer_snapshot=(u32)work->children[0];
  slot=((0U-pointer_snapshot)|pointer_snapshot)>>31;
  child.record=GetDefinitionTargetRecord(work->actor,work->ordinal);
  child.ordinal=work->ordinal;
  created=CreateDefinitionTask(gChildEntry,52,&child,parent);
  /* Only after the child call does the live slot become a byte displacement. */
  offset=slot<<2;
  __asm__("" : "+r"(offset));
  /* Actual low-register memory address retains the array root first. */
  *(TaskNode **)((u8 *)children+offset)=created;
  work->delay=50;
  raw_ordinal=work->ordinal+1;work->ordinal=raw_ordinal;
  shifted_ordinal=raw_ordinal<<24;
  __asm__("" : "+r"(shifted_ordinal));
  ordinal=shifted_ordinal>>24;
  if(ordinal==work->count)++event->phase;
  break;
 }
 case 258:
  if((u8)PollDefinitionTaskArray(work->children,2)!=0)event->phase=2;
  break;
 }
 return 0;
}
