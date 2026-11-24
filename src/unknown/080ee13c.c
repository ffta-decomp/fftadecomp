typedef unsigned char u8;typedef unsigned short u16;typedef signed short s16;typedef unsigned int u32;typedef signed int s32;typedef struct TaskNode TaskNode;
struct SequenceEvent {u16 phase,unknown02;void *owner;u8 unknown08[12];s16 definition;u16 variant;u8 unknown18[4];};
struct ChildEvent {u32 unknown00;void *record;u8 unknown08[12];u16 ordinal;u8 unknown16[6];};
struct SequenceWork {u8 variant,count,ordinal,delay;void *owner;TaskNode *children[2],*opening,*operation;u32 unknown18;};
extern TaskNode * CreateDefinitionEffectTask(void *,const void *,u8,u32,const void *,TaskNode *);
extern void FinishDefinitionSequence(void);
extern TaskNode * PollDefinitionEffectTask(TaskNode *);
extern u32 CountDefinitionTargets(void *,u16);
extern u32 PollDefinitionTaskArray(TaskNode **,u16);
extern void * GetDefinitionTargetRecord(void *,u32);
extern u32 ReadDefinitionTargetRowCount(const void *);
extern TaskNode * CreateProjectedAuthoredSequence(void *,u8,TaskNode *);
extern TaskNode * CreateAuthoredOwnerOpening(u32,void *,TaskNode *);
extern u32 IsActionEffectChildAtState258(TaskNode *);
extern TaskNode * PollAndReleaseAuthoredOperation(TaskNode *);
extern TaskNode * CreateDefinitionTask(const void *,u16,const void *,TaskNode *);
extern const u8 gOpeningSequence[],gChildEntry[];
__asm__(
 ".global CreateDefinitionEffectTask\n.thumb_set CreateDefinitionEffectTask,0x80e03f9\n"
 ".global FinishDefinitionSequence\n.thumb_set FinishDefinitionSequence,0x80d38b5\n"
 ".global PollDefinitionEffectTask\n.thumb_set PollDefinitionEffectTask,0x80e05dd\n"
 ".global CountDefinitionTargets\n.thumb_set CountDefinitionTargets,0x80d8859\n"
 ".global PollDefinitionTaskArray\n.thumb_set PollDefinitionTaskArray,0x80e0571\n"
 ".global GetDefinitionTargetRecord\n.thumb_set GetDefinitionTargetRecord,0x80dd4a5\n"
 ".global ReadDefinitionTargetRowCount\n.thumb_set ReadDefinitionTargetRowCount,0x80dd495\n"
 ".global CreateProjectedAuthoredSequence\n.thumb_set CreateProjectedAuthoredSequence,0x80eee51\n"
 ".global CreateAuthoredOwnerOpening\n.thumb_set CreateAuthoredOwnerOpening,0x80eeef1\n"
 ".global IsActionEffectChildAtState258\n.thumb_set IsActionEffectChildAtState258,0x80eef31\n"
 ".global PollAndReleaseAuthoredOperation\n.thumb_set PollAndReleaseAuthoredOperation,0x80eef6d\n"
 ".global CreateDefinitionTask\n.thumb_set CreateDefinitionTask,0x8005b6d\n"
 ".global gOpeningSequence\n.set gOpeningSequence,0x839957c\n"
 ".global gChildEntry\n.set gChildEntry,0x80edff9\n"
);
typedef char WorkSize[sizeof(struct SequenceWork)==28?1:-1];
typedef char ChildSize[sizeof(struct ChildEvent)==28?1:-1];
s32 AdvanceAuthoredTargetRowChildSequence(TaskNode *,struct SequenceEvent *,struct SequenceWork *) __asm__("OriginalActionCallback_000EE13C");
s32 AdvanceAuthoredTargetRowChildSequence(TaskNode *input_parent,struct SequenceEvent *input_event,struct SequenceWork *input_work)
{
 TaskNode *parent=input_parent;
 register struct SequenceEvent *event __asm__("r6")=input_event;
 register struct SequenceWork *work __asm__("r5")=input_work;
 register u32 phase __asm__("r3");
 struct ChildEvent child;
 __asm__("" : "+r"(parent), "+r"(event), "+r"(work));
 phase=event->phase;__asm__("" : "+r"(phase));
 switch((s32)phase){
 case 0:{
  register void *owner __asm__("r4");
  u16 variant;u32 count;
  variant=event->variant;work->variant=variant;
  owner=event->owner;__asm__("" : "+r"(owner));work->owner=owner;
  count=5;if((u8)variant!=0)count=0;
  work->opening=CreateDefinitionEffectTask(owner,gOpeningSequence,count,1,(const void *)phase,parent);
  break;
 }
 case 1:FinishDefinitionSequence();break;
 case 256:
  work->opening=PollDefinitionEffectTask(work->opening);if(work->opening!=0)break;
  if(work->variant!=0){
   work->delay=1;work->count=CountDefinitionTargets(work->owner,0);event->phase=259;
  }else{work->opening=CreateAuthoredOwnerOpening(2,work->owner,parent);++event->phase;}
  break;
 case 257:
  work->opening=PollDefinitionEffectTask(work->opening);if(work->opening!=0)break;
  work->operation=CreateProjectedAuthoredSequence(work->owner,2,parent);
  /* These are two independent original queries, with a fresh owner reload. */
  if((u8)CountDefinitionTargets(work->owner,0)!=0)work->count=CountDefinitionTargets(work->owner,0);
  ++event->phase;break;
 case 258:
  if((u8)ReadDefinitionTargetRowCount(work->owner)==0){
   work->operation=PollAndReleaseAuthoredOperation(work->operation);
   if(work->operation==0)event->phase=2;
  }else{
   if(work->variant==0 && (u8)IsActionEffectChildAtState258(work->operation)==0)break;
   work->delay=1;++event->phase;
  }
  break;
 case 259:{
  TaskNode **children=work->children;
  register u32 working __asm__("r4");
  u32 pointer_snapshot,ordinal,shifted_ordinal;TaskNode *created;
  PollDefinitionTaskArray(children,2);
  if(--work->delay!=0)break;
  pointer_snapshot=(u32)work->children[0];working=0U-pointer_snapshot;
  __asm__("" : "+r"(working));working|=pointer_snapshot;working>>=31;
  /* The getter precedes the fresh ordinal load into the partial child event. */
  child.record=GetDefinitionTargetRecord(work->owner,work->ordinal);
  child.ordinal=work->ordinal;
  created=CreateDefinitionTask(gChildEntry,48,&child,parent);
  working<<=2;working=(u32)((u8 *)children+working);*(TaskNode **)working=created;
  work->delay=84;
  ordinal=work->ordinal+1;work->ordinal=ordinal;
  shifted_ordinal=ordinal<<24;__asm__("" : "+r"(shifted_ordinal));
  if((shifted_ordinal>>24)==work->count)++event->phase;
  break;
 }
 case 260:
  work->operation=PollAndReleaseAuthoredOperation(work->operation);if(work->operation!=0)break;
  if((u8)PollDefinitionTaskArray(work->children,2)!=0)event->phase=2;
  break;
 }
 return 0;
}
