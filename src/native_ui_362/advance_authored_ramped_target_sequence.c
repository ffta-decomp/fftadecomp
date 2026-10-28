typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
typedef struct TaskNode TaskNode;
struct DefinitionRamp {u16 value;s16 remaining,error;u16 step,period,magnitude;};
struct SequenceEvent {u16 phase,unknown02;void *actor;u8 unknown08[14];u16 variant;u8 unknown18[4];};
struct ChildEvent {u32 unknown00;void *record;u8 unknown08[12];u16 ordinal;u8 unknown16[6];};
struct SequenceWork {u8 variant,count,ordinal,delay;u16 x,y;struct DefinitionRamp ramp;TaskNode *children[2];u8 unknown1C[8];TaskNode *positioned;void *model;TaskNode *auxiliary,*palettes[3],*opening;void *actor;TaskNode *stage;};
struct __attribute__((packed)) DefinitionResourceHeader {u16 flags,relative_offset;};
typedef char EventSize[sizeof(struct SequenceEvent)==28?1:-1];
typedef char ChildSize[sizeof(struct ChildEvent)==28?1:-1];
typedef char WorkSize[sizeof(struct SequenceWork)==72?1:-1];
typedef char RampSize[sizeof(struct DefinitionRamp)==12?1:-1];
extern TaskNode * CreateDefinitionEffectTask(void *,const void *,u8,u8,const void *,TaskNode *);
extern void FinishDefinitionSequence(void);
extern TaskNode * PollDefinitionEffectTask(TaskNode *);
extern u32 CountDefinitionTargets(void *,u16);
extern u32 PollDefinitionTaskArray(TaskNode **,u16);
extern void * GetDefinitionTargetRecord(void *,u8);
extern TaskNode * CreateDefinitionTask(const void *,u16,const void *,TaskNode *);
extern void InitializeDefinitionRamp(struct DefinitionRamp *,u16,u16,u16);
extern void AdvanceDefinitionRamp(struct DefinitionRamp *);
extern u32 IsDefinitionRampComplete(const struct DefinitionRamp *);
extern void ConfigureDefinitionResourceCoordinates(u8,u8,u16,s16,s16);
extern void * CreateDefinitionResource(u8,const struct DefinitionResourceHeader *,u16,u8);
extern void SetDefinitionResourceEnabled(void *,u8);
extern void PublishDefinitionResourcePosition(u8,s32,s32);
extern void ReleaseDefinitionResource(void *,u8);
extern TaskNode * CreateDefinitionAuxiliaryTask(const void *,TaskNode *);
extern TaskNode * PollDefinitionAuxiliary(TaskNode *);
extern void ConfigureDefinitionAuxiliary(TaskNode *,u8,u8);
extern TaskNode * CreateDefinitionPaletteTask(const void *,TaskNode *);
extern TaskNode * CreateParameterizedPaletteTask(const void *,TaskNode *,u16);
extern TaskNode * PollDefinitionPalette(TaskNode *);
extern u32 PollPaletteArray(void **,u32);
extern TaskNode * CreatePositionedDefinitionTask(int,s16,int,u8,u32,void *,const void *,TaskNode *);
extern TaskNode * PollPositionedDefinitionTask(TaskNode *);
extern void PlaceDefinitionResource(const void *,u32,u32,s32,s32,u32);
extern TaskNode * CreateDefinitionStageTask(const void *,u8,u16,u16,TaskNode *);
extern u32 ReadDisplayHighMaskWord(u8);
/* D6098 stores LOW16 y; this caller transports its original signed-H6 view.
 * BC08 stores LOW16 x/y; full signed words here preserve the native LDRSHs. */
extern const u8 gOpeningSequence[],gInitialPalette[],gAuxiliarySequence[],gPositionedSequence[],gStageSequence[],gFollowPalette0[],gFollowPalette1[],gFollowPalette2[],gFollowModel[],gChildEntry[];
extern const struct DefinitionResourceHeader gInitialResource;
__asm__(
 ".global gOpeningSequence\n.set gOpeningSequence,0x8397718\n"
 ".global gInitialPalette\n.set gInitialPalette,0x8949574\n"
 ".global gAuxiliarySequence\n.set gAuxiliarySequence,0x894d69c\n"
 ".global gPositionedSequence\n.set gPositionedSequence,0x8397760\n"
 ".global gStageSequence\n.set gStageSequence,0x83977cc\n"
 ".global gFollowPalette0\n.set gFollowPalette0,0x894959c\n"
 ".global gFollowPalette1\n.set gFollowPalette1,0x89495fc\n"
 ".global gFollowPalette2\n.set gFollowPalette2,0x8948684\n"
 ".global gFollowModel\n.set gFollowModel,0x88f54a0\n"
 ".global gChildEntry\n.set gChildEntry,0x80e7131\n"
 ".global gInitialResource\n.set gInitialResource,0x88ed538\n"
 ".global CreateDefinitionEffectTask\n.thumb_set CreateDefinitionEffectTask,0x80e03f9\n"
 ".global FinishDefinitionSequence\n.thumb_set FinishDefinitionSequence,0x80d38b5\n"
 ".global PollDefinitionEffectTask\n.thumb_set PollDefinitionEffectTask,0x80e05dd\n"
 ".global CountDefinitionTargets\n.thumb_set CountDefinitionTargets,0x80d8859\n"
 ".global PollDefinitionTaskArray\n.thumb_set PollDefinitionTaskArray,0x80e0571\n"
 ".global GetDefinitionTargetRecord\n.thumb_set GetDefinitionTargetRecord,0x80dd4a5\n"
 ".global CreateDefinitionTask\n.thumb_set CreateDefinitionTask,0x8005b6d\n"
 ".global InitializeDefinitionRamp\n.thumb_set InitializeDefinitionRamp,0x80e0609\n"
 ".global AdvanceDefinitionRamp\n.thumb_set AdvanceDefinitionRamp,0x80e064d\n"
 ".global IsDefinitionRampComplete\n.thumb_set IsDefinitionRampComplete,0x80e0691\n"
 ".global ConfigureDefinitionResourceCoordinates\n.thumb_set ConfigureDefinitionResourceCoordinates,0x80d49fd\n"
 ".global CreateDefinitionResource\n.thumb_set CreateDefinitionResource,0x80d4b65\n"
 ".global SetDefinitionResourceEnabled\n.thumb_set SetDefinitionResourceEnabled,0x800bda5\n"
 ".global PublishDefinitionResourcePosition\n.thumb_set PublishDefinitionResourcePosition,0x800bc09\n"
 ".global ReleaseDefinitionResource\n.thumb_set ReleaseDefinitionResource,0x80d4d15\n"
 ".global CreateDefinitionAuxiliaryTask\n.thumb_set CreateDefinitionAuxiliaryTask,0x80d3e9d\n"
 ".global PollDefinitionAuxiliary\n.thumb_set PollDefinitionAuxiliary,0x80d3f09\n"
 ".global ConfigureDefinitionAuxiliary\n.thumb_set ConfigureDefinitionAuxiliary,0x80d3f85\n"
 ".global CreateDefinitionPaletteTask\n.thumb_set CreateDefinitionPaletteTask,0x80d4705\n"
 ".global CreateParameterizedPaletteTask\n.thumb_set CreateParameterizedPaletteTask,0x80d4725\n"
 ".global PollDefinitionPalette\n.thumb_set PollDefinitionPalette,0x80d4775\n"
 ".global PollPaletteArray\n.thumb_set PollPaletteArray,0x80d48dd\n"
 ".global CreatePositionedDefinitionTask\n.thumb_set CreatePositionedDefinitionTask,0x80d6099\n"
 ".global PollPositionedDefinitionTask\n.thumb_set PollPositionedDefinitionTask,0x80d6135\n"
 ".global PlaceDefinitionResource\n.thumb_set PlaceDefinitionResource,0x80d7221\n"
 ".global CreateDefinitionStageTask\n.thumb_set CreateDefinitionStageTask,0x80dfd8d\n"
 ".global ReadDisplayHighMaskWord\n.thumb_set ReadDisplayHighMaskWord,0x80035a9\n"
);
s32 AdvanceAuthoredRampedTargetSequence(TaskNode *,struct SequenceEvent *,struct SequenceWork *) __asm__("OriginalActionCallback_000E72B4");
s32 AdvanceAuthoredRampedTargetSequence(TaskNode *parent,struct SequenceEvent *event,struct SequenceWork *work)
{
 struct ChildEvent child;
 register s32 phase __asm__("r3")=event->phase;
 /* Actual full phase also supplies the phase0 zero outgoing word. */
 __asm__("" : "+r"(phase));
 switch(phase) {
 case 0: {
  u16 variant;void *actor;u8 count;
  variant=event->variant;work->variant=variant;
  actor=event->actor;work->actor=actor;
  count=6;
  if((u8)variant!=0)count=0;
  work->opening=CreateDefinitionEffectTask(actor,gOpeningSequence,count,1,(const void *)phase,parent);
  break;
 }
 case 1:FinishDefinitionSequence();break;
 case 256:
  work->opening=PollDefinitionEffectTask(work->opening);
  if(work->opening!=0)break;
  if(work->variant!=0) {
   work->delay=1;
   work->count=CountDefinitionTargets(work->actor,0);
   event->phase=259;
  } else {
   void *model;TaskNode *auxiliary;u32 mask;u16 value;u16 *display;
   work->x=120;work->y=96;
   InitializeDefinitionRamp(&work->ramp,62,86,119);
   ConfigureDefinitionResourceCoordinates(0,2,0,(s16)work->x,(s16)work->ramp.value);
   model=CreateDefinitionResource(0,&gInitialResource,995,6);
   work->model=model;
   SetDefinitionResourceEnabled(model,1);
   mask=ReadDisplayHighMaskWord(2);
   display=(u16 *)0x03000940;
   value=*display;value|=mask;*display=value;
   work->palettes[0]=CreateDefinitionPaletteTask(gInitialPalette,parent);
   auxiliary=CreateDefinitionAuxiliaryTask(gAuxiliarySequence,parent);
   work->auxiliary=auxiliary;
   ConfigureDefinitionAuxiliary(auxiliary,12,255);
   work->positioned=CreatePositionedDefinitionTask((s16)work->x,(s16)work->y,0,1,2,work->unknown1C,gPositionedSequence,parent);
   work->stage=CreateDefinitionStageTask(gStageSequence,2,4,0,parent);
   ++event->phase;
  }
  break;
 case 257: {
  struct DefinitionRamp *ramp=&work->ramp;
  register TaskNode *palette __asm__("r4");
  u32 mask;u16 value;u16 *display;
  if((u8)IsDefinitionRampComplete(ramp)==0) {
   AdvanceDefinitionRamp(ramp);
   PublishDefinitionResourcePosition(0,(s16)work->x,(s16)work->ramp.value);
   break;
  }
  work->auxiliary=PollDefinitionAuxiliary(work->auxiliary);
  if(work->auxiliary!=0)break;
  palette=PollDefinitionPalette(work->palettes[0]);work->palettes[0]=palette;
  if(palette!=0)break;
  /* The full returned NULL remains the native model-clear/outgoing carrier
   * across release and mask helpers, then is consumed by the actual call. */
  __asm__("" : "+r"(palette));
  ReleaseDefinitionResource(work->model,0);
  work->model=palette;
  mask=ReadDisplayHighMaskWord(2);
  display=(u16 *)0x03000940;
  value=*display;value&=~mask;*display=value;
  PlaceDefinitionResource(gFollowModel,1,3,(s16)work->x,(s16)(work->y-10),(u32)palette);
  work->palettes[0]=CreateDefinitionPaletteTask(gFollowPalette0,parent);
  work->palettes[1]=CreateDefinitionPaletteTask(gFollowPalette1,parent);
  work->palettes[2]=CreateParameterizedPaletteTask(gFollowPalette2,parent,30);
  work->ordinal=49;
  ++event->phase;
  break;
 }
 case 258: {
  u32 count;
  if(work->ordinal!=0)--work->ordinal;
  work->positioned=PollPositionedDefinitionTask(work->positioned);
  if(work->positioned!=0)break;
  if(work->ordinal!=0)break;
  work->delay=1;
  count=CountDefinitionTargets(work->actor,0);work->count=count;
  if((u8)count==0)event->phase=260;
  else ++event->phase;
  break;
 }
 case 259: {
  register u32 initial_address __asm__("r2")=20;
  register u32 saved_base __asm__("r8");
  register u32 offset __asm__("r4");
  u32 pointer_snapshot,slot,raw_ordinal,shifted_ordinal,ordinal;
  TaskNode *created;
  /* The real offset20 is defined in R2 before adding the complete work base;
   * the saved R8 address is used by the poll and later destination only. */
  __asm__("" : "+r"(initial_address));
  initial_address+=(u32)work;
  saved_base=initial_address;
  __asm__("" : : "r"(saved_base));
  PollDefinitionTaskArray((TaskNode **)saved_base,2);
  if(--work->delay!=0)break;
  pointer_snapshot=(u32)work->children[0];
  slot=((0U-pointer_snapshot)|pointer_snapshot)>>31;
  child.record=GetDefinitionTargetRecord(work->actor,work->ordinal);
  child.ordinal=work->ordinal;
  created=CreateDefinitionTask(gChildEntry,36,&child,parent);
  offset=slot<<2;
  __asm__("" : "+r"(offset));
  offset+=saved_base;
  *(TaskNode **)offset=created;
  work->delay=50;
  raw_ordinal=work->ordinal+1;work->ordinal=raw_ordinal;
  shifted_ordinal=raw_ordinal<<24;
  __asm__("" : "+r"(shifted_ordinal));
  ordinal=shifted_ordinal>>24;
  if(ordinal==work->count)++event->phase;
  break;
 }
 case 260: {
  u32 mask;u16 value;u16 *display;
  if((u8)PollPaletteArray((void **)work->palettes,3)==0)break;
  mask=ReadDisplayHighMaskWord(3);
  display=(u16 *)0x03000940;
  value=*display;value&=~mask;*display=value;
  if((u8)PollDefinitionTaskArray(work->children,2)!=0)event->phase=2;
  break;
 }
 }
 return 0;
}
