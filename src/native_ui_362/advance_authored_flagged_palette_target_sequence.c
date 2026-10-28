typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
typedef struct TaskNode TaskNode;
struct SequenceEvent {u16 phase,unknown02;void *actor;u8 unknown08[12];s16 definition;u16 variant;u8 unknown18[4];};
struct ChildEvent {u32 unknown00;void *record;u8 unknown08[12];u16 flag,ordinal;u8 unknown18[4];};
struct SequenceWork {u8 flag,count,ordinal,delay,variant,unknown05[3];TaskNode *children[2],*opening;void *actor;};
typedef char EventSize[sizeof(struct SequenceEvent)==28?1:-1];
typedef char ChildSize[sizeof(struct ChildEvent)==28?1:-1];
typedef char WorkSize[sizeof(struct SequenceWork)==24?1:-1];
extern TaskNode *CreateDefinitionEffectTask(void *,const void *,u8,u8,const void *,TaskNode *);
extern void FinishDefinitionSequence(void);
extern TaskNode *PollDefinitionEffectTask(TaskNode *);
extern u32 CountDefinitionTargets(void *,u16);
extern void *GetDefinitionResourceBuffer(void);
extern void TransferDefinitionResource(const void *,u32,void *,u32);
extern void CopyPaletteGroups(const void *,u32,u32,u32,u32);
extern void MergeDisplayControlByte(u8);
extern u32 PollDefinitionTaskArray(TaskNode **,u16);
extern void *GetDefinitionTargetRecord(void *,u8);
extern TaskNode *CreateDefinitionTask(const void *,u16,const void *,TaskNode *);
extern u32 ReadDisplayHighMaskWord(u8);
extern const u8 gOpeningSequence[],gPalette01[],gPalette2[],gChildEntry[];
__asm__(
 ".global CreateDefinitionEffectTask\n.thumb_set CreateDefinitionEffectTask,0x80e03f9\n"
 ".global FinishDefinitionSequence\n.thumb_set FinishDefinitionSequence,0x80d38b5\n"
 ".global PollDefinitionEffectTask\n.thumb_set PollDefinitionEffectTask,0x80e05dd\n"
 ".global CountDefinitionTargets\n.thumb_set CountDefinitionTargets,0x80d8859\n"
 ".global GetDefinitionResourceBuffer\n.thumb_set GetDefinitionResourceBuffer,0x80d3af9\n"
 ".global TransferDefinitionResource\n.thumb_set TransferDefinitionResource,0x8000b69\n"
 ".global CopyPaletteGroups\n.thumb_set CopyPaletteGroups,0x80d45d1\n"
 ".global MergeDisplayControlByte\n.thumb_set MergeDisplayControlByte,0x8003621\n"
 ".global PollDefinitionTaskArray\n.thumb_set PollDefinitionTaskArray,0x80e0571\n"
 ".global GetDefinitionTargetRecord\n.thumb_set GetDefinitionTargetRecord,0x80dd4a5\n"
 ".global CreateDefinitionTask\n.thumb_set CreateDefinitionTask,0x8005b6d\n"
 ".global ReadDisplayHighMaskWord\n.thumb_set ReadDisplayHighMaskWord,0x80035a9\n"
 ".global gOpeningSequence\n.set gOpeningSequence,0x83983d8\n"
 ".global gPalette01\n.set gPalette01,0x88ea0d8\n"
 ".global gPalette2\n.set gPalette2,0x88e9c14\n"
 ".global gChildEntry\n.set gChildEntry,0x80e8f3d\n"
);
s32 AdvanceAuthoredFlaggedPaletteTargetSequence(TaskNode *,struct SequenceEvent *,struct SequenceWork *) __asm__("OriginalActionCallback_000E921C");
s32 AdvanceAuthoredFlaggedPaletteTargetSequence(TaskNode *parent,struct SequenceEvent *event,struct SequenceWork *work)
{
 struct ChildEvent child;
 register s32 phase __asm__("r3")=event->phase;
 __asm__("" : "+r"(phase));
 switch(phase) {
 case 0: {
  register u32 definition __asm__("r1");
  u32 variant;void *actor;u8 count;
  /* The native signed-halfword load defines a complete word before XOR. */
  definition=(s32)event->definition;
  __asm__("" : "+r"(definition));
  definition^=35;
  work->flag=((0U-definition)|definition)>>31;
  variant=event->variant;work->variant=variant;
  actor=event->actor;work->actor=actor;
  count=5;if((u8)variant!=0)count=0;
  work->opening=CreateDefinitionEffectTask(actor,gOpeningSequence,count,1,(const void *)phase,parent);
  break;
 }
 case 1:FinishDefinitionSequence();break;
 case 256: {
  register TaskNode *opening __asm__("r8");
  u32 count;
  opening=PollDefinitionEffectTask(work->opening);work->opening=opening;
  if(opening!=0)break;
  /* Real full returned NULL survives all target/resource/palette calls. */
  __asm__("" : "+r"(opening));
  count=CountDefinitionTargets(work->actor,0);work->count=count;
  if((u8)count==0){event->phase=2;break;}
  TransferDefinitionResource(GetDefinitionResourceBuffer(),0,(void *)0x0600ffc0,16);
  if(work->flag==0) {
   CopyPaletteGroups(gPalette01,6,0,1,1);
   CopyPaletteGroups(gPalette01,7,1,1,1);
   CopyPaletteGroups(gPalette2,8,1,2,1);
  }
  work->delay=1;work->ordinal=(u32)opening;
  MergeDisplayControlByte(1);
  ++event->phase;
  break;
 }
 case 257: {
  TaskNode **children=work->children;
  u32 pointer_snapshot,slot,raw_ordinal,shifted_ordinal,ordinal;
  register u32 offset __asm__("r4");
  TaskNode *created;
  PollDefinitionTaskArray(children,2);
  if(--work->delay!=0)break;
  pointer_snapshot=(u32)work->children[0];
  slot=((0U-pointer_snapshot)|pointer_snapshot)>>31;
  child.flag=work->flag;child.ordinal=work->ordinal;
  child.record=GetDefinitionTargetRecord(work->actor,work->ordinal);
  created=CreateDefinitionTask(gChildEntry,44,&child,parent);
  offset=slot<<2;
  __asm__("" : "+r"(offset));
  *(TaskNode **)((u8 *)children+offset)=created;
  work->delay=62;
  raw_ordinal=work->ordinal+1;work->ordinal=raw_ordinal;
  shifted_ordinal=raw_ordinal<<24;
  __asm__("" : "+r"(shifted_ordinal));
  ordinal=shifted_ordinal>>24;
  if(ordinal==work->count)++event->phase;
  break;
 }
 case 258:
  if((u8)PollDefinitionTaskArray(work->children,2)!=0) {
   u32 mask=ReadDisplayHighMaskWord(2);
   u16 *display=(u16 *)0x03000940;
   u16 value=*display;value&=~mask;*display=value;
   event->phase=2;
  }
  break;
 }
 return 0;
}
