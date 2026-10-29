typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
typedef struct TaskNode TaskNode;
struct DirectionSequenceEvent {u16 phase,unknown02;void *actor;u8 unknown08[12];s16 definition_id;u16 variant;u8 unknown18[4];};
struct DirectionSequenceWork {
 u8 variant,unknown01[3];s16 x,y;u8 completion,unknown09[3];
 void *actor,*record,*rendered,*target;
 TaskNode *opening;void *positioned_out;u32 unknown24;
 TaskNode *positioned;void *resource;TaskNode *auxiliary,*palettes[2],*late_palette,*motion,*record_child,*sequence;
};
struct DirectionOffset {u16 x,y;};
struct DirectionOffsets {struct DirectionOffset pair[4];};
struct DirectionDisplayShadow {u16 control;u8 unknown02[72];volatile u8 byte74;};
typedef char WorkSize[sizeof(struct DirectionSequenceWork)==76?1:-1];
typedef char EventSize[sizeof(struct DirectionSequenceEvent)==28?1:-1];
extern const u8 gOpening[],gRecordSequence[],gCoordinateResource[],gAuxiliaryA[],gPaletteA[],gPaletteB[];
extern const u8 gStageA[],gRecordFollowup[],gStageB[],gResource[],gAuxiliaryB[],gPositionedSequence[],gLatePalette[],gStageC[],gTargetMotion[];
extern const struct DirectionOffsets gDirectionOffsets;
extern struct DirectionDisplayShadow gDisplayShadow;
extern TaskNode *CreateDefinitionEffectTask(void *,const void *,u8,u8,const s16 *,TaskNode *);
extern void CleanupDefinitionInputs(void);
extern TaskNode *PollDefinitionEffect(TaskNode *);
extern u32 QueryActorAvailability(void *);
extern TaskNode *CreateRecordSequence(void *,void **,u16,u8,u8 *,const void *,u16,u16,TaskNode *);
extern void ProjectRecordPosition(const void *,s16 *,s16 *);
extern s32 ReadRecordDirection(void *);
extern void LoadCoordinateResource(const void *,u8,u8,s32,s32,u32);
extern TaskNode *CreateAuxiliary(const void *,TaskNode *);
extern TaskNode *CreatePaletteSequence(const void *,TaskNode *);
extern TaskNode *CreateSequenceStage(const void *,u8,u16,u16,TaskNode *);
extern u32 PollPaletteArray(TaskNode **,u32);
extern TaskNode *PollAuxiliary(TaskNode *);
extern u32 ReadDisplayMask(u8);
extern void SelectRecordFlag(void *,u8);
extern void RemoveTaskBranch(TaskNode *);
extern TaskNode *CreateFollowupSequence(void *,u8,u8 *,const void *,u32,u32,TaskNode *);
extern void *GetDefinitionTarget(void *,u8);
extern void *ProjectTargetActor(void *,s16 *,s16 *,u16 *);
extern void ConfigureResourceCoordinates(u8,u8,u16,s16,s16);
extern void *CreateResource(u8,const void *,u16,u8);
extern void SetAuxiliaryTiming(TaskNode *,u16,u16);
extern TaskNode *CreatePositionedTask(s32,s32,s32,u8,u32,void *,const void *,TaskNode *);
extern TaskNode *CreateLatePalette(const void *,TaskNode *,u16);
extern void *PollResource(void *,u8);
extern TaskNode *PollPaletteSequence(TaskNode *);
extern TaskNode *PollPositionedTask(TaskNode *);
extern TaskNode *CreateActorMotion(void *,u16,u16,TaskNode *);
extern TaskNode *PollAndReleaseMotion(TaskNode *);
extern TaskNode *CreateTargetMotion(void *,const void *,u8,u16,u32,TaskNode *,u32);
extern u32 PollRecordHandles(void *);
__asm__(
 ".global gOpening\n.set gOpening,0x83a6410\n"
 ".global gRecordSequence\n.set gRecordSequence,0x83a649c\n"
 ".global gCoordinateResource\n.set gCoordinateResource,0x88f58e0\n"
 ".global gAuxiliaryA\n.set gAuxiliaryA,0x894d69c\n"
 ".global gPaletteA\n.set gPaletteA,0x894be84\n"
 ".global gPaletteB\n.set gPaletteB,0x894beac\n"
 ".global gStageA\n.set gStageA,0x83a64a4\n"
 ".global gRecordFollowup\n.set gRecordFollowup,0x83a64a0\n"
 ".global gStageB\n.set gStageB,0x83a64b4\n"
 ".global gResource\n.set gResource,0x88f06b0\n"
 ".global gAuxiliaryB\n.set gAuxiliaryB,0x894daa0\n"
 ".global gPositionedSequence\n.set gPositionedSequence,0x83a6458\n"
 ".global gLatePalette\n.set gLatePalette,0x894abf0\n"
 ".global gStageC\n.set gStageC,0x83a64ac\n"
 ".global gTargetMotion\n.set gTargetMotion,0x83a6488\n"
 ".global gDirectionOffsets\n.set gDirectionOffsets,0x8149f78\n"
 ".global gDisplayShadow\n.set gDisplayShadow,0x3000940\n"
 ".global CreateDefinitionEffectTask\n.thumb_set CreateDefinitionEffectTask,0x80e03f9\n"
 ".global CleanupDefinitionInputs\n.thumb_set CleanupDefinitionInputs,0x80d38b5\n"
 ".global PollDefinitionEffect\n.thumb_set PollDefinitionEffect,0x80e05dd\n"
 ".global QueryActorAvailability\n.thumb_set QueryActorAvailability,0x80d3b55\n"
 ".global CreateRecordSequence\n.thumb_set CreateRecordSequence,0x80ddf69\n"
 ".global ProjectRecordPosition\n.thumb_set ProjectRecordPosition,0x80dbdc9\n"
 ".global ReadRecordDirection\n.thumb_set ReadRecordDirection,0x80dbc89\n"
 ".global LoadCoordinateResource\n.thumb_set LoadCoordinateResource,0x80d7221\n"
 ".global CreateAuxiliary\n.thumb_set CreateAuxiliary,0x80d3e9d\n"
 ".global CreatePaletteSequence\n.thumb_set CreatePaletteSequence,0x80d4705\n"
 ".global CreateSequenceStage\n.thumb_set CreateSequenceStage,0x80dfd8d\n"
 ".global PollPaletteArray\n.thumb_set PollPaletteArray,0x80d48dd\n"
 ".global PollAuxiliary\n.thumb_set PollAuxiliary,0x80d3f09\n"
 ".global ReadDisplayMask\n.thumb_set ReadDisplayMask,0x80035a9\n"
 ".global SelectRecordFlag\n.thumb_set SelectRecordFlag,0x80de3bd\n"
 ".global RemoveTaskBranch\n.thumb_set RemoveTaskBranch,0x80dba51\n"
 ".global CreateFollowupSequence\n.thumb_set CreateFollowupSequence,0x80de4f5\n"
 ".global GetDefinitionTarget\n.thumb_set GetDefinitionTarget,0x80dd4a5\n"
 ".global ProjectTargetActor\n.thumb_set ProjectTargetActor,0x80dd749\n"
 ".global ConfigureResourceCoordinates\n.thumb_set ConfigureResourceCoordinates,0x80d49fd\n"
 ".global CreateResource\n.thumb_set CreateResource,0x80d4b65\n"
 ".global SetAuxiliaryTiming\n.thumb_set SetAuxiliaryTiming,0x80d3f85\n"
 ".global CreatePositionedTask\n.thumb_set CreatePositionedTask,0x80d6099\n"
 ".global CreateLatePalette\n.thumb_set CreateLatePalette,0x80d4725\n"
 ".global PollResource\n.thumb_set PollResource,0x80d4d2d\n"
 ".global PollPaletteSequence\n.thumb_set PollPaletteSequence,0x80d4775\n"
 ".global PollPositionedTask\n.thumb_set PollPositionedTask,0x80d6135\n"
 ".global CreateActorMotion\n.thumb_set CreateActorMotion,0x80df9e5\n"
 ".global PollAndReleaseMotion\n.thumb_set PollAndReleaseMotion,0x80dba5d\n"
 ".global CreateTargetMotion\n.thumb_set CreateTargetMotion,0x80dcfe5\n"
 ".global PollRecordHandles\n.thumb_set PollRecordHandles,0x80de1f1\n"
 "");
s32 AdvanceAuthoredDirectionResourceSequence(TaskNode *,struct DirectionSequenceEvent *,struct DirectionSequenceWork *) __asm__("OriginalActionCallback_00119914");
s32 AdvanceAuthoredDirectionResourceSequence(TaskNode *parent,struct DirectionSequenceEvent *event,struct DirectionSequenceWork *work)
{
 u16 phase=event->phase;
 switch(phase) {
 case 0: {
  u16 variant=event->variant;void *actor;u8 count;
  work->variant=(u8)variant;actor=event->actor;work->actor=actor;count=6;
  if((u8)variant!=0) count=0;
  work->opening=CreateDefinitionEffectTask(actor,gOpening,count,0,(const s16 *)(u32)phase,parent);break;
 }
 case 1: CleanupDefinitionInputs();break;
 case 256: {
  u32 unavailable;
  work->opening=PollDefinitionEffect(work->opening);if(work->opening!=0) break;
  unavailable=(u8)QueryActorAvailability(work->actor);
  if(unavailable!=0) {event->phase=2;break;}
  work->record_child=CreateRecordSequence(work->actor,&work->record,84,1,&work->completion,gRecordSequence,2,unavailable,parent);
  ProjectRecordPosition(work->record,&work->x,&work->y);++event->phase;break;
 }
 case 257: {
  struct DirectionOffsets offsets=gDirectionOffsets;
  s32 raw_direction,direction; s32 y;
  register s32 x __asm__("r3");
  register u32 origin_x __asm__("r4");
  register const void *resource __asm__("r1");
  register const struct DirectionOffset *row __asm__("r0");
  if(work->completion==0) break;
  raw_direction=ReadRecordDirection(work->record);
  resource=gCoordinateResource;
  /* Actual resource pointer is defined after the getter and before the
   * signed row calculation; the same full pointer is the later call input. */
  __asm__("" : : "r"(resource));
  direction=(s8)raw_direction;
  row=&offsets.pair[direction];
  /* The real row-X working definition precedes the origin-X load. */
  x=row->x;
  __asm__("" : "+r"(x));
  origin_x=(u16)work->x;
  x+=origin_x;
  __asm__("" : "+r"(x) : "r"(origin_x));
  x=(s16)x;
  /* The same initialized row address survives the X working calculation
   * until its actual final Y halfword load; no call crosses this interval. */
  __asm__("" : : "r"(row));
  y=(s16)(row->y+(u16)work->y);
  LoadCoordinateResource(resource,0,2,x,y,0);
  work->auxiliary=CreateAuxiliary(gAuxiliaryA,parent);
  work->palettes[0]=CreatePaletteSequence(gPaletteA,parent);
  work->palettes[1]=CreatePaletteSequence(gPaletteB,parent);
  work->sequence=CreateSequenceStage(gStageA,1,4,0,parent);++event->phase;break;
 }
 case 258: {
  TaskNode *remaining;u32 mask,control;
  if((u8)PollPaletteArray(work->palettes,2)==0) break;
  remaining=PollAuxiliary(work->auxiliary);work->auxiliary=remaining;if(remaining!=0) break;
  gDisplayShadow.byte74=(u32)remaining;
  mask=ReadDisplayMask(2);control=gDisplayShadow.control;control&=~mask;gDisplayShadow.control=control;
  SelectRecordFlag(work->record,0);RemoveTaskBranch(work->record_child);
  work->record_child=CreateFollowupSequence(work->record,1,&work->completion,gRecordFollowup,(u32)remaining,(u32)remaining,parent);
  work->target=GetDefinitionTarget(work->actor,0);
  work->rendered=ProjectTargetActor(work->target,&work->x,&work->y,0);
  work->sequence=CreateSequenceStage(gStageB,1,4,0,parent);++event->phase;break;
 }
 case 259: {
  u32 mask,control;
  if(work->completion==0) break;
  ConfigureResourceCoordinates(1,3,0,work->x,work->y);
  work->resource=CreateResource(1,gResource,796,7);
  mask=ReadDisplayMask(3);control=gDisplayShadow.control;control|=mask;gDisplayShadow.control=control;
  work->auxiliary=CreateAuxiliary(gAuxiliaryB,parent);SetAuxiliaryTiming(work->auxiliary,8,255);
  work->positioned=CreatePositionedTask(work->x,work->y,0,1,2,&work->positioned_out,gPositionedSequence,parent);
  work->late_palette=CreateLatePalette(gLatePalette,parent,20);
  work->sequence=CreateSequenceStage(gStageC,1,4,0,parent);++event->phase;break;
 }
 case 260: {
  u32 mask,control;
  work->resource=PollResource(work->resource,1);if(work->resource!=0) break;
  mask=ReadDisplayMask(3);control=gDisplayShadow.control;control&=~mask;gDisplayShadow.control=control;
  work->auxiliary=PollAuxiliary(work->auxiliary);if(work->auxiliary!=0) break;
  work->late_palette=PollPaletteSequence(work->late_palette);if(work->late_palette!=0) break;
  work->positioned=PollPositionedTask(work->positioned);if(work->positioned!=0) break;
  work->motion=CreateActorMotion(work->target,11,0,parent);++event->phase;break;
 }
 case 261: {
  TaskNode *remaining;
  remaining=PollAndReleaseMotion(work->motion);work->motion=remaining;if(remaining!=0) break;
  work->motion=CreateTargetMotion(work->target,gTargetMotion,12,0,12,parent,(u32)remaining);++event->phase;break;
 }
 case 262:
  if((u8)PollRecordHandles(work->record)==0) break;
  work->motion=PollAndReleaseMotion(work->motion);if(work->motion!=0) break;
  event->phase=2;break;
 }
 return 0;
}
