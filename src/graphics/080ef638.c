typedef unsigned char u8; typedef unsigned short u16; typedef signed short s16; typedef unsigned int u32; typedef signed int s32;
typedef struct { s16 value;u16 opaque[5]; } Ramp;
typedef struct {u16 phase,pad;void *record;} Event;
typedef struct {s16 x,y;u16 timer,pad;Ramp ramp;void *record,*object;u32 unknown;void *blend,*scan,*child;} Work;
extern void *RetailCall_080dd4c4(void*) __asm__("RetailCall_080dd4c4");
extern void *RetailCall_080dc1e8(void*,u32,u32,u32,void*,void*,void*) __asm__("RetailCall_080dc1e8");
extern void *RetailCall_080dba5c(void*) __asm__("RetailCall_080dba5c");
extern u32 RetailCall_08003a74(void*) __asm__("RetailCall_08003a74"),RetailCall_08003a80(void*) __asm__("RetailCall_08003a80");
extern void RetailCall_080034b8(u32,u32) __asm__("RetailCall_080034b8");
extern u32 RetailCall_080035a8(u32) __asm__("RetailCall_080035a8");
extern void RetailCall_080dbdc8(void*,s16*,s16*) __asm__("RetailCall_080dbdc8");
extern void RetailCall_080dc224(void*,s32,s32,s16*,s16*) __asm__("RetailCall_080dc224");
extern void RetailCall_08003508(s32,u32) __asm__("RetailCall_08003508"),RetailCall_08003558(s32,u32) __asm__("RetailCall_08003558");
extern void RetailCall_080e0608(Ramp*,s32,s32,s32) __asm__("RetailCall_080e0608"),RetailCall_080e064c(Ramp*) __asm__("RetailCall_080e064c");
extern u32 RetailCall_080e0690(Ramp*) __asm__("RetailCall_080e0690"),RetailCall_080dd580(void*) __asm__("RetailCall_080dd580");
extern void *RetailCall_080d9914(u32,u32,void*) __asm__("RetailCall_080d9914");
extern u32 RetailCall_080d499c(u32,u32) __asm__("RetailCall_080d499c");
extern u16 *RetailCall_080d996c(void*) __asm__("RetailCall_080d996c");
extern void RetailCall_080d9ba8(void*,u32) __asm__("RetailCall_080d9ba8");
extern void *RetailCall_080d3e9c(const void*,void*) __asm__("RetailCall_080d3e9c"),*RetailCall_080d3f08(void*) __asm__("RetailCall_080d3f08"),*RetailCall_080d9b64(void*) __asm__("RetailCall_080d9b64");
#define SHADOW (*(u16*)0x03000940)
#define ADVANCE() do {register u32 next asm("r0")=event->phase+1;asm volatile("" : "+r"(next));next_phase=next;goto store_phase;}while(0)
s32 RemainingBand43_000EF638(void *parent,Event *event,Work *work)
{
 s16 initial_x,initial_y,moving_y,returning_y;
 s32 phase=event->phase;
 s32 next_phase;
 switch((s32)phase){
 case 0:
  work->record=event->record;
  work->object=RetailCall_080dd4c4(work->record);
  work->timer=36;
  break;
 case 1:break;
 case 256:{
  u32 timer=work->timer-1;
  work->timer=timer;
  if((u16)timer==0){
   work->child=RetailCall_080dc1e8(work->object,0,0,7,(void*)0x0600ee40,(void*)0x06005800,parent);
   work->timer=66;
   ADVANCE();
  }
  break;
 }
 case 257:{
  u32 timer=work->timer;
  void *child;
  if(timer!=0)work->timer=timer-1;
  child=RetailCall_080dba5c(work->child);
  work->child=child;
  if(child!=0)break;
  if(work->timer!=0)break;
  {
   u32 first=RetailCall_08003a74((void*)0x06005800);
   u32 combined=(u16)(first|RetailCall_08003a80((void*)0x06008000));
   u32 mask;
   RetailCall_080034b8(combined,2);
   mask=RetailCall_080035a8(2);
   {register u32 control asm("r1")=SHADOW;asm("" : "+r"(control));control|=mask;SHADOW=control;}
  }
  RetailCall_080dbdc8(work->object,&work->x,&work->y);
  RetailCall_080dc224(work->object,work->x,work->y,&initial_x,&initial_y);
  RetailCall_08003508(initial_x,2);
  RetailCall_08003558(initial_y,2);
  RetailCall_080e0608(&work->ramp,work->y,(s16)((u16)work->y-24),72);
  work->blend=RetailCall_080d3e9c((void*)0x0894d810,parent);
  ADVANCE();
 }
 case 258:{
  Ramp *ramp=&work->ramp;
  RetailCall_080e064c(ramp);
  RetailCall_080dc224(work->object,work->x,work->ramp.value,0,&moving_y);
  RetailCall_08003558(moving_y,2);
  if((u8)RetailCall_080e0690(ramp)){
   work->timer=8;ADVANCE();
  }
  break;
 }
 case 259:{
  u32 timer=work->timer-1;
  work->timer=timer;
  if((u16)timer!=0)break;
  if((u8)RetailCall_080dd580(work->record)){
   void *scan=RetailCall_080d9914(2,0,parent);
   u16 base=RetailCall_080d499c(2,0);
   u16 *buffer=RetailCall_080d996c(scan);
   u16 row=0;
   register Ramp *ramp asm("r8")=&work->ramp;
   asm("" : "+r"(ramp));
   do{buffer[row]=base;row++;}while(row<=159);
   RetailCall_080d9ba8(scan,1);
   work->scan=scan;
   RetailCall_080e0608(ramp,0,80,36);
   work->timer=18;
   next_phase=260;
  }else{
   register Ramp *else_ramp asm("r0")=&work->ramp;
   register s32 start_y asm("r1");
   u16 y;
   asm("" : "+l"(else_ramp));
   y=work->y;
   start_y=(s16)(y-24);
   asm("" : : "l"(start_y));
   RetailCall_080e0608(else_ramp,start_y,(s16)(y-8),36);
   next_phase=261;
  }
  goto store_phase;
 }
 case 260:{
  u16 previous=work->ramp.value;
  Ramp *ramp=&work->ramp;
  register Ramp *later_ramp asm("r8");
  register s32 current asm("r0");
  register s32 prior_signed asm("r4");
  RetailCall_080e064c(ramp);
  prior_signed=(s16)previous;
  asm("" : "+l"(prior_signed));
  current=work->ramp.value;
  asm("" : "+l"(current));
  later_ramp=ramp;
  asm("" : "+r"(later_ramp));
  if(prior_signed!=current){
   u16 *buffer=RetailCall_080d996c(work->scan);
   u16 start=work->y-72;
   u32 row=0;
   register u32 last_timer asm("r1");
   do{
    u16 *slot;
    u32 value;
    {register u32 parity asm("r0")=1;
     asm volatile("and %0, %1" : "+l"(parity) : "l"(row) : "cc");
     if(parity){asm volatile("add %0, %1, %2\n\tlsl %0, %0, #1\n\tadd %0, %0, %3" : "=&l"(slot) : "l"(row), "l"((u32)start), "l"(buffer) : "cc");value=*slot+1;}
     else {asm volatile("add %0, %1, %2\n\tlsl %0, %0, #1\n\tadd %0, %0, %3" : "=&l"(slot) : "l"(row), "l"((u32)start), "l"(buffer) : "cc");value=*slot-1;}}
    *slot=value;
    last_timer=work->timer;
    asm("" : : "l"(last_timer));
    if(row>=((u32)last_timer>>1))break;
    row=(u16)(row+1);
   }while(row<=55);
   {register u32 timer_next asm("r0")=last_timer+2;
    asm("" : "+l"(timer_next));
    work->timer=timer_next;}
  }
  if((u8)RetailCall_080e0690(later_ramp)){
   SHADOW&=~RetailCall_080035a8(2);
   ADVANCE();
  }
  break;
 }
 case 261:{
  Ramp *ramp=&work->ramp;
  RetailCall_080e064c(ramp);
  RetailCall_080dc224(work->object,work->x,work->ramp.value,0,&returning_y);
  RetailCall_08003558(returning_y,2);
  if((u8)RetailCall_080e0690(ramp)){
   SHADOW&=~RetailCall_080035a8(2);ADVANCE();
  }
  break;
 }
 case 262:{
  void *blend=RetailCall_080d3f08(work->blend);
  work->blend=blend;
  if(blend==0){
   void *scan=RetailCall_080d9b64(work->scan);
   work->scan=scan;
   if(scan==0){
    next_phase=2;
store_phase:
    event->phase=next_phase;
   }
  }
  break;
 }
 }
 return 0;
}

__asm__(
".global RetailCall_080dd4c4\n.thumb_set RetailCall_080dd4c4,0x080dd4c5\n"
".global RetailCall_080dc1e8\n.thumb_set RetailCall_080dc1e8,0x080dc1e9\n"
".global RetailCall_080dba5c\n.thumb_set RetailCall_080dba5c,0x080dba5d\n"
".global RetailCall_08003a74\n.thumb_set RetailCall_08003a74,0x08003a75\n"
".global RetailCall_08003a80\n.thumb_set RetailCall_08003a80,0x08003a81\n"
".global RetailCall_080034b8\n.thumb_set RetailCall_080034b8,0x080034b9\n"
".global RetailCall_080035a8\n.thumb_set RetailCall_080035a8,0x080035a9\n"
".global RetailCall_080dbdc8\n.thumb_set RetailCall_080dbdc8,0x080dbdc9\n"
".global RetailCall_080dc224\n.thumb_set RetailCall_080dc224,0x080dc225\n"
".global RetailCall_08003508\n.thumb_set RetailCall_08003508,0x08003509\n"
".global RetailCall_08003558\n.thumb_set RetailCall_08003558,0x08003559\n"
".global RetailCall_080e0608\n.thumb_set RetailCall_080e0608,0x080e0609\n"
".global RetailCall_080e064c\n.thumb_set RetailCall_080e064c,0x080e064d\n"
".global RetailCall_080e0690\n.thumb_set RetailCall_080e0690,0x080e0691\n"
".global RetailCall_080dd580\n.thumb_set RetailCall_080dd580,0x080dd581\n"
".global RetailCall_080d9914\n.thumb_set RetailCall_080d9914,0x080d9915\n"
".global RetailCall_080d499c\n.thumb_set RetailCall_080d499c,0x080d499d\n"
".global RetailCall_080d996c\n.thumb_set RetailCall_080d996c,0x080d996d\n"
".global RetailCall_080d9ba8\n.thumb_set RetailCall_080d9ba8,0x080d9ba9\n"
".global RetailCall_080d3e9c\n.thumb_set RetailCall_080d3e9c,0x080d3e9d\n"
".global RetailCall_080d3f08\n.thumb_set RetailCall_080d3f08,0x080d3f09\n"
".global RetailCall_080d9b64\n.thumb_set RetailCall_080d9b64,0x080d9b65\n"
);
