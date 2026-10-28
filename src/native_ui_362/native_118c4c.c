typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef struct {u16 phase; u16 unused2; void *owner;} SceneEvent;
typedef struct {u16 timer; u16 unused2; void *effect; void *owner; void *child;} SceneWork;
extern void FillHalfwords(const u16 *,void *,u32) __asm__("0x0814186c");
extern void *CreateAuthoredChild(void *,const void *,u32,u32,const u32 *,void *) __asm__("0x080e03f8");
extern void *AdvanceAuthoredChild(void *) __asm__("0x080e05dc");
extern void *CreateTimedChild(void *) __asm__("0x080e5694");
extern void TriggerCue(u32,u32,u32,u32) __asm__("0x080dbed4");
extern void *AdvanceTimedChild(void *) __asm__("0x080e051c");
u32 RemainingBand43_00118C4C(void *task,SceneEvent *event,SceneWork *work)
{
 u16 phase=event->phase;
 switch(phase) {
 case 0: {
  u16 zeroA;
  u16 zeroB;
  u32 position;
  u8 *palette;
  work->owner=event->owner;
  position=0x00f80078;
  zeroA=phase;
  palette=(u8 *)0x03003920;
  FillHalfwords(&zeroA,palette,0x01000040);
  zeroB=phase;
  palette+=512;
  FillHalfwords(&zeroB,palette,0x01000070);
  work->child=CreateAuthoredChild(work->owner,(const void *)0x083a6208,4,6,&position,task);
  break;
 }
 case 1:
  break;
 case 256:
  work->child=AdvanceAuthoredChild(work->child);
  if(work->child==0) {
   work->effect=CreateTimedChild(task);
   work->timer=65;
   ++event->phase;
  }
  break;
 case 257:
  if(work->timer!=0) {
   --work->timer;
   if(work->timer==0)TriggerCue(0,1,0,0);
  }
  work->effect=AdvanceTimedChild(work->effect);
  if(work->effect==0)event->phase=2;
  break;
 }
 return 0;
}
