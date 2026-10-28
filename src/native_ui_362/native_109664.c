typedef unsigned char u8;typedef unsigned short u16;typedef signed short s16;typedef unsigned int u32;
typedef struct {u16 phase,pad;void *record;u8 reserved[12];u16 mode,ordinal;} Event;
typedef struct {u8 mode,ordinal;s16 x,y;u16 untouched;void *record,*coordinates;u32 output,unused20,unused24;void *first,*second;} Work;
extern void *Coordinates(void*,s16*,s16*,int) __asm__("0x080DD748");
extern u32 Predicate(void*) __asm__("0x080DD580");
extern void *CreateChild(int,int,int,int,int,void*,const void*,void*) __asm__("0x080D6098");
extern void *CreateOther(void*,const void*,int,int,int,void*,int) __asm__("0x080DCFE4");
extern void *Aux(const void*,int,int,int,void*) __asm__("0x080DFD8C");
extern void *PollChild(void*) __asm__("0x080D6134");
extern void *PollOther(void*) __asm__("0x080DBA5C");
u32 RemainingBand43_00109664(void *parent,Event *event,Work *work)
{
 switch(event->phase){
 case 0:work->record=event->record;work->mode=event->mode;work->ordinal=event->ordinal;work->coordinates=Coordinates(work->record,&work->x,&work->y,0);break;
 case 256:{int flags;
 work->first=CreateChild(work->x,work->y,0,1,3,&work->output,(void*)0x083A17C4,parent);
 if(work->mode&1)flags=4;else flags=2;
 work->second=CreateOther(work->record,(u8*)0x083A1810+20U*work->ordinal,12,32,flags|8,parent,32);++event->phase;break;}
 case 257:work->first=PollChild(work->first);if(work->first)break;++event->phase;break;
 case 258:work->second=PollOther(work->second);if(work->second)break;event->phase=2;break;
 }return 0;
}
