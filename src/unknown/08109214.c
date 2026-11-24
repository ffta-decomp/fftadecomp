typedef unsigned char u8;typedef unsigned short u16;typedef signed short s16;typedef unsigned int u32;
typedef struct {u16 phase,pad;void *record;u8 reserved[12];u16 mode;} Event;
typedef struct {u8 mode,pad;s16 x,y;u16 untouched;void *record,*coordinates;u32 output;void *first,*second,*aux;} Work;
extern void *Coordinates(void*,s16*,s16*,int) __asm__("0x080DD748");
extern u32 Predicate(void*) __asm__("0x080DD580");
extern void *CreateChild(int,int,int,int,int,void*,const void*,void*) __asm__("0x080D6098");
extern void *CreateOther(void*,const void*,int,int,int,void*,int) __asm__("0x080DCFE4");
extern void *Aux(const void*,int,int,int,void*) __asm__("0x080DFD8C");
extern void *PollChild(void*) __asm__("0x080D6134");
extern void *PollOther(void*) __asm__("0x080DBA5C");
u32 RemainingBand43_00109214(void *parent,Event *event,Work *work)
{
 switch(event->phase){
 case 0:work->mode=event->mode;work->record=event->record;work->coordinates=Coordinates(work->record,&work->x,&work->y,0);break;
 case 1:break;
 case 256:{int flags;
 if((u8)Predicate(work->record)){int channel;
 work->first=CreateChild(work->x,work->y,0,1,1,&work->output,(void*)0x083A16D4,parent);
 if(work->mode&1)channel=16;else channel=8;
 work->aux=Aux((void*)0x083A1708,1,channel|4,0,parent);}
 if(work->mode&1)flags=4;else flags=2;
 work->second=CreateOther(work->record,(void*)0x083A16EC,12,10,flags,parent,10);++event->phase;break;}
 case 257:work->first=PollChild(work->first);if(work->first)break;work->second=PollOther(work->second);if(work->second)break;event->phase=2;break;
 }return 0;
}
