typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
typedef struct TaskNode TaskNode;
struct SequenceEvent {u16 phase,unknown02;void *actor;u8 unknown08[12];short definition;u16 variant;u8 unknown18[4];};
struct ChildEvent {u32 unknown00;void *first,*second;u8 unknown0C[8];u16 flag;u8 unknown16[6];};
struct SequenceWork {u16 delay;u8 flag,variant;TaskNode *first,*second,*third,*opening;void *actor;TaskNode *stage;};
typedef char EventSize[sizeof(struct SequenceEvent)==28?1:-1];
typedef char ChildSize[sizeof(struct ChildEvent)==28?1:-1];
typedef char WorkSize[sizeof(struct SequenceWork)==28?1:-1];
extern TaskNode *CreateDefinitionEffectTask(void *,const void *,u8,u8,const void *,TaskNode *);
extern void FinishDefinitionSequence(void);
extern TaskNode *PollDefinitionEffectTask(TaskNode *);
extern TaskNode *PollDefinitionChild(TaskNode *);
extern u32 CountDefinitionTargets(void *,u16);
extern void *GetDefinitionTargetRecord(void *,u8);
extern u32 TestRecordFlag7(const void *);
extern TaskNode *CreateDefinitionTask(const void *,u16,const void *,TaskNode *);
extern TaskNode *CreateDefinitionStageTask(const void *,u8,u16,u16,TaskNode *);
extern const u8 gOpeningSequence[],gFirstChildEntry[],gSecondChildEntry[],gThirdChildEntry[],gStageSequence[];
__asm__(
 ".global gOpeningSequence\n.set gOpeningSequence,0x0839753c\n"
 ".global gFirstChildEntry\n.set gFirstChildEntry,0x080e6a49\n"
 ".global gSecondChildEntry\n.set gSecondChildEntry,0x080e6b11\n"
 ".global gThirdChildEntry\n.set gThirdChildEntry,0x080e6d55\n"
 ".global gStageSequence\n.set gStageSequence,0x08397664\n"
 ".global CreateDefinitionEffectTask\n.thumb_set CreateDefinitionEffectTask,0x080e03f9\n"
 ".global FinishDefinitionSequence\n.thumb_set FinishDefinitionSequence,0x080d38b5\n"
 ".global PollDefinitionEffectTask\n.thumb_set PollDefinitionEffectTask,0x080e05dd\n"
 ".global PollDefinitionChild\n.thumb_set PollDefinitionChild,0x080e051d\n"
 ".global CountDefinitionTargets\n.thumb_set CountDefinitionTargets,0x080d8859\n"
 ".global GetDefinitionTargetRecord\n.thumb_set GetDefinitionTargetRecord,0x080dd4a5\n"
 ".global TestRecordFlag7\n.thumb_set TestRecordFlag7,0x080dd581\n"
 ".global CreateDefinitionTask\n.thumb_set CreateDefinitionTask,0x08005b6d\n"
 ".global CreateDefinitionStageTask\n.thumb_set CreateDefinitionStageTask,0x080dfd8d\n"
);
s32 AdvanceAuthoredPairedTargetSequence(TaskNode *,struct SequenceEvent *,struct SequenceWork *) __asm__("OriginalActionCallback_000E6E10");
s32 AdvanceAuthoredPairedTargetSequence(TaskNode *parent,struct SequenceEvent *event,struct SequenceWork *work)
{
 struct ChildEvent pair_event;
 struct ChildEvent delayed_event;
 register s32 phase __asm__("r3")=event->phase;
 /* The full zero-extended phase drives dispatch; phase0 is also the actual
  * fifth outgoing opening word before R3 is reused for the fourth argument. */
 __asm__("" : "+r"(phase));
 switch(phase) {
 case 0: {
  u32 variant;void *actor;u8 count;
  if(event->definition==122)work->flag=1;
  variant=event->variant;work->variant=variant;
  actor=event->actor;work->actor=actor;
  count=4;
  if((u8)variant!=0)count=0;
  work->opening=CreateDefinitionEffectTask(actor,gOpeningSequence,count,1,(const void *)phase,parent);
  break;
 }
 case 1:FinishDefinitionSequence();break;
 case 256:
  work->opening=PollDefinitionEffectTask(work->opening);
  if(work->opening!=0)break;
  if((u8)CountDefinitionTargets(work->actor,0)==0)event->phase=2;
  else ++event->phase;
  break;
 case 257: {
  u8 enabled;
  pair_event.flag=work->flag;
  pair_event.first=GetDefinitionTargetRecord(work->actor,0);
  pair_event.second=GetDefinitionTargetRecord(work->actor,1);
  enabled=TestRecordFlag7(pair_event.first);
  work->first=CreateDefinitionTask(gFirstChildEntry,44,&pair_event,parent);
  if(enabled!=0) {
   work->second=CreateDefinitionTask(gSecondChildEntry,280,&pair_event,parent);
   work->stage=CreateDefinitionStageTask(gStageSequence,2,4,0,parent);
   work->delay=120;
   ++event->phase;
  } else event->phase=259;
  break;
 }
 case 258:
  if(work->delay!=0) {
   if(--work->delay==0) {
    delayed_event.first=GetDefinitionTargetRecord(work->actor,1);
    work->third=CreateDefinitionTask(gThirdChildEntry,36,&delayed_event,parent);
   }
  }
  work->first=PollDefinitionChild(work->first);
  if(work->first!=0)break;
  work->second=PollDefinitionChild(work->second);
  if(work->second!=0)break;
  if(work->third==0)break;
  ++event->phase;
  /* The native falls through and polls all three again in this same call. */
 case 259:
  work->first=PollDefinitionChild(work->first);
  if(work->first!=0)break;
  work->second=PollDefinitionChild(work->second);
  if(work->second!=0)break;
  work->third=PollDefinitionChild(work->third);
  if(work->third!=0)break;
  event->phase=2;
  break;
 }
 return 0;
}
