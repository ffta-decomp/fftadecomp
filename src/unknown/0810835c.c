typedef unsigned char u8;typedef unsigned short u16;typedef signed short s16;typedef unsigned int u32;typedef signed int s32;
typedef struct {u16 phase,pad;void *record;u32 opaque[3];u16 ordinal,variant;u32 unknown24;} Event;
/* Typed used extent20; the proven parent allocates24. */
typedef struct {u8 mode,pad;s16 x,y;u16 unknown6;void *record,*object,*child;} Work;
extern void *GetRecordObject(void*,s16*,s16*,s16*) __asm__("0x080dd749");
extern void *CreateRecordSequence(void*,const void*,u32,u32,u32,void*,u32) __asm__("0x080dcfe5");
extern void *PollRecordSequence(void*) __asm__("0x080dba5d");
s32 RemainingBand43_0010835C(void *parent,Event *event,Work *work)
{
 s32 phase=event->phase,next_phase;
 switch(phase){
 case 0:
  work->mode=event->ordinal;
  work->record=event->record;
  work->object=GetRecordObject(work->record,&work->x,&work->y,0);
  break;
 case 1:break;
 case 256:{
  u32 mode_bit=work->mode&1;
  u32 flags=2;
  if(mode_bit)flags=4;
  work->child=CreateRecordSequence(work->record,(void*)0x083a0f20,12,0,flags|8,parent,0);
  next_phase=event->phase+1;goto store_phase;
 }
 case 257:{
  void *child=PollRecordSequence(work->child);
  work->child=child;
  if(child==0){
   next_phase=2;
store_phase:
   event->phase=next_phase;
  }
  break;
 }
 }
 return 0;
}
