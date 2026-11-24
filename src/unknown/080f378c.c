typedef unsigned char u8;typedef unsigned short u16;typedef signed short s16;typedef unsigned int u32;
typedef struct {u16 phase,pad;void *record;} Event;
typedef struct {u16 timer;u8 notified,pad;u32 output;void *child,*notification,*record,*begin,*other,*aux;} Work;
extern void *Begin(void*,void**,u32,int,u8*,const void*,int,u32,void*) __asm__("0x080DDF68");
extern void *Select(void*,int) __asm__("0x080DD4A4");
extern void *Coordinates(void*) __asm__("0x080DD4C4");
extern void GetPosition(void*,s16*,s16*) __asm__("0x080DBDC8");
extern void *CreateChild(int,int,int,int,int,u32*,const void*,void*) __asm__("0x080D6098");
extern void *Aux(const void*,int,int,int,void*) __asm__("0x080DFD8C");
extern void *CreateOther(void*,const void*,int,int,u32,void*,int) __asm__("0x080DCFE4");
extern void *PollChild(void*) __asm__("0x080D6134");
extern void *PollOther(void*) __asm__("0x080DBA5C");
extern u32 Complete(void*) __asm__("0x080DE244");
u32 RemainingBand43_000F378C(void *parent,Event *event,Work *work)
{
 switch(event->phase) {
 case 0:work->record=event->record;work->timer=71;break;
 case 256:{u16 remaining=--work->timer;
 if(remaining)break;
 work->begin=Begin(work->record,&work->notification,32775,2,&work->notified,(void*)0x0839ACF8,5,remaining,parent);
 ++event->phase;break;}
 case 257:
 if(work->notified) {s16 x,y;void *selected=Select(work->record,0);
 GetPosition(Coordinates(selected),&x,&y);
 work->child=CreateChild(x,y,0,1,1,&work->output,(void*)0x0839ACB8,parent);
 work->aux=Aux((void*)0x0839AD08,1,4,10,parent);
 work->other=CreateOther(selected,(void*)0x0839ACE4,12,31,2,parent,31);
 ++event->phase;
 }break;
 case 258:
 work->child=PollChild(work->child);if(work->child)break;
 work->other=PollOther(work->other);if(work->other)break;
 if((u8)Complete(work->notification))event->phase=2;
 break;
 }
 return 0;
}
