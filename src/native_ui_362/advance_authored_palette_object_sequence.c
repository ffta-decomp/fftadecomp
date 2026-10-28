typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
typedef struct TaskNode TaskNode;
struct SequenceWork {u32 unknown00,unknown04;TaskNode *auxiliary,*palette,*object,*opening;u32 unknown18;};
struct DisplayShadow {u16 control;u8 unknown02[72];volatile u8 byte74;u8 unknown75[3];volatile u8 byte78;};
typedef char WorkSize[sizeof(struct SequenceWork)==28?1:-1];
extern const u8 gOpeningDescriptor[],gPositionRecord[],gPaletteSequence[],gAuxiliarySequence[],gObjectSequence[];
extern u8 gPaletteShadow[];
extern struct DisplayShadow gDisplayShadow;
extern TaskNode *CreateManagedTaskChild(const void *,u8,TaskNode *);
extern void CpuSet(const void *,void *,u32);
extern void RestoreSceneStage(void);
extern TaskNode *PollManagedTaskChild(TaskNode *);
extern void ConfigureBackgroundRecord(const void *,u32,u32,s32,s32,u32);
extern TaskNode *CreatePaletteTask(const void *,TaskNode *);
extern TaskNode *CreateAuxiliaryTask(const void *,TaskNode *);
extern TaskNode *CreateDefinitionObject(u32,u32,u32,u32,const void *,TaskNode *);
extern TaskNode *PollAuxiliary(TaskNode *);
extern TaskNode *PollPalette(TaskNode *);
extern u32 ReadDisplayMaskWord(u8);
extern void SetSceneMode(u16);
extern TaskNode *PollDefinitionObject(TaskNode *);
__asm__(
 ".global gOpeningDescriptor\n.set gOpeningDescriptor,0x83a6ab4\n"
 ".global gPaletteShadow\n.set gPaletteShadow,0x3003920\n"
 ".global gPositionRecord\n.set gPositionRecord,0x88f4d34\n"
 ".global gPaletteSequence\n.set gPaletteSequence,0x894c770\n"
 ".global gAuxiliarySequence\n.set gAuxiliarySequence,0x894d69c\n"
 ".global gObjectSequence\n.set gObjectSequence,0x83a6acc\n"
 ".global gDisplayShadow\n.set gDisplayShadow,0x3000940\n"
 ".global CreateManagedTaskChild\n.thumb_set CreateManagedTaskChild,0x80d7a71\n"
 ".global CpuSet\n.thumb_set CpuSet,0x814186d\n"
 ".global RestoreSceneStage\n.thumb_set RestoreSceneStage,0x80d35d9\n"
 ".global PollManagedTaskChild\n.thumb_set PollManagedTaskChild,0x80d7abd\n"
 ".global ConfigureBackgroundRecord\n.thumb_set ConfigureBackgroundRecord,0x80d7221\n"
 ".global CreatePaletteTask\n.thumb_set CreatePaletteTask,0x80d4705\n"
 ".global CreateAuxiliaryTask\n.thumb_set CreateAuxiliaryTask,0x80d3e9d\n"
 ".global CreateDefinitionObject\n.thumb_set CreateDefinitionObject,0x80d98d5\n"
 ".global PollAuxiliary\n.thumb_set PollAuxiliary,0x80d3f09\n"
 ".global PollPalette\n.thumb_set PollPalette,0x80d4775\n"
 ".global ReadDisplayMaskWord\n.thumb_set ReadDisplayMaskWord,0x80035a9\n"
 ".global SetSceneMode\n.thumb_set SetSceneMode,0x80d3ac1\n"
 ".global PollDefinitionObject\n.thumb_set PollDefinitionObject,0x80d9b65\n");
s32 AdvanceAuthoredPaletteObjectSequence(TaskNode *,u16 *,struct SequenceWork *) __asm__("OriginalActionCallback_0011B764");
s32 AdvanceAuthoredPaletteObjectSequence(TaskNode *parent,u16 *event,struct SequenceWork *work)
{
 u16 fill;
 u16 phase=*event;
 switch(phase) {
 case 0:
  work->opening=CreateManagedTaskChild(gOpeningDescriptor,2,parent);
  fill=phase;CpuSet(&fill,gPaletteShadow,0x01000010);break;
 case 1:RestoreSceneStage();break;
 case 256: {
  TaskNode *remaining=PollManagedTaskChild(work->opening);work->opening=remaining;
  if(remaining!=0)break;
  ConfigureBackgroundRecord(gPositionRecord,0,2,0,(s32)remaining,(u32)remaining);
  work->palette=CreatePaletteTask(gPaletteSequence,parent);
  work->auxiliary=CreateAuxiliaryTask(gAuxiliarySequence,parent);
  work->object=CreateDefinitionObject(2,0,0,0,gObjectSequence,parent);
  ++*event;break;
 }
 case 257: {
  u32 mask;
  work->auxiliary=PollAuxiliary(work->auxiliary);if(work->auxiliary!=0)break;
  work->palette=PollPalette(work->palette);if(work->palette!=0)break;
  mask=ReadDisplayMaskWord(2);gDisplayShadow.control&=~mask;
  gDisplayShadow.byte74=191;
  gDisplayShadow.byte78=16;
  SetSceneMode(0);++*event;break;
 }
 case 258:
  work->object=PollDefinitionObject(work->object);if(work->object!=0)break;
  *event=2;break;
 }
 return 0;
}
