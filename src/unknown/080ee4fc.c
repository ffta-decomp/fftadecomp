typedef unsigned char u8;typedef unsigned short u16;typedef signed short s16;typedef unsigned int u32;typedef signed int s32;typedef struct TaskNode TaskNode;
struct SequenceEvent {u16 phase,unknown02;void *owner;u8 unknown08[12];s16 definition;u16 variant;u8 unknown18[4];};
struct SequenceWork {u8 unknown00[2];s16 x,y;u8 unknown06,variant;void *record,*projection;u8 first_output[16];TaskNode *first;u8 second_output[12];TaskNode *second,*opening,*operation;void *owner;TaskNode *sequence,*stage;};
extern TaskNode * CreateDefinitionEffectTask(void *,const void *,u32,u32,const void *,TaskNode *);
extern void FinishDefinitionSequence(void);
extern TaskNode * PollDefinitionEffectTask(TaskNode *);
extern void * GetDefinitionTargetRecord(void *,u32);
extern u32 ReadDefinitionTargetRowCount(const void *);
extern TaskNode * CreateProjectedAuthoredSequence(void *,u8,TaskNode *);
extern TaskNode * CreateAuthoredOwnerOpening(u32,void *,TaskNode *);
extern u32 IsActionEffectChildAtState258(TaskNode *);
extern TaskNode * PollAndReleaseAuthoredOperation(TaskNode *);
extern void * ProjectActorWithDefaultTransition(void *,u16 *,u16 *,u16 *);
extern u32 HasDefinitionTargetNegativeProperty(const void *);
extern TaskNode * CreatePositionedDefinitionTask(s32,s32,s32,u8,u32,void *,const void *,TaskNode *);
extern TaskNode * PollAndReleasePositionedDefinitionTask(TaskNode *);
extern TaskNode * CreateDefinitionMotionTask(void *,const void *,u8,u16,u16,TaskNode *,u16);
extern TaskNode * PollAndReleaseDefinitionMotion(TaskNode *);
extern TaskNode * CreateDefinitionStageTask(const void *,u8,u16,u8,TaskNode *);
extern void * CopyBytes(void *,const void *,u32);
extern const u8 gOpeningSequence[],gOffsets[],gFirstProjection[],gSecondProjection[],gMotionRows[],gStageSequence[];
__asm__(
 ".global CreateDefinitionEffectTask\n.thumb_set CreateDefinitionEffectTask,0x80e03f9\n"
 ".global FinishDefinitionSequence\n.thumb_set FinishDefinitionSequence,0x80d38b5\n"
 ".global PollDefinitionEffectTask\n.thumb_set PollDefinitionEffectTask,0x80e05dd\n"
 ".global GetDefinitionTargetRecord\n.thumb_set GetDefinitionTargetRecord,0x80dd4a5\n"
 ".global ReadDefinitionTargetRowCount\n.thumb_set ReadDefinitionTargetRowCount,0x80dd495\n"
 ".global CreateProjectedAuthoredSequence\n.thumb_set CreateProjectedAuthoredSequence,0x80eee51\n"
 ".global CreateAuthoredOwnerOpening\n.thumb_set CreateAuthoredOwnerOpening,0x80eeef1\n"
 ".global IsActionEffectChildAtState258\n.thumb_set IsActionEffectChildAtState258,0x80eef31\n"
 ".global PollAndReleaseAuthoredOperation\n.thumb_set PollAndReleaseAuthoredOperation,0x80eef6d\n"
 ".global ProjectActorWithDefaultTransition\n.thumb_set ProjectActorWithDefaultTransition,0x80dd749\n"
 ".global HasDefinitionTargetNegativeProperty\n.thumb_set HasDefinitionTargetNegativeProperty,0x80dd5ed\n"
 ".global CreatePositionedDefinitionTask\n.thumb_set CreatePositionedDefinitionTask,0x80d6099\n"
 ".global PollAndReleasePositionedDefinitionTask\n.thumb_set PollAndReleasePositionedDefinitionTask,0x80d6135\n"
 ".global CreateDefinitionMotionTask\n.thumb_set CreateDefinitionMotionTask,0x80dcfe5\n"
 ".global PollAndReleaseDefinitionMotion\n.thumb_set PollAndReleaseDefinitionMotion,0x80dba5d\n"
 ".global CreateDefinitionStageTask\n.thumb_set CreateDefinitionStageTask,0x80dfd8d\n"
 ".global CopyBytes\n.thumb_set CopyBytes,0x81443fd\n"
 ".global gOpeningSequence\n.set gOpeningSequence,0x83996fc\n"
 ".global gOffsets\n.set gOffsets,0x8149d08\n"
 ".global gFirstProjection\n.set gFirstProjection,0x839972c\n"
 ".global gSecondProjection\n.set gSecondProjection,0x839978c\n"
 ".global gMotionRows\n.set gMotionRows,0x83997d4\n"
 ".global gStageSequence\n.set gStageSequence,0x83997fc\n"
);
typedef char WorkSize[sizeof(struct SequenceWork)==72?1:-1];
s32 AdvanceAuthoredTargetPropertySequence(TaskNode *,struct SequenceEvent *,struct SequenceWork *) __asm__("OriginalActionCallback_000EE4FC");
s32 AdvanceAuthoredTargetPropertySequence(TaskNode *input_parent,struct SequenceEvent *input_event,struct SequenceWork *input_work)
{
 TaskNode *parent=input_parent;
 struct SequenceEvent *event=input_event;
 struct SequenceWork *work=input_work;
 register u32 phase __asm__("r3");
 u8 offsets[2];
 __asm__("" : "+r"(parent), "+r"(event), "+r"(work));
 phase=event->phase;__asm__("" : "+r"(phase));
 switch((s32)phase){
 case 0:{
  u16 variant=event->variant;
  void *owner;
  register u32 count __asm__("r5");
  work->variant=variant;owner=event->owner;work->owner=owner;
  count=4;__asm__("" : "+r"(count));if((u8)variant!=0)count=0;
  work->opening=CreateDefinitionEffectTask(owner,gOpeningSequence,count,1,(const void *)phase,parent);
  break;
 }
 case 1:FinishDefinitionSequence();break;
 case 256:{
  void *record;
  work->opening=PollDefinitionEffectTask(work->opening);if(work->opening!=0)break;
  record=GetDefinitionTargetRecord(work->owner,0);work->record=record;
  work->projection=ProjectActorWithDefaultTransition(record,(u16 *)&work->x,(u16 *)&work->y,0);
  if(work->variant!=0)event->phase=258;
  else{work->opening=CreateAuthoredOwnerOpening(4,work->owner,parent);++event->phase;}
  break;
 }
 case 257:
  work->opening=PollDefinitionEffectTask(work->opening);if(work->opening!=0)break;
  work->operation=CreateProjectedAuthoredSequence(work->owner,4,parent);
  ++event->phase;break;
 case 258:{
  register u32 selection __asm__("r5");
  u32 stage_variant;
  CopyBytes(offsets,gOffsets,2);
  if((u8)ReadDefinitionTargetRowCount(work->owner)==0){
   work->operation=PollAndReleaseAuthoredOperation(work->operation);
   if(work->operation==0)event->phase=2;
   break;
  }
  if(work->variant==0&&(u8)IsActionEffectChildAtState258(work->operation)==0)break;
  work->first=CreatePositionedDefinitionTask(work->x,work->y,0,1,4,work->first_output,gFirstProjection,parent);
  selection=0;__asm__("" : "+r"(selection));
  if((u8)HasDefinitionTargetNegativeProperty(work->record)!=0){
   work->second=CreatePositionedDefinitionTask(work->x,work->y,0,1,3,work->second_output,gSecondProjection,parent);
   selection=1;
  }
  /* The source-specific table stride is 20; offsets remain a copied local array. */
  work->sequence=CreateDefinitionMotionTask(work->record,gMotionRows+selection*20,12,offsets[selection],10,parent,40);
  stage_variant=1;if(selection!=0)stage_variant=2;
  work->stage=CreateDefinitionStageTask(gStageSequence,stage_variant,4,0,parent);
  ++event->phase;break;
 }
 case 259:
  work->operation=PollAndReleaseAuthoredOperation(work->operation);if(work->operation!=0)break;
  work->first=PollAndReleasePositionedDefinitionTask(work->first);if(work->first!=0)break;
  /* Original polls this field even if the property branch did not write it. */
  work->second=PollAndReleasePositionedDefinitionTask(work->second);if(work->second!=0)break;
  work->sequence=PollAndReleaseDefinitionMotion(work->sequence);if(work->sequence==0)event->phase=2;
  break;
 }
 return 0;
}
