typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
typedef struct TaskNode TaskNode;
struct SequenceEvent {u16 phase,unknown02;void *actor;u8 unknown08[12];u8 definition_low,unknown21;u16 variant;u8 unknown18[4];};
struct ChildEvent {u16 phase,unknown02;void *record;u8 unknown08[12];u16 style,ordinal;u8 unknown18[4];};
struct SequenceWork {u8 style,variant,count,ordinal,delay,unknown05[3];TaskNode *children[2],*opening;void *actor;};
typedef char EventSize[sizeof(struct SequenceEvent)==28?1:-1];
typedef char ChildEventSize[sizeof(struct ChildEvent)==28?1:-1];
typedef char WorkSize[sizeof(struct SequenceWork)==24?1:-1];
extern TaskNode *CreateDefinitionEffectTask(void *,const void *,u8,u8,const void *,TaskNode *);
extern void FinishDefinitionSequence(void);
extern TaskNode *PollDefinitionEffectTask(TaskNode *);
extern u32 CountDefinitionTargets(void *,u16);
extern u32 PollDefinitionTaskArray(TaskNode **,u16);
extern void *GetDefinitionTargetRecord(void *,u8);
extern TaskNode *CreateDefinitionTask(const void *,u16,const void *,TaskNode *);
extern const void *const gOpeningSequences[];
extern const u8 gOpeningCounts[],gChildEntry[];
__asm__(
 ".global gOpeningSequences\n.set gOpeningSequences,0x08396cb8\n"
 ".global gOpeningCounts\n.set gOpeningCounts,0x08396cc0\n"
 ".global gChildEntry\n.set gChildEntry,0x080e4845\n"
 ".global CreateDefinitionEffectTask\n.thumb_set CreateDefinitionEffectTask,0x80e03f9\n"
 ".global FinishDefinitionSequence\n.thumb_set FinishDefinitionSequence,0x80d38b5\n"
 ".global PollDefinitionEffectTask\n.thumb_set PollDefinitionEffectTask,0x80e05dd\n"
 ".global CountDefinitionTargets\n.thumb_set CountDefinitionTargets,0x80d8859\n"
 ".global PollDefinitionTaskArray\n.thumb_set PollDefinitionTaskArray,0x80e0571\n"
 ".global GetDefinitionTargetRecord\n.thumb_set GetDefinitionTargetRecord,0x80dd4a5\n"
 ".global CreateDefinitionTask\n.thumb_set CreateDefinitionTask,0x8005b6d\n"
);

s32 AdvanceAuthoredPairedTargetSequence(TaskNode *,struct SequenceEvent *,struct SequenceWork *) __asm__("OriginalActionCallback_000E4A14");
s32 AdvanceAuthoredPairedTargetSequence(TaskNode *parent,struct SequenceEvent *event,struct SequenceWork *work)
{
 struct ChildEvent child;
 switch(event->phase) {
 case 0: {
  u16 variant;void *actor;u8 style,count;
  work->style=event->definition_low-9;
  variant=event->variant;work->variant=(u8)variant;
  actor=event->actor;work->actor=actor;
  {
   register const u8 *counts_base __asm__("r0")=gOpeningCounts;
   u32 count_address;
   /* This real table address is defined before the fresh style index.
    * The base dies at its indexed byte load, before call setup. */
   __asm__("" : : "r"(counts_base));
   style=work->style;
   count_address=(u32)style+(u32)counts_base;
   count=*(const u8 *)count_address;
  }
  if((u8)variant!=0)count=0;
  work->opening=CreateDefinitionEffectTask(actor,gOpeningSequences[style],count,1,0,parent);
  break;
 }
 case 1:FinishDefinitionSequence();break;
 case 256: {
  TaskNode *opening;u32 count;
  opening=PollDefinitionEffectTask(work->opening);work->opening=opening;
  if(opening!=0)break;
  count=CountDefinitionTargets(work->actor,0);work->count=count;
  if((u8)count==0){event->phase=2;break;}
  work->delay=1;++event->phase;break;
 }
 case 257: {
  TaskNode **children=work->children;u32 slot,pointer_snapshot,ordinal,raw_ordinal,shifted_ordinal;
  TaskNode *created;u32 slot_offset,slot_address;
  PollDefinitionTaskArray(children,2);
  if(--work->delay!=0)break;
  /* Snapshot the actual full pointer before the opaque lookup/spawn.
   * The original derives a 0/1 slot with NEG/OR/unsigned bit31. */
  pointer_snapshot=(u32)children[0];
  slot=((0U-pointer_snapshot)|pointer_snapshot)>>31;
  child.style=work->style;child.ordinal=work->ordinal;
  child.record=GetDefinitionTargetRecord(work->actor,work->ordinal);
  created=CreateDefinitionTask(gChildEntry,44,&child,parent);
  slot_offset=slot<<2;
  slot_address=(u32)children+slot_offset;
  *(TaskNode **)slot_address=created;
  work->delay=56;
  raw_ordinal=work->ordinal+1;
  work->ordinal=raw_ordinal;
  /* This is the actual full shifted value after the byte store. Its
   * unsigned projection is consumed next, not a mask kept across calls. */
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
