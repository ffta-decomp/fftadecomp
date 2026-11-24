typedef unsigned char u8;typedef unsigned short u16;typedef signed short s16;typedef unsigned int u32;typedef signed int s32;typedef struct TaskNode TaskNode;
struct SequenceEvent {u16 phase,unknown02;void *owner;u8 unknown08[12];s16 definition;u16 variant;u8 unknown18[4];};
struct SequenceWork {u16 timer;s16 x,y;u8 unknown06,variant;void *record,*projection;u8 output[4];TaskNode *positioned;void *object,*palette;TaskNode *auxiliary,*opening,*operation;void *owner;TaskNode *sequence,*stage;};
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
extern TaskNode * CreatePositionedDefinitionTask(s32,s32,s32,u8,u32,void *,const void *,TaskNode *);
extern TaskNode * PollAndReleasePositionedDefinitionTask(TaskNode *);
extern TaskNode * CreateDefinitionMotionTask(void *,const void *,u8,u16,u16,TaskNode *,u16);
extern TaskNode * PollAndReleaseDefinitionMotion(TaskNode *);
extern TaskNode * CreateDefinitionStageTask(const void *,u8,u16,u8,TaskNode *);
extern void ConfigureDefinitionResourceCoordinates(u8,u8,u16,s16,s16);
extern void * CreateDefinitionResource(u8,const void *,u16,u8);
extern void * PollAndReleaseDefinitionResource(void *,u8);
extern void * CreateDefinitionObject(const void *,u16,s32,s32,s32,u16,u8);
extern void SetDefinitionObjectSortKey(void *,s16);
extern void * PollAndReleaseDefinitionObject(void *);
extern void CopyDefinitionRecordCoordinates(const void *,u16 *,u16 *,u16 *);
extern u32 ReadDisplayHighMaskWord(u8);
extern TaskNode * CreateDefinitionAuxiliaryTask(const void *,TaskNode *);
extern TaskNode * PollDefinitionAuxiliary(TaskNode *);
extern const u8 gOpeningSequence[],gPositionedSequence[],gPaletteResource[],gAuxiliarySequence[],gMotionRow[],gStageSequence[],gObjectResource[];
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
 ".global CreatePositionedDefinitionTask\n.thumb_set CreatePositionedDefinitionTask,0x80d6099\n"
 ".global PollAndReleasePositionedDefinitionTask\n.thumb_set PollAndReleasePositionedDefinitionTask,0x80d6135\n"
 ".global CreateDefinitionMotionTask\n.thumb_set CreateDefinitionMotionTask,0x80dcfe5\n"
 ".global PollAndReleaseDefinitionMotion\n.thumb_set PollAndReleaseDefinitionMotion,0x80dba5d\n"
 ".global CreateDefinitionStageTask\n.thumb_set CreateDefinitionStageTask,0x80dfd8d\n"
 ".global ConfigureDefinitionResourceCoordinates\n.thumb_set ConfigureDefinitionResourceCoordinates,0x80d49fd\n"
 ".global CreateDefinitionResource\n.thumb_set CreateDefinitionResource,0x80d4b65\n"
 ".global PollAndReleaseDefinitionResource\n.thumb_set PollAndReleaseDefinitionResource,0x80d4d2d\n"
 ".global CreateDefinitionObject\n.thumb_set CreateDefinitionObject,0x80d5e81\n"
 ".global SetDefinitionObjectSortKey\n.thumb_set SetDefinitionObjectSortKey,0x8011059\n"
 ".global PollAndReleaseDefinitionObject\n.thumb_set PollAndReleaseDefinitionObject,0x8011485\n"
 ".global CopyDefinitionRecordCoordinates\n.thumb_set CopyDefinitionRecordCoordinates,0x80dbd5d\n"
 ".global ReadDisplayHighMaskWord\n.thumb_set ReadDisplayHighMaskWord,0x80035a9\n"
 ".global CreateDefinitionAuxiliaryTask\n.thumb_set CreateDefinitionAuxiliaryTask,0x80d3e9d\n"
 ".global PollDefinitionAuxiliary\n.thumb_set PollDefinitionAuxiliary,0x80d3f09\n"
 ".global gOpeningSequence\n.set gOpeningSequence,0x8399834\n"
 ".global gPositionedSequence\n.set gPositionedSequence,0x8399858\n"
 ".global gPaletteResource\n.set gPaletteResource,0x88eea08\n"
 ".global gAuxiliarySequence\n.set gAuxiliarySequence,0x894d834\n"
 ".global gMotionRow\n.set gMotionRow,0x8399870\n"
 ".global gStageSequence\n.set gStageSequence,0x8399884\n"
 ".global gObjectResource\n.set gObjectResource,0x84fc91c\n"
);
typedef char WorkSize[sizeof(struct SequenceWork)==56?1:-1];
s32 AdvanceAuthoredTargetCoordinateObjectSequence(TaskNode *,struct SequenceEvent *,struct SequenceWork *) __asm__("OriginalActionCallback_000EE6E4");
s32 AdvanceAuthoredTargetCoordinateObjectSequence(TaskNode *input_parent,struct SequenceEvent *input_event,struct SequenceWork *input_work)
{
 TaskNode *parent=input_parent;
 struct SequenceEvent *event=input_event;
 struct SequenceWork *work=input_work;
 register u32 phase __asm__("r3");
 __asm__("" : "+r"(parent), "+r"(event), "+r"(work));
 phase=event->phase;__asm__("" : "+r"(phase));
 switch((s32)phase){
 case 0:{
  u16 variant=event->variant;
  register void *owner __asm__("r4");
  u32 count;
  work->variant=variant;owner=event->owner;__asm__("" : "+r"(owner));work->owner=owner;
  count=3;if((u8)variant!=0)count=0;
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
  else{work->opening=CreateAuthoredOwnerOpening(5,work->owner,parent);++event->phase;}
  break;
 }
 case 257:
  work->opening=PollDefinitionEffectTask(work->opening);if(work->opening!=0)break;
  work->operation=CreateProjectedAuthoredSequence(work->owner,5,parent);
  ++event->phase;break;
 case 258:{
  u32 mask;u16 *shadow;
  register u32 previous __asm__("r1");
  if((u8)ReadDefinitionTargetRowCount(work->owner)==0){
   work->operation=PollAndReleaseAuthoredOperation(work->operation);
   if(work->operation==0)event->phase=2;
   break;
  }
  if(work->variant==0&&(u8)IsActionEffectChildAtState258(work->operation)==0)break;
  work->positioned=CreatePositionedDefinitionTask(work->x,work->y,0,1,1,work->output,gPositionedSequence,parent);
  ConfigureDefinitionResourceCoordinates(0,2,0,work->x,work->y);
  work->palette=CreateDefinitionResource(0,gPaletteResource,904,6);
  mask=ReadDisplayHighMaskWord(2);shadow=(u16 *)0x03000940;
  previous=*shadow;__asm__("" : "+r"(previous));
  previous|=mask;__asm__("" : "+r"(previous));*shadow=previous;
  work->auxiliary=CreateDefinitionAuxiliaryTask(gAuxiliarySequence,parent);
  work->sequence=CreateDefinitionMotionTask(work->record,gMotionRow,12,30,10,parent,30);
  work->stage=CreateDefinitionStageTask(gStageSequence,1,4,0,parent);
  work->timer=4;++event->phase;break;
 }
 case 259:{
  u16 out_x,out_y,out_z;
  void *created;
  if(--work->timer!=0)break;
  CopyDefinitionRecordCoordinates(work->projection,&out_x,&out_y,&out_z);
  created=CreateDefinitionObject(gObjectResource,1,(s16)out_x,(s16)out_y,(s16)out_z,972,7);work->object=created;
  SetDefinitionObjectSortKey(created,1);
  ++event->phase;break;
 }
 case 260:{
  u32 mask;u16 *shadow;
  register u32 previous __asm__("r1");
  work->auxiliary=PollDefinitionAuxiliary(work->auxiliary);if(work->auxiliary!=0)break;
  work->palette=PollAndReleaseDefinitionResource(work->palette,0);if(work->palette!=0)break;
  /* This clear happens on every reached cleanup entry, before the remaining polls. */
  mask=ReadDisplayHighMaskWord(2);shadow=(u16 *)0x03000940;
  previous=*shadow;__asm__("" : "+r"(previous));*shadow=previous&~mask;
  work->positioned=PollAndReleasePositionedDefinitionTask(work->positioned);if(work->positioned!=0)break;
  work->object=PollAndReleaseDefinitionObject(work->object);if(work->object!=0)break;
  work->sequence=PollAndReleaseDefinitionMotion(work->sequence);if(work->sequence==0)event->phase=2;
  break;
 }
 }
 return 0;
}
