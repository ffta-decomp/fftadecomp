typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
typedef struct TaskNode TaskNode;
struct SequenceEvent {u16 phase,unknown02;void *actor;u8 unknown08[12];u8 definition_low,unknown21;u16 variant;u8 unknown18[4];};
struct ChildEvent {u32 unknown00;void *record;u8 unknown08[12];u16 selector,ordinal;u8 unknown18[4];};
struct SequenceWork {u8 variant,selector,count,ordinal,delay,unknown05[3];TaskNode *children[2];u8 output[20];TaskNode *positioned,*auxiliary,*palette,*opening;void *actor;TaskNode *stage;};
typedef char EventSize[sizeof(struct SequenceEvent)==28?1:-1];
typedef char ChildSize[sizeof(struct ChildEvent)==28?1:-1];
typedef char WorkSize[sizeof(struct SequenceWork)==60?1:-1];
extern TaskNode *CreateDefinitionEffectTask(void *,const void *,u8,u8,const void *,TaskNode *);
extern void FinishDefinitionSequence(void);
extern TaskNode *PollDefinitionEffectTask(TaskNode *);
extern u32 CountDefinitionTargets(void *,u16);
extern u32 PollDefinitionTaskArray(TaskNode **,u16);
extern void *GetDefinitionTargetRecord(void *,u8);
extern TaskNode *CreateDefinitionTask(const void *,u16,const void *,TaskNode *);
extern void PlaceDefinitionResource(const void *,u32,u32,s32,s32,u32);
extern TaskNode *CreatePositionedDefinitionTask(int,u16,int,u8,u32,void *,const void *,TaskNode *);
extern TaskNode *PollPositionedDefinitionTask(TaskNode *);
extern TaskNode *CreateDefinitionAuxiliaryTask(const void *,TaskNode *);
extern TaskNode *PollDefinitionAuxiliary(TaskNode *);
extern TaskNode *CreateDefinitionPaletteTask(const void *,TaskNode *,u16);
extern TaskNode *PollDefinitionPalette(TaskNode *);
extern TaskNode *CreateDefinitionStageTask(const void *,u8,u16,u16,TaskNode *);
extern u32 ReadDisplayHighMaskWord(u8);
extern const u8 gOpeningCounts[],gPositionedIds[],gPaletteParameters[],gInitialOrdinals[],gSpawnDelays[],gStageSequences[];
extern const void *const gOpeningSequences[],*const gPositionedSequences[],*const gAuxiliarySequences[];
extern const u8 gModelResource[],gPaletteSequence[],gChildEntry[];
__asm__(
 ".global gOpeningCounts\n.set gOpeningCounts,0x083965dc\n"
 ".global gOpeningSequences\n.set gOpeningSequences,0x083965d0\n"
 ".global gPositionedIds\n.set gPositionedIds,0x083967d8\n"
 ".global gPositionedSequences\n.set gPositionedSequences,0x083967c0\n"
 ".global gAuxiliarySequences\n.set gAuxiliarySequences,0x083967e4\n"
 ".global gPaletteParameters\n.set gPaletteParameters,0x083967f3\n"
 ".global gInitialOrdinals\n.set gInitialOrdinals,0x083967f0\n"
 ".global gSpawnDelays\n.set gSpawnDelays,0x083967de\n"
 ".global gStageSequences\n.set gStageSequences,0x08396824\n"
 ".global gModelResource\n.set gModelResource,0x088f4674\n"
 ".global gPaletteSequence\n.set gPaletteSequence,0x0894aba0\n"
 ".global gChildEntry\n.set gChildEntry,0x080e3ac9\n"
 ".global CreateDefinitionEffectTask\n.thumb_set CreateDefinitionEffectTask,0x080e03f9\n"
 ".global FinishDefinitionSequence\n.thumb_set FinishDefinitionSequence,0x080d38b5\n"
 ".global PollDefinitionEffectTask\n.thumb_set PollDefinitionEffectTask,0x080e05dd\n"
 ".global CountDefinitionTargets\n.thumb_set CountDefinitionTargets,0x080d8859\n"
 ".global PollDefinitionTaskArray\n.thumb_set PollDefinitionTaskArray,0x080e0571\n"
 ".global GetDefinitionTargetRecord\n.thumb_set GetDefinitionTargetRecord,0x080dd4a5\n"
 ".global CreateDefinitionTask\n.thumb_set CreateDefinitionTask,0x08005b6d\n"
 ".global PlaceDefinitionResource\n.thumb_set PlaceDefinitionResource,0x080d7221\n"
 ".global CreatePositionedDefinitionTask\n.thumb_set CreatePositionedDefinitionTask,0x080d6099\n"
 ".global PollPositionedDefinitionTask\n.thumb_set PollPositionedDefinitionTask,0x080d6135\n"
 ".global CreateDefinitionAuxiliaryTask\n.thumb_set CreateDefinitionAuxiliaryTask,0x080d3e9d\n"
 ".global PollDefinitionAuxiliary\n.thumb_set PollDefinitionAuxiliary,0x080d3f09\n"
 ".global CreateDefinitionPaletteTask\n.thumb_set CreateDefinitionPaletteTask,0x080d4725\n"
 ".global PollDefinitionPalette\n.thumb_set PollDefinitionPalette,0x080d4775\n"
 ".global CreateDefinitionStageTask\n.thumb_set CreateDefinitionStageTask,0x080dfd8d\n"
 ".global ReadDisplayHighMaskWord\n.thumb_set ReadDisplayHighMaskWord,0x080035a9\n"
);
s32 AdvanceAuthoredIndexedTargetSequence(TaskNode *,struct SequenceEvent *,struct SequenceWork *) __asm__("OriginalActionCallback_000E3C0C");
s32 AdvanceAuthoredIndexedTargetSequence(TaskNode *parent,struct SequenceEvent *event,struct SequenceWork *work)
{
 struct ChildEvent child;
 register s32 phase __asm__("r3")=event->phase;
 /* Actual full dispatch word also supplies the phase0 zero stack argument. */
 __asm__("" : "+r"(phase));
 switch(phase) {
 case 0: {
  u16 variant;void *actor;u8 selector,count;
  work->selector=event->definition_low-2;
  variant=event->variant;work->variant=variant;
  actor=event->actor;work->actor=actor;
  {
   register const u8 *counts_base __asm__("r0")=gOpeningCounts;
   u32 address;
   /* Real table base precedes the fresh byte selector and dies at the load. */
   __asm__("" : : "r"(counts_base));
   selector=work->selector;
   address=(u32)selector+(u32)counts_base;
   count=*(const u8 *)address;
  }
  if((u8)variant!=0)count=0;
  work->opening=CreateDefinitionEffectTask(actor,gOpeningSequences[selector],count,1,(const void *)phase,parent);
  break;
 }
 case 1:FinishDefinitionSequence();break;
 case 256: {
  u32 variant,count;
  work->opening=PollDefinitionEffectTask(work->opening);
  if(work->opening!=0)break;
  variant=work->variant;
  if(variant!=0) {
   work->delay=1;
   count=CountDefinitionTargets(work->actor,0);work->count=count;
   if((u8)count==0)event->phase=259;
   else event->phase=258;
  } else {
   PlaceDefinitionResource(gModelResource,0,2,120,64,variant);
   work->positioned=CreatePositionedDefinitionTask(120,96,0,1,gPositionedIds[work->selector],work->output,gPositionedSequences[work->selector],parent);
   work->auxiliary=CreateDefinitionAuxiliaryTask(gAuxiliarySequences[work->selector],parent);
   work->palette=CreateDefinitionPaletteTask(gPaletteSequence,parent,gPaletteParameters[work->selector]);
   work->stage=CreateDefinitionStageTask(gStageSequences+8*work->selector,1,4,0,parent);
   work->ordinal=gInitialOrdinals[work->selector];
   ++event->phase;
  }
  break;
 }
 case 257: {
  u32 mask,count;u16 *display;u16 value;
  work->positioned=PollPositionedDefinitionTask(work->positioned);
  work->auxiliary=PollDefinitionAuxiliary(work->auxiliary);
  work->palette=PollDefinitionPalette(work->palette);
  if(--work->ordinal!=0)break;
  mask=ReadDisplayHighMaskWord(2);
  display=(u16 *)0x03000940;
  value=*display;value&=~mask;*display=value;
  work->delay=1;
  count=CountDefinitionTargets(work->actor,0);work->count=count;
  if((u8)count==0)event->phase=259;
  else ++event->phase;
  break;
 }
 case 258: {
  u32 initial_address=8;
  TaskNode **children;
  register u32 saved_base __asm__("r8");
  u32 pointer_snapshot,slot,raw_ordinal,shifted_ordinal,ordinal;
  register u32 offset __asm__("r4");
  TaskNode *created;
  /* The native defines the actual byte offset before adding the work base. */
  __asm__("" : "+r"(initial_address));
  initial_address+=(u32)work;
  children=(TaskNode **)initial_address;
  saved_base=initial_address;
  /* The actual child-cell base survives both poll and constructor calls. */
  __asm__("" : : "r"(saved_base));
  PollDefinitionTaskArray(children,2);
  if(--work->delay!=0)break;
  pointer_snapshot=(u32)work->children[0];
  slot=((0U-pointer_snapshot)|pointer_snapshot)>>31;
  child.selector=work->selector;child.ordinal=work->ordinal;
  child.record=GetDefinitionTargetRecord(work->actor,work->ordinal);
  created=CreateDefinitionTask(gChildEntry,48,&child,parent);
  offset=slot<<2;
  /* The shifted slot is the actual destructive address target, not a
   * second copied base; R0 constructor result remains untouched. */
  __asm__("" : "+r"(offset));
  offset+=saved_base;
  *(TaskNode **)offset=created;
  work->delay=gSpawnDelays[work->selector];
  raw_ordinal=work->ordinal+1;work->ordinal=raw_ordinal;
  shifted_ordinal=raw_ordinal<<24;
  __asm__("" : "+r"(shifted_ordinal));
  ordinal=shifted_ordinal>>24;
  if(ordinal==work->count)++event->phase;
  break;
 }
 case 259:
  work->positioned=PollPositionedDefinitionTask(work->positioned);
  if(work->positioned!=0)break;
  work->auxiliary=PollDefinitionAuxiliary(work->auxiliary);
  if(work->auxiliary!=0)break;
  work->palette=PollDefinitionPalette(work->palette);
  if(work->palette!=0)break;
  if((u8)PollDefinitionTaskArray(work->children,2)!=0)event->phase=2;
  break;
 }
 return 0;
}
