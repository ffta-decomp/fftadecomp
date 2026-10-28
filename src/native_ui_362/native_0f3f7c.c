typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef struct {u16 x,y;} CoordinatePair;
typedef struct {u16 phase,unused2;const CoordinatePair *coordinates;u8 unused8[12];u8 delay,unused21;u16 mode;} SceneEvent;
typedef struct {u16 value;u8 rest[10];} ScalarRamp;
typedef struct {u8 mode,delay;s16 x,y;u16 unused6;void *handles[2];ScalarRamp ramp;} SceneWork;
extern void *CreateSceneResource(const void *,u32,int,int,u32,u32,u32,u32) __asm__("0x080d5cc0");
extern void SetResourceSortKey(void *,u32) __asm__("0x08011058");
extern void StartRamp(ScalarRamp *,int,int,u32) __asm__("0x080e0608");
extern void AdvanceRamp(ScalarRamp *) __asm__("0x080e064c");
extern u32 IsRampComplete(ScalarRamp *) __asm__("0x080e0690");
extern void *AdvanceResource(void *) __asm__("0x08011484");
extern void SetResourcePosition(void *,int,int,u32) __asm__("0x080107d4");
extern void ReleaseResources(void **,u32) __asm__("0x080d5f74");
u32 RemainingBand43_000F3F7C(void *unused,SceneEvent *event,SceneWork *work)
{
 switch(event->phase) {
 case 0: {
  const CoordinatePair *coordinates=event->coordinates;
  work->delay=event->delay+1;
  work->mode=event->mode;
  work->x=coordinates->x;
  work->y=0xffccu+coordinates->y;
  break;
 }
 case 256: {
  u8 remaining=--work->delay;
  if(remaining==0) {
   const void *resource=(const void *)0x084f6130;
   u32 tile;
   u32 sortBase;
   work->handles[0]=CreateSceneResource(resource,6,work->x,work->y,({tile=845;tile;}),6,1,remaining);
   work->handles[1]=CreateSceneResource(resource,7,work->x,work->y,tile,6,1,remaining);
   SetResourceSortKey(work->handles[0],({u32 mode=work->mode;sortBase=4;sortBase-mode;}));
   SetResourceSortKey(work->handles[1],sortBase-work->mode);
   StartRamp(&work->ramp,work->y,(s16)((u16)work->y+40),34);
   ++event->phase;
  }
  break;
 }
 case 257: {
  register ScalarRamp *advanceInput __asm__("r4")=&work->ramp;
  ScalarRamp *ramp;
  u8 index;
  void **handles;
  __asm__("" : "+r"(advanceInput));
  AdvanceRamp(advanceInput);
  index=0;
  __asm__("" : "+r"(advanceInput));
  ramp=advanceInput;
  handles=work->handles;
  do {
   void **slot=&handles[index];
   void *updated=AdvanceResource(*slot);
   *slot=updated;
   if(updated!=0)SetResourcePosition(updated,work->x,(s16)work->ramp.value,0);
   ++index;
  } while(index<=1);
  if((u8)IsRampComplete(ramp)!=0)++event->phase;
  break;
 }
 case 258:
  ReleaseResources(work->handles,2);
  event->phase=2;
  break;
 }
 return 0;
}
