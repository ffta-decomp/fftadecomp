typedef unsigned short u16;typedef signed short s16;typedef unsigned int u32;
typedef struct {u16 phase,pad;void *record;} Event;
typedef struct {u16 untouched;s16 x,y;u16 pad6;void *record,*coordinates;u32 output[2];void *first,*second,*aux;} Work;
extern void *Coordinates(void *,s16 *,s16 *,int) __asm__("0x080DD748");
extern void *CreateChild(int,int,int,int,int,void *,const void *,void *) __asm__("0x080D6098");
extern void *CreateOther(void *,const void *,int,int,int,void *,int) __asm__("0x080DCFE4");
extern void *CreateAux(const void *,int,int,int,void *) __asm__("0x080DFD8C");
extern void *PollChild(void *) __asm__("0x080D6134");
extern void *PollOther(void *) __asm__("0x080DBA5C");
u32 RemainingBand43_000FE234(void *parent,Event *event,Work *work)
{
 switch(event->phase) {
 case 0:
  work->record=event->record;
  work->coordinates=Coordinates(work->record,&work->x,&work->y,0);
  work->first=CreateChild(work->x,work->y,0,1,2,work->output,(void *)0x0839D874,parent);
  work->second=CreateOther(work->record,(void *)0x0839D8A4,12,20,2,parent,20);
  work->aux=CreateAux((void *)0x0839D8C0,1,4,0,parent);
  break;
 case 1:break;
 case 256:
  work->first=PollChild(work->first);if(work->first)break;
  work->second=PollOther(work->second);if(work->second)break;
  event->phase=2;break;
 }
 return 0;
}
