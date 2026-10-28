typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
typedef struct TaskNode TaskNode;
typedef void (*TaskCallback)(TaskNode *,u16 *,void *);
struct PairedChildEvent {u16 phase,unknown02;void *actor;u8 unknown08[12];s16 definition_id;u16 variant;u8 unknown18[4];};
struct PairedChildWork {
 s16 x,y;u16 delay;u8 variant,completion;
 TaskNode *children[2];void *record,*actor;TaskNode *opening;
 void *positioned_out;u32 unknown20;TaskNode *positioned,*motion,*sequence;
};
struct OpaqueChildEvent {u8 bytes[28];};
typedef char WorkSize[sizeof(struct PairedChildWork)==48?1:-1];
typedef char EventSize[sizeof(struct PairedChildEvent)==28?1:-1];
typedef char ChildEventSize[sizeof(struct OpaqueChildEvent)==28?1:-1];
extern const u8 gOpening[],gPositionedSequence[],gOpeningStage[],gChildStage[];
extern u8 gBufferBase[];
extern TaskNode *CreateDefinitionEffectTask(void *,const void *,u8,u8,const s16 *,TaskNode *);
extern void CleanupDefinitionInputs(void);
extern TaskNode *PollDefinitionEffect(TaskNode *);
extern void ApplyBufferOperation(const void *,void *,u32,u32);
extern void *GetActorNestedRecord(void *);
extern void ConfigureRecordDelay(void *,u16);
extern TaskNode *CreateRecordMotion(void *,u8 *,u8,s32,u32,u32,u32,TaskNode *);
extern void ProjectRecordPosition(const void *,s16 *,s16 *);
extern TaskNode *CreatePositionedTask(s32,s32,s32,u8,u32,void *,const void *,TaskNode *);
extern TaskNode *CreateSequenceStage(const void *,u8,u16,u16,TaskNode *);
extern TaskNode *CreateOppositePhaseChild(TaskCallback,u16,const void *,TaskNode *);
extern void RunAuthoredFirstChild(TaskNode *,u16 *,void *);
extern void RunAuthoredSecondChild(TaskNode *,u16 *,void *);
extern TaskNode *PollPositionedTask(TaskNode *);
extern TaskNode *PollAndReleaseMotion(TaskNode *);
extern TaskNode *PollAndReleaseChild(TaskNode *);
__asm__(
 ".global gOpening\n.set gOpening,0x83a6810\n"
 ".global gPositionedSequence\n.set gPositionedSequence,0x83a6834\n"
 ".global gOpeningStage\n.set gOpeningStage,0x83a684c\n"
 ".global gChildStage\n.set gChildStage,0x83a6854\n"
 ".global gBufferBase\n.set gBufferBase,0x3003a80\n"
 ".global CreateDefinitionEffectTask\n.thumb_set CreateDefinitionEffectTask,0x80e03f9\n"
 ".global CleanupDefinitionInputs\n.thumb_set CleanupDefinitionInputs,0x80d38b5\n"
 ".global PollDefinitionEffect\n.thumb_set PollDefinitionEffect,0x80e05dd\n"
 ".global ApplyBufferOperation\n.thumb_set ApplyBufferOperation,0x81482d5\n"
 ".global GetActorNestedRecord\n.thumb_set GetActorNestedRecord,0x80dd47d\n"
 ".global ConfigureRecordDelay\n.thumb_set ConfigureRecordDelay,0x80de10d\n"
 ".global CreateRecordMotion\n.thumb_set CreateRecordMotion,0x80de4b1\n"
 ".global ProjectRecordPosition\n.thumb_set ProjectRecordPosition,0x80dbdc9\n"
 ".global CreatePositionedTask\n.thumb_set CreatePositionedTask,0x80d6099\n"
 ".global CreateSequenceStage\n.thumb_set CreateSequenceStage,0x80dfd8d\n"
 ".global CreateOppositePhaseChild\n.thumb_set CreateOppositePhaseChild,0x8005b6d\n"
 ".global RunAuthoredFirstChild\n.thumb_set RunAuthoredFirstChild,0x811ab45\n"
 ".global RunAuthoredSecondChild\n.thumb_set RunAuthoredSecondChild,0x811acf5\n"
 ".global PollPositionedTask\n.thumb_set PollPositionedTask,0x80d6135\n"
 ".global PollAndReleaseMotion\n.thumb_set PollAndReleaseMotion,0x80dba5d\n"
 ".global PollAndReleaseChild\n.thumb_set PollAndReleaseChild,0x80e051d\n"
 "");
s32 AdvanceAuthoredPairedChildSequence(TaskNode *,struct PairedChildEvent *,struct PairedChildWork *) __asm__("OriginalActionCallback_0011AE00");
s32 AdvanceAuthoredPairedChildSequence(TaskNode *parent,struct PairedChildEvent *event,struct PairedChildWork *work)
{
 struct OpaqueChildEvent child_event;
 u16 phase=event->phase;
 switch(phase) {
 case 0: {
  u16 variant=event->variant;void *actor;u8 count;
  work->variant=(u8)variant;actor=event->actor;work->actor=actor;
  count=3;if((u8)variant!=0) count=0;
  work->opening=CreateDefinitionEffectTask(actor,gOpening,count,0,(const s16 *)(u32)phase,parent);break;
 }
 case 1: CleanupDefinitionInputs();break;
 case 256: {
  TaskNode *remaining;
  remaining=PollDefinitionEffect(work->opening);work->opening=remaining;
  if(remaining!=0) break;
  ApplyBufferOperation(gBufferBase,gBufferBase+192,16,6);
  work->record=GetActorNestedRecord(work->actor);
  ConfigureRecordDelay(work->record,60);
  work->motion=CreateRecordMotion(work->record,&work->completion,1,-1,(u32)remaining,58,(u32)remaining,parent);
  ++event->phase;break;
 }
 case 257:
  if(work->completion==0) break;
  ProjectRecordPosition(work->record,&work->x,&work->y);
  work->positioned=CreatePositionedTask(work->x,work->y,0,1,1,&work->positioned_out,gPositionedSequence,parent);
  work->sequence=CreateSequenceStage(gOpeningStage,1,4,0,parent);
  work->delay=28;++event->phase;break;
 case 258:
  if(work->delay!=0) {--work->delay;break;}
  /* The original passes one shared, unwritten 28B template. Both frozen
   * child interfaces consume no startup fields or retain its address. */
  work->children[0]=CreateOppositePhaseChild(RunAuthoredFirstChild,48,&child_event,parent);
  work->children[1]=CreateOppositePhaseChild(RunAuthoredSecondChild,36,&child_event,parent);
  work->sequence=CreateSequenceStage(gChildStage,1,4,0,parent);
  ++event->phase;break;
 case 259:
  work->positioned=PollPositionedTask(work->positioned);if(work->positioned!=0) break;
  work->motion=PollAndReleaseMotion(work->motion);if(work->motion!=0) break;
  work->children[0]=PollAndReleaseChild(work->children[0]);if(work->children[0]!=0) break;
  work->children[1]=PollAndReleaseChild(work->children[1]);if(work->children[1]!=0) break;
  event->phase=2;break;
 }
 return 0;
}
