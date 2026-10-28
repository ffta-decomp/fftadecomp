typedef unsigned char u8;typedef unsigned short u16;typedef signed short s16;typedef unsigned int u32;
typedef struct {u16 phase,pad;void *record;u8 reserved[12];u16 mode,hold;} Event;
typedef struct {u8 mode,pad;u16 timer;s16 x,y;void *coordinates,*record;u32 output[2];void *child,*aux;} Work;
extern void *Coordinates(void*,s16*,s16*,int) __asm__("0x080DD748");
extern void *CreateChild(int,int,int,int,int,void*,const void*,void*) __asm__("0x080D6098");
extern void *Aux(const void*,int,int,int,void*) __asm__("0x080DFD8C");
extern void *PollChild(void*) __asm__("0x080D6134");
u32 RemainingBand43_000F7EC0(void *parent,Event *event,Work *work)
{
 switch(event->phase){
 case 0:work->mode=event->mode;work->timer=event->hold+1;work->record=event->record;work->coordinates=Coordinates(work->record,&work->x,&work->y,0);break;
 case 1:break;
 case 256:if(--work->timer)break;
 work->child=CreateChild(work->x,work->y,0,1,2,work->output,(void*)0x0839BE80,parent);
 work->aux=Aux((void*)0x0839BEDC,1,4,0,parent);++event->phase;break;
 case 257:work->child=PollChild(work->child);if(!work->child)event->phase=2;break;
 }return 0;
}
