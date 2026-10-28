typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
typedef struct TaskNode TaskNode;
struct SequenceEvent {u16 phase,unknown02;void *actor;u8 unknown08[14];u16 variant;u8 unknown18[4];};
struct SequenceWork {
 u16 timer;u8 variant,unknown03;s16 x,y;void *projected;
 u8 positioned_output[8];TaskNode *positioned,*palette,*auxiliary,*stage,*opening;
 void *actor;TaskNode *motion,*sequence;
};
typedef char EventSize[sizeof(struct SequenceEvent)==28?1:-1];
typedef char WorkSize[sizeof(struct SequenceWork)==52?1:-1];
extern TaskNode *CreateDefinitionEffectTask(void *,const void *,u8,u8,const void *,TaskNode *);
extern void FinishDefinitionSequence(void);
extern TaskNode *PollDefinitionEffectTask(TaskNode *);
extern u32 CountDefinitionTargets(void *,u16);
extern void *GetDefinitionTargetRecord(void *,u8);
extern void *ProjectDefinitionRecord(void *,s16 *,s16 *,s16 *);
extern void PlaceDefinitionResource(const void *,u32,u32,s32,s32,u32);
extern TaskNode *CreateDefinitionPaletteTask(const void *,TaskNode *);
extern void ConfigureDefinitionPalette(TaskNode *,u8);
extern TaskNode *CreateDefinitionAuxiliaryTask(const void *,TaskNode *);
extern TaskNode *CreateDefinitionStage(u8,u8,u8,const void *,TaskNode *);
extern void ConfigureDefinitionStage(TaskNode *,u8,u8,u8);
extern TaskNode *CreateDefinitionMotion(void *,const void *,u8,u16,u32,TaskNode *,u16);
extern TaskNode *CreateDefinitionSequence(const void *,u8,u16,u16,TaskNode *);
extern u32 TestDefinitionRecord(void *);
extern TaskNode *CreatePositionedDefinitionTask(s32,s32,s32,u8,u32,void *,const void *,TaskNode *);
extern TaskNode *PollDefinitionAuxiliary(TaskNode *);
extern u32 ReadDisplayHighMaskWord(u8);
extern TaskNode *PollDefinitionStage(TaskNode *);
extern void ReleaseDefinitionPalette(TaskNode *);
extern TaskNode *PollPositionedDefinitionTask(TaskNode *);
extern TaskNode *PollDefinitionMotion(TaskNode *);
extern const u8 gOpeningSequence[],gModelResource[],gPaletteSequence[],gAuxiliarySequence[],gStageParameters[],gMotionSequence[],gInitialSequence[],gPositionedSequence[],gDelayedSequence[];
__asm__(
 ".global CreateDefinitionEffectTask\n.thumb_set CreateDefinitionEffectTask,0x80e03f9\n"
 ".global FinishDefinitionSequence\n.thumb_set FinishDefinitionSequence,0x80d38b5\n"
 ".global PollDefinitionEffectTask\n.thumb_set PollDefinitionEffectTask,0x80e05dd\n"
 ".global CountDefinitionTargets\n.thumb_set CountDefinitionTargets,0x80d8859\n"
 ".global GetDefinitionTargetRecord\n.thumb_set GetDefinitionTargetRecord,0x80dd4a5\n"
 ".global ProjectDefinitionRecord\n.thumb_set ProjectDefinitionRecord,0x80dd749\n"
 ".global PlaceDefinitionResource\n.thumb_set PlaceDefinitionResource,0x80d7221\n"
 ".global CreateDefinitionPaletteTask\n.thumb_set CreateDefinitionPaletteTask,0x80d4705\n"
 ".global ConfigureDefinitionPalette\n.thumb_set ConfigureDefinitionPalette,0x80d47a1\n"
 ".global CreateDefinitionAuxiliaryTask\n.thumb_set CreateDefinitionAuxiliaryTask,0x80d3e9d\n"
 ".global CreateDefinitionStage\n.thumb_set CreateDefinitionStage,0x80d979d\n"
 ".global ConfigureDefinitionStage\n.thumb_set ConfigureDefinitionStage,0x80d984d\n"
 ".global CreateDefinitionMotion\n.thumb_set CreateDefinitionMotion,0x80dcfe5\n"
 ".global CreateDefinitionSequence\n.thumb_set CreateDefinitionSequence,0x80dfd8d\n"
 ".global TestDefinitionRecord\n.thumb_set TestDefinitionRecord,0x80dd581\n"
 ".global CreatePositionedDefinitionTask\n.thumb_set CreatePositionedDefinitionTask,0x80d6099\n"
 ".global PollDefinitionAuxiliary\n.thumb_set PollDefinitionAuxiliary,0x80d3f09\n"
 ".global ReadDisplayHighMaskWord\n.thumb_set ReadDisplayHighMaskWord,0x80035a9\n"
 ".global PollDefinitionStage\n.thumb_set PollDefinitionStage,0x80d9b65\n"
 ".global ReleaseDefinitionPalette\n.thumb_set ReleaseDefinitionPalette,0x80d4769\n"
 ".global PollPositionedDefinitionTask\n.thumb_set PollPositionedDefinitionTask,0x80d6135\n"
 ".global PollDefinitionMotion\n.thumb_set PollDefinitionMotion,0x80dba5d\n"
 ".global gOpeningSequence\n.set gOpeningSequence,0x8398304\n"
 ".global gModelResource\n.set gModelResource,0x88f4f14\n"
 ".global gPaletteSequence\n.set gPaletteSequence,0x89491b4\n"
 ".global gAuxiliarySequence\n.set gAuxiliarySequence,0x894d740\n"
 ".global gStageParameters\n.set gStageParameters,0x8398370\n"
 ".global gMotionSequence\n.set gMotionSequence,0x8398374\n"
 ".global gInitialSequence\n.set gInitialSequence,0x8398388\n"
 ".global gPositionedSequence\n.set gPositionedSequence,0x8398340\n"
 ".global gDelayedSequence\n.set gDelayedSequence,0x8398390\n"
);
s32 AdvanceAuthoredRecordCoordinateSequence(TaskNode *,struct SequenceEvent *,struct SequenceWork *) __asm__("OriginalActionCallback_000E8D40");
s32 AdvanceAuthoredRecordCoordinateSequence(TaskNode *input_parent,struct SequenceEvent *input_event,struct SequenceWork *input_work)
{
 TaskNode *parent=input_parent;
 register struct SequenceEvent *event __asm__("r5")=input_event;
 register struct SequenceWork *work __asm__("r6")=input_work;
 register s32 phase __asm__("r3");
 /* All real incoming pointers are initialized before local binding use.
  * Parent stays ordinary: never bind a nullable pointer to hard R7. */
 __asm__("" : "+r"(parent), "+r"(event), "+r"(work));
 phase=event->phase;
 __asm__("" : "+r"(phase));
 switch(phase) {
 case 0: {
  u32 variant=event->variant;void *actor;u8 count;
  work->variant=variant;actor=event->actor;work->actor=actor;
  count=5;if((u8)variant!=0)count=0;
  work->opening=CreateDefinitionEffectTask(actor,gOpeningSequence,count,1,(const void *)phase,parent);
  break;
 }
 case 1:FinishDefinitionSequence();break;
 case 256: {
  register TaskNode *opening __asm__("r4");
  register void *record __asm__("r8");
  u32 count,duration;u8 y;
  TaskNode *palette,*stage;void *queried_record;
  opening=PollDefinitionEffectTask(work->opening);work->opening=opening;
  if(opening!=0)break;
  /* Actual full returned NULL survives through the sixth model word. */
  __asm__("" : "+r"(opening));
  count=CountDefinitionTargets(work->actor,0);
  if((u8)count==0){event->phase=2;break;}
  queried_record=GetDefinitionTargetRecord(work->actor,0);
  record=queried_record;
  /* The complete record pointer survives all subsequent resource calls. */
  __asm__("" : : "r"(record));
  work->projected=ProjectDefinitionRecord(queried_record,&work->x,&work->y,0);
  PlaceDefinitionResource(gModelResource,0,2,work->x,work->y,(u32)opening);
  palette=CreateDefinitionPaletteTask(gPaletteSequence,parent);work->palette=palette;
  ConfigureDefinitionPalette(palette,1);
  work->auxiliary=CreateDefinitionAuxiliaryTask(gAuxiliarySequence,parent);
  stage=CreateDefinitionStage(0,2,0,gStageParameters,parent);work->stage=stage;
  /* The byte consumer is a fresh low byte of alias-visible signed H6. */
  y=*(u8 *)&work->y;
  ConfigureDefinitionStage(stage,0,(u8)(y-64),y);
  /* Define the retained duration at its actual seventh-argument stage. */
  work->motion=CreateDefinitionMotion(record,gMotionSequence,12,160,4,parent,(duration=150));
  work->timer=duration;
  work->sequence=CreateDefinitionSequence(gInitialSequence,1,4,0,parent);
  if((u8)TestDefinitionRecord(record)!=0)++event->phase;
  else event->phase=258;
  break;
 }
 case 257:
  if(--work->timer!=0)break;
  work->positioned=CreatePositionedDefinitionTask(work->x,work->y,0,1,2,work->positioned_output,gPositionedSequence,parent);
  work->sequence=CreateDefinitionSequence(gDelayedSequence,1,4,0,parent);
  ++event->phase;
  break;
 case 258: {
  register TaskNode *stage __asm__("r4");
  u32 mask;u16 *display,value;
  work->auxiliary=PollDefinitionAuxiliary(work->auxiliary);
  if(work->auxiliary!=0)break;
  mask=ReadDisplayHighMaskWord(2);
  display=(u16 *)0x03000940;value=*display;value&=~mask;*display=value;
  stage=PollDefinitionStage(work->stage);work->stage=stage;
  if(stage!=0)break;
  /* The native returned NULL is stored after the opaque palette release. */
  __asm__("" : "+r"(stage));
  if(work->palette!=0){ReleaseDefinitionPalette(work->palette);work->palette=stage;}
  work->positioned=PollPositionedDefinitionTask(work->positioned);
  if(work->positioned!=0)break;
  work->motion=PollDefinitionMotion(work->motion);
  if(work->motion!=0)break;
  event->phase=2;
  break;
 }
 }
 return 0;
}
