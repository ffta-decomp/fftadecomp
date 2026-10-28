typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
typedef struct TaskNode TaskNode;
struct ChildEvent {u32 unknown00;void *input;u32 unknown08[3];u16 ordinal;u8 unknown16[6];};
typedef char ChildEventSize[sizeof(struct ChildEvent)==28?1:-1];
struct ActionCell {s8 x;u8 height;s8 y;u8 untouched;};
struct AdjacentEvent {u16 phase,unknown02;void *actor;u8 unknown08[12];s16 definition_id;u16 variant;u8 unknown18[4];};
struct AdjacentWork {u32 unknown00;u8 mode,variant,completion,unknown07,count,index,delay,unknown11;u16 counter,unknown14;struct ActionCell cells[4];u32 position_output;TaskNode *position_task,*palette,*cell_tasks[4],*actor_task;void *record,*actor;TaskNode *opening,*record_sequence,*motions[4],*stage;};
typedef char EventSize[sizeof(struct AdjacentEvent)==28?1:-1];
typedef char WorkSize[sizeof(struct AdjacentWork)==100?1:-1];
typedef char CellSize[sizeof(struct ActionCell)==4?1:-1];
extern const u8 gOpening[],gRecordPhase[],gRecordSequence[],gPositionSequence[],gOffsetMotion[],gStageFirst[],gStageMode0[],gStageMode1[],gStageMode2[],gResource[],gPalette[];
extern TaskNode *CreateDefinitionEffectTask(void *,const void *,u8,u8,const s16 *,TaskNode *);
extern void CleanupDefinitionInputs(void);
extern TaskNode *PollDefinitionEffect(TaskNode *);
extern void LoadDefinitionResource(const void *,u32,u32,u32,u32);
extern TaskNode *CreateRecordPhaseTask(void *,void **,u32,u32,u8 *,const void *,u32,u32,TaskNode *);
extern void ProjectRecordPosition(const void *,s16 *,s16 *);
extern TaskNode *CreatePositionedDefinitionTask(s32,s32,s32,u8,u32,void *,const void *,TaskNode *);
extern TaskNode *PollPositionedDefinitionTask(TaskNode *);
extern TaskNode *CreateSequenceStage(const void *,u8,u16,u16,TaskNode *);
extern void SelectRecordFlag(void *,u8);
extern void StopRecordMotion(TaskNode *);
extern TaskNode *CreateRecordSequence(void *,u8,u8 *,const void *,u16,u16,TaskNode *);
extern void ReadRecordTileCoordinates(const void *,s16 *,s16 *,s16 *);
extern u32 BuildNeighborCells(u8,u8,struct ActionCell *,u8,u8,u16);
extern void *FindRecordAtCell(s8,s8);
extern void RefreshRecordDirection(void *);
extern u32 ReadCellEligibility(struct ActionCell *);
extern TaskNode *CreateActionTask(void *,u16,const u32 *,TaskNode *);
extern TaskNode *CreatePaletteTask(const void *,TaskNode *,u16);
extern u32 PollDefinitionGroup(TaskNode **,u16);
extern TaskNode *PollActorTask(TaskNode *);
extern TaskNode *PollPalette(TaskNode *);
extern u32 ReadActorTargetCount(void *,u16);
extern void *GetTargetRecord(void *,u8);
extern TaskNode *CreateOffsetMotion(void *,const void *,s32,u32,u32,TaskNode *,u32);
extern u32 PollRecordHandles(void *);
extern TaskNode *PollRecordMotion(TaskNode *);
extern s32 CellActionCallback(TaskNode *,void *,void *);
extern s32 ActorActionCallback(TaskNode *,void *,void *);
__asm__(
 ".global gOpening\n.set gOpening,0x0839b1f0\n"
 ".global gRecordPhase\n.set gRecordPhase,0x0839b240\n"
 ".global gRecordSequence\n.set gRecordSequence,0x0839b244\n"
 ".global gPositionSequence\n.set gPositionSequence,0x0839b214\n"
 ".global gOffsetMotion\n.set gOffsetMotion,0x0839b22c\n"
 ".global gStageFirst\n.set gStageFirst,0x0839b248\n"
 ".global gStageMode0\n.set gStageMode0,0x0839b250\n"
 ".global gStageMode1\n.set gStageMode1,0x0839b258\n"
 ".global gStageMode2\n.set gStageMode2,0x0839b268\n"
 ".global gResource\n.set gResource,0x088eaa30\n"
 ".global gPalette\n.set gPalette,0x0894a9c8\n"
 ".global CreateDefinitionEffectTask\n.thumb_set CreateDefinitionEffectTask,0x80e03f9\n"
 ".global CleanupDefinitionInputs\n.thumb_set CleanupDefinitionInputs,0x80d38b5\n"
 ".global PollDefinitionEffect\n.thumb_set PollDefinitionEffect,0x80e05dd\n"
 ".global LoadDefinitionResource\n.thumb_set LoadDefinitionResource,0x80d45d1\n"
 ".global CreateRecordPhaseTask\n.thumb_set CreateRecordPhaseTask,0x80ddf69\n"
 ".global ProjectRecordPosition\n.thumb_set ProjectRecordPosition,0x80dbdc9\n"
 ".global CreatePositionedDefinitionTask\n.thumb_set CreatePositionedDefinitionTask,0x80d6099\n"
 ".global PollPositionedDefinitionTask\n.thumb_set PollPositionedDefinitionTask,0x80d6135\n"
 ".global CreateSequenceStage\n.thumb_set CreateSequenceStage,0x80dfd8d\n"
 ".global SelectRecordFlag\n.thumb_set SelectRecordFlag,0x80de3bd\n"
 ".global StopRecordMotion\n.thumb_set StopRecordMotion,0x80dba51\n"
 ".global CreateRecordSequence\n.thumb_set CreateRecordSequence,0x80de4f5\n"
 ".global ReadRecordTileCoordinates\n.thumb_set ReadRecordTileCoordinates,0x80dbd79\n"
 ".global BuildNeighborCells\n.thumb_set BuildNeighborCells,0x80d8709\n"
 ".global FindRecordAtCell\n.thumb_set FindRecordAtCell,0x80dd6b9\n"
 ".global RefreshRecordDirection\n.thumb_set RefreshRecordDirection,0x80de269\n"
 ".global ReadCellEligibility\n.thumb_set ReadCellEligibility,0x80d8d09\n"
 ".global CreateActionTask\n.thumb_set CreateActionTask,0x8005b6d\n"
 ".global CreatePaletteTask\n.thumb_set CreatePaletteTask,0x80d4725\n"
 ".global PollDefinitionGroup\n.thumb_set PollDefinitionGroup,0x80e0571\n"
 ".global PollActorTask\n.thumb_set PollActorTask,0x80e051d\n"
 ".global PollPalette\n.thumb_set PollPalette,0x80d4775\n"
 ".global ReadActorTargetCount\n.thumb_set ReadActorTargetCount,0x80d8859\n"
 ".global GetTargetRecord\n.thumb_set GetTargetRecord,0x80dd4a5\n"
 ".global CreateOffsetMotion\n.thumb_set CreateOffsetMotion,0x80dcfe5\n"
 ".global PollRecordHandles\n.thumb_set PollRecordHandles,0x80de1f1\n"
 ".global PollRecordMotion\n.thumb_set PollRecordMotion,0x80dba5d\n"
 ".global CellActionCallback\n.thumb_set CellActionCallback,0x80f4c6d\n"
 ".global ActorActionCallback\n.thumb_set ActorActionCallback,0x80f4a71\n"
);
s32 AdvanceAuthoredAdjacentRecordSequence(TaskNode *,struct AdjacentEvent *,struct AdjacentWork *) __asm__("OriginalActionCallback_000F4DFC");
s32 AdvanceAuthoredAdjacentRecordSequence(TaskNode *parent,struct AdjacentEvent *event,struct AdjacentWork *work)
{
 s16 position_x,position_y;
 s16 tile_x,tile_height,tile_y;
 switch(event->phase) {
 case 0: {
  u16 variant;void *actor;u8 count;
  work->mode=0;
  if(event->definition_id==319)work->mode=1;
  else if(event->definition_id==340)work->mode=2;
  variant=event->variant;work->variant=(u8)variant;
  actor=event->actor;work->actor=actor;
  count=3;if((u8)variant!=0)count=0;
  work->opening=CreateDefinitionEffectTask(actor,gOpening,count,0,0,parent);
  break;
 }
 case 1:CleanupDefinitionInputs();break;
 case 256: {
  u8 variant;
  work->opening=PollDefinitionEffect(work->opening);if(work->opening!=0)break;
  if(work->mode==1)LoadDefinitionResource(gResource,6,1,3,1);
  else if(work->mode==2)LoadDefinitionResource(gResource,6,1,3,1);
  variant=work->variant;
  if(variant!=0){work->delay=1;event->phase=260;break;}
  work->record_sequence=CreateRecordPhaseTask(work->actor,&work->record,144,1,&work->completion,gRecordPhase,variant,variant,parent);
  ++event->phase;break;
 }
 case 257:
  if(work->completion==0)break;
  if(work->mode==2){work->counter=12;++event->phase;break;}
  ProjectRecordPosition(work->record,&position_x,&position_y);
  work->position_task=CreatePositionedDefinitionTask(position_x,position_y,0,1,1,&work->position_output,gPositionSequence,parent);
  work->stage=CreateSequenceStage(gStageFirst,1,4,0,parent);
  ++event->phase;break;
 case 258: {
  TaskNode *remaining;u8 ordinal;
  if(work->mode==2 && work->counter!=0){--work->counter;break;}
  remaining=PollPositionedDefinitionTask(work->position_task);work->position_task=remaining;if(remaining!=0)break;
  SelectRecordFlag(work->record,0);StopRecordMotion(work->record_sequence);
  work->record_sequence=CreateRecordSequence(work->record,1,&work->completion,gRecordSequence,(u32)remaining,(u32)remaining,parent);
  ReadRecordTileCoordinates(work->record,&tile_x,&tile_height,&tile_y);
  BuildNeighborCells((u8)tile_x,(u8)tile_y,work->cells,0,2,1);
  ordinal=0;
  do {void *record;record=FindRecordAtCell(work->cells[ordinal].x,work->cells[ordinal].y);if(record!=0)RefreshRecordDirection(record);++ordinal;}while(ordinal<=3);
  work->counter=44;++event->phase;break;
 }
 case 259: {
  struct ChildEvent child_event;
  u8 ordinal;
  if(--work->counter!=0)break;
  if(work->mode==0)work->stage=CreateSequenceStage(gStageMode0,1,4,0,parent);
  else if(work->mode==1)work->stage=CreateSequenceStage(gStageMode1,2,4,0,parent);
  else if(work->mode==2)work->stage=CreateSequenceStage(gStageMode2,2,4,0,parent);
  ordinal=0;
  do {
   struct ActionCell *cell=&work->cells[ordinal];
   if((u8)ReadCellEligibility(cell)!=0){child_event.ordinal=ordinal;child_event.input=cell;work->cell_tasks[ordinal]=CreateActionTask((void *)CellActionCallback,24,(const u32 *)&child_event,parent);}
   ++ordinal;
  }while(ordinal<=3);
  if(work->mode!=0){child_event.input=work->record;work->actor_task=CreateActionTask((void *)ActorActionCallback,48,(const u32 *)&child_event,parent);}
  work->palette=CreatePaletteTask(gPalette,parent,0);
  ++event->phase;break;
 }
 case 260: {
  u32 count;
  if((u8)PollDefinitionGroup(work->cell_tasks,4)==0)break;
  work->actor_task=PollActorTask(work->actor_task);if(work->actor_task!=0)break;
  work->palette=PollPalette(work->palette);if(work->palette!=0)break;
  count=ReadActorTargetCount(work->actor,0);work->count=(u8)count;
  if((u8)count==0){event->phase=2;break;}
  work->delay=1;++event->phase;break;
 }
 case 261: {
  u8 zero;void *target;u32 parity,flags;
  zero=--work->delay;if(zero!=0)break;
  target=GetTargetRecord(work->actor,work->index);
  parity=work->index&1;flags=2;if(parity!=0)flags=4;
  work->motions[work->index]=CreateOffsetMotion(target,gOffsetMotion,(u8)(12-parity),0,flags|8,parent,zero);
  work->delay=40;++work->index;
  if(work->index==work->count)++event->phase;
  break;
 }
 case 262: {
  u8 all_done,ordinal;
  if((u8)PollRecordHandles(work->record)==0)break;
  all_done=1;ordinal=0;
  do {work->motions[ordinal]=PollRecordMotion(work->motions[ordinal]);if(work->motions[ordinal]!=0)all_done=0;++ordinal;}while(ordinal<=3);
  if(all_done!=0)event->phase=2;
  break;
 }
 }
 return 0;
}
