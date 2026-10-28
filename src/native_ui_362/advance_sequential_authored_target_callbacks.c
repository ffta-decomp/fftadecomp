typedef unsigned char u8;typedef unsigned short u16;typedef unsigned int u32;typedef int s32;
typedef struct {u16 phase,pad;void *actor;u32 ordinal,flags,unknown16;u16 definition,variant;u32 unknown24;}Event;
typedef struct {u16 ordinal;u8 count,flag,variant,opaque5[7];void *child,*actor;}Work;
extern u32 GetTargetCount(void*) asm("0x080dd495");
extern void Cleanup(void) asm("0x080d38b5");
extern void *PollChild(void*) asm("0x080e051d");
extern void *CreateCallback(void*,u32,const void*,void*) asm("0x08005b6d");
s32 OriginalAuthoredAction_0010A4B0(void *parent,Event *event,Work *work)
{
 Event child_event;
 s32 phase=event->phase;
 switch(phase){
 case 0:
  work->variant=event->variant;
  work->actor=event->actor;
  if(event->flags&2)work->flag=1;
  work->count=GetTargetCount(work->actor);
  break;
 case 1:Cleanup();break;
 case 256:{
  void *child=work->child;
  if(child!=0){
   u32 ordinal;
   child=PollChild(child);work->child=child;
   if(child!=0)break;
   ordinal=work->ordinal+1;work->ordinal=ordinal;
   if((u16)ordinal==work->count)event->phase=2;
  }else{
   child_event.definition=279;
   child_event.variant=1;
   if(work->ordinal==0)child_event.variant=0;
   child_event.actor=work->actor;
   child_event.ordinal=work->ordinal;
   work->child=CreateCallback((void*)0x080efab1,44,&child_event,parent);
  }
  break;
 }
 }
 return 0;
}
