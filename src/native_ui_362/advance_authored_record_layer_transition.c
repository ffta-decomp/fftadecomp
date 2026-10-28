typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
typedef struct TaskNode TaskNode;
struct LayerEvent {u16 phase,unknown02;u32 unknown04;void *record;u8 unknown0c[8];s16 definition_id;u8 unknown16[6];};
struct LayerWork {u16 unknown00;u8 variant,unknown03;s16 x,y;void *record;TaskNode *opening;void *positioned_out;TaskNode *positioned,*auxiliary,*layer,*stage;};
typedef char EventSize[sizeof(struct LayerEvent)==28?1:-1];
typedef char WorkSize[sizeof(struct LayerWork)==36?1:-1];
extern const u8 gOpeningDescriptor[],gFirstAuxiliary[],gSecondAuxiliary[],gStage[];
extern const void *gPositionedSequences[];
extern u16 gDisplayControl;
extern void RefreshRecordDirection(void *);
extern void CleanupDefinitionInputs(void);
extern u32 ReadRecordPhaseStatus(void *);
extern TaskNode *CreateManagedTaskChild(const void *,u8,TaskNode *);
extern TaskNode *PollManagedTaskChild(TaskNode *);
extern TaskNode *StartRecordLayerTask(void *,u32,u32,u32,void *,void *,TaskNode *);
extern TaskNode *PollRecordLayer(TaskNode *);
extern u32 ExtractFirstControlBits(u32);
extern u32 ExtractSecondControlBits(u32);
extern void SetDisplayGroupA(u32,u8);
extern u32 ReadDisplayMaskWord(u8);
extern void ProjectRecordPosition(const void *,s16 *,s16 *);
extern void ComputeRecordCenter(void *,s32,s32,s16 *,s16 *);
extern void SetDisplayGroupB(s32,u8);
extern void SetDisplayGroupC(s32,u8);
extern TaskNode *CreateAuxiliaryTask(const void *,TaskNode *);
extern TaskNode *CreatePositionedTask(s32,s32,s32,u8,u32,void *,const void *,TaskNode *);
extern TaskNode *CreateSequenceStage(const void *,u8,u16,u16,TaskNode *);
extern TaskNode *PollAuxiliary(TaskNode *);
extern void SetRecordFlag(void *,u8);
extern TaskNode *PollPositioned(TaskNode *);
__asm__(
 ".global gOpeningDescriptor\n.set gOpeningDescriptor,0x83960a8\n"
 ".global gFirstAuxiliary\n.set gFirstAuxiliary,0x83960f8\n"
 ".global gSecondAuxiliary\n.set gSecondAuxiliary,0x8396102\n"
 ".global gPositionedSequences\n.set gPositionedSequences,0x83960f0\n"
 ".global gStage\n.set gStage,0x839610c\n"
 ".global gDisplayControl\n.set gDisplayControl,0x3000940\n"
 ".global RefreshRecordDirection\n.thumb_set RefreshRecordDirection,0x80de269\n"
 ".global CleanupDefinitionInputs\n.thumb_set CleanupDefinitionInputs,0x80d38b5\n"
 ".global ReadRecordPhaseStatus\n.thumb_set ReadRecordPhaseStatus,0x80de489\n"
 ".global CreateManagedTaskChild\n.thumb_set CreateManagedTaskChild,0x80d7a71\n"
 ".global PollManagedTaskChild\n.thumb_set PollManagedTaskChild,0x80d7abd\n"
 ".global StartRecordLayerTask\n.thumb_set StartRecordLayerTask,0x80dc1e9\n"
 ".global PollRecordLayer\n.thumb_set PollRecordLayer,0x80dba5d\n"
 ".global ExtractFirstControlBits\n.thumb_set ExtractFirstControlBits,0x8003a75\n"
 ".global ExtractSecondControlBits\n.thumb_set ExtractSecondControlBits,0x8003a81\n"
 ".global SetDisplayGroupA\n.thumb_set SetDisplayGroupA,0x80034b9\n"
 ".global ReadDisplayMaskWord\n.thumb_set ReadDisplayMaskWord,0x80035a9\n"
 ".global ProjectRecordPosition\n.thumb_set ProjectRecordPosition,0x80dbdc9\n"
 ".global ComputeRecordCenter\n.thumb_set ComputeRecordCenter,0x80dc225\n"
 ".global SetDisplayGroupB\n.thumb_set SetDisplayGroupB,0x8003509\n"
 ".global SetDisplayGroupC\n.thumb_set SetDisplayGroupC,0x8003559\n"
 ".global CreateAuxiliaryTask\n.thumb_set CreateAuxiliaryTask,0x80d3e9d\n"
 ".global CreatePositionedTask\n.thumb_set CreatePositionedTask,0x80d6099\n"
 ".global CreateSequenceStage\n.thumb_set CreateSequenceStage,0x80dfd8d\n"
 ".global PollAuxiliary\n.thumb_set PollAuxiliary,0x80d3f09\n"
 ".global SetRecordFlag\n.thumb_set SetRecordFlag,0x80dbeb5\n"
 ".global PollPositioned\n.thumb_set PollPositioned,0x80d6135\n");
s32 AdvanceAuthoredRecordLayerTransition(TaskNode *,struct LayerEvent *,struct LayerWork *) __asm__("OriginalActionCallback_000E3388");
s32 AdvanceAuthoredRecordLayerTransition(TaskNode *parent,struct LayerEvent *event,struct LayerWork *work)
{
 s16 center_x,center_y;
 u16 phase=event->phase;
 switch(phase) {
 case 0:
  work->variant=(u8)phase;
  if(event->definition_id==357)work->variant=1;
  work->record=event->record;
  RefreshRecordDirection(work->record);break;
 case 1:CleanupDefinitionInputs();break;
 case 256:
  if((u8)ReadRecordPhaseStatus(work->record)==0)break;
  work->opening=CreateManagedTaskChild(gOpeningDescriptor,2,parent);
  ++event->phase;break;
 case 257:
  work->opening=PollManagedTaskChild(work->opening);if(work->opening!=0)break;
  work->layer=StartRecordLayerTask(work->record,0,0,6,(void *)0x0600f9e0,(void *)0x06005000,parent);
  ++event->phase;break;
 case 258: {
  u32 control;
  work->layer=PollRecordLayer(work->layer);if(work->layer!=0)break;
  control=ExtractFirstControlBits(0x06005000);
  control|=ExtractSecondControlBits(0x06008000);
  SetDisplayGroupA((u16)control,3);
  { u32 mask=ReadDisplayMaskWord(3);u16 value=gDisplayControl;value|=mask;gDisplayControl=value; }
  ProjectRecordPosition(work->record,&work->x,&work->y);
  ComputeRecordCenter(work->record,work->x,work->y,&center_x,&center_y);
  SetDisplayGroupB(center_x,3);
  SetDisplayGroupC(center_y,3);
  work->auxiliary=CreateAuxiliaryTask(gFirstAuxiliary,parent);
  if(work->variant==1)
   work->positioned=CreatePositionedTask(work->x,work->y,0,1,1,&work->positioned_out,gPositionedSequences[work->variant],parent);
  work->stage=CreateSequenceStage(gStage,1,4,0,parent);
  ++event->phase;break;
 }
 case 259:
  work->auxiliary=PollAuxiliary(work->auxiliary);if(work->auxiliary!=0)break;
  if(work->variant==0)SetRecordFlag(work->record,0);
  else SetRecordFlag(work->record,1);
  work->auxiliary=CreateAuxiliaryTask(gSecondAuxiliary,parent);
  if(work->variant==0)
   work->positioned=CreatePositionedTask(work->x,work->y,0,1,1,&work->positioned_out,gPositionedSequences[work->variant],parent);
  ++event->phase;break;
 case 260:
  work->positioned=PollPositioned(work->positioned);if(work->positioned!=0)break;
  work->auxiliary=PollAuxiliary(work->auxiliary);if(work->auxiliary!=0)break;
  { u32 mask=ReadDisplayMaskWord(3);gDisplayControl&=~mask; }
  event->phase=2;break;
 }
 return 0;
}
