typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
typedef struct { u16 phase,pad; void *actor;u32 unknown8,flags,unknown16;u16 definition,variant;u32 unknown24;} Event;
typedef struct {u8 count,ordinal,delay,variant;void *children[2],*opening,*actor;} Work;
extern void *OpenSequence(void*,const void*,u32,u32,const void*,void*) asm("0x080e03f9");
extern void Cleanup(void) asm("0x080d38b5");
extern void *Poll(void*) asm("0x080e05dd");
extern u32 CountTargets(void*,u32) asm("0x080d8859");
extern u32 PollChildren(void**,u32) asm("0x080e0571");
extern void *GetTarget(void*,u32) asm("0x080dd4a5");
extern void *CreateCallback(void*,u32,const void*,void*) asm("0x08005b6d");
#define ADVANCE() do {register s32 advanced_phase asm("r0")=event->phase+1;asm volatile("" : "+r"(advanced_phase));next_phase=advanced_phase;goto store_phase;}while(0)
s32 OriginalAuthoredAction_000EF37C(void *parent,Event *event,Work *work)
{
 Event child_event;
 s32 phase=event->phase,next_phase;
 switch(phase){
 case 0:{
  u32 count;
  u32 variant=event->variant;
  void *actor;
  work->variant=variant;
  actor=event->actor;
  work->actor=actor;
  count=2;
  if((u8)variant!=0)count=0;
  work->opening=OpenSequence(actor,(void*)0x08399a3c,count,1,(void*)phase,parent);
  break;
 }
 case 1:Cleanup();break;
 case 256:{
  void *opening=Poll(work->opening);
  u32 count;
  work->opening=opening;
  if(opening!=0)break;
  count=CountTargets(work->actor,0);
  work->count=count;
  if((u8)count==0){next_phase=2;goto store_phase;}
  work->delay=1;
  ADVANCE();
 }
 case 257:{
  void **children=work->children;
  u32 delay,bits,slot,advanced;
  void *created;
  PollChildren(children,2);
  delay=work->delay-1;
  work->delay=delay;
  if((u8)delay!=0)break;
  bits=(u32)work->children[0];
  slot=((0U-bits)|bits)>>31;
  child_event.actor=GetTarget(work->actor,work->ordinal);
  created=CreateCallback((void*)0x080ef235,40,&child_event,parent);
  {
   void **destination=children+slot;
   *destination=created;
  }
  work->delay=50;
  advanced=work->ordinal+1;
  work->ordinal=advanced;
  if((u8)advanced==work->count)ADVANCE();
  break;
 }
 case 258:
  if((u8)PollChildren(work->children,2)){
   next_phase=2;
store_phase:
   event->phase=next_phase;
  }
  break;
 }
 return 0;
}
