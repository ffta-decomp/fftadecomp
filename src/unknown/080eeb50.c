typedef unsigned char u8;typedef unsigned short u16;typedef signed short s16;typedef unsigned int u32;typedef signed int s32;typedef struct TaskNode TaskNode;
struct SequenceEvent {u16 phase,unknown02;void *owner;u8 unknown08[12];s16 definition;u16 variant;u8 unknown18[4];};
struct SequenceWork {u16 timer;u8 variant,unknown03;s16 x,y;void *projection;TaskNode *auxiliary,*palette,*first_object,*second_object,*opening;void *owner;TaskNode *motion,*stage;};
extern TaskNode * CreateDefinitionEffectTask(void *,const void *,u32,u32,const void *,TaskNode *);
extern void FinishDefinitionSequence(void);
extern TaskNode * PollDefinitionEffectTask(TaskNode *);
extern void * GetDefinitionTargetRecord(void *,u32);
extern u32 CheckDefinitionOwnerReadiness(void *,u16);
extern void * ProjectActorWithDefaultTransition(void *,u16 *,u16 *,u16 *);
extern u32 ReadProjectedRecordFlag15(const void *);
extern TaskNode * CreateDefinitionMotionTask(void *,const void *,u8,u16,u16,TaskNode *,u16);
extern void ConfigureDefinitionRecordResource(const void *,u8,u8,s32,u16,u32);
extern TaskNode * CreateDefinitionAuxiliaryTask(const void *,TaskNode *);
extern TaskNode * CreateDefinitionPaletteTask(const void *,TaskNode *);
extern TaskNode * CreateDefinitionObjectTask(u8,u8,u8,TaskNode *);
extern void SetDefinitionObjectTaskPosition(TaskNode *,s16,s16,u16);
extern u32 ReadDisplayLowMaskWord(u8);
extern TaskNode * CreateDefinitionOverlayTask(u8,u16,u8,u8,const void *,TaskNode *);
extern TaskNode * CreateDefinitionStageTask(const void *,u8,u16,u8,TaskNode *);
extern TaskNode * PollDefinitionPalette(TaskNode *);
extern TaskNode * PollDefinitionAuxiliary(TaskNode *);
extern u32 ReadDisplayHighMaskWord(u8);
extern TaskNode * PollAndReleaseDefinitionMotion(TaskNode *);
extern TaskNode * PollDefinitionObjectTask(TaskNode *);
extern const u8 gOpeningSequence[],gMotionRow[],gResourceRecord[],gAuxiliarySequence[],gPaletteSequence[],gObjectSequence[],gStageSequence[];
__asm__(
 ".global CreateDefinitionEffectTask\n.thumb_set CreateDefinitionEffectTask,0x80e03f9\n"
 ".global FinishDefinitionSequence\n.thumb_set FinishDefinitionSequence,0x80d38b5\n"
 ".global PollDefinitionEffectTask\n.thumb_set PollDefinitionEffectTask,0x80e05dd\n"
 ".global GetDefinitionTargetRecord\n.thumb_set GetDefinitionTargetRecord,0x80dd4a5\n"
 ".global CheckDefinitionOwnerReadiness\n.thumb_set CheckDefinitionOwnerReadiness,0x80d8859\n"
 ".global ProjectActorWithDefaultTransition\n.thumb_set ProjectActorWithDefaultTransition,0x80dd749\n"
 ".global ReadProjectedRecordFlag15\n.thumb_set ReadProjectedRecordFlag15,0x80dd73d\n"
 ".global CreateDefinitionMotionTask\n.thumb_set CreateDefinitionMotionTask,0x80dcfe5\n"
 ".global ConfigureDefinitionRecordResource\n.thumb_set ConfigureDefinitionRecordResource,0x80d7221\n"
 ".global CreateDefinitionAuxiliaryTask\n.thumb_set CreateDefinitionAuxiliaryTask,0x80d3e9d\n"
 ".global CreateDefinitionPaletteTask\n.thumb_set CreateDefinitionPaletteTask,0x80d4705\n"
 ".global CreateDefinitionObjectTask\n.thumb_set CreateDefinitionObjectTask,0x80dab85\n"
 ".global SetDefinitionObjectTaskPosition\n.thumb_set SetDefinitionObjectTaskPosition,0x80dad3d\n"
 ".global ReadDisplayLowMaskWord\n.thumb_set ReadDisplayLowMaskWord,0x80035d1\n"
 ".global CreateDefinitionOverlayTask\n.thumb_set CreateDefinitionOverlayTask,0x80d98d5\n"
 ".global CreateDefinitionStageTask\n.thumb_set CreateDefinitionStageTask,0x80dfd8d\n"
 ".global PollDefinitionPalette\n.thumb_set PollDefinitionPalette,0x80d4775\n"
 ".global PollDefinitionAuxiliary\n.thumb_set PollDefinitionAuxiliary,0x80d3f09\n"
 ".global ReadDisplayHighMaskWord\n.thumb_set ReadDisplayHighMaskWord,0x80035a9\n"
 ".global PollAndReleaseDefinitionMotion\n.thumb_set PollAndReleaseDefinitionMotion,0x80dba5d\n"
 ".global PollDefinitionObjectTask\n.thumb_set PollDefinitionObjectTask,0x80d9b65\n"
 ".global gOpeningSequence\n.set gOpeningSequence,0x839992c\n"
 ".global gMotionRow\n.set gMotionRow,0x8399954\n"
 ".global gResourceRecord\n.set gResourceRecord,0x88f5544\n"
 ".global gAuxiliarySequence\n.set gAuxiliarySequence,0x894d8b8\n"
 ".global gPaletteSequence\n.set gPaletteSequence,0x894ac90\n"
 ".global gObjectSequence\n.set gObjectSequence,0x8399950\n"
 ".global gStageSequence\n.set gStageSequence,0x8399968\n"
);
typedef char WorkSize[sizeof(struct SequenceWork)==44?1:-1];
s32 AdvanceAuthoredOwnerCoordinateWindowSequence(TaskNode *,struct SequenceEvent *,struct SequenceWork *) __asm__("OriginalActionCallback_000EEB50");
s32 AdvanceAuthoredOwnerCoordinateWindowSequence(TaskNode *input_parent,struct SequenceEvent *input_event,struct SequenceWork *input_work)
{
 TaskNode *parent=input_parent;
 struct SequenceEvent *event=input_event;
 register struct SequenceWork *work __asm__("r6")=input_work;
 register u32 phase __asm__("r3");
 __asm__("" : "+r"(parent), "+r"(event), "+r"(work));
 phase=input_event->phase;__asm__("" : "+r"(phase));
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
  register TaskNode *opening __asm__("r9");
  register TaskNode *returned __asm__("r0");
  void *record,*projection;
  u8 *shadow;
  u32 low_mask;
  register u32 window_mask __asm__("r4");
  returned=PollDefinitionEffectTask(work->opening);opening=returned;
  __asm__("" : : "r"(opening), "r"(returned));
  work->opening=returned;if(returned!=0)break;
  if((u8)CheckDefinitionOwnerReadiness(work->owner,0)==0){event->phase=2;break;}
  record=GetDefinitionTargetRecord(work->owner,0);
  projection=ProjectActorWithDefaultTransition(record,(u16 *)&work->x,(u16 *)&work->y,0);work->projection=projection;
  if((u8)ReadProjectedRecordFlag15(projection)!=0)work->y=(u16)work->y-8;
  work->motion=CreateDefinitionMotionTask(record,gMotionRow,12,60,10,parent,60);
  ConfigureDefinitionRecordResource(gResourceRecord,0,2,work->x,160,(u32)opening);
  work->auxiliary=CreateDefinitionAuxiliaryTask(gAuxiliarySequence,parent);
  work->palette=CreateDefinitionPaletteTask(gPaletteSequence,parent);
  work->first_object=CreateDefinitionObjectTask(0,0,0,parent);
  SetDefinitionObjectTaskPosition(work->first_object,work->x,work->y,32);
  shadow=(u8 *)0x03000940;
  /* Preserve each original observed shadow-byte read, including overwritten values. */
  (void)*(volatile u8 *)(shadow+66);
  window_mask=63;__asm__("" : "+r"(window_mask));shadow[66]=63;
  low_mask=ReadDisplayLowMaskWord(2);window_mask&=~low_mask;
  (void)*(volatile u8 *)(shadow+68);shadow[68]=window_mask;
  (void)*(volatile u8 *)(shadow+59);shadow[59]=(u32)opening;
  (void)*(volatile u8 *)(shadow+58);shadow[58]=(u32)opening;
  (void)*(volatile u8 *)(shadow+63);shadow[63]=(u32)opening;
  (void)*(volatile u8 *)(shadow+62);shadow[62]=255;
  {
   register u32 observed __asm__("r1")=*(u16 *)shadow;
   register u32 literal_mask __asm__("r3")=0x2000;
   register u32 combined __asm__("r0")=literal_mask;
   __asm__("" : "+r"(combined) : "r"(observed), "r"(literal_mask));
   combined|=observed;
   *(u16 *)shadow=combined;
  }
  work->second_object=CreateDefinitionOverlayTask(2,0,1,1,gObjectSequence,parent);
  work->stage=CreateDefinitionStageTask(gStageSequence,1,4,0,parent);
  work->timer=72;
  {register struct SequenceEvent *advance_event __asm__("r1")=event;
   __asm__("" : "+r"(advance_event));++advance_event->phase;}
  break;
 }
 case 257:
  if(--work->timer==0){
   register struct SequenceEvent *timer_event __asm__("r2")=event;
   __asm__("" : "+r"(timer_event));++timer_event->phase;
  }
  break;
 case 258:{
  u32 mask;u16 *shadow;
  register u32 previous __asm__("r1");
  register u32 filter __asm__("r0");
  work->palette=PollDefinitionPalette(work->palette);if(work->palette!=0)break;
  work->auxiliary=PollDefinitionAuxiliary(work->auxiliary);if(work->auxiliary!=0)break;
  mask=ReadDisplayHighMaskWord(2);shadow=(u16 *)0x03000940;
  previous=*shadow;__asm__("" : "+r"(previous));
  previous&=~mask;__asm__("" : "+r"(previous));
  filter=0xdfff;__asm__("" : "+r"(filter));*shadow=previous&filter;
  work->motion=PollAndReleaseDefinitionMotion(work->motion);if(work->motion!=0)break;
  work->first_object=PollDefinitionObjectTask(work->first_object);if(work->first_object!=0)break;
  work->second_object=PollDefinitionObjectTask(work->second_object);
  if(work->second_object==0){
   register u32 finished_phase __asm__("r0")=2;
   register struct SequenceEvent *finished_event __asm__("r3")=event;
   __asm__("" : "+r"(finished_phase), "+r"(finished_event));
   finished_event->phase=finished_phase;
  }
  break;
 }
 }
 return 0;
}
