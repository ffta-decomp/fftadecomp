typedef unsigned char u8;typedef unsigned short u16;typedef unsigned int u32;typedef signed int s32;
typedef struct {u8 unknown0[6],complete;}SceneOwner;
typedef struct {u16 phase,pad2;SceneOwner *owner;u8 unknown8[12];u16 first_variant,second_variant;u32 unknown24;}Event;
typedef struct {SceneOwner *owner;u32 unknown4;void *resource;u8 timer,first_variant,second_variant,unknown15;u8 transfer16[28],transfer44[28],fill72[28],unknown100[80];}Work;
typedef struct {volatile u16 control;u8 unknown2[72];volatile u8 first,second;u8 unknown76[2];volatile u8 third;}Shadow;
typedef struct {u8 unknown0[16];u8 *first,*second;}BufferBank;
typedef void (*ClearFunction)(void*,u32);
extern Shadow DisplayShadow asm("0x03000940");
extern BufferBank BankA asm("0x03000990"),BankB asm("0x030008b0");
extern ClearFunction const CurrentClearFunction asm("0x0836d4b8");
extern u8 PrimaryScheduler[1] asm("0x03002710"),SecondaryScheduler[4] asm("0x030027e0");
extern void PrepareSceneSubsystem(void) asm("0x0801db79"),RefreshSubsystem(void) asm("0x081452f5"),PrepareSecondarySubsystem(void) asm("0x08148541"),CompleteSceneSubsystem(void) asm("0x080231c1"),ActivateSubsystem(void) asm("0x08145799");
extern void ConfigureSubsystemMode(u32) asm("0x0802292d");
extern void CallClear(void*,u32,ClearFunction) asm("0x0814224d");
extern void InitializeFill(void*,u32,void*,u32) asm("0x08000b69"),InitializeTransfer(void*,void*,void*,u32) asm("0x08000b21");
extern void ClearSchedulerGroup(void*,u32) asm("0x08006be1");
extern void ConfigureLayer(u32,u32,u32,u32,u32,void*,void*) asm("0x0801e459");
extern void *CreateResource(u32) asm("0x08121b65");
extern void ReleaseResource(void*) asm("0x08121b79");
extern void ConfigureResource(void*,u32,u32,void*,void*,u32,u32,u32,u32,u32) asm("0x0801174d");
extern u32 ResourceReady(void) asm("0x08011861");
extern void ConfigureDisplayMode(u32) asm("0x0801339d");
s32 AdvanceSceneTransitionCommand(void*,Event*,Work*) asm("CoreRegion_00126118");
s32 AdvanceSceneTransitionCommand(void *unused,Event *event,Work *work)
{
 s32 phase=event->phase;
 u32 next_phase;
 switch(phase){
 case 1:
  if(work->resource!=0){ReleaseResource(work->resource);work->resource=0;}
  break;
 case 0:
  work->owner=event->owner;
  work->first_variant=event->first_variant;
  work->second_variant=event->second_variant;
  PrepareSceneSubsystem();RefreshSubsystem();PrepareSecondarySubsystem();
  ConfigureSubsystemMode(2);
  {
   ClearFunction const *clear_cell=&CurrentClearFunction;
   void *destination=(void*)0x030039a0;
   CallClear(destination,32,*clear_cell);
  }
  InitializeFill(work->fill72,0x11111111,BankA.first+32,8);
  InitializeTransfer(work->transfer44,0,BankA.second,640);
  {
   volatile u8 *shadow_base=(volatile u8*)&DisplayShadow;
   volatile u8 *cursor=shadow_base+74;
   (void)*cursor;(void)*cursor;*cursor=255;
   cursor++;(void)*cursor;*cursor=phase;
   asm volatile("" : "+r"(shadow_base));
   shadow_base+=78;(void)*shadow_base;*shadow_base=16;
  }
  break;
 case 256:{
  u32 layer_flags;
  InitializeTransfer(work->transfer16,0,BankB.second,640);
  layer_flags=0;
  asm volatile("" : "+r"(layer_flags));
  work->timer=8;
  {
   volatile u16 *control=&DisplayShadow.control;
   volatile u8 *shadow_base=(volatile u8*)control;
   volatile u8 *cursor;
   register u32 control_working asm("r0");
   register u32 shadow_zero asm("r5");
   /* H0 read, enable-mask working value and independent clear zero. */
   asm volatile(
    "ldrh r1, [%2]\n\t"
    "mov r3, #192\n\t"
    "lsl r3, r3, #4\n\t"
    "add %0, r3, #0\n\t"
    "mov %1, #0\n\t"
    "orr %0, r1"
    : "=&r"(control_working), "=&r"(shadow_zero)
    : "r"(control), "m"(*control)
    : "r1", "r3", "cc");
   control_working&=0x8cff;
   asm volatile("" : "+r"(control_working));
   *control=control_working;
   cursor=shadow_base+74;(void)*cursor;*cursor=shadow_zero;
   cursor++;(void)*cursor;*cursor=shadow_zero;
   asm volatile("" : "+r"(shadow_base));
   {
    register volatile u8 *third asm("r0")=shadow_base+78;
    asm volatile("" : "+r"(third));
    (void)*third;*third=shadow_zero;
   }
  ClearSchedulerGroup(PrimaryScheduler,0);
  ClearSchedulerGroup(PrimaryScheduler,3);
  ClearSchedulerGroup(PrimaryScheduler,4);
  ClearSchedulerGroup(PrimaryScheduler,2);
  ClearSchedulerGroup(PrimaryScheduler,5);
  ClearSchedulerGroup(PrimaryScheduler,6);
  ClearSchedulerGroup(PrimaryScheduler,7);
  SecondaryScheduler[3]=shadow_zero;ClearSchedulerGroup(SecondaryScheduler,0);
  }
  ConfigureLayer(2,0,0,0,layer_flags,(void*)0x06008000,(void*)0x06005800);
  ConfigureLayer(3,0,0,0,layer_flags,(void*)0x06008000,(void*)0x06005000);
  next_phase=257;goto store_phase;
 }
 case 257:{
  u32 timer=work->timer;
  if(timer!=0){timer--;work->timer=timer;if((u8)timer!=0)break;}
  next_phase=258;goto store_phase;
 }
 case 258:
  work->resource=CreateResource(0xa04);
  ConfigureResource(work->resource,1,36,&BankB,&BankA,2,2,24,4,928);
  ConfigureDisplayMode(2);
  event->phase=259;
  break;
 case 259:
  if((u16)ResourceReady()==0)break;
  ActivateSubsystem();RefreshSubsystem();
  work->timer=64;
  next_phase=260;goto store_phase;
 case 260:{
  u32 timer=work->timer;
  if(timer!=0){timer--;work->timer=timer;if((u8)timer!=0)break;}
  ReleaseResource(work->resource);work->resource=0;
  next_phase=261;goto store_phase;
 }
 case 261:{
  register SceneOwner *owner asm("r0");
  CompleteSceneSubsystem();
  owner=work->owner;
  asm volatile("" : "+r"(owner));
  owner->complete=1;
  next_phase=3;
 }
store_phase:event->phase=next_phase;
  break;
 }
 return 0;
}
