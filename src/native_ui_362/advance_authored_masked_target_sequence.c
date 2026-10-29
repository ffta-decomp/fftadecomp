typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
typedef struct TaskNode TaskNode;
struct SequenceEvent {u16 phase,unknown02;void *actor;u8 unknown08[12];short definition;u16 variant;u8 unknown18[4];};
struct ChildEvent {u16 phase,unknown02;void *record;u8 unknown08[12];u16 ordinal,unwritten22;u8 unknown18[4];};
struct SequenceWork {u8 count,ordinal,delay,variant;void *actor;TaskNode *children[2],*opening;};
typedef char EventSize[sizeof(struct SequenceEvent)==28?1:-1];
typedef char ChildEventSize[sizeof(struct ChildEvent)==28?1:-1];
typedef char WorkSize[sizeof(struct SequenceWork)==20?1:-1];
extern TaskNode *CreateDefinitionEffectTask(void *,const void *,u8,u8,const void *,TaskNode *);
extern void FinishDefinitionSequence(void);
extern TaskNode *PollDefinitionEffectTask(TaskNode *);
extern u32 CountDefinitionTargets(void *,u16);
extern u32 PollDefinitionTaskArray(TaskNode **,u16);
extern void *GetDefinitionTargetRecord(void *,u8);
extern TaskNode *CreateDefinitionTask(const void *,u16,const void *,TaskNode *);
extern const u8 gOpeningSequence[],gChildEntry[];
/* Physical full-R0 views: each selected getter ends in LDRH R0 and returns
 * that zero-extended word; the caller performs full-word bit operations. */
extern u32 ReadDisplayLowMaskWord(u8);
extern u32 ReadDisplayHighMaskWord(u8);
__asm__(
 ".global ReadDisplayLowMaskWord\n.thumb_set ReadDisplayLowMaskWord,0x080035d1\n"
 ".global ReadDisplayHighMaskWord\n.thumb_set ReadDisplayHighMaskWord,0x080035a9\n"
 ".global gOpeningSequence\n.set gOpeningSequence,0x0839735c\n"
 ".global gChildEntry\n.set gChildEntry,0x080e61e5\n"
 ".global CreateDefinitionEffectTask\n.thumb_set CreateDefinitionEffectTask,0x80e03f9\n"
 ".global FinishDefinitionSequence\n.thumb_set FinishDefinitionSequence,0x80d38b5\n"
 ".global PollDefinitionEffectTask\n.thumb_set PollDefinitionEffectTask,0x80e05dd\n"
 ".global CountDefinitionTargets\n.thumb_set CountDefinitionTargets,0x80d8859\n"
 ".global PollDefinitionTaskArray\n.thumb_set PollDefinitionTaskArray,0x80e0571\n"
 ".global GetDefinitionTargetRecord\n.thumb_set GetDefinitionTargetRecord,0x80dd4a5\n"
 ".global CreateDefinitionTask\n.thumb_set CreateDefinitionTask,0x8005b6d\n"
);

s32 AdvanceAuthoredMaskedTargetSequence(TaskNode *,struct SequenceEvent *,struct SequenceWork *) __asm__("OriginalActionCallback_000E6590");
s32 AdvanceAuthoredMaskedTargetSequence(TaskNode *input_parent,struct SequenceEvent *input_event,struct SequenceWork *input_work)
{
 struct ChildEvent child;
 register TaskNode *parent __asm__("r8")=input_parent;
 struct SequenceEvent *event=input_event;
 register struct SequenceWork *work __asm__("r5")=input_work;
 register u32 phase __asm__("r3");
 __asm__("" : "+r"(parent), "+r"(event), "+r"(work));
 phase=event->phase;__asm__("" : "+r"(phase));
 switch((s32)phase) {
 case 0: {
  u16 variant;void *actor;u8 count;
  variant=event->variant;work->variant=(u8)variant;
  actor=event->actor;work->actor=actor;
  count=6;
  if((u8)variant!=0)count=0;
  work->opening=CreateDefinitionEffectTask(actor,gOpeningSequence,count,1,(const void *)phase,parent);
  break;
 }
 case 1:FinishDefinitionSequence();break;
 case 256: {
  TaskNode *opening;u32 count,pair;volatile u8 *display;
  register u32 returned_mask __asm__("r0");
  register u32 first_working __asm__("r1");
  register u32 stored_mask __asm__("r0");
  register u32 all __asm__("r5");
  opening=PollDefinitionEffectTask(work->opening);work->opening=opening;
  if(opening!=0)break;
  count=CountDefinitionTargets(work->actor,0);work->count=count;
  if((u8)count==0){event->phase=2;break;}
  work->delay=1;
  returned_mask=ReadDisplayLowMaskWord(3);
  display=(volatile u8 *)0x03000940;all=63;
  first_working=all&~returned_mask;
  stored_mask=first_working;
  __asm__("" : "+r"(stored_mask) : "r"(first_working), "r"(all));
  /* These three byte reads occur in the original before their stores.
   * Only these shadow accesses are observable; the task payload is ordinary RAM. */
  (void)display[66];display[66]=stored_mask;
  pair=ReadDisplayLowMaskWord(2);
  pair|=ReadDisplayLowMaskWord(3);
  stored_mask=all&~pair;
  (void)display[67];display[67]=stored_mask;
  returned_mask=ReadDisplayLowMaskWord(2);
  all&=~returned_mask;
  (void)display[68];display[68]=all;
  ++event->phase;break;
 }
 case 257: {
  register TaskNode **children __asm__("r6")=work->children;
  u32 slot,pointer_snapshot,raw_ordinal;u8 ordinal;
  TaskNode *created;u32 slot_offset;
  register u32 slot_address __asm__("r4");
  PollDefinitionTaskArray(children,2);
  if(--work->delay!=0)break;
  /* Snapshot the actual full pointer before the opaque lookup/spawn.
   * The original derives a 0/1 slot with NEG/OR/unsigned bit31. */
  pointer_snapshot=(u32)work->children[0];
  slot=((0U-pointer_snapshot)|pointer_snapshot)>>31;
  child.record=GetDefinitionTargetRecord(work->actor,work->ordinal);
  child.ordinal=work->ordinal;
  created=CreateDefinitionTask(gChildEntry,64,&child,parent);
  slot_offset=slot<<2;
  slot_address=(u32)children+slot_offset;
  *(TaskNode **)slot_address=created;
  work->delay=68;
  raw_ordinal=work->ordinal+1;
  work->ordinal=raw_ordinal;
  /* Actual LOW8 working value compared with fresh stored count. */
  ordinal=(u8)raw_ordinal;
  if(ordinal==work->count)++event->phase;
  break;
 }
 case 258: {
  u32 mask;volatile u16 *display;
  register u32 previous __asm__("r1");
  register u32 filter __asm__("r0");
  if((u8)PollDefinitionTaskArray(work->children,2)==0)break;
  mask=ReadDisplayHighMaskWord(2);
  display=(volatile u16 *)0x03000940;
  previous=*display;
  previous&=~mask;*display=previous;
  mask=ReadDisplayHighMaskWord(3);
  previous=*display;
  previous&=~mask;
  filter=0x9fff;
  *display=previous&filter;
  event->phase=2;break;
 }
 }
 return 0;
}
