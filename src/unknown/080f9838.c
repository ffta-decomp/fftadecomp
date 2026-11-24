typedef unsigned char u8;typedef unsigned short u16;typedef signed short s16;typedef unsigned int u32;
typedef struct {u16 phase,pad;void *record;u8 pad8[12];u16 mode;} Event;
typedef struct {u8 mode,pad[3];s16 x,y;void *record,*result;u32 output;void *child,*other;} Work;
extern void *Position(void*,s16*,s16*,int) __asm__("0x080DD748");
extern u32 Predicate(void*) __asm__("0x080DD580");
extern void *CreateChild(int,int,int,int,int,u32*,const void*,void*) __asm__("0x080D6098");
extern void *CreateOther(void*,const void*,int,int,u32,void*,int) __asm__("0x080DCFE4");
extern void *PollChild(void*) __asm__("0x080D6134");
extern void *PollOther(void*) __asm__("0x080DBA5C");
u32 RemainingBand43_000F9838(void *parent,Event *event,Work *work)
{
 switch(event->phase) {
 case 0: {void *record;work->mode=event->mode;record=event->record;work->record=record;work->result=Position(record,&work->x,&work->y,0);break;}
 case 1:break;
 case 256:{u32 flags,discarded;
 if((u8)Predicate(work->record)) work->child=CreateChild(work->x,work->y,0,1,1,&work->output,(void*)0x0839C518,parent);
 flags=(work->mode&1)?4:2;
 work->other=CreateOther(work->record,(void*)0x0839C530,12,0,flags|8,parent,0);
 discarded=work->mode&1;__asm__ volatile("" : "+r"(discarded));
 ++event->phase;break;}
 case 257:
 work->child=PollChild(work->child);if(work->child)break;
 work->other=PollOther(work->other);if(work->other)break;
 event->phase=2;break;
 }
 return 0;
}
