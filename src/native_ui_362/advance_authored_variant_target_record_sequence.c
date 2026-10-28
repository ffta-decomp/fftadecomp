typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
typedef struct TaskNode TaskNode;
struct SequenceEvent {u16 phase,unknown02;void *record;u32 parameter;u8 unknown0c[8];s16 definition;u16 variant;u8 unknown18[4];};
struct ChildEvent {u32 unknown00;void *record;u8 unknown08[12];u16 ordinal,direct;u8 unknown18[4];};
struct SequenceWork {
 u8 kind,count,ordinal,delay,direct,variant;u16 unknown06;
 TaskNode *children[2],*palettes[3],*flagged_palette,*auxiliary,*opening;
 void *owner;TaskNode *stage;void **records;u16 list_count,unknown36;
};
typedef char WorkSize[sizeof(struct SequenceWork)==56?1:-1];
typedef char EventSize[sizeof(struct SequenceEvent)==28?1:-1];
typedef char ChildSize[sizeof(struct ChildEvent)==28?1:-1];
extern TaskNode *CreateDefinitionEffectTask(void *,const void *,u8,u32,const void *,TaskNode *);
extern void FinishDefinitionSequence(void);
extern TaskNode *PollDefinitionEffectTask(TaskNode *);
extern u32 QueryDefinitionTargets(void *,u16,u16,TaskNode *);
extern void PlaceDefinitionResource(const void *,u32,u32,s32,s32,u32);
extern u32 ReadDisplayHighMaskWord(u8);
extern TaskNode *CreateDefinitionPaletteTask(const void *,TaskNode *);
extern TaskNode *CreateFlaggedDefinitionPaletteTask(const void *,TaskNode *,u16);
extern TaskNode *CreateDefinitionAuxiliaryTask(const void *,TaskNode *);
extern TaskNode *CreateDefinitionStageTask(const void *,u8,u16,u8,TaskNode *);
extern u32 PollDefinitionTaskArray(TaskNode **,u16);
/* Physical caller word is the already zero-extended byte; callee retains LOW8 consumption. */
extern void *GetDefinitionTargetRecord(void *,u32);
extern TaskNode *CreateDefinitionTask(const void *,u16,const void *,TaskNode *);
extern u32 TestEquipmentRecordFlag7(const void *);
extern TaskNode *PollDefinitionAuxiliary(TaskNode *);
extern u32 PollDefinitionPaletteArray(TaskNode **,u16);
extern TaskNode *PollDefinitionPalette(TaskNode *);
extern const u8 gOpeningCounts[],gModelResource[],gPalette0[],gPalette1[],gPalette2[],gFlaggedPalette[],gAuxiliarySequence[],gStageSequence[],gChildEntry[];
extern const void *const gOpeningSequences[];
__asm__(
 ".global CreateDefinitionEffectTask\n.thumb_set CreateDefinitionEffectTask,0x80e03f9\n"
 ".global FinishDefinitionSequence\n.thumb_set FinishDefinitionSequence,0x80d38b5\n"
 ".global PollDefinitionEffectTask\n.thumb_set PollDefinitionEffectTask,0x80e05dd\n"
 ".global QueryDefinitionTargets\n.thumb_set QueryDefinitionTargets,0x80d8925\n"
 ".global PlaceDefinitionResource\n.thumb_set PlaceDefinitionResource,0x80d7221\n"
 ".global ReadDisplayHighMaskWord\n.thumb_set ReadDisplayHighMaskWord,0x80035a9\n"
 ".global CreateDefinitionPaletteTask\n.thumb_set CreateDefinitionPaletteTask,0x80d4705\n"
 ".global CreateFlaggedDefinitionPaletteTask\n.thumb_set CreateFlaggedDefinitionPaletteTask,0x80d4725\n"
 ".global CreateDefinitionAuxiliaryTask\n.thumb_set CreateDefinitionAuxiliaryTask,0x80d3e9d\n"
 ".global CreateDefinitionStageTask\n.thumb_set CreateDefinitionStageTask,0x80dfd8d\n"
 ".global PollDefinitionTaskArray\n.thumb_set PollDefinitionTaskArray,0x80e0571\n"
 ".global GetDefinitionTargetRecord\n.thumb_set GetDefinitionTargetRecord,0x80dd4a5\n"
 ".global CreateDefinitionTask\n.thumb_set CreateDefinitionTask,0x8005b6d\n"
 ".global TestEquipmentRecordFlag7\n.thumb_set TestEquipmentRecordFlag7,0x80dd581\n"
 ".global PollDefinitionAuxiliary\n.thumb_set PollDefinitionAuxiliary,0x80d3f09\n"
 ".global PollDefinitionPaletteArray\n.thumb_set PollDefinitionPaletteArray,0x80d48dd\n"
 ".global PollDefinitionPalette\n.thumb_set PollDefinitionPalette,0x80d4775\n"
 ".global gOpeningCounts\n.set gOpeningCounts,0x83986c8\n"
 ".global gOpeningSequences\n.set gOpeningSequences,0x83986c0\n"
 ".global gModelResource\n.set gModelResource,0x88f4f6c\n"
 ".global gPalette0\n.set gPalette0,0x8949224\n"
 ".global gPalette1\n.set gPalette1,0x894923c\n"
 ".global gPalette2\n.set gPalette2,0x8949268\n"
 ".global gFlaggedPalette\n.set gFlaggedPalette,0x894ac90\n"
 ".global gAuxiliarySequence\n.set gAuxiliarySequence,0x894d754\n"
 ".global gStageSequence\n.set gStageSequence,0x8398710\n"
 ".global gChildEntry\n.set gChildEntry,0x80e97f5\n"
);
s32 AdvanceAuthoredVariantTargetRecordSequence(TaskNode *,struct SequenceEvent *,struct SequenceWork *) __asm__("OriginalActionCallback_000E9920");
s32 AdvanceAuthoredVariantTargetRecordSequence(TaskNode *input_parent,struct SequenceEvent *input_event,struct SequenceWork *input_work)
{
 /* Keep parent ordinary: explicit hard R7 suppresses its native callee-save in this compiler.
    The actual event capture is instead initialized in callee-preserved R6 before R1 is reused. */
 TaskNode *parent=input_parent;
 register struct SequenceEvent *event __asm__("r6")=input_event;
 struct SequenceWork *work=input_work;
 register s32 phase __asm__("r1");
 struct ChildEvent child;
 __asm__("" : "+r"(parent), "+r"(event), "+r"(work));
 phase=event->phase;
 __asm__("" : "+r"(phase));
 switch(phase) {
 case 0: {
  s32 definition;
  register const u8 *counts_base __asm__("r0");
  register u32 direct __asm__("r3");
  u32 selector,address;u8 count;
  work->kind=phase;
  definition=event->definition;
  if(definition==409) {
   work->kind=1;work->direct=1;work->records=event->record;
   work->list_count=event->parameter;
  } else {
   if(definition==313)work->kind=1;
   work->variant=event->variant;work->owner=event->record;
  }
  /* Direct/variant/owner are deliberately not initialized in the other arm. */
  counts_base=gOpeningCounts;
  __asm__("" : : "r"(counts_base));
  selector=work->kind;address=selector+(u32)counts_base;
  count=*(const u8 *)address;
  if(work->variant!=0)count=0;
  direct=work->direct;
  if(direct==0) {
   /* The actual initialized zero is the full fifth outgoing pointer word. */
   __asm__("" : "+r"(direct));
   work->opening=CreateDefinitionEffectTask(work->owner,gOpeningSequences[selector],count,1,(const void *)direct,parent);
  } else work->opening=CreateDefinitionEffectTask(work->owner,gOpeningSequences[selector],count,7,0,parent);
  break;
 }
 case 1:FinishDefinitionSequence();break;
 case 256:
  work->opening=PollDefinitionEffectTask(work->opening);
  if(work->opening!=0)break;
  if(work->variant!=0) {
   u32 count;
   work->delay=1;count=QueryDefinitionTargets(work->owner,0,170,parent);work->count=count;
   if((u8)count==0)event->phase=259;else event->phase=258;
  } else ++event->phase;
  break;
 case 257: {
  u32 mask,count;u16 *shadow;
  PlaceDefinitionResource(gModelResource,0,2,120,96,0);
  mask=ReadDisplayHighMaskWord(2);shadow=(u16 *)0x03000940;
  {
   register u32 previous __asm__("r1")=*shadow;
   __asm__("" : "+r"(previous));
   previous|=mask;*shadow=previous;
  }
  work->palettes[0]=CreateDefinitionPaletteTask(gPalette0,parent);
  work->palettes[1]=CreateDefinitionPaletteTask(gPalette1,parent);
  work->palettes[2]=CreateDefinitionPaletteTask(gPalette2,parent);
  work->flagged_palette=CreateFlaggedDefinitionPaletteTask(gFlaggedPalette,parent,135);
  work->auxiliary=CreateDefinitionAuxiliaryTask(gAuxiliarySequence,parent);
  work->delay=150;
  if(work->direct!=0)count=work->list_count;
  else count=QueryDefinitionTargets(work->owner,0,170,parent);
  work->count=count;
  work->stage=CreateDefinitionStageTask(gStageSequence,1,4,0,parent);
  if(work->count==0)event->phase=259;else ++event->phase;
  break;
 }
 case 258: {
  TaskNode **children=work->children;
  register u32 saved_base __asm__("r8");
  register u32 shifted_delay __asm__("r0");
  u32 pointer_snapshot,slot,raw_ordinal,shifted_ordinal;
  register u32 destination __asm__("r1");
  TaskNode *created;
  PollDefinitionTaskArray(children,2);
  shifted_delay=work->delay-1;work->delay=shifted_delay;
  shifted_delay<<=24;
  __asm__("" : "+r"(shifted_delay));
  /* Native R8 receives the real base after the wrapping timer definition. */
  saved_base=(u32)children;
  __asm__("" : "+r"(saved_base));
  if(shifted_delay!=0)break;
  pointer_snapshot=(u32)work->children[0];
  slot=((0U-pointer_snapshot)|pointer_snapshot)>>31;
  child.ordinal=work->ordinal;child.direct=work->direct;
  {
   u32 direct=work->direct;
   register u32 ordinal __asm__("r1")=work->ordinal;
   /* Native captures both fresh bytes before CMP; the same ordinal enters either consumer.
      Input-only observes the actual initialized byte snapshot; the physical caller word is declared full-width below. */
   __asm__("" : : "r"(direct), "r"(ordinal));
   if(direct!=0)child.record=work->records[ordinal];
   else child.record=GetDefinitionTargetRecord(work->owner,ordinal);
  }
  created=CreateDefinitionTask(gChildEntry,36,&child,parent);
  destination=slot<<2;
  __asm__("" : "+r"(destination));
  destination+=saved_base;*(TaskNode **)destination=created;
  work->delay=50;
  if(work->direct==0 && (u8)TestEquipmentRecordFlag7(child.record)==0)work->delay-=10;
  raw_ordinal=work->ordinal+1;work->ordinal=raw_ordinal;
  shifted_ordinal=raw_ordinal<<24;
  __asm__("" : "+r"(shifted_ordinal));
  if((shifted_ordinal>>24)==work->count)++event->phase;
  break;
 }
 case 259: {
  u32 mask;u16 *shadow;
  work->auxiliary=PollDefinitionAuxiliary(work->auxiliary);
  if(work->auxiliary!=0)break;
  if((u8)PollDefinitionPaletteArray(work->palettes,3)==0)break;
  work->flagged_palette=PollDefinitionPalette(work->flagged_palette);
  if(work->flagged_palette!=0)break;
  mask=ReadDisplayHighMaskWord(2);shadow=(u16 *)0x03000940;
  {
   /* The fresh halfword is the actual initialized BIC destination, not the returned mask. */
   register u32 previous __asm__("r1")=*shadow;
   __asm__("" : "+r"(previous));
   previous&=~mask;*shadow=previous;
  }
  if((u8)PollDefinitionTaskArray(work->children,2)==0)break;
  mask=ReadDisplayHighMaskWord(2);
  {
   register u32 previous __asm__("r1")=*shadow;
   __asm__("" : "+r"(previous));
   previous&=~mask;*shadow=previous;
  }
  event->phase=2;
  break;
 }
 }
 return 0;
}
