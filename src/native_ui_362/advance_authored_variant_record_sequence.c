typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
typedef struct TaskNode TaskNode;
struct VariantEvent {u16 phase,unknown02;u32 unknown04;void *record;u8 unknown0c[8];u16 definition_id;u8 unknown16[6];};
struct VariantWork {u16 unknown00;u8 variant,completion;s16 x,y;void *record;TaskNode *opening;void *positioned_out;u32 unknown14;TaskNode *positioned;void *resource;TaskNode *auxiliary,*palette,*motion;u32 unknown2c;TaskNode *stage;};
typedef char EventSize[sizeof(struct VariantEvent)==28?1:-1];
typedef char WorkSize[sizeof(struct VariantWork)==52?1:-1];
extern const u8 gFirstGroups[],gSecondGroups[],gOpeningDescriptor[],gBgPalette[],gObjPalette[],gResource[],gAuxiliarySequence[],gFinalStage[];
extern const void *gPaletteSequences[],*gPositionedSequences[];
extern u16 gDisplayControl;
extern void *CopyBytes(void *,const void *,u32);
extern void CleanupDefinitionInputs(void);
extern TaskNode *CreateManagedTaskChild(const void *,u8,TaskNode *);
extern TaskNode *PollManagedTaskChild(TaskNode *);
extern void CopyPaletteGroups(const void *,u32,u32,u32,u32);
extern void ApplyRecordValue(void *,u16);
extern TaskNode *CreateRecordMotion(void *,u8 *,u8,s32,u32,u32,u32,TaskNode *);
extern void ProjectRecordPosition(const void *,s16 *,s16 *);
extern void ConfigureResourceCoordinates(u8,u8,u16,s16,s16);
extern void *CreateDefinitionResource(u8,const void *,u16,u8);
extern u32 ReadDisplayMaskWord(u8);
extern TaskNode *CreateAuxiliaryTask(const void *,TaskNode *);
extern TaskNode *CreatePaletteTask(const void *,TaskNode *);
extern TaskNode *CreatePositionedTask(s32,s32,s32,u8,u32,void *,const void *,TaskNode *);
extern TaskNode *CreateSequenceStage(const void *,u8,u16,u16,TaskNode *);
extern void *PollResource(void *,u8);
extern TaskNode *PollAuxiliary(TaskNode *);
extern TaskNode *PollPalette(TaskNode *);
extern TaskNode *PollPositioned(TaskNode *);
extern TaskNode *PollRecordMotion(TaskNode *);
__asm__(
 ".global gFirstGroups\n.set gFirstGroups,0x8149c84\n"
 ".global gSecondGroups\n.set gSecondGroups,0x8149c86\n"
 ".global gOpeningDescriptor\n.set gOpeningDescriptor,0x8395ff4\n"
 ".global gBgPalette\n.set gBgPalette,0x88eb650\n"
 ".global gObjPalette\n.set gObjPalette,0x88ea7f0\n"
 ".global gResource\n.set gResource,0x88f1870\n"
 ".global gAuxiliarySequence\n.set gAuxiliarySequence,0x894d690\n"
 ".global gPaletteSequences\n.set gPaletteSequences,0x8396080\n"
 ".global gPositionedSequences\n.set gPositionedSequences,0x8396078\n"
 ".global gFinalStage\n.set gFinalStage,0x8396088\n"
 ".global gDisplayControl\n.set gDisplayControl,0x3000940\n"
 ".global CopyBytes\n.thumb_set CopyBytes,0x81443fd\n"
 ".global CleanupDefinitionInputs\n.thumb_set CleanupDefinitionInputs,0x80d38b5\n"
 ".global CreateManagedTaskChild\n.thumb_set CreateManagedTaskChild,0x80d7a71\n"
 ".global PollManagedTaskChild\n.thumb_set PollManagedTaskChild,0x80d7abd\n"
 ".global CopyPaletteGroups\n.thumb_set CopyPaletteGroups,0x80d45d1\n"
 ".global ApplyRecordValue\n.thumb_set ApplyRecordValue,0x80de10d\n"
 ".global CreateRecordMotion\n.thumb_set CreateRecordMotion,0x80de4b1\n"
 ".global ProjectRecordPosition\n.thumb_set ProjectRecordPosition,0x80dbdc9\n"
 ".global ConfigureResourceCoordinates\n.thumb_set ConfigureResourceCoordinates,0x80d49fd\n"
 ".global CreateDefinitionResource\n.thumb_set CreateDefinitionResource,0x80d4b65\n"
 ".global ReadDisplayMaskWord\n.thumb_set ReadDisplayMaskWord,0x80035a9\n"
 ".global CreateAuxiliaryTask\n.thumb_set CreateAuxiliaryTask,0x80d3e9d\n"
 ".global CreatePaletteTask\n.thumb_set CreatePaletteTask,0x80d4705\n"
 ".global CreatePositionedTask\n.thumb_set CreatePositionedTask,0x80d6099\n"
 ".global CreateSequenceStage\n.thumb_set CreateSequenceStage,0x80dfd8d\n"
 ".global PollResource\n.thumb_set PollResource,0x80d4d2d\n"
 ".global PollAuxiliary\n.thumb_set PollAuxiliary,0x80d3f09\n"
 ".global PollPalette\n.thumb_set PollPalette,0x80d4775\n"
 ".global PollPositioned\n.thumb_set PollPositioned,0x80d6135\n"
 ".global PollRecordMotion\n.thumb_set PollRecordMotion,0x80dba5d\n");
s32 AdvanceAuthoredVariantRecordSequence(TaskNode *,struct VariantEvent *,struct VariantWork *) __asm__("OriginalActionCallback_000E317C");
s32 AdvanceAuthoredVariantRecordSequence(TaskNode *parent,struct VariantEvent *event,struct VariantWork *work)
{
 u8 first_groups[2],second_groups[2];
 switch(event->phase) {
 case 0:
  work->variant=(u8)((u8)event->definition_id-98);
  work->record=event->record;break;
 case 1:CleanupDefinitionInputs();break;
 case 256:
  CopyBytes(first_groups,gFirstGroups,2);
  CopyBytes(second_groups,gSecondGroups,2);
  work->opening=CreateManagedTaskChild(gOpeningDescriptor,3,parent);
  CopyPaletteGroups(gBgPalette,6,0,first_groups[work->variant],1);
  CopyPaletteGroups(gObjPalette,6,1,second_groups[work->variant],1);
  ++event->phase;break;
 case 257: {
  TaskNode *remaining=PollManagedTaskChild(work->opening);work->opening=remaining;
  if(remaining!=0)break;
  ApplyRecordValue(work->record,60);
  work->motion=CreateRecordMotion(work->record,&work->completion,1,-1,(u32)remaining,58,(u32)remaining,parent);
  ++event->phase;break;
 }
 case 258:
  if(work->completion==0)break;
  ProjectRecordPosition(work->record,&work->x,&work->y);
  ConfigureResourceCoordinates(0,2,0,work->x,(s16)(work->y-32));
  work->resource=CreateDefinitionResource(0,gResource,975,6);
  { u32 mask=ReadDisplayMaskWord(2); u16 value=gDisplayControl; value|=mask; gDisplayControl=value; }
  work->auxiliary=CreateAuxiliaryTask(gAuxiliarySequence,parent);
  work->palette=CreatePaletteTask(gPaletteSequences[work->variant],parent);
  work->positioned=CreatePositionedTask(work->x,(s16)(work->y-32),0,1,2,&work->positioned_out,gPositionedSequences[work->variant],parent);
  work->stage=CreateSequenceStage(gFinalStage,1,4,30,parent);
  ++event->phase;break;
 case 259:
  work->resource=PollResource(work->resource,0);if(work->resource!=0)break;
  work->auxiliary=PollAuxiliary(work->auxiliary);if(work->auxiliary!=0)break;
  { u32 mask=ReadDisplayMaskWord(2); gDisplayControl&=~mask; }
  work->palette=PollPalette(work->palette);if(work->palette!=0)break;
  work->positioned=PollPositioned(work->positioned);if(work->positioned!=0)break;
  work->motion=PollRecordMotion(work->motion);if(work->motion!=0)break;
  event->phase=2;break;
 }
 return 0;
}
