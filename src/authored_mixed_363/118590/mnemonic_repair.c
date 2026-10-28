typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef struct {u16 phase,unused2; void *record;} SceneEvent;
typedef struct {u16 value;u8 rest[10];} ScalarRamp;
typedef struct {s16 x,y;u16 timer,unused6;void *handles[3];ScalarRamp ramps[3];void *record;} SceneWork;
extern void ProjectRecord(void *,s16 *,s16 *) __asm__("0x080d8c58");
extern void *CreateSceneResource(const void *,u32,int,int,u32,u32,u32,u32) __asm__("0x080d5cc0");
extern void SetResourceHidden(void *,u32) __asm__("0x0801115c");
extern void SetResourceFlag8(void *,u32) __asm__("0x080111a8");
extern void SetResourcePosition(void *,int,int,u32) __asm__("0x080107d4");
extern void StartRamp(ScalarRamp *,int,int,u32) __asm__("0x080e0608");
extern void AdvanceRamp(ScalarRamp *) __asm__("0x080e064c");
extern u32 IsRampComplete(ScalarRamp *) __asm__("0x080e0690");
extern void ReleaseResources(void **,u32) __asm__("0x080d5f74");
u32 RemainingBand43_00118590(void *unused,SceneEvent *event,SceneWork *work)
{
 switch(event->phase) {
 case 0: {
  void *record=event->record;
  work->record=record;
  ProjectRecord(record,&work->x,&work->y);
  break;
 }
 case 1: {
  u8 index=0;
  void **handles=work->handles;
  do {
   u32 slot=(u32)index*4;
   __asm__("add %0, %1, %0" : "+l"(slot) : "l"(handles) : "cc");
   if(*(void **)slot!=0)for(;;){}
   ++index;
  } while(index<=2);
  break;
 }
 case 256: {
  u8 index=0;
  void **handles=work->handles;
  ScalarRamp *first=&work->ramps[0];
  ScalarRamp *second=&work->ramps[1];
  ScalarRamp *third=&work->ramps[2];
  do {
   void *created=CreateSceneResource((const void *)0x08501200,index,work->x,work->y,995,6,0,0);
   u32 slot=(u32)index*4;
   __asm__("add %0, %1, %0" : "+l"(slot) : "l"(handles) : "cc");
   *(void **)slot=created;
   SetResourceHidden(created,0);
   SetResourceFlag8(*(void **)slot,1);
   ++index;
  } while(index<=2);
  StartRamp(first,0,84,120);
  StartRamp(second,0,59,120);
  StartRamp(third,0,42,120);
  ++event->phase;
  break;
 }
 case 257: {
  u8 index=0;
  void **handles=work->handles;
  ScalarRamp *first=&work->ramps[0];
  u16 timer;
  do {
   u32 slot;
   AdvanceRamp(&work->ramps[index]);
   slot=(u32)index*4;
   __asm__("add %0, %1, %0" : "+l"(slot) : "l"(handles) : "cc");
   SetResourcePosition(*(void **)slot,work->x,(s16)((u16)work->y-work->ramps[index].value),0);
   ++index;
  } while(index<=2);
  timer=++work->timer;
  if(timer==44) {
   index=0;
   do {u32 slot=(u32)index*4; __asm__("add %0, %1, %0" : "+l"(slot) : "l"(handles) : "cc"); SetResourceHidden(*(void **)slot,1);++index;}while(index<=2);
  } else if(timer==52) {
   index=0;
   do {u32 slot=(u32)index*4; __asm__("add %0, %1, %0" : "+l"(slot) : "l"(handles) : "cc"); SetResourceFlag8(*(void **)slot,0);++index;}while(index<=2);
  }
  if((u8)IsRampComplete(first)!=0) {
   ReleaseResources(handles,3);
   event->phase=2;
  }
  break;
 }
 }
 return 0;
}
