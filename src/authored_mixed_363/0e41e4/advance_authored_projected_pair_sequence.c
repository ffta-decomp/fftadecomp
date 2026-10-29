typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
typedef struct TaskNode TaskNode;
struct CoordinateCurve {s32 from_x,from_y,to_x,to_y,sign_x,sign_y;u32 delta_x,delta_y;s32 error,half_delta_y;u32 full_delta_y;};
struct SequenceEvent {u16 phase,unknown02;void *actor;u8 unknown08[12];s16 definition;u16 variant;u8 unknown18[4];};
struct SequenceWork {u8 kind,style,variant,unknown03;u16 delay,x,y;u8 unknown0A[6];void *actor,*record,*model;u8 unknown1C[8];TaskNode *positioned;void *paired[2];TaskNode *palettes[2],*auxiliary,*opening,*motions[2],*stage;struct CoordinateCurve curve;};
struct __attribute__((packed)) DefinitionResourceHeader {u16 flags,relative_offset;};
typedef char EventSize[sizeof(struct SequenceEvent)==28?1:-1];
typedef char WorkSize[sizeof(struct SequenceWork)==120?1:-1];
typedef char CurveSize[sizeof(struct CoordinateCurve)==44?1:-1];
extern TaskNode * CreateDefinitionEffectTask(void *,const void *,u8,u8,const void *,TaskNode *);
extern void FinishDefinitionSequence(void);
extern TaskNode * PollDefinitionEffectTask(TaskNode *);
extern u32 CountDefinitionTargets(void *,u16);
extern void * GetDefinitionTargetRecord(void *,u8);
/* Fourth argument is the original full signed load; helper consumes LOW16. */
extern void ConfigureDefinitionResourceCoordinates(u8,u8,u16,s32,s16);
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
extern TaskNode * CreatePositionedDefinitionTask(int,s16,int,u8,u32,void *,const void *,TaskNode *);
extern TaskNode * PollPositionedDefinitionTask(TaskNode *);
extern void PlaceDefinitionResource(const void *,u32,u32,s32,s32,u32);
extern TaskNode * CreateDefinitionStageTask(const void *,u8,u16,u16,TaskNode *);
extern u32 ReadDisplayHighMaskWord(u8);
extern void CopyCountedPaletteGroups(const void *,u32,u32,u32,u32);
extern void * ResolveDefinitionRecordCoordinates(void *,u16 *,u16 *,u16 *);
extern void InitializeCoordinateCurve(struct CoordinateCurve *,s32,s32,s32,s32);
extern void AdvanceCoordinateCurve(struct CoordinateCurve *);
extern u32 IsCoordinateCurveComplete(const struct CoordinateCurve *);
extern u32 ReadDefinitionRecordSelector(void *,u8);
extern TaskNode * CreateDefinitionRecordMotion(void *,u16,TaskNode *);
extern TaskNode * CreateConditionalRecordSequence(void *,const void *,u8,u16,u16,TaskNode *,u16);
extern void CopyDefinitionRecordCoordinates(const u16 *,u16 *,u16 *,u16 *);
extern void * CreatePairedDefinitionResource(const struct DefinitionResourceHeader *,u16,s32,s32,s32,u32,u8);
extern void SetDefinitionObjectSortKey(void *,s16);
extern u32 PollDefinitionWorkset(void **,u16);
extern TaskNode * PollDefinitionRecordMotion(TaskNode *);
/* Paired-resource x/y/z and resource are physical word transports; the
 * helper consumes LOW16. Resource is the original full 927 snapshot.
 * These are caller views, not shared ABI edits. */
extern const u8 gOpeningCounts[],gSpecialPaletteGroups[],gMotionDelays[],gConditionalSequences[],gPositionedIds[],gPaletteParameters[],gInitialPalette[],gAuxiliarySequence[],gMainFollowModel[],gNormalFollowPalette[],gSpecialFollowPalette[],gParameterizedPalette[];
extern const void *const gOpeningSequences[],*const gStageSequences[],*const gPositionedSequences[];
extern const struct DefinitionResourceHeader gModelHeader,gPairedHeader;
__asm__(
 ".global gOpeningCounts\n.set gOpeningCounts,0x8396a2c\n"
 ".global gOpeningSequences\n.set gOpeningSequences,0x8396a24\n"
 ".global gSpecialPaletteGroups\n.set gSpecialPaletteGroups,0x88ea7f0\n"
 ".global gMotionDelays\n.set gMotionDelays,0x8396ac8\n"
 ".global gConditionalSequences\n.set gConditionalSequences,0x8396aa0\n"
 ".global gPositionedIds\n.set gPositionedIds,0x8396a98\n"
 ".global gPositionedSequences\n.set gPositionedSequences,0x8396a90\n"
 ".global gPaletteParameters\n.set gPaletteParameters,0x8396a9a\n"
 ".global gStageSequences\n.set gStageSequences,0x8396afc\n"
 ".global gInitialPalette\n.set gInitialPalette,0x8948d48\n"
 ".global gAuxiliarySequence\n.set gAuxiliarySequence,0x894d69c\n"
 ".global gParameterizedPalette\n.set gParameterizedPalette,0x894aba0\n"
 ".global gMainFollowModel\n.set gMainFollowModel,0x88f46f0\n"
 ".global gNormalFollowPalette\n.set gNormalFollowPalette,0x8948d70\n"
 ".global gSpecialFollowPalette\n.set gSpecialFollowPalette,0x894a458\n"
 ".global gModelHeader\n.set gModelHeader,0x88ed538\n"
 ".global gPairedHeader\n.set gPairedHeader,0x84f6130\n"
 ".global CreateDefinitionEffectTask\n.thumb_set CreateDefinitionEffectTask,0x80e03f9\n"
 ".global FinishDefinitionSequence\n.thumb_set FinishDefinitionSequence,0x80d38b5\n"
 ".global PollDefinitionEffectTask\n.thumb_set PollDefinitionEffectTask,0x80e05dd\n"
 ".global CountDefinitionTargets\n.thumb_set CountDefinitionTargets,0x80d8859\n"
 ".global GetDefinitionTargetRecord\n.thumb_set GetDefinitionTargetRecord,0x80dd4a5\n"
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
 ".global CreatePositionedDefinitionTask\n.thumb_set CreatePositionedDefinitionTask,0x80d6099\n"
 ".global PollPositionedDefinitionTask\n.thumb_set PollPositionedDefinitionTask,0x80d6135\n"
 ".global PlaceDefinitionResource\n.thumb_set PlaceDefinitionResource,0x80d7221\n"
 ".global CreateDefinitionStageTask\n.thumb_set CreateDefinitionStageTask,0x80dfd8d\n"
 ".global ReadDisplayHighMaskWord\n.thumb_set ReadDisplayHighMaskWord,0x80035a9\n"
 ".global CopyCountedPaletteGroups\n.thumb_set CopyCountedPaletteGroups,0x80d45d1\n"
 ".global ResolveDefinitionRecordCoordinates\n.thumb_set ResolveDefinitionRecordCoordinates,0x80dd749\n"
 ".global InitializeCoordinateCurve\n.thumb_set InitializeCoordinateCurve,0x80075cd\n"
 ".global AdvanceCoordinateCurve\n.thumb_set AdvanceCoordinateCurve,0x80076a1\n"
 ".global IsCoordinateCurveComplete\n.thumb_set IsCoordinateCurveComplete,0x8007881\n"
 ".global ReadDefinitionRecordSelector\n.thumb_set ReadDefinitionRecordSelector,0x80dd685\n"
 ".global CreateDefinitionRecordMotion\n.thumb_set CreateDefinitionRecordMotion,0x80df90d\n"
 ".global CreateConditionalRecordSequence\n.thumb_set CreateConditionalRecordSequence,0x80dcfe5\n"
 ".global CopyDefinitionRecordCoordinates\n.thumb_set CopyDefinitionRecordCoordinates,0x80dbd5d\n"
 ".global CreatePairedDefinitionResource\n.thumb_set CreatePairedDefinitionResource,0x80d5e81\n"
 ".global SetDefinitionObjectSortKey\n.thumb_set SetDefinitionObjectSortKey,0x8011059\n"
 ".global PollDefinitionWorkset\n.thumb_set PollDefinitionWorkset,0x80d5f25\n"
 ".global PollDefinitionRecordMotion\n.thumb_set PollDefinitionRecordMotion,0x80dba5d\n"
);
s32 AdvanceAuthoredProjectedPairSequence(TaskNode *,struct SequenceEvent *,struct SequenceWork *) __asm__("OriginalActionCallback_000E41E4");
s32 AdvanceAuthoredProjectedPairSequence(TaskNode *parent,struct SequenceEvent *input_event,struct SequenceWork *input_work)
{
 register struct SequenceEvent *event __asm__("r10")=input_event;
 register struct SequenceWork *incoming_work __asm__("r2")=input_work;
 struct SequenceWork *work;
 register s32 phase __asm__("r1");
 u16 projected_x,projected_y,projected_z;
 /* Saved event and the original incoming pointer have distinct uses. */
 __asm__("" : "+r"(incoming_work) : "r"(event));
 work=incoming_work;
 phase=input_event->phase;
 __asm__("" : "+r"(phase));
 switch(phase) {
 case 0: {
  register u32 raw_definition __asm__("r2")=(u16)event->definition;
  register u32 zero __asm__("r5");
  register struct SequenceEvent *source __asm__("r4");
  register u32 variant __asm__("r1");
  register void *actor __asm__("r3");
  register u32 style __asm__("r4");
  u8 count;
  /* The unsigned snapshot and fresh signed comparison are distinct reads. */
  __asm__("" : "+r"(raw_definition));
  if(event->definition!=102) {
   register u32 kind __asm__("r0")=raw_definition-6;
   __asm__("" : "+r"(kind));
   work->kind=kind;work->style=kind;
  } else {
   work->kind=2;work->style=phase;
  }
  /* The case-local event address dies at the actor load, before R4
   * becomes the selector snapshot; phase R1 is already consumed. */
  source=event;
  __asm__("" : : "r"(source));
  variant=source->variant;
  __asm__("" : "+r"(variant));
  zero=0;
  __asm__("" : "+r"(zero));
  work->variant=variant;
  actor=source->actor;
  __asm__("" : : "r"(actor));
  work->actor=actor;
  {
   register const u8 *counts_base __asm__("r0")=gOpeningCounts;
   u32 address;
   __asm__("" : : "r"(counts_base));
   style=work->style;
   /* The byte storage becomes the actual fullword R4 index used by both
    * address calculations, after the event-root R4 has died. */
   __asm__("" : : "r"(style));
   address=(u32)style+(u32)counts_base;
   count=*(const u8 *)address;
  }
  if((u8)variant!=0)count=0;
  if(work->kind!=2) {
   register const void *const *sequences __asm__("r1")=gOpeningSequences;
   register u32 sequence_index __asm__("r0");
   register const void *sequence __asm__("r1");
   __asm__("" : : "r"(sequences));
   sequence_index=style<<2;
   __asm__("" : "+r"(sequence_index));
   sequence_index+=(u32)sequences;
   sequence=*(const void **)sequence_index;
   __asm__("" : : "r"(sequence));
   work->opening=CreateDefinitionEffectTask(actor,sequence,count,1,(const void *)zero,parent);
  } else
   work->opening=CreateDefinitionEffectTask(actor,gOpeningSequences[0],count,7,(const void *)zero,
    ({register TaskNode *stack_parent __asm__("r4")=parent;
      /* The sixth argument is read only after the fifth is stored. */
      __asm__("" : "+r"(stack_parent));stack_parent;}));
  break;
 }
 case 1:FinishDefinitionSequence();break;
 case 256: {
  void *target,*model;TaskNode *auxiliary;u32 path,sequence_address,mask;u16 value,*display;register s32 y __asm__("r3");
  work->opening=PollDefinitionEffectTask(work->opening);
  if(work->opening!=0)break;
  if(work->kind==2) {
   CopyCountedPaletteGroups(gSpecialPaletteGroups,6,1,5,1);
   CopyCountedPaletteGroups(gSpecialPaletteGroups,7,1,5,1);
  }
  if((u8)CountDefinitionTargets(work->actor,0)==0)goto finish_sequence;
  target=GetDefinitionTargetRecord(work->actor,0);
  work->record=ResolveDefinitionRecordCoordinates(target,&work->x,&work->y,0);
  {
   register struct CoordinateCurve *initial_curve __asm__("r0")=&work->curve;
   register s32 from_y __asm__("r1");
   /* This real first argument is established before the fresh Y load. */
   __asm__("" : "+r"(initial_curve));
   /* Original signed H8 read: real LDRSH output and offset scratch. */
   __asm__ volatile("mov r2, #8\n\tldrsh %0, [%1, r2]"
    : "=&l"(y) : "l"(work), "m"(work->y) : "r2", "cc");
   from_y=y-40;
   /* The copied start and shared Y working value precede destructive Y-16. */
   __asm__("" : "+r"(from_y), "+r"(y) : "r"(initial_curve));
   y-=16;
   InitializeCoordinateCurve(initial_curve,from_y,0,y,71);
  }
  ConfigureDefinitionResourceCoordinates(0,2,0,
   ({register s32 coordinate __asm__("r3");
    /* Original signed H6 read; only its two-instruction address island remains ASM. */
    __asm__ volatile("mov r4, #6\n\tldrsh %0, [%1, r4]"
     : "=&l"(coordinate) : "l"(work), "m"(work->x) : "r4", "cc");coordinate;}),(s16)work->curve.from_x);
  model=CreateDefinitionResource(0,&gModelHeader,995,6);
  work->model=model;SetDefinitionResourceEnabled(model,1);
  mask=ReadDisplayHighMaskWord(2);
  display=(u16 *)0x03000940;
  value=*display;value|=mask;*display=value;
  work->palettes[0]=CreateDefinitionPaletteTask(gInitialPalette,parent);
  auxiliary=CreateDefinitionAuxiliaryTask(gAuxiliarySequence,parent);
  work->auxiliary=auxiliary;
  ConfigureDefinitionAuxiliary(auxiliary,12,255);
  path=1;
  /* This actual one definition survives the opaque selector call. */
  __asm__("" : "+r"(path));
  if((u8)ReadDefinitionRecordSelector(target,0)!=0)path=0;
  if(path==0)
   work->motions[0]=CreateDefinitionRecordMotion(work->record,gMotionDelays[work->style],parent);
  sequence_address=20*path+(u32)gConditionalSequences;
  work->motions[1]=CreateConditionalRecordSequence(target,(const void *)sequence_address,12,gMotionDelays[work->style],2,parent,gMotionDelays[work->style]);
  work->stage=CreateDefinitionStageTask(gStageSequences[work->style],2,4,0,parent);
  work->delay=65;
  {
   register struct SequenceEvent *publication __asm__("r2")=event;
   /* This actual late publication address dies at its halfword store. */
   __asm__("" : "+r"(publication));
   ++publication->phase;
  }
  break;
 }
 case 257: {
  register u32 paired_resource __asm__("r8");
  struct CoordinateCurve *curve=&work->curve;
  if(IsCoordinateCurveComplete(curve)==0) {
   AdvanceCoordinateCurve(curve);
   PublishDefinitionResourcePosition(0,
    ({register s32 coordinate __asm__("r1");
    /* Original signed H6 read; only its two-instruction address island remains ASM. */
    __asm__ volatile("mov r3, #6\n\tldrsh %0, [%1, r3]"
     : "=&l"(coordinate) : "l"(work), "m"(work->x) : "r3", "cc");coordinate;}),(s16)work->curve.from_x);
  }
  work->auxiliary=PollDefinitionAuxiliary(work->auxiliary);
  if(--work->delay!=0)break;
  work->positioned=CreatePositionedDefinitionTask(
   ({register s32 coordinate __asm__("r0");
    /* Original signed H6 read; only its two-instruction address island remains ASM. */
    __asm__ volatile("mov r4, #6\n\tldrsh %0, [%1, r4]"
     : "=&l"(coordinate) : "l"(work), "m"(work->x) : "r4", "cc");coordinate;}),(s16)work->y,0,1,gPositionedIds[work->style],work->unknown1C,gPositionedSequences[work->style],parent);
  CopyDefinitionRecordCoordinates(work->record,&projected_x,&projected_y,&projected_z);
  work->paired[0]=CreatePairedDefinitionResource(&gPairedHeader,2,(s16)projected_x,(s16)projected_y,(s16)projected_z,
   ({register u32 resource_literal __asm__("r0")=927;
     paired_resource=resource_literal;
     /* The physical argument is the literal working value; R8 is its snapshot. */
     __asm__("" : : "r"(paired_resource), "r"(resource_literal));resource_literal;}),6);
  work->paired[1]=CreatePairedDefinitionResource(&gPairedHeader,3,
   ({register const u16 *coordinate_source __asm__("r0")=&projected_x;
     register s32 coordinate __asm__("r2");
     /* Fresh second-call OUT X load, after the first call may update OUT storage. */
     __asm__ volatile("mov r1, #0\n\tldrsh %0, [%1, r1]"
      : "=&l"(coordinate) : "l"(coordinate_source), "m"(*coordinate_source) : "r1", "cc");coordinate;}),(s16)projected_y,(s16)projected_z,
   ({register u32 stack_resource __asm__("r4")=paired_resource;
     /* The preceding Z stack argument has consumed the OUT addresses. */
     __asm__("" : "+r"(stack_resource));stack_resource;}),6);
  SetDefinitionObjectSortKey(work->paired[0],-1);
  SetDefinitionObjectSortKey(work->paired[1],1);
  work->palettes[1]=CreateParameterizedPaletteTask(gParameterizedPalette,parent,gPaletteParameters[work->kind]);
  {
   register struct SequenceEvent *publication __asm__("r1")=event;
   /* This actual late publication address dies at its halfword store. */
   __asm__("" : "+r"(publication));
   ++publication->phase;
  }
  break;
 }
 case 258: {
  register TaskNode *palette __asm__("r4");
  u32 mask;u16 value,*display;
  palette=PollDefinitionPalette(work->palettes[0]);work->palettes[0]=palette;
  if(palette!=0)break;
  __asm__("" : "+r"(palette));
  ReleaseDefinitionResource(work->model,0);work->model=palette;
  mask=ReadDisplayHighMaskWord(2);
  display=(u16 *)0x03000940;
  value=*display;value&=~mask;*display=value;
  PlaceDefinitionResource(gMainFollowModel,1,3,
   ({register s32 coordinate __asm__("r3");
    /* Original signed H6 read; only its two-instruction address island remains ASM. */
    __asm__ volatile("mov r2, #6\n\tldrsh %0, [%1, r2]"
     : "=&l"(coordinate) : "l"(work), "m"(work->x) : "r2", "cc");coordinate;}),(s16)work->y,(u32)palette);
  /* Actual branch-owned arguments feed the same call/store tail. */
  if(work->kind!=2)
   work->palettes[0]=CreateDefinitionPaletteTask(gNormalFollowPalette,parent);
  else
   work->palettes[0]=CreateDefinitionPaletteTask(gSpecialFollowPalette,parent);
  {
   register struct SequenceEvent *publication __asm__("r3")=event;
   /* This actual late publication address dies at its halfword store. */
   __asm__("" : "+r"(publication));
   ++publication->phase;
  }
  break;
 }
 case 259: {
  u32 raw,byte_value;
  register u32 ready __asm__("r4");
  raw=PollDefinitionWorkset(work->paired,2);
  byte_value=(u8)raw;
  /* Normalize the actual projected byte, then preserve that real result
   * across the unconditional positioned-resource poll. */
  __asm__("" : "+r"(byte_value));
  {
   register u32 presence __asm__("r1")=(0U-byte_value)|byte_value;
   /* The fullword NEG/OR working value dies at boolean projection. */
   __asm__("" : "+r"(presence));
   ready=presence>>31;
  }
  __asm__("" : "+r"(ready));
  work->positioned=PollPositionedDefinitionTask(work->positioned);
  if(work->positioned!=0)ready=0;
  if(ready==0)break;
  work->palettes[0]=PollDefinitionPalette(work->palettes[0]);
  if(work->palettes[0]!=0)break;
  work->palettes[1]=PollDefinitionPalette(work->palettes[1]);
  if(work->palettes[1]!=0)break;
  {
   u32 mask;u16 value,*display;
   mask=ReadDisplayHighMaskWord(3);
   display=(u16 *)0x03000940;
   value=*display;value&=~mask;*display=value;
  }
  {
   register struct SequenceEvent *publication __asm__("r4")=event;
   /* This actual late publication address dies at its halfword store. */
   __asm__("" : "+r"(publication));
   ++publication->phase;
  }
  break;
 }
 case 260:
  work->motions[0]=PollDefinitionRecordMotion(work->motions[0]);
  if(work->motions[0]!=0)break;
  work->motions[1]=PollDefinitionRecordMotion(work->motions[1]);
  if(work->motions[1]!=0)break;
 finish_sequence: {
   register u32 finished_phase __asm__("r0")=2;
   /* Both original terminal paths share the word-before-target store. */
   __asm__("" : "+r"(finished_phase));
   event->phase=finished_phase;
  }
  break;
 }
 return 0;
}
