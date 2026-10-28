typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
typedef struct TaskNode TaskNode;
struct SequenceEvent {u16 phase,unknown02;void *actor;u8 unknown08[12];short definition;u16 variant;u8 unknown18[4];};
struct ChildEvent {u16 phase,unknown02;void *record;u8 unknown08[12];u16 ordinal,flags;u8 unknown18[4];};
struct SequenceWork {u8 count,ordinal,delay,child_variant,variant,unknown05[3];TaskNode *auxiliary;void *actor;TaskNode *children[2],*opening;};
typedef char EventSize[sizeof(struct SequenceEvent)==28?1:-1];
typedef char ChildEventSize[sizeof(struct ChildEvent)==28?1:-1];
typedef char WorkSize[sizeof(struct SequenceWork)==28?1:-1];
extern TaskNode *CreateDefinitionEffectTask(void *,const void *,u8,u8,const void *,TaskNode *);
extern void FinishDefinitionSequence(void);
extern TaskNode *PollDefinitionEffectTask(TaskNode *);
extern u32 CountDefinitionTargets(void *,u16);
extern u32 PollDefinitionTaskArray(TaskNode **,u16);
extern void *GetDefinitionTargetRecord(void *,u8);
extern TaskNode *CreateDefinitionTask(const void *,u16,const void *,TaskNode *);
extern const u8 gOpeningSequence[],gChildEntry[],gAuxiliarySequence[],gModelResource[];
extern TaskNode *CreateDefinitionAuxiliaryTask(const void *,TaskNode *);
extern void ConfigureDefinitionAuxiliary(TaskNode *,u8,u8);
extern TaskNode *PollDefinitionAuxiliary(TaskNode *);
extern void PlaceDefinitionResource(const void *,u32,u32,s32,s32,u32);
extern u32 ReadDisplayLowMaskWord(u8);
extern u32 ReadDisplayHighMaskWord(u8);
__asm__(
 ".global gAuxiliarySequence\n.set gAuxiliarySequence,0x0894d69c\n"
 ".global gModelResource\n.set gModelResource,0x088f46cc\n"
 ".global CreateDefinitionAuxiliaryTask\n.thumb_set CreateDefinitionAuxiliaryTask,0x080d3e9d\n"
 ".global ConfigureDefinitionAuxiliary\n.thumb_set ConfigureDefinitionAuxiliary,0x080d3f85\n"
 ".global PollDefinitionAuxiliary\n.thumb_set PollDefinitionAuxiliary,0x080d3f09\n"
 ".global PlaceDefinitionResource\n.thumb_set PlaceDefinitionResource,0x080d7221\n"
 ".global ReadDisplayLowMaskWord\n.thumb_set ReadDisplayLowMaskWord,0x080035d1\n"
 ".global ReadDisplayHighMaskWord\n.thumb_set ReadDisplayHighMaskWord,0x080035a9\n"
 ".global gOpeningSequence\n.set gOpeningSequence,0x08396d34\n"
 ".global gChildEntry\n.set gChildEntry,0x080e4b41\n"
 ".global CreateDefinitionEffectTask\n.thumb_set CreateDefinitionEffectTask,0x80e03f9\n"
 ".global FinishDefinitionSequence\n.thumb_set FinishDefinitionSequence,0x80d38b5\n"
 ".global PollDefinitionEffectTask\n.thumb_set PollDefinitionEffectTask,0x80e05dd\n"
 ".global CountDefinitionTargets\n.thumb_set CountDefinitionTargets,0x80d8859\n"
 ".global PollDefinitionTaskArray\n.thumb_set PollDefinitionTaskArray,0x80e0571\n"
 ".global GetDefinitionTargetRecord\n.thumb_set GetDefinitionTargetRecord,0x80dd4a5\n"
 ".global CreateDefinitionTask\n.thumb_set CreateDefinitionTask,0x8005b6d\n"
);

s32 AdvanceAuthoredAuxiliaryTargetSequence(TaskNode *,struct SequenceEvent *,struct SequenceWork *) __asm__("OriginalActionCallback_000E4CF4");
s32 AdvanceAuthoredAuxiliaryTargetSequence(TaskNode *input_parent,struct SequenceEvent *input_event,struct SequenceWork *input_work)
{
 register TaskNode *parent __asm__("r8")=input_parent;
 register struct SequenceEvent *entry_event __asm__("r1")=input_event;
 register struct SequenceWork *entry_work __asm__("r2")=input_work;
 struct SequenceEvent *event;
 struct SequenceWork *work;
 struct ChildEvent child;
 register s32 phase __asm__("r1");
 /* The complete entry parent snapshot is preserved across all helpers and
  * consumed by the three native call sites, independently of child cursors. */
 __asm__("" : "+r"(parent), "+r"(entry_event), "+r"(entry_work));
 event=entry_event;work=entry_work;
 phase=event->phase;
 /* H0 storage is halfword; this actual dispatch/byte-store snapshot is fullword. */
 __asm__("" : "+r"(phase));
 switch(phase) {
 case 0: {
  u8 count;
  work->variant=(u8)event->variant;
  work->actor=event->actor;
  if(event->definition==11)work->child_variant=phase;
  else work->child_variant=1;
  count=5;
  if(work->variant!=0)count=0;
  work->opening=CreateDefinitionEffectTask(work->actor,gOpeningSequence,count,1,0,parent);
  break;
 }
 case 1:FinishDefinitionSequence();break;
 case 256: {
  register TaskNode *opening __asm__("r4");
  TaskNode *auxiliary;u32 count,mask,value;u8 *display;
  opening=PollDefinitionEffectTask(work->opening);work->opening=opening;
  if(opening!=0)break;
  /* The original keeps this full returned NULL in R4 across the following
   * calls, then consumes it as both outgoing model words. */
  __asm__("" : "+r"(opening));
  count=CountDefinitionTargets(work->actor,0);work->count=count;
  if((u8)count==0){event->phase=2;break;}
  work->delay=1;
  auxiliary=CreateDefinitionAuxiliaryTask(gAuxiliarySequence,parent);
  work->auxiliary=auxiliary;
  ConfigureDefinitionAuxiliary(auxiliary,12,255);
  PlaceDefinitionResource(gModelResource,1,3,0,(s32)opening,(u32)opening);
  mask=ReadDisplayLowMaskWord(3);
  display=(u8 *)0x03000940;
  /* This initialized working mask is overwritten by BIC before its byte
   * store; the later independent literal 63 is defined after the B69 read. */
  value=63;
  __asm__("" : "+r"(value));
  value&=~mask;
  /* The two otherwise-unused byte reads precede their actual stores. */
  (void)((volatile u8 *)display)[68];display[68]=value;
  (void)((volatile u8 *)display)[69];display[69]=63;
  {
   register u32 shadow __asm__("r1")=*(u16 *)display;
   register u32 enable_mask __asm__("r2");
   register u32 working __asm__("r0");
   /* Fresh H0, the actual constant, and its destructive working copy have
    * separate native definitions after the preceding B69 store. */
   __asm__("" : "+r"(shadow));
   enable_mask=0x8000;
   __asm__("" : "+r"(enable_mask));
   working=enable_mask;
   __asm__("" : "+r"(working));
   working|=shadow;
   *(u16 *)display=working;
  }
  ++event->phase;break;
 }
 case 257: {
  TaskNode **children;u32 slot,pointer_snapshot,ordinal,raw_ordinal,shifted_ordinal;
  TaskNode *created;u32 slot_offset,slot_address;
  work->auxiliary=PollDefinitionAuxiliary(work->auxiliary);
  children=work->children;
  PollDefinitionTaskArray(children,2);
  if(--work->delay!=0)break;
  /* Snapshot the actual full pointer before the opaque lookup/spawn.
   * The original derives a 0/1 slot with NEG/OR/unsigned bit31. */
  pointer_snapshot=(u32)children[0];
  slot=((0U-pointer_snapshot)|pointer_snapshot)>>31;
  child.ordinal=work->ordinal;child.flags=work->child_variant;
  child.record=GetDefinitionTargetRecord(work->actor,work->ordinal);
  created=CreateDefinitionTask(gChildEntry,44,&child,parent);
  slot_offset=slot<<2;
  slot_address=(u32)children+slot_offset;
  *(TaskNode **)slot_address=created;
  work->delay=64;
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
 case 258: {
  TaskNode *auxiliary;u32 mask;u16 *display;u16 value;
  auxiliary=PollDefinitionAuxiliary(work->auxiliary);work->auxiliary=auxiliary;
  if(auxiliary!=0)break;
  if((u8)PollDefinitionTaskArray(work->children,2)==0)break;
  mask=ReadDisplayHighMaskWord(3);
  display=(u16 *)0x03000940;
  value=*display;value&=~mask;value&=0x7fff;*display=value;
  event->phase=2;break;
 }
 }
 return 0;
}
