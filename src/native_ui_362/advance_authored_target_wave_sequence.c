typedef unsigned char u8;typedef unsigned short u16;typedef signed short s16;typedef unsigned int u32;typedef signed int s32;
typedef struct {s16 value;u16 opaque[5];} Curve;
typedef union {u32 word;struct{s16 x,y;} pair;} Offset;
typedef struct {u16 phase,pad;void *actor;u32 unknown8,flags;u32 unknown16;u16 definition,variant;u32 unknown24;} Event;
typedef struct {u16 timer;u8 ordinal,count,variant,flag;s16 x,y;u8 completion,pad;void *children[4],*record,*target,*blend,*palette,*wave0,*wave1;Curve first,second;void *script,*child,*opening,*actor,*stage;} Work;
extern void *RetailCall_080e03f8(void*,const void*,u32,u32,const void*,void*) __asm__("0x080e03f9");
extern void RetailCall_080d38b4(void) __asm__("0x080d38b5");
extern void *RetailCall_080e05dc(void*) __asm__("0x080e05dd");
extern u32 RetailCall_080dd494(void*) __asm__("0x080dd495");
extern void *RetailCall_080ddf68(void*,void**,u32,u32,u8*,const void*,u32,u32,void*) __asm__("0x080ddf69");
extern void *RetailCall_080d3e9c(const void*,void*) __asm__("0x080d3e9d"),*RetailCall_080d3f08(void*) __asm__("0x080d3f09");
extern void RetailCall_080dbdc8(void*,s16*,s16*) __asm__("0x080dbdc9");
extern u32 RetailCall_080dbc88(void*) __asm__("0x080dbc89");
extern void RetailCall_080e0608(Curve*,s32,s32,s32) __asm__("0x080e0609"),RetailCall_080e064c(Curve*) __asm__("0x080e064d");
extern u32 RetailCall_080e0690(Curve*) __asm__("0x080e0691");
extern void *RetailCall_080dab84(u32,u32,u32,void*) __asm__("0x080dab85");
extern void RetailCall_080d9ba8(void*,u32) __asm__("0x080d9ba9"),RetailCall_080dac40(void*,s32,s32,u32) __asm__("0x080dac41");
extern void *RetailCall_080dfd8c(const void*,u32,u32,u32,void*) __asm__("0x080dfd8d");
extern void RetailCall_080d4020(void) __asm__("0x080d4021");
extern void *RetailCall_080d4704(const void*,void*) __asm__("0x080d4705"),*RetailCall_080d4774(void*) __asm__("0x080d4775"),*RetailCall_080d9b64(void*) __asm__("0x080d9b65");
extern void *RetailCall_080dd214(void*,u32,u32,void*) __asm__("0x080dd215"),*RetailCall_080dd4a4(void*,u32) __asm__("0x080dd4a5"),*RetailCall_080dd4c4(void*) __asm__("0x080dd4c5");
extern void RetailCall_080db838(void*) __asm__("0x080db839");
extern u32 RetailCall_080d8b4c(void) __asm__("0x080d8b4d"),RetailCall_080e0570(void**,u32) __asm__("0x080e0571"),RetailCall_080dd580(void*) __asm__("0x080dd581");
extern void *RetailCall_08005b6c(void*,u32,const void*,void*) __asm__("0x08005b6d"),*RetailCall_080dba5c(void*) __asm__("0x080dba5d");

typedef struct {Offset rows[4];} OffsetTable;
extern const OffsetTable RecordOffsets __asm__("0x08149ef4");
extern const u8 DefinitionCounts[] __asm__("0x083a1ca0");
extern const void *const DefinitionResources[] __asm__("0x083a1c98");
typedef struct {u16 control;u8 pad[56];volatile u8 b58,b59,b60,b61;u8 b62;volatile u8 b63,b64,b65,b66,b67,b68;} Shadow;
extern Shadow DisplayShadow __asm__("0x03000940");
#define SHADOW (DisplayShadow.control)
s32 OriginalAuthoredAction_0010A850(void *parent,Event *event,Work *work)
{
 OffsetTable offsets;
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
  work->opening=RetailCall_080e03f8(work->actor,(void*)0x083a1c60,count,7,(void*)phase,parent);
  work->count=RetailCall_080dd494(work->actor);
  break;
 }
 case 1:RetailCall_080d38b4();break;
 case 256:{
  void *opening=RetailCall_080e05dc(work->opening);
  work->opening=opening;
  if(opening!=0)break;
  {
   u32 variant=work->variant;
   if(variant!=0){work->timer=20;next_phase=260;goto store_phase;}
   else{
    u32 parameter=84;
    if(work->flag!=0)parameter=52;
    work->script=RetailCall_080ddf68(work->actor,&work->record,parameter,DefinitionCounts[work->flag],&work->completion,DefinitionResources[work->flag],variant,variant,parent);
    {register s32 advanced_phase asm("r0")=event->phase+1;asm volatile("" : "+r"(advanced_phase));next_phase=advanced_phase;}goto store_phase;
   }
  }
 }
 case 257:{
  Shadow *shadow;
  u32 index;
  offsets=RecordOffsets;
  if(work->completion==0)break;
  work->blend=RetailCall_080d3e9c((void*)0x0894de60,parent);
  shadow=&DisplayShadow;
  shadow->b66=31;
  shadow->b67=63;
  shadow->b68=31;
  shadow->b59=0;
  shadow->b58=0;
  shadow->b63=0;
  shadow->b62=255;
  shadow->b61=0;
  shadow->b60=0;
  shadow->b65=0;
  shadow->b64=-1;
  SHADOW|=0x6000;
  RetailCall_080dbdc8(work->record,&work->x,&work->y);
  index=(u8)RetailCall_080dbc88(work->record);
  work->x=(u16)work->x+offsets.rows[index].pair.x;
  work->y=(u16)work->y+offsets.rows[index].pair.y;
  RetailCall_080e0608(&work->first,0,154,80);
  RetailCall_080e0608(&work->second,0,154,76);
  work->timer=4;
  work->wave0=RetailCall_080dab84(1,0,0,parent);
  work->wave1=RetailCall_080dab84(0,0,0,parent);
  RetailCall_080d9ba8(work->wave0,1);
  RetailCall_080d9ba8(work->wave1,1);
  work->stage=RetailCall_080dfd8c((void*)0x083a1ca4,1,4,0,parent);
  {register s32 advanced_phase asm("r0")=event->phase+1;asm volatile("" : "+r"(advanced_phase));next_phase=advanced_phase;}goto store_phase;
 }
 case 258:{
  Curve *first=&work->first;
  u32 timer;
  RetailCall_080e064c(first);
  RetailCall_080dac40(work->wave0,work->x,work->y,(u16)work->first.value);
  timer=work->timer;
  if(timer!=0){work->timer=timer-1;break;}
  {
   Curve *second=&work->second;
   void *blend;
   RetailCall_080e064c(second);
   RetailCall_080dac40(work->wave1,work->x,work->y,(u16)second->value);
   if((u8)RetailCall_080e0690(first)==0)break;
   if((u8)RetailCall_080e0690(second)==0)break;
   blend=RetailCall_080d3f08(work->blend);
   work->blend=blend;
   if(blend!=0)break;
   SHADOW&=0x9fff;
   RetailCall_080d4020();
   work->palette=RetailCall_080d4704((void*)0x0894ac90,parent);
   {register s32 advanced_phase asm("r0")=event->phase+1;asm volatile("" : "+r"(advanced_phase));next_phase=advanced_phase;}goto store_phase;
  }
 }
 case 259:{
  void *child=RetailCall_080d9b64(work->wave0);
  work->wave0=child;
  if(child!=0)break;
  child=RetailCall_080d9b64(work->wave1);
  work->wave1=child;
  if(child!=0)break;
  child=RetailCall_080d4774(work->palette);
  work->palette=child;
  if(child!=0)break;
  if((u8)RetailCall_080dd494(work->actor)==0){
   work->child=RetailCall_080dd214(work->record,0,0,parent);
   next_phase=262;
  }else{
   work->timer=20;
   {register s32 advanced_phase asm("r0")=event->phase+1;asm volatile("" : "+r"(advanced_phase));next_phase=advanced_phase;}
  }
  goto store_phase;
 }
 case 260:{
  u32 timer=work->timer-1;
  work->timer=timer;
  if((u16)timer!=0)break;
  work->target=RetailCall_080dd4a4(work->actor,work->ordinal);
  RetailCall_080db838(RetailCall_080dd4c4(work->target));
  event->phase++;
 }
 /* Actual same-call phase260 ->261. */
 case 261:{
  void **children;
  void *created;
  u32 slot,ordinal;
  if((u8)RetailCall_080d8b4c()!=0)break;
  children=work->children;
  RetailCall_080e0570(children,4);
  slot=work->ordinal&3;
  child_event.definition=work->ordinal;
  child_event.variant=work->flag;
  child_event.actor=work->target;
  created=RetailCall_08005b6c((void*)0x0810a6e9,36,&child_event,parent);
  children+=slot;
  *children=created;
  ordinal=work->ordinal+1;
  work->ordinal=ordinal;
  if((u8)ordinal==work->count){{register s32 advanced_phase asm("r0")=event->phase+1;asm volatile("" : "+r"(advanced_phase));next_phase=advanced_phase;}goto store_phase;}
  work->timer=64;
  if((u8)RetailCall_080dd580(work->target)==0)work->timer=30;
  next_phase=260;goto store_phase;
 }
 case 262:
  if((u8)RetailCall_080e0570(work->children,4)){
   void *child=RetailCall_080dba5c(work->child);
   work->child=child;
   if(child==0){
    next_phase=2;
store_phase:
    event->phase=next_phase;
   }
  }
  break;
 }
 return 0;
}
