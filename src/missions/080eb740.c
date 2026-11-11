typedef unsigned char u8;typedef unsigned short u16;typedef signed int s32;typedef unsigned int u32;typedef struct TaskNode TaskNode;
struct SequenceEvent {u16 phase,unknown02;void *owner;u8 unknown08[12];u16 definition,variant;u8 unknown18[4];};
struct CoordinateCurve {union {u32 word;u16 halves[2];} initial;u8 unknown04[40];};
struct SequenceWork {u16 timer;u8 variant,unknown03;TaskNode *child,*auxiliary,*palettes[3],*control;struct CoordinateCurve first_curve,second_curve;void *owner;TaskNode *opening,*followup,*stage,*fade;};
extern TaskNode * CreateDefinitionEffectTask(void *,const void *,u8,u32,const void *,TaskNode *);
extern void FinishDefinitionSequence(void);
extern TaskNode * PollDefinitionEffectTask(TaskNode *);
extern TaskNode * CreateDefinitionFadeTask(u8,u16,TaskNode *);
extern TaskNode * PollDefinitionFadeTask(TaskNode *);
extern void PlaceDefinitionResource(const void *,u32,u32,s32,s32,u32);
extern TaskNode * CreateDefinitionAuxiliaryTask(const void *,TaskNode *);
extern void CreateDefinitionPaletteSet(const void *,TaskNode **,u16,TaskNode *);
extern void SetDefinitionPaletteMode(TaskNode *,u8);
extern void RemoveDefinitionPaletteSet(TaskNode **,u16);
extern TaskNode * CreateDefinitionObjectTask(u8,u8,u8,TaskNode *);
extern u32 ReadDefinitionObjectDataWord(TaskNode *);
extern void UpdateDefinitionObjectShape(TaskNode *,u32,u32,u32,u16);
extern void CommitDefinitionObjectUpdate(TaskNode *);
extern void InitializeCoordinateCurve(struct CoordinateCurve *,s32,s32,s32,s32);
extern void AdvanceCoordinateCurve(struct CoordinateCurve *);
extern u32 IsCoordinateCurveComplete(const struct CoordinateCurve *);
extern u32 ReadDisplayLowMaskByte(u8);
extern u32 IsTaskStateTwo(const TaskNode *);
extern TaskNode * CreateDefinitionTask(const void *,u16,const void *,TaskNode *);
extern TaskNode * CreateDefinitionStageTask(const void *,u8,u16,u8,TaskNode *);
extern void ClearRelatedRecordFlags(void *);
extern TaskNode * PollDefinitionAuxiliary(TaskNode *);
extern void BeginDefinitionControlRelease(TaskNode *);
extern u32 ReadDisplayHighMaskWord(u8);
extern void RemoveCurrentGroupTask(TaskNode *);
extern void RemoveDefinitionControlTask(TaskNode *);
extern u32 CountDefinitionTargets(void *,u16);
extern TaskNode * CreateActionEffectChild(void *,u8,TaskNode *);
extern TaskNode * PollAndReleaseActionEffectChild(TaskNode *);
extern const u8 gOpeningSequence[],gResource[],gPaletteSet[],gStageSequence[],gChildEntry[],gAuxiliarySequence[];
__asm__(
 ".global CreateDefinitionEffectTask\n.thumb_set CreateDefinitionEffectTask,0x80e03f9\n"
 ".global FinishDefinitionSequence\n.thumb_set FinishDefinitionSequence,0x80d38b5\n"
 ".global PollDefinitionEffectTask\n.thumb_set PollDefinitionEffectTask,0x80e05dd\n"
 ".global CreateDefinitionFadeTask\n.thumb_set CreateDefinitionFadeTask,0x80dfd69\n"
 ".global PollDefinitionFadeTask\n.thumb_set PollDefinitionFadeTask,0x80dfed9\n"
 ".global PlaceDefinitionResource\n.thumb_set PlaceDefinitionResource,0x80d7221\n"
 ".global CreateDefinitionAuxiliaryTask\n.thumb_set CreateDefinitionAuxiliaryTask,0x80d3e9d\n"
 ".global CreateDefinitionPaletteSet\n.thumb_set CreateDefinitionPaletteSet,0x80d4871\n"
 ".global SetDefinitionPaletteMode\n.thumb_set SetDefinitionPaletteMode,0x80d47a1\n"
 ".global RemoveDefinitionPaletteSet\n.thumb_set RemoveDefinitionPaletteSet,0x80d4939\n"
 ".global CreateDefinitionObjectTask\n.thumb_set CreateDefinitionObjectTask,0x80dab85\n"
 ".global ReadDefinitionObjectDataWord\n.thumb_set ReadDefinitionObjectDataWord,0x80dabb5\n"
 ".global UpdateDefinitionObjectShape\n.thumb_set UpdateDefinitionObjectShape,0x80dac81\n"
 ".global CommitDefinitionObjectUpdate\n.thumb_set CommitDefinitionObjectUpdate,0x80d9b99\n"
 ".global InitializeCoordinateCurve\n.thumb_set InitializeCoordinateCurve,0x80075cd\n"
 ".global AdvanceCoordinateCurve\n.thumb_set AdvanceCoordinateCurve,0x80076a1\n"
 ".global IsCoordinateCurveComplete\n.thumb_set IsCoordinateCurveComplete,0x8007881\n"
 ".global ReadDisplayLowMaskByte\n.thumb_set ReadDisplayLowMaskByte,0x80035d1\n"
 ".global IsTaskStateTwo\n.thumb_set IsTaskStateTwo,0x8005bb1\n"
 ".global CreateDefinitionTask\n.thumb_set CreateDefinitionTask,0x8005b6d\n"
 ".global CreateDefinitionStageTask\n.thumb_set CreateDefinitionStageTask,0x80dfd8d\n"
 ".global ClearRelatedRecordFlags\n.thumb_set ClearRelatedRecordFlags,0x80edb81\n"
 ".global PollDefinitionAuxiliary\n.thumb_set PollDefinitionAuxiliary,0x80d3f09\n"
 ".global BeginDefinitionControlRelease\n.thumb_set BeginDefinitionControlRelease,0x80d9b39\n"
 ".global ReadDisplayHighMaskWord\n.thumb_set ReadDisplayHighMaskWord,0x80035a9\n"
 ".global RemoveCurrentGroupTask\n.thumb_set RemoveCurrentGroupTask,0x8005b59\n"
 ".global RemoveDefinitionControlTask\n.thumb_set RemoveDefinitionControlTask,0x80d9b59\n"
 ".global CountDefinitionTargets\n.thumb_set CountDefinitionTargets,0x80d8859\n"
 ".global CreateActionEffectChild\n.thumb_set CreateActionEffectChild,0x80edb99\n"
 ".global PollAndReleaseActionEffectChild\n.thumb_set PollAndReleaseActionEffectChild,0x80edbdd\n"
 ".global gOpeningSequence\n.set gOpeningSequence,0x8398ea0\n"
 ".global gResource\n.set gResource,0x88f4ea8\n"
 ".global gPaletteSet\n.set gPaletteSet,0x8398f0c\n"
 ".global gStageSequence\n.set gStageSequence,0x8398fc4\n"
 ".global gChildEntry\n.set gChildEntry,0x80eb515\n"
 ".global gAuxiliarySequence\n.set gAuxiliarySequence,0x894d720\n"
);
typedef char WorkSize[sizeof(struct SequenceWork)==136?1:-1];
typedef char CurveSize[sizeof(struct CoordinateCurve)==44?1:-1];
s32 AdvanceAuthoredCurvedOwnerFlagSequence(TaskNode *,struct SequenceEvent *,struct SequenceWork *) __asm__("OriginalActionCallback_000EB740");
s32 AdvanceAuthoredCurvedOwnerFlagSequence(TaskNode *input_parent,struct SequenceEvent *input_event,struct SequenceWork *input_work)
{
 register TaskNode *parent __asm__("r8")=input_parent;
 struct SequenceEvent *event=input_event;
 struct SequenceWork *work=input_work;
 register s32 phase __asm__("r1");
 u8 child_event[28];
 __asm__("" : "+r"(parent), "+r"(event), "+r"(work));
 phase=event->phase;__asm__("" : "+r"(phase));
 switch(phase){
 case 0:{
  u16 captured_variant=event->variant;
  void *owner;
  register u32 variant __asm__("r0");
  work->variant=captured_variant;owner=event->owner;work->owner=owner;
  variant=(u8)captured_variant;__asm__("" : "+r"(variant));
  if(variant!=0)break;
  work->opening=CreateDefinitionEffectTask(owner,gOpeningSequence,5,4,(const void *)variant,parent);break;
 }
 case 1:FinishDefinitionSequence();break;
 case 256:
  if(work->variant!=0){
   work->opening=PollDefinitionEffectTask(work->opening);if(work->opening!=0)break;
   event->phase=262;
  }else{work->fade=CreateDefinitionFadeTask(1,30,parent);++event->phase;}
  break;
 case 257:{
  register TaskNode **objects __asm__("r4");
  register TaskNode *cleared __asm__("r1");
  register struct CoordinateCurve *first __asm__("r9");
  register struct CoordinateCurve *second __asm__("r10");
  register u32 second_definition __asm__("r2");
  TaskNode **stage_cell;
  TaskNode *control;
  register const void *palette_source __asm__("r0");
  u8 index;
  u32 duration;
  volatile u8 *shadow;
  register u32 mask __asm__("r4");
  register u32 zero __asm__("r5");
  register u32 previous __asm__("r1");
  register u32 high_mask __asm__("r2");
  register u32 combined __asm__("r0");
  register TaskNode *shape_control __asm__("r0");
  register u32 first_value __asm__("r3");
  register u32 second_word __asm__("r1");
  work->opening=PollDefinitionEffectTask(work->opening);if(work->opening!=0)break;
  objects=&work->fade;__asm__("" : "+r"(objects));
  cleared=PollDefinitionFadeTask(*objects);__asm__("" : "+r"(cleared));
  *objects=cleared;if(cleared!=0)break;
  PlaceDefinitionResource(gResource,0,2,0,(s32)cleared,(u32)cleared);
  /* Capture the real first call argument before evolving the fade-cell address. */
  palette_source=gPaletteSet;__asm__("" : "+r"(palette_source));
  /* Native evolves the already captured fade-cell address into the palette base. */
  objects=(TaskNode **)((u8 *)objects-120);__asm__("" : "+r"(objects));
  CreateDefinitionPaletteSet(palette_source,objects,3,parent);
  index=0;
  first=&work->first_curve;__asm__("" : "+r"(first));
  second_definition=72;__asm__("" : "+r"(second_definition));
  second_definition+=(u32)work;__asm__("" : "+r"(second_definition));
  second=(struct CoordinateCurve *)second_definition;__asm__("" : "+r"(second));
  stage_cell=&work->stage;__asm__("" : "+r"(stage_cell));
  do{
   register u32 palette_address __asm__("r0")=(u32)index*4;
   /* One native three-register address addition; memory access stays in C. */
   __asm__("add %0, %1, %0" : "+l"(palette_address) : "l"(objects) : "cc");
   SetDefinitionPaletteMode(*(TaskNode **)palette_address,1);
   index=(u8)(index+1);
  }while(index<=2);
  control=CreateDefinitionObjectTask(0,0,0,parent);work->control=control;
  ReadDefinitionObjectDataWord(control);
  duration=89;__asm__("" : "+r"(duration));
  InitializeCoordinateCurve(first,0,0,120,duration);
  InitializeCoordinateCurve(second,0,0,80,duration);
  shape_control=work->control;first_value=work->first_curve.initial.halves[0];second_word=work->second_curve.initial.word;
  __asm__("" : "+r"(shape_control), "+r"(first_value), "+r"(second_word));
  UpdateDefinitionObjectShape(shape_control,120,80,first_value,(u16)second_word);
  /* Exact observed shadow reads and ordered byte writes; no blanket volatile work state. */
  shadow=(volatile u8 *)0x03000940;__asm__("" : "+r"(shadow));
  (void)shadow[66];zero=0;__asm__("" : "+r"(zero));
  mask=63;__asm__("" : "+r"(mask));shadow[66]=63;
  mask&=~ReadDisplayLowMaskByte(2);(void)shadow[68];shadow[68]=mask;
  (void)shadow[59];shadow[59]=zero;(void)shadow[58];shadow[58]=zero;
  (void)shadow[63];shadow[63]=zero;(void)shadow[62];shadow[62]=255;
  previous=*(volatile u16 *)shadow;__asm__("" : "+r"(previous));
  high_mask=0x2000;__asm__("" : "+r"(high_mask));
  combined=high_mask;__asm__("" : "+r"(combined));*(volatile u16 *)shadow=combined|previous;
  {
   TaskNode *created_stage=CreateDefinitionStageTask(gStageSequence,1,4,0,parent);
   register TaskNode **stage_write __asm__("r2")=stage_cell;
   __asm__("" : "+r"(stage_write));
   *stage_write=created_stage;
  }
  ++event->phase;break;
 }
 case 258:{
  struct CoordinateCurve *first=&work->first_curve;
  register struct CoordinateCurve *second __asm__("r5");
  register TaskNode *shape_control __asm__("r0");
  register u32 first_value __asm__("r3");
  register u32 second_word __asm__("r1");
  AdvanceCoordinateCurve(first);
  second=&work->second_curve;__asm__("" : "+r"(second));
  AdvanceCoordinateCurve(second);
  shape_control=work->control;first_value=work->first_curve.initial.halves[0];second_word=work->second_curve.initial.word;
  __asm__("" : "+r"(shape_control), "+r"(first_value), "+r"(second_word));
  UpdateDefinitionObjectShape(shape_control,120,80,first_value,(u16)second_word);
  CommitDefinitionObjectUpdate(work->control);
  if(IsCoordinateCurveComplete(first)==0)break;
  if(IsCoordinateCurveComplete(second)==0)break;
  work->child=CreateDefinitionTask(gChildEntry,1228,child_event,parent);
  work->timer=250;++event->phase;break;
 }
 case 259:
  if(--work->timer!=0)break;
  work->auxiliary=CreateDefinitionAuxiliaryTask(gAuxiliarySequence,parent);
  work->timer=30;++event->phase;break;
 case 260:{
  register u32 working __asm__("r0");
  register u32 remaining __asm__("r4");
  register u32 previous __asm__("r1");
  u32 mask;u16 *shadow;
  TaskNode *child;
  working=work->timer-1;__asm__("" : "+r"(working));
  work->timer=working;remaining=(u16)working;__asm__("" : "+r"(remaining));
  if(remaining!=0)break;
  child=work->child;
  if(child!=0&&IsTaskStateTwo(child)!=0){RemoveCurrentGroupTask(work->child);work->child=(TaskNode *)remaining;}
  RemoveDefinitionPaletteSet(work->palettes,3);
  BeginDefinitionControlRelease(work->control);
  mask=ReadDisplayHighMaskWord(2);shadow=(u16 *)0x03000940;
  previous=*shadow;__asm__("" : "+r"(previous));previous&=~mask;previous&=0xdfff;*shadow=previous;
  work->fade=CreateDefinitionFadeTask(0,30,parent);
  ClearRelatedRecordFlags(work->owner);++event->phase;break;
 }
 case 261:
  work->auxiliary=PollDefinitionAuxiliary(work->auxiliary);if(work->auxiliary!=0)break;
  work->fade=PollDefinitionFadeTask(work->fade);if(work->fade!=0)break;
  RemoveDefinitionControlTask(work->control);
  if((u8)CountDefinitionTargets(work->owner,0)==0)event->phase=2;else ++event->phase;
  break;
 case 262:
  work->followup=CreateActionEffectChild(work->owner,4,parent);++event->phase;break;
 case 263:
  work->followup=PollAndReleaseActionEffectChild(work->followup);if(work->followup==0)event->phase=2;
  break;
 }
 return 0;
}
