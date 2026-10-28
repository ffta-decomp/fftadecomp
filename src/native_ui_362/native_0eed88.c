typedef unsigned char u8;typedef unsigned short u16;typedef signed short s16;typedef unsigned int u32;
typedef struct {u16 phase,pad;void *record;u8 reserved[12];u16 x,y,ordinal;} Event;
typedef struct {u8 ordinal,pad;s16 x,y;u16 untouched;u32 output;void *first,*second,*record,*aux;} Work;
extern const void *Assets[] __asm__("0x0839999C");
extern void *CreateChild(int,int,int,int,int,void*,const void*,void*) __asm__("0x080D6098");
extern void *Aux(const void*,int,int,int,void*) __asm__("0x080DFD8C");
extern void *CreateSecond(const void*,void*) __asm__("0x080D4704");
extern void *PollFirst(void*) __asm__("0x080D6134");
extern void *PollSecond(void*) __asm__("0x080D4774");
u32 RemainingBand43_000EED88(void *parent,Event *event,Work *work)
{
 switch(event->phase){
 case 0:work->x=event->x;work->y=event->y;work->ordinal=event->ordinal;work->record=event->record;break;
 case 256:work->first=CreateChild(work->x,work->y,0,1,1,&work->output,(void*)0x08399984,parent);work->aux=Aux((void*)0x083999B8,1,4,0,parent);++event->phase;break;
 case 257:work->first=PollFirst(work->first);if(work->first)break;work->second=CreateSecond(Assets[work->ordinal],parent);++event->phase;break;
 case 258:work->second=PollSecond(work->second);if(work->second)break;event->phase=2;break;
 }return 0;
}
