typedef unsigned char u8;typedef unsigned short u16;typedef signed short s16;typedef unsigned int u32;
typedef struct {u16 phase,pad;void *record;u8 reserved[12];u16 mode;} Event;
typedef struct {u8 mode,pad;s16 x,y;u16 untouched;void *record,*coordinates,*child;} Work;
extern void *Coordinates(void*,s16*,s16*,int) __asm__("0x080DD748");
extern void *CreateChild(void*,const void*,int,int,int,void*,int) __asm__("0x080DCFE4");
extern void *PollChild(void*) __asm__("0x080DBA5C");
u32 RemainingBand43_000EFCC0(void *parent,Event *event,Work *work)
{
 switch(event->phase){
 case 0:work->mode=event->mode;work->record=event->record;work->coordinates=Coordinates(work->record,&work->x,&work->y,0);break;
 case 1:break;
 case 256:{int flags;if(work->mode&1)flags=4;else flags=2;work->child=CreateChild(work->record,(void*)0x08399C1C,12,0,flags|8,parent,0);++event->phase;break;}
 case 257:work->child=PollChild(work->child);if(work->child)break;event->phase=2;break;
 }return 0;
}
