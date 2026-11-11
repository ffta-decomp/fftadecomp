typedef unsigned char u8;typedef unsigned short u16;typedef short s16;typedef unsigned int u32;typedef int s32;
typedef struct {u16 phase,pad;void *actor;u8 ordinal,pad9[11];u16 definition,variant;u32 unknown24;}Event;
typedef struct {u32 x:16;u32 y:16;}PackedOffset;
typedef struct {u16 opaque0;u8 mode,variant;u16 opaque4;s16 x,y;u16 opaque10;void *children[3],*target,*object,*special,*actor,*opening;}Work;
extern void *GetTarget(void*,u32) asm("0x080dd4a5"),*GetIndexedRecord(void*,u32) asm("0x080dd4b5");
extern void GetPosition(void*,volatile u16*,volatile u16*,volatile u16*) asm("0x080dbda1");
extern void *Open(void*,const void*,u32,u32,const void*,void*) asm("0x080e03f9");
extern void Cleanup(void) asm("0x080d38b5");
extern void *PollOpening(void*) asm("0x080e05dd");
extern u32 CountTargets(void*,u32) asm("0x080d8859");
extern void *GetObject(void*,s16*,s16*,s16*) asm("0x080dd749");
extern u32 HasTargetClass(void*) asm("0x080dd581"),HasTargetState(void*,u32) asm("0x080dd671");
extern void *GetObjectRecord(void*) asm("0x080dd479");
extern u32 ReadProperty(void*,u32) asm("0x080c7ea5");
extern s32 SignedModulo(s32,s32) asm("0x08141875");
extern void *CreateSpecial(void*,u32,u32,void*) asm("0x080dd215");
extern void *CreateCallback(void*,u32,const void*,void*) asm("0x08005b6d");
extern void *PollChild(void*) asm("0x080e051d"),*PollSpecial(void*) asm("0x080dba5d");
#define ADVANCE() do {register s32 advanced_phase asm("r0")=event->phase+1;asm volatile("" : "+r"(advanced_phase));next_phase=advanced_phase;goto store_phase;}while(0)
s32 OriginalAuthoredAction_000EFAB0(void *parent,Event *event,Work *work)
{
 volatile u16 out_x,out_y,out_z;
 Event child_event;
 PackedOffset offset;
 s32 phase=event->phase,next_phase;
 switch(phase){
 case 0:{
  void *actor;
  u8 ordinal;
  u32 flags,count;
  const void *parameter;
  s32 selector;
  work->variant=event->variant;
  actor=event->actor;work->actor=actor;
  work->mode=phase;
  ordinal=0;flags=1;parameter=0;
  selector=(s16)event->definition;
  if(selector==279){
   work->mode=flags;
   ordinal=event->ordinal;flags=6;
   GetPosition(GetIndexedRecord(actor,ordinal),&out_x,&out_y,&out_z);
   offset.x=out_x-120;
   offset.y=out_y-96;
   parameter=&offset;
  }else if(selector==296){work->mode=2;flags=7;}
  work->target=GetTarget(work->actor,ordinal);
  count=3;if(work->variant!=0)count=0;
  work->opening=Open(work->actor,(void*)0x08399a98,count,flags,parameter,parent);
  break;
 }
 case 1:Cleanup();break;
 case 256:{
  void *opening=PollOpening(work->opening);
  u32 kind;
  work->opening=opening;if(opening!=0)break;
  if((u8)CountTargets(work->actor,0)==0){next_phase=2;goto store_phase;}
  work->object=GetObject(work->target,&work->x,&work->y,0);
  kind=0;
  if((u8)HasTargetClass(work->target)==0){
   if(work->mode==1){
    u32 property=(u16)ReadProperty(GetObjectRecord(work->object),6);
    if(SignedModulo(property,5)!=0){
     work->special=CreateSpecial(work->object,4,0,parent);
     next_phase=258;goto store_phase;
    }
   }
  }else{u32 target_state=HasTargetState(work->target,0)<<24;kind=2;if(target_state!=0)kind=1;}
  {
   Event *child_out=&child_event;
   child_out->definition=work->x;
   child_out->variant=work->y;
   work->children[0]=CreateCallback((void*)0x080ef485,36,child_out,parent);
   if(kind!=2){
    child_out->actor=work->target;
    work->children[1]=CreateCallback((void*)0x080ef639,44,child_out,parent);
   }
   child_out->actor=work->target;
   work->children[2]=CreateCallback((void*)0x080ef971,40,child_out,parent);
  }
  ADVANCE();
 }
 case 257:{
  void *first=PollChild(work->children[0]),*second,*third;
  work->children[0]=first;if(first!=0)break;
  second=PollChild(work->children[1]);work->children[1]=second;if(second!=0)break;
  third=PollChild(work->children[2]);work->children[2]=third;if(third!=0)break;
  ADVANCE();
 }
 case 258:{
  void *special=PollSpecial(work->special);
  work->special=special;if(special!=0)break;
  next_phase=2;
store_phase:event->phase=next_phase;
  break;
 }
 }
 return 0;
}
