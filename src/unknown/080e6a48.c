typedef unsigned char u8;typedef unsigned short u16;typedef signed short s16;typedef unsigned int u32;typedef signed int s32;
typedef struct {u16 phase,pad;void *record;u8 opaque[12];u16 flag;} Event;
typedef struct {u8 flag,pad[3];s16 x,y;void *record,*object;u8 output[16];void *positioned,*sequence,*stage;} Work;
extern void *GetRecordObject(void*,s16*,s16*,s16*) __asm__("0x080dd749");
extern void *CreatePositioned(s32,s32,s32,u32,u32,void*,const void*,void*) __asm__("0x080d6099");
extern void *CreateRecordSequence(void*,const void*,u32,u32,u32,void*,u32) __asm__("0x080dcfe5");
extern void *CreateStage(const void*,u32,u32,u32,void*) __asm__("0x080dfd8d");
extern void *PollPositioned(void*) __asm__("0x080d6135");
extern void *PollSequence(void*) __asm__("0x080dba5d");
s32 RemainingBand43_000E6A48(void *parent,Event *event,Work *work)
{
 s32 phase=event->phase;
 switch(phase){
 case 0:{
  u32 kind;
  work->flag=event->flag;
  work->record=event->record;
  work->object=GetRecordObject(work->record,&work->x,&work->y,0);
  work->positioned=CreatePositioned(work->x,work->y,0,1,4,work->output,(void*)0x0839756c,parent);
  kind=0;
  if(work->flag==1)kind=2;
  work->sequence=CreateRecordSequence(work->record,(void*)(0x08397614+20*kind),12,0,4,parent,55);
  work->stage=CreateStage((void*)0x08397674,1,4,0,parent);
  break;
 }
 case 1:break;
 case 256:{
  void *positioned=PollPositioned(work->positioned);
  work->positioned=positioned;
  if(positioned==0){
   void *sequence=PollSequence(work->sequence);
   work->sequence=sequence;
   if(sequence==0)event->phase=2;
  }
  break;
 }
 }
 return 0;
}
