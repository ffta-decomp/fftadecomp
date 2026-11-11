typedef unsigned char u8;typedef unsigned short u16;typedef signed short s16;typedef unsigned int u32;typedef signed int s32;
typedef struct {u16 phase,pad;void *actor;u32 unknown8,flags,unknown16;u16 definition,variant;u32 unknown24;} Event;
typedef struct {s16 x,y;u8 unknown4,variant,flag,completion,unknown8,count,delay,unknown11;u16 index,unknown14;void *children[4],*record,*blend,*palette_a,*palette_b,*actor,*opening,*script;u32 unknown60,unknown64;void *stage;} Work;
extern void *RetailCall_080e03f8(void*,const void*,u32,u32,const void*,void*) __asm__("0x080e03f9");
extern void RetailCall_080d38b4(void) __asm__("0x080d38b5");
extern void *RetailCall_080e05dc(void*) __asm__("0x080e05dd");
extern u32 RetailCall_080d8858(void*,u32) __asm__("0x080d8859");
extern void *RetailCall_080ddf68(void*,void**,u32,u32,u8*,const void*,u32,u32,void*) __asm__("0x080ddf69");
extern void RetailCall_080dbdc8(void*,s16*,s16*) __asm__("0x080dbdc9");
extern void *RetailCall_080dfd8c(const void*,u32,u32,u32,void*) __asm__("0x080dfd8d");
extern void RetailCall_080d7220(const void*,u32,u32,s32,s32,u32) __asm__("0x080d7221");
extern void *RetailCall_080d3e9c(const void*,void*) __asm__("0x080d3e9d"),*RetailCall_080d4704(const void*,void*) __asm__("0x080d4705");
extern void *RetailCall_080d3f08(void*) __asm__("0x080d3f09"),*RetailCall_080d4774(void*) __asm__("0x080d4775");
extern u32 RetailCall_080035a8(u32) __asm__("0x080035a9"),RetailCall_080e0570(void**,u32) __asm__("0x080e0571");
extern void *RetailCall_080dd4a4(void*,u32) __asm__("0x080dd4a5"),*RetailCall_08005b6c(void*,u32,const void*,void*) __asm__("0x08005b6d");
extern u32 RetailCall_080de1f0(void*) __asm__("0x080de1f1");

typedef struct {u16 control;} Shadow;
extern Shadow DisplayShadow __asm__("0x03000940");
#define ADVANCE() do {register s32 advanced_phase asm("r0")=event->phase+1;asm volatile("" : "+r"(advanced_phase));next_phase=advanced_phase;goto store_phase;}while(0)
s32 OriginalAuthoredAction_001083EC(void *parent,Event *event,Work *work)
{
 Event child_event;
 s32 phase=event->phase,next_phase;
 switch(phase){
 case 0:{
  u32 variant=event->variant;
  u32 count;
  work->variant=variant;
  work->actor=event->actor;
  count=2;
  if((u8)variant!=0)count=0;
  if(event->flags&2)work->flag=1;
  work->opening=RetailCall_080e03f8(work->actor,(void*)0x083a0ef4,count,0,(void*)phase,parent);
  break;
 }
 case 1:RetailCall_080d38b4();break;
 case 256:{
  void *opening=RetailCall_080e05dc(work->opening);
  u32 count,parameter;
  work->opening=opening;
  if(opening!=0)break;
  count=RetailCall_080d8858(work->actor,0);
  work->count=count;
  if((u8)count==0){next_phase=2;goto store_phase;}
  parameter=92;
  if(work->flag!=0)parameter=148;
  work->script=RetailCall_080ddf68(work->actor,&work->record,parameter,1,&work->completion,(void*)0x083a0f34,(u32)opening,(u32)opening,parent);
  RetailCall_080dbdc8(work->record,&work->x,&work->y);
  work->stage=RetailCall_080dfd8c((void*)0x083a0f38,1,4,0,parent);
  ADVANCE();
 }
 case 257:
  if(work->completion==0)break;
  RetailCall_080d7220((void*)0x088f5b18,0,2,work->x,(s16)((u16)work->y-12),0);
  work->blend=RetailCall_080d3e9c((void*)0x0894dc70,parent);
  work->palette_a=RetailCall_080d4704((void*)0x0894bf74,parent);
  work->palette_b=RetailCall_080d4704((void*)0x0894848c,parent);
  work->stage=RetailCall_080dfd8c((void*)0x083a0f40,1,4,0,parent);
  ADVANCE();
 case 258:{
  void *blend=RetailCall_080d3f08(work->blend);
  void *palette;
  work->blend=blend;
  if(blend!=0)break;
  palette=RetailCall_080d4774(work->palette_a);
  work->palette_a=palette;
  if(palette!=0)break;
  DisplayShadow.control&=~RetailCall_080035a8(2);
  palette=RetailCall_080d4774(work->palette_b);
  work->palette_b=palette;
  if(palette!=0)break;
  work->delay=1;
  ADVANCE();
 }
 case 259:{
  void **children=work->children;
  u32 delay;
  void *created;
  u32 advanced;
  RetailCall_080e0570(children,4);
  delay=work->delay-1;
  work->delay=delay;
  if((u8)delay!=0)break;
  {
   Event *child_event_out=&child_event;
   u32 index=work->index;
   child_event_out->definition=index;
   child_event_out->actor=RetailCall_080dd4a4(work->actor,(u8)index);
   created=RetailCall_08005b6c((void*)0x0810835d,24,child_event_out,parent);
  }
  {
   void **destination=children+work->index;
   *destination=created;
  }
  work->delay=30;
  advanced=work->index+1;
  work->index=advanced;
  if((u16)advanced==work->count)ADVANCE();
  break;
 }
 case 260:
  if((u8)RetailCall_080e0570(work->children,4))ADVANCE();
  break;
 case 261:
  if((u8)RetailCall_080de1f0(work->record)){
   next_phase=2;
store_phase:
   event->phase=next_phase;
  }
  break;
 }
 return 0;
}
