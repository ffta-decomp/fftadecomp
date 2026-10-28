typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
typedef struct TaskNode TaskNode;
struct SequenceEvent {u16 phase,unknown02;void *actor;u32 unknown08,flags;u8 unknown10[6];u16 variant;u8 unknown18[4];};
struct ChildEvent {u32 unknown00;void *record;u8 unknown08[12];u16 ordinal;u8 unknown16[6];};
struct SequenceWork {u8 variant,count,ordinal,delay;TaskNode *children[2],*resource,*auxiliary,*palettes[4],*opening;void *actor;TaskNode *sequence;};
typedef char EventSize[sizeof(struct SequenceEvent)==28?1:-1];
typedef char ChildSize[sizeof(struct ChildEvent)==28?1:-1];
typedef char WorkSize[sizeof(struct SequenceWork)==48?1:-1];
extern TaskNode *CreateDefinitionEffectTask(void *,const void *,u8,u8,const void *,TaskNode *);
extern void FinishDefinitionSequence(void);
extern TaskNode *PollDefinitionEffectTask(TaskNode *);
extern u32 QueryDefinitionTargets(void *,u16,u16,TaskNode *);
extern void ConfigureDefinitionResource(u8,u8,u8,s32,s32);
extern TaskNode *CreateDefinitionResource(u8,const void *,u16,u16);
extern u32 ReadDisplayHighMaskWord(u8);
extern TaskNode *CreateDefinitionAuxiliaryTask(const void *,TaskNode *);
extern TaskNode *CreateDefinitionPaletteTask(const void *,TaskNode *);
extern TaskNode *CreateDefinitionSequence(const void *,u8,u16,u16,TaskNode *);
extern u32 PollDefinitionTaskArray(TaskNode **,u16);
extern void *GetDefinitionTargetRecord(void *,u8);
extern TaskNode *CreateDefinitionTask(const void *,u16,const void *,TaskNode *);
extern TaskNode *PollDefinitionAuxiliary(TaskNode *);
extern TaskNode *PollDefinitionResource(TaskNode *,u8);
extern u32 PollDefinitionPaletteArray(TaskNode **,u16);
extern TaskNode *PollDefinitionPalette(TaskNode *);
extern const u8 gOpeningSequence[],gResource[],gAuxiliarySequence[],gPalette0[],gPalette1[],gPalette2[],gPalette3[],gInitialSequence[],gChildEntry[];
__asm__(
 ".global CreateDefinitionEffectTask\n.thumb_set CreateDefinitionEffectTask,0x80e03f9\n"
 ".global FinishDefinitionSequence\n.thumb_set FinishDefinitionSequence,0x80d38b5\n"
 ".global PollDefinitionEffectTask\n.thumb_set PollDefinitionEffectTask,0x80e05dd\n"
 ".global QueryDefinitionTargets\n.thumb_set QueryDefinitionTargets,0x80d8925\n"
 ".global ConfigureDefinitionResource\n.thumb_set ConfigureDefinitionResource,0x80d49fd\n"
 ".global CreateDefinitionResource\n.thumb_set CreateDefinitionResource,0x80d4b65\n"
 ".global ReadDisplayHighMaskWord\n.thumb_set ReadDisplayHighMaskWord,0x80035a9\n"
 ".global CreateDefinitionAuxiliaryTask\n.thumb_set CreateDefinitionAuxiliaryTask,0x80d3e9d\n"
 ".global CreateDefinitionPaletteTask\n.thumb_set CreateDefinitionPaletteTask,0x80d4705\n"
 ".global CreateDefinitionSequence\n.thumb_set CreateDefinitionSequence,0x80dfd8d\n"
 ".global PollDefinitionTaskArray\n.thumb_set PollDefinitionTaskArray,0x80e0571\n"
 ".global GetDefinitionTargetRecord\n.thumb_set GetDefinitionTargetRecord,0x80dd4a5\n"
 ".global CreateDefinitionTask\n.thumb_set CreateDefinitionTask,0x8005b6d\n"
 ".global PollDefinitionAuxiliary\n.thumb_set PollDefinitionAuxiliary,0x80d3f09\n"
 ".global PollDefinitionResource\n.thumb_set PollDefinitionResource,0x80d4d2d\n"
 ".global PollDefinitionPaletteArray\n.thumb_set PollDefinitionPaletteArray,0x80d48dd\n"
 ".global PollDefinitionPalette\n.thumb_set PollDefinitionPalette,0x80d4775\n"
 ".global gOpeningSequence\n.set gOpeningSequence,0x8398264\n"
 ".global gResource\n.set gResource,0x88edf80\n"
 ".global gAuxiliarySequence\n.set gAuxiliarySequence,0x894d7e4\n"
 ".global gPalette0\n.set gPalette0,0x8949784\n"
 ".global gPalette1\n.set gPalette1,0x8949798\n"
 ".global gPalette2\n.set gPalette2,0x89497ac\n"
 ".global gPalette3\n.set gPalette3,0x894ab00\n"
 ".global gInitialSequence\n.set gInitialSequence,0x83982b4\n"
 ".global gChildEntry\n.set gChildEntry,0x80e8a31\n"
);
s32 AdvanceAuthoredResourceTargetSequence(TaskNode *,struct SequenceEvent *,struct SequenceWork *) __asm__("OriginalActionCallback_000E8B24");
s32 AdvanceAuthoredResourceTargetSequence(TaskNode *parent,struct SequenceEvent *event,struct SequenceWork *work)
{
 struct ChildEvent child;
 register s32 phase __asm__("r3")=event->phase;
 __asm__("" : "+r"(phase));
 switch(phase) {
 case 0: {
  u32 variant=event->variant;void *actor;u8 count;
  work->variant=variant;actor=event->actor;work->actor=actor;
  count=3;if((u8)variant!=0)count=0;
  if(event->flags&1)count=0;
  work->opening=CreateDefinitionEffectTask(actor,gOpeningSequence,count,1,(const void *)phase,parent);
  break;
 }
 case 1:FinishDefinitionSequence();break;
 case 256: {
  u32 count;
  work->opening=PollDefinitionEffectTask(work->opening);
  if(work->opening!=0)break;
  if(work->variant!=0) {
   work->delay=1;
   count=QueryDefinitionTargets(work->actor,0,60,parent);work->count=count;
   if((u8)count==0)event->phase=258;
   else event->phase=257;
   break;
  }
  ConfigureDefinitionResource(0,2,0,120,96);
  work->resource=CreateDefinitionResource(0,gResource,0x3c7,6);
  {
   u32 mask=ReadDisplayHighMaskWord(2);
   u16 *display=(u16 *)0x03000940;
   register u32 control __asm__("r1")=*display;
   /* The native fresh H0 word is the destructive OR accumulator. */
   __asm__("" : "+r"(control));
   control|=mask;*display=control;
  }
  work->auxiliary=CreateDefinitionAuxiliaryTask(gAuxiliarySequence,parent);
  work->palettes[0]=CreateDefinitionPaletteTask(gPalette0,parent);
  work->palettes[1]=CreateDefinitionPaletteTask(gPalette1,parent);
  work->palettes[2]=CreateDefinitionPaletteTask(gPalette2,parent);
  work->palettes[3]=CreateDefinitionPaletteTask(gPalette3,parent);
  work->delay=40;
  work->count=QueryDefinitionTargets(work->actor,0,60,parent);
  work->sequence=CreateDefinitionSequence(gInitialSequence,1,4,0,parent);
  if(work->count==0)event->phase=258;
  else ++event->phase;
  break;
 }
 case 257: {
  TaskNode **children=work->children;
  register u32 saved_base __asm__("r8")=(u32)children;
  u32 pointer_snapshot,slot,raw_ordinal,shifted_ordinal,ordinal;
  register u32 offset __asm__("r4");
  TaskNode *created;
  /* Initial low-pointer poll and later preserved numeric base are distinct. */
  __asm__("" : : "r"(saved_base));
  PollDefinitionTaskArray(children,2);
  if(--work->delay!=0)break;
  pointer_snapshot=(u32)work->children[0];
  slot=((0U-pointer_snapshot)|pointer_snapshot)>>31;
  child.ordinal=work->ordinal;
  child.record=GetDefinitionTargetRecord(work->actor,work->ordinal);
  created=CreateDefinitionTask(gChildEntry,32,&child,parent);
  offset=slot<<2;
  __asm__("" : "+r"(offset));
  offset+=saved_base;
  *(TaskNode **)offset=created;
  work->delay=45;
  raw_ordinal=work->ordinal+1;work->ordinal=raw_ordinal;
  shifted_ordinal=raw_ordinal<<24;
  __asm__("" : "+r"(shifted_ordinal));
  ordinal=shifted_ordinal>>24;
  if(ordinal==work->count)++event->phase;
  break;
 }
 case 258:
  work->auxiliary=PollDefinitionAuxiliary(work->auxiliary);
  if(work->auxiliary!=0)break;
  work->resource=PollDefinitionResource(work->resource,0);
  if(work->resource!=0)break;
  if((u8)PollDefinitionPaletteArray(work->palettes,3)==0)break;
  work->palettes[3]=PollDefinitionPalette(work->palettes[3]);
  if(work->palettes[3]!=0)break;
  if((u8)PollDefinitionTaskArray(work->children,2)!=0)event->phase=2;
  break;
 }
 return 0;
}
