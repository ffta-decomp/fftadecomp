typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct Owner {u8 unknown00[6];u8 completed;};
struct DisplaySnapshot {u16 control;u8 unknown02[72];u8 flags74;u8 unknown75[5];};
struct DisplayShadow {u16 control;u8 unknown02[72];volatile u8 flags74;u8 unknown75[5];};
struct DialogWorkspace {
 struct Owner *owner;
 u8 unknown04[4];
 void *dialog;
 u8 timer,mode,message;
 u8 unknown15[85];
 struct DisplaySnapshot saved;
};
struct DialogEvent {u16 state;u8 unknown02[2];struct Owner *owner;u8 unknown08[12];u16 mode,message;};
extern struct DisplayShadow gDisplayShadow;
extern u8 gDialogFirstData[],gDialogSecondData[];
extern void *AllocateSceneTaskBytes(u32);
extern void ReleaseSceneTaskAllocation(void *);
extern void CopyDisplayBytes(void *,const void *,u32);
extern void InitializeManagedDialog(void *,u8,u32,void *,void *,u16,u16,u8,u8,u16);
extern void SetManagedDialogOutputFlags(u16);
extern u32 PollManagedDialog(void);
asm(".global gDisplayShadow\n.set gDisplayShadow,0x03000940\n.global gDialogFirstData\n.set gDialogFirstData,0x030008b0\n.global gDialogSecondData\n.set gDialogSecondData,0x03000990\n.global AllocateSceneTaskBytes\n.thumb_set AllocateSceneTaskBytes,0x08121b65\n.global ReleaseSceneTaskAllocation\n.thumb_set ReleaseSceneTaskAllocation,0x08121b79\n.global CopyDisplayBytes\n.thumb_set CopyDisplayBytes,0x081443fd\n.global InitializeManagedDialog\n.thumb_set InitializeManagedDialog,0x0801174d\n.global SetManagedDialogOutputFlags\n.thumb_set SetManagedDialogOutputFlags,0x0801339d\n.global PollManagedDialog\n.thumb_set PollManagedDialog,0x08011861");
u32 AdvanceManagedSceneDialog(void *node,struct DialogEvent *event,struct DialogWorkspace *workspace) asm("CoreRegion_00125FA8");
u32 AdvanceManagedSceneDialog(void *node,struct DialogEvent *event,struct DialogWorkspace *workspace)
{
 register struct DialogWorkspace *work asm("r5")=workspace;
 /* Original R5 holds the initialized workspace through callback-visible phases. */
 asm("" : "+r"(work));
 switch(event->state) {
 case 1:
  if(work->dialog) {
   ReleaseSceneTaskAllocation(work->dialog);
   work->dialog=0;
  }
  break;
 case 0: {
  u32 flags;
  struct DisplayShadow *shadow;
  work->owner=event->owner;
  work->mode=event->mode;
  work->message=event->message;
  work->timer=0;
  shadow=&gDisplayShadow;
  /* The initialized display base survives the copy before its RMW uses. */
  asm("" : "+r"(shadow));
  CopyDisplayBytes(&work->saved,shadow,80);
  shadow->control|=0xc00;
  flags=shadow->flags74&0xe3;
  shadow->flags74=flags;
  break;
 }
 case 256: {
  void *dialog=AllocateSceneTaskBytes(0xa04);
  work->dialog=dialog;
  switch(work->mode) {
  case 1:
   InitializeManagedDialog(dialog,1,work->message,gDialogFirstData,gDialogSecondData,2,2,24,4,928);
   SetManagedDialogOutputFlags(2);
   break;
  case 2:
   InitializeManagedDialog(dialog,2,work->message,gDialogFirstData,gDialogSecondData,2,2,24,0,928);
   SetManagedDialogOutputFlags(2);
   break;
  }
  event->state=257;
  break;
 }
 case 257:
  if((u16)PollManagedDialog()!=0)event->state=258;
  break;
 case 258: {
  u32 timer=work->timer;
  if(timer!=0) {
   timer--;
   work->timer=timer;
   if((u8)timer!=0)break;
  }
  ReleaseSceneTaskAllocation(work->dialog);
  work->dialog=0;
  event->state=259;
  break;
 }
 case 259: {
  u8 flags;
  gDisplayShadow.control=work->saved.control;
  flags=work->saved.flags74;
  gDisplayShadow.flags74=flags;
  work->owner->completed=1;
  event->state=3;
  break;
 }
 }
 return 0;
}
