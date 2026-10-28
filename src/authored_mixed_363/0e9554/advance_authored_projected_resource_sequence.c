typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
typedef struct TaskNode TaskNode;
struct SequenceEvent {u16 phase,unknown02;void *record;u8 unknown08[12];s16 definition;u16 variant;u8 unknown18[4];};
struct SequenceWork {
 u8 mode,direct_record;u16 unknown02;
 s16 x,y;void *record;u8 output[4];
 TaskNode *motion;void *resource;TaskNode *palette0,*palette1,*auxiliary;
 void *owner_record;TaskNode *opening;
 u16 saved_palette0[16],saved_palette1[16];void *backup;
};
typedef char WorkSize[sizeof(struct SequenceWork)==112?1:-1];
extern void BiosCpuSet(const void *,void *,u32);
extern void CopyCountedPaletteGroupsToShadow(const void *,u32,u32,u32,u32);
extern void *AllocateSceneResource(u32);
extern void ReleaseSceneResource(void *);
extern void *NextManagedTransferRequest(void);
extern void QueueDmaCopy16(void *,u32,u32,u16);
extern void FinishDefinitionSequence(void);
extern u8 ReadDefinitionReadiness(void);
extern void *GetDefinitionTargetRecord(void *,u8);
/* The fifth word is physically signed full-width; the helper consumes LOW16. */
extern void *ProjectActorAndApplyValue(void *,u16 *,u16 *,u16 *,s32);
extern void ProjectDefinitionRecordPosition(const void *,s16 *,s16 *);
/* X is physically a full sign-extended caller word; the callee consumes LOW16. */
extern void ConfigureDefinitionCoordinates(u8,u8,u16,s32,s16);
extern void SetRecordSlotEnabled(u8,u8);
extern void *CreateDefinitionResource(u8,const void *,u16,u8);
extern void SetDefinitionResourceEnabled(void *,u8);
extern u32 ReadDisplayHighMaskWord(u8);
/* The second caller word is signed full-width; the callee stores LOW16. */
extern TaskNode *CreatePositionedDefinitionTask(s32,s32,s32,u8,u32,void *,const void *,TaskNode *);
extern TaskNode *CreateDefinitionPaletteTask(const void *,TaskNode *);
extern void ConfigureDefinitionPalette(TaskNode *,u8);
extern TaskNode *CreateDefinitionAuxiliaryTask(const void *,TaskNode *);
extern TaskNode *CreateDefinitionStageTask(const void *,u8,u16,u8,TaskNode *);
extern TaskNode *PollDefinitionAuxiliary(TaskNode *);
extern TaskNode *PollDefinitionPalette(TaskNode *);
extern TaskNode *PollProjectedEffect(TaskNode *);
extern void ReleaseDefinitionResource(void *,u8);
extern u32 QueryRecordBoundary(void *);
extern const u8 gPaletteGroups[],gResourceRecord[],gPositionSequence[],gPaletteSequence0[],gPaletteSequence1[],gAuxiliarySequence[],gOpeningSequence[];
__asm__(
 ".global BiosCpuSet\n.thumb_set BiosCpuSet,0x814186d\n"
 ".global CopyCountedPaletteGroupsToShadow\n.thumb_set CopyCountedPaletteGroupsToShadow,0x80d45d1\n"
 ".global AllocateSceneResource\n.thumb_set AllocateSceneResource,0x800a655\n"
 ".global ReleaseSceneResource\n.thumb_set ReleaseSceneResource,0x800a669\n"
 ".global NextManagedTransferRequest\n.thumb_set NextManagedTransferRequest,0x80d3af9\n"
 ".global QueueDmaCopy16\n.thumb_set QueueDmaCopy16,0x8000a99\n"
 ".global FinishDefinitionSequence\n.thumb_set FinishDefinitionSequence,0x80d38b5\n"
 ".global ReadDefinitionReadiness\n.thumb_set ReadDefinitionReadiness,0x801bdb1\n"
 ".global GetDefinitionTargetRecord\n.thumb_set GetDefinitionTargetRecord,0x80dd4a5\n"
 ".global ProjectActorAndApplyValue\n.thumb_set ProjectActorAndApplyValue,0x80dd761\n"
 ".global ProjectDefinitionRecordPosition\n.thumb_set ProjectDefinitionRecordPosition,0x80dbdc9\n"
 ".global ConfigureDefinitionCoordinates\n.thumb_set ConfigureDefinitionCoordinates,0x80d49fd\n"
 ".global SetRecordSlotEnabled\n.thumb_set SetRecordSlotEnabled,0x800bc4d\n"
 ".global CreateDefinitionResource\n.thumb_set CreateDefinitionResource,0x80d4b65\n"
 ".global SetDefinitionResourceEnabled\n.thumb_set SetDefinitionResourceEnabled,0x800bda5\n"
 ".global ReadDisplayHighMaskWord\n.thumb_set ReadDisplayHighMaskWord,0x80035a9\n"
 ".global CreatePositionedDefinitionTask\n.thumb_set CreatePositionedDefinitionTask,0x80d6099\n"
 ".global CreateDefinitionPaletteTask\n.thumb_set CreateDefinitionPaletteTask,0x80d4705\n"
 ".global ConfigureDefinitionPalette\n.thumb_set ConfigureDefinitionPalette,0x80d47dd\n"
 ".global CreateDefinitionAuxiliaryTask\n.thumb_set CreateDefinitionAuxiliaryTask,0x80d3e9d\n"
 ".global CreateDefinitionStageTask\n.thumb_set CreateDefinitionStageTask,0x80dfd8d\n"
 ".global PollDefinitionAuxiliary\n.thumb_set PollDefinitionAuxiliary,0x80d3f09\n"
 ".global PollDefinitionPalette\n.thumb_set PollDefinitionPalette,0x80d4775\n"
 ".global PollProjectedEffect\n.thumb_set PollProjectedEffect,0x80d6135\n"
 ".global ReleaseDefinitionResource\n.thumb_set ReleaseDefinitionResource,0x80d4d15\n"
 ".global QueryRecordBoundary\n.thumb_set QueryRecordBoundary,0x80d8cd5\n"
 ".global gPaletteGroups\n.set gPaletteGroups,0x88ea1f4\n"
 ".global gResourceRecord\n.set gResourceRecord,0x88ed5bc\n"
 ".global gPositionSequence\n.set gPositionSequence,0x83985a8\n"
 ".global gPaletteSequence0\n.set gPaletteSequence0,0x8949374\n"
 ".global gPaletteSequence1\n.set gPaletteSequence1,0x8949f18\n"
 ".global gAuxiliarySequence\n.set gAuxiliarySequence,0x894d69c\n"
 ".global gOpeningSequence\n.set gOpeningSequence,0x83985c0\n"
);
s32 AdvanceAuthoredProjectedResourceSequence(TaskNode *,struct SequenceEvent *,struct SequenceWork *) __asm__("OriginalActionCallback_000E9554");
s32 AdvanceAuthoredProjectedResourceSequence(TaskNode *input_parent,struct SequenceEvent *input_event,struct SequenceWork *input_work)
{
 TaskNode *parent=input_parent;
 struct SequenceEvent *event=input_event;
 struct SequenceWork *work=input_work;
 register s32 phase __asm__("r1");
 u16 zero;
 __asm__("" : "+r"(parent), "+r"(event), "+r"(work));
 phase=event->phase;
 __asm__("" : "+r"(phase));
 switch(phase) {
 case 0: {
  s32 definition;
  u16 *palette;
  register u16 *fill_source __asm__("r1");
  register u16 *second_bank __asm__("r0");
  register u32 bank_displacement __asm__("r1");
  work->mode=phase;work->direct_record=phase;
  definition=event->definition;
  if(definition==97)work->mode=1;
  else if(definition==396){work->mode=2;work->direct_record=1;}
  if(work->direct_record==0)work->owner_record=event->record;
  else work->record=event->record;
  /* The original base begins only after record selection has stored. */
  palette=(u16 *)0x03003980;
  BiosCpuSet(palette,work->saved_palette0,16);
  /* Bounded native address stage: byte displacement512, then base+offset.
   * Both outputs are defined by actual instructions; no memory is touched. */
  __asm__("mov %1,#128\n\tlsl %1,%1,#2\n\tadd %0,%2,%1"
          : "=&r"(second_bank), "=&r"(bank_displacement)
          : "r"(palette) : "cc");
  BiosCpuSet(second_bank,work->saved_palette1,16);
  fill_source=&zero;
  /* The real source address is defined before its halfword is written,
   * then moves from R1 to the first argument without another address. */
  __asm__("" : "+r"(fill_source));
  *fill_source=0;BiosCpuSet(fill_source,palette,0x01000010);
  CopyCountedPaletteGroupsToShadow(gPaletteGroups,9,1,0,1);
  work->backup=AllocateSceneResource(2048);
  QueueDmaCopy16(NextManagedTransferRequest(),0x06005800,(u32)work->backup,1024);
  if(work->direct_record==0)QueryRecordBoundary(work->owner_record);
  break;
 }
 case 1:FinishDefinitionSequence();break;
 case 256: {
  u32 mask;u16 *shadow;
  if(ReadDefinitionReadiness()!=0)break;
  if(work->direct_record==0) {
   void *record=GetDefinitionTargetRecord(work->owner_record,0);
   /* Both original arms form their own OUT addresses and full stack word
    * before the common call; a shared value ternary loses those phases. */
   if(work->mode==0)
    work->record=ProjectActorAndApplyValue(record,(u16 *)&work->x,(u16 *)&work->y,0,-2);
   else
    work->record=ProjectActorAndApplyValue(record,(u16 *)&work->x,(u16 *)&work->y,0,-1);
  } else ProjectDefinitionRecordPosition(work->record,&work->x,&work->y);
  {
   register s32 model_x __asm__("r3");
   register u32 x_offset __asm__("r2");
   u32 raw_y;s32 model_y;
   /* One actual signed halfword read. The m operand declares exactly H4. */
   __asm__("mov %1,#4\n\tldrsh %0,[%2,%1]"
           : "=&r"(model_x), "=&r"(x_offset)
           : "r"(work), "m"(work->x) : "cc");
   /* Actual signed X definition precedes the independent unsigned Y read. */
   __asm__("" : "+r"(model_x));
   raw_y=(u16)work->y;model_y=(s16)(raw_y-8);
   ConfigureDefinitionCoordinates(0,2,0,model_x,model_y);
  }
  SetRecordSlotEnabled(0,1);
  work->resource=CreateDefinitionResource(0,gResourceRecord,576,9);
  SetDefinitionResourceEnabled(work->resource,1);
  mask=ReadDisplayHighMaskWord(2);shadow=(u16 *)0x03000940;
  {
   register u32 previous __asm__("r1")=*shadow;
   /* The original destructive OR retains its fresh word as destination. */
   __asm__("orr %0,%1" : "+r"(previous) : "r"(mask) : "cc");
   *shadow=previous;
  }
  {
   register s32 positioned_x __asm__("r0");
   register u32 x_offset __asm__("r1");
   /* A new alias-visible signed H4 read precedes the independent H6 read. */
   __asm__("mov %1,#4\n\tldrsh %0,[%2,%1]"
           : "=&r"(positioned_x), "=&r"(x_offset)
           : "r"(work), "m"(work->x) : "cc");
   work->motion=CreatePositionedDefinitionTask(positioned_x,work->y,0,1,1,work->output,gPositionSequence,parent);
  }
  work->palette0=CreateDefinitionPaletteTask(gPaletteSequence0,parent);
  work->palette1=CreateDefinitionPaletteTask(gPaletteSequence1,parent);
  ConfigureDefinitionPalette(work->palette0,9);
  work->auxiliary=CreateDefinitionAuxiliaryTask(gAuxiliarySequence,parent);
  if(work->direct_record==0)work->opening=CreateDefinitionStageTask(gOpeningSequence,1,4,0,parent);
  ++event->phase;
  break;
 }
 case 257: {
  u32 mask;u16 *shadow;
  register TaskNode *motion __asm__("r4");
  work->auxiliary=PollDefinitionAuxiliary(work->auxiliary);
  if(work->auxiliary!=0)break;
  work->palette0=PollDefinitionPalette(work->palette0);
  if(work->palette0!=0)break;
  work->palette1=PollDefinitionPalette(work->palette1);
  if(work->palette1!=0)break;
  mask=ReadDisplayHighMaskWord(2);shadow=(u16 *)0x03000940;*shadow&=~mask;
  motion=PollProjectedEffect(work->motion);work->motion=motion;
  if(motion!=0)break;
  /* Preserve the returned full NULL across release for its actual W20 store. */
  __asm__("" : "+r"(motion));
  ReleaseDefinitionResource(work->resource,0);work->resource=motion;
  QueueDmaCopy16(NextManagedTransferRequest(),(u32)work->backup,0x06005800,1024);
  ++event->phase;
  break;
 }
 case 258: {
  u16 *palette;
  register u16 *saved_source __asm__("r0")=work->saved_palette0;
  /* The actual first source address precedes the independent saved base. */
  __asm__("" : : "r"(saved_source));
  palette=(u16 *)0x03003980;
  BiosCpuSet(saved_source,palette,16);
  BiosCpuSet(work->saved_palette1,palette+256,16);
  ReleaseSceneResource(work->backup);work->backup=0;event->phase=2;
  break;
 }
 }
 return 0;
}
