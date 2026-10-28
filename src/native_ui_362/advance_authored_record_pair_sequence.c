typedef unsigned char u8;typedef signed char s8;typedef unsigned short u16;typedef signed short s16;typedef unsigned int u32;typedef signed int s32;
typedef struct {u16 phase,pad;void *actor;u32 opaque[3];u16 definition,variant;u32 unknown24;} Event;
typedef struct {s16 x,y;u8 variant,completion,unknown6;s8 count;u8 delay,pad;u16 index;u8 first_out[12];void *positioned_a;u8 second_out[8];void *positioned_b,*model,*blend,*palettes[2];u32 unknown56;void *children[4],*record,*actor,*opening,*script,*stage;} Work;
extern void *RetailCall_080e03f8(void*,const void*,u32,u32,const void*,void*) __asm__("0x080e03f9");
extern void RetailCall_080d38b4(void) __asm__("0x080d38b5");
extern void *RetailCall_080e05dc(void*) __asm__("0x080e05dd");
extern u32 RetailCall_080dd494(void*) __asm__("0x080dd495");
extern void *RetailCall_080ddf68(void*,void**,u32,u32,u8*,const void*,u32,u32,void*) __asm__("0x080ddf69");
extern void RetailCall_080dbdc8(void*,s16*,s16*) __asm__("0x080dbdc9"),RetailCall_080d49fc(u32,u32,u32,s32,s32) __asm__("0x080d49fd");
extern void *RetailCall_080d4b64(u32,const void*,u32,u32) __asm__("0x080d4b65");
extern void RetailCall_0800bda4(void*,u32) __asm__("0x0800bda5");
extern u32 RetailCall_080035a8(u32) __asm__("0x080035a9");
extern void *RetailCall_080d3e9c(const void*,void*) __asm__("0x080d3e9d"),*RetailCall_080d3f08(void*) __asm__("0x080d3f09"),*RetailCall_080d4704(const void*,void*) __asm__("0x080d4705");
extern void RetailCall_080d47a0(void*,u32) __asm__("0x080d47a1");
extern void *RetailCall_080d6098(s32,s32,s32,u32,u32,void*,const void*,void*) __asm__("0x080d6099");
extern u32 RetailCall_080dbc88(void*) __asm__("0x080dbc89");
extern void RetailCall_0800be10(void*,u32) __asm__("0x0800be11"),RetailCall_080d6194(void*,u32) __asm__("0x080d6195");
extern void *RetailCall_080dfd8c(const void*,u32,u32,u32,void*) __asm__("0x080dfd8d");
extern void RetailCall_080d4938(void**,u32) __asm__("0x080d4939"),RetailCall_080d4d14(void*,u32) __asm__("0x080d4d15");
extern void *RetailCall_080d6134(void*) __asm__("0x080d6135");
extern u32 RetailCall_080d8858(void*,u32) __asm__("0x080d8859"),RetailCall_080e0570(void**,u32) __asm__("0x080e0571");
extern void *RetailCall_080dd4a4(void*,u32) __asm__("0x080dd4a5"),*RetailCall_08005b6c(void*,u32,const void*,void*) __asm__("0x08005b6d");
extern u32 RetailCall_080de1f0(void*) __asm__("0x080de1f1");

typedef struct {u16 control;} Shadow;
extern Shadow DisplayShadow __asm__("0x03000940");
#define ADVANCE() do {register s32 advanced_phase asm("r0")=event->phase+1;asm volatile("" : "+r"(advanced_phase));next_phase=advanced_phase;goto store_phase;}while(0)
s32 OriginalAuthoredAction_000FC13C(void *parent,Event *event,Work *work)
{
 Event child_event;
 s32 phase=event->phase,next_phase;
 switch(phase){
 case 0:{
  u32 variant=event->variant;
  void *actor;
  u32 count;
  work->variant=variant;
  actor=event->actor;
  work->actor=actor;
  count=6;
  if((u8)variant!=0)count=0;
  work->opening=RetailCall_080e03f8(actor,(void*)0x0839d1c8,count,0,(void*)phase,parent);
  break;
 }
 case 1:RetailCall_080d38b4();break;
 case 256:{
  void *opening=RetailCall_080e05dc(work->opening);
  work->opening=opening;
  if(opening!=0)break;
  {
   u32 variant=work->variant;
   if(variant!=0){
    work->count=RetailCall_080dd494(work->actor);
    work->delay=1;
    next_phase=260;goto store_phase;
   }else{
    work->script=RetailCall_080ddf68(work->actor,&work->record,148,1,&work->completion,(void*)0x0839d2cc,variant,variant,parent);
    RetailCall_080dbdc8(work->record,&work->x,&work->y);
    ADVANCE();
   }
  }
 }
 case 257:{
  void *model;
  if(work->completion==0)break;
  RetailCall_080d49fc(0,2,0,work->x,work->y);
  model=RetailCall_080d4b64(0,(void*)0x088edb7c,966,6);
  work->model=model;
  RetailCall_0800bda4(model,1);
  {
   u32 mask=RetailCall_080035a8(2);
   register u32 control asm("r1")=DisplayShadow.control;
   asm("" : "+r"(control));
   control|=mask;
   DisplayShadow.control=control;
  }
  work->blend=RetailCall_080d3e9c((void*)0x0894d7bc,parent);
  work->palettes[0]=RetailCall_080d4704((void*)0x08949554,parent);
  work->palettes[1]=RetailCall_080d4704((void*)0x08949564,parent);
  RetailCall_080d47a0(work->palettes[0],1);
  RetailCall_080d47a0(work->palettes[1],1);
  work->positioned_a=RetailCall_080d6098(work->x,work->y,0,1,3,work->first_out,(void*)0x0839d210,parent);
  if((s8)RetailCall_080dbc88(work->record)>1){
   RetailCall_0800be10(work->model,1);
   RetailCall_080d6194(work->positioned_a,1);
  }
  work->stage=RetailCall_080dfd8c((void*)0x0839d2d0,2,4,0,parent);
  work->index=30;
  ADVANCE();
 }
 case 258:{
  u32 index=work->index-1;
  work->index=index;
  if((u16)index!=0)break;
  work->positioned_b=RetailCall_080d6098(work->x,work->y,0,1,2,work->second_out,(void*)0x0839d258,parent);
  ADVANCE();
 }
 case 259:{
  void *old_blend=work->blend;
  u32 bits=(u32)old_blend;
  u32 had_blend=((0U-bits)|bits)>>31;
  void *blend=RetailCall_080d3f08(old_blend);
  void *positioned;
  u32 count;
  work->blend=blend;
  if(blend!=0)break;
  if(had_blend!=0){
   RetailCall_080d4938(work->palettes,2);
   RetailCall_080d4d14(work->model,0);
   work->model=blend;
   DisplayShadow.control&=~RetailCall_080035a8(2);
  }
  positioned=RetailCall_080d6134(work->positioned_a);
  work->positioned_a=positioned;
  if(positioned!=0)break;
  positioned=RetailCall_080d6134(work->positioned_b);
  work->positioned_b=positioned;
  if(positioned!=0)break;
  count=RetailCall_080d8858(work->actor,0);
  work->count=count;
  if((s32)(count<<24)<=0){next_phase=261;goto store_phase;}
  work->delay=1;ADVANCE();
 }
 case 260:{
  void **children=work->children;
  u32 delay,index;
  void *created;
  RetailCall_080e0570(children,4);
  delay=work->delay-1;
  work->delay=delay;
  if((u8)delay!=0)break;
  {
   Event *child_event_out=&child_event;
   index=work->index;
   child_event_out->definition=index;
   child_event_out->actor=RetailCall_080dd4a4(work->actor,(u8)index);
   created=RetailCall_08005b6c((void*)0x080fc059,36,child_event_out,parent);
  }
  {
   void **destination=children+work->index;
   *destination=created;
  }
  work->delay=30;
  work->index++;
  if(work->index==work->count)ADVANCE();
  break;
 }
 case 261:
  if((u8)RetailCall_080de1f0(work->record)){
   if((u8)RetailCall_080e0570(work->children,4)){
    next_phase=2;
store_phase:
    event->phase=next_phase;
   }
  }
  break;
 }
 return 0;
}
