typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
typedef struct TaskNode TaskNode;
struct RecordSequenceEvent {u16 phase,unknown02;u32 unknown04;void *record;u8 unknown0c[16];};
struct RecordSequenceWork {u16 unknown00,delay;void *record;TaskNode *child;void *positioned_out;u32 unknown10;TaskNode *positioned;u32 unknown18;TaskNode *stage;};
typedef char EventSize[sizeof(struct RecordSequenceEvent)==28?1:-1];
typedef char WorkSize[sizeof(struct RecordSequenceWork)==32?1:-1];
extern const u8 gManagedDescriptor[],gPositionedSequence[],gAuthoredStage[];
extern void CleanupDefinitionInputs(void);
extern TaskNode *CreateManagedTaskChild(const void *,u8,TaskNode *);
extern TaskNode *PollManagedTaskChild(TaskNode *);
extern void ApplyRecordValue(void *,u16);
extern void ProjectRecordPosition(const void *,s16 *,s16 *);
extern TaskNode *CreatePositionedTask(s32,s32,s32,u8,u32,void *,const void *,TaskNode *);
extern TaskNode *CreateSequenceStage(const void *,u8,u16,u16,TaskNode *);
extern TaskNode *PollPositionedTask(TaskNode *);
extern void RestoreActorMotionPresentation(void *);
__asm__(
 ".global gManagedDescriptor\n.set gManagedDescriptor,0x8395f80\n"
 ".global gPositionedSequence\n.set gPositionedSequence,0x8395fa4\n"
 ".global gAuthoredStage\n.set gAuthoredStage,0x8395fd4\n"
 ".global CleanupDefinitionInputs\n.thumb_set CleanupDefinitionInputs,0x80d38b5\n"
 ".global CreateManagedTaskChild\n.thumb_set CreateManagedTaskChild,0x80d7a71\n"
 ".global PollManagedTaskChild\n.thumb_set PollManagedTaskChild,0x80d7abd\n"
 ".global ApplyRecordValue\n.thumb_set ApplyRecordValue,0x80de10d\n"
 ".global ProjectRecordPosition\n.thumb_set ProjectRecordPosition,0x80dbdc9\n"
 ".global CreatePositionedTask\n.thumb_set CreatePositionedTask,0x80d6099\n"
 ".global CreateSequenceStage\n.thumb_set CreateSequenceStage,0x80dfd8d\n"
 ".global PollPositionedTask\n.thumb_set PollPositionedTask,0x80d6135\n"
 ".global RestoreActorMotionPresentation\n.thumb_set RestoreActorMotionPresentation,0x80de391\n");
s32 AdvanceAuthoredRecordPositionedSequence(TaskNode *,struct RecordSequenceEvent *,struct RecordSequenceWork *) __asm__("OriginalActionCallback_000E308C");
s32 AdvanceAuthoredRecordPositionedSequence(TaskNode *parent,struct RecordSequenceEvent *event,struct RecordSequenceWork *work)
{
 s16 x,y;
 switch(event->phase) {
 case 0:work->record=event->record;break;
 case 1:CleanupDefinitionInputs();break;
 case 256:
  work->child=CreateManagedTaskChild(gManagedDescriptor,3,parent);
  ApplyRecordValue(work->record,68);
  work->delay=6;++event->phase;break;
 case 257:
  if(work->delay!=0) {if(--work->delay!=0) break;}
  work->child=PollManagedTaskChild(work->child);if(work->child!=0) break;
  ProjectRecordPosition(work->record,&x,&y);
  work->positioned=CreatePositionedTask(x,y,0,1,2,&work->positioned_out,gPositionedSequence,parent);
  work->stage=CreateSequenceStage(gAuthoredStage,1,4,0,parent);
  ++event->phase;break;
 case 258:
  work->positioned=PollPositionedTask(work->positioned);if(work->positioned!=0) break;
  RestoreActorMotionPresentation(work->record);event->phase=2;break;
 }
 return 0;
}
