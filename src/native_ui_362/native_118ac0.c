typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef struct {u16 phase; u16 unused2; void *owner;} SceneEvent;
typedef struct {u32 unused0; void *effect; void *overlay; void *owner; void *child;} SceneWork;
extern void FillHalfwords(const u16 *,void *,u32) __asm__("0x0814186c");
extern void *CreateAuthoredChild(void *,const void *,u32,u32,const u32 *,void *) __asm__("0x080e03f8");
extern void *AdvanceAuthoredChild(void *) __asm__("0x080e05dc");
extern void *CreateModeEffect(u32,void *,void *) __asm__("0x080f2e40");
extern void *AdvanceModeEffect(void *) __asm__("0x080f1210");
extern void *CreateAuthoredOverlay(const void *,void *) __asm__("0x080d4704");
extern void *AdvanceAuthoredOverlay(void *) __asm__("0x080d4774");
u32 RemainingBand43_00118AC0(void *task,SceneEvent *event,SceneWork *work)
{
 u16 phase=event->phase;
 switch(phase) {
 case 0: {
  u16 zeroA;
  u16 zeroB;
  u32 position;
  u8 *palette;
  work->owner=event->owner;
  position=0x00f800d8;
  zeroA=phase;
  palette=(u8 *)0x03003920;
  FillHalfwords(&zeroA,palette,0x01000040);
  zeroB=phase;
  palette+=512;
  FillHalfwords(&zeroB,palette,0x01000070);
  work->child=CreateAuthoredChild(work->owner,(const void *)0x083a616c,5,6,&position,task);
  break;
 }
 case 1:
  break;
 case 256:
  work->child=AdvanceAuthoredChild(work->child);
  if(work->child==0) {
   work->effect=CreateModeEffect(3,work->owner,task);
   work->overlay=CreateAuthoredOverlay((const void *)0x0894ab00,task);
   ++event->phase;
  }
  break;
 case 257:
  work->overlay=AdvanceAuthoredOverlay(work->overlay);
  if(work->overlay==0) {
   work->effect=AdvanceModeEffect(work->effect);
   if(work->effect==0)event->phase=2;
  }
  break;
 }
 return 0;
}
