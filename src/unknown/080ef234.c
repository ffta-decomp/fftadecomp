typedef unsigned char u8;typedef unsigned short u16;typedef signed short s16;typedef unsigned int u32;
typedef struct {u16 phase,pad;void *record;u8 reserved[12];u16 mode;} Event;
typedef struct {u8 mode,pad;u16 timer;s16 x,y,z;u16 untouched;void *record,*coordinates,*first,*second;u32 unused28;void *third,*aux;} Work;
extern void *Coordinates(void*,s16*,s16*,s16*) __asm__("0x080DD748");
extern u32 CoordPredicate(void*) __asm__("0x080DD73C");
extern void *Create(const void*,u32,int,int,int,u32,u32) __asm__("0x080D5E80");
extern void SetFlag(void*,u32) __asm__("0x08010884");
extern void SetValue(void*,u32) __asm__("0x08011058");
extern void *CreateChild(void*,const void*,int,int,int,void*,int) __asm__("0x080DCFE4");
extern void *Aux(const void*,int,int,int,void*) __asm__("0x080DFD8C");
extern u32 PollGroup(void**,u32) __asm__("0x080D5F24");
extern void *PollChild(void*) __asm__("0x080DBA5C");
u32 RemainingBand43_000EF234(void *parent,Event *event,Work *work)
{
 switch(event->phase){
 case 0:
 work->mode=event->mode;work->record=event->record;work->coordinates=Coordinates(work->record,&work->x,&work->y,&work->z);
 if((u8)CoordPredicate(work->coordinates))work->y-=8;
 break;
 case 256:{int flags,channel;
 work->first=Create((void*)0x084FA3B0,0,work->x,work->y,work->z,1020,6);SetFlag(work->first,1);
 if(work->mode&1)flags=4;else flags=2;
 work->third=CreateChild(work->record,(void*)0x08399A54,12,44,flags,parent,44);
 if(work->mode&1)channel=16;else channel=8;
 work->aux=Aux((void*)0x08399A68,1,channel|4,0,parent);
 work->timer=10;++event->phase;break;}
 case 257:
 if(--work->timer)break;
 work->second=Create((void*)0x084FA3B0,1,work->x,work->y,work->z,1020,6);SetValue(work->second,1);++event->phase;break;
 case 258:
 if(!(u8)PollGroup(&work->first,2))break;
 work->third=PollChild(work->third);if(work->third)break;event->phase=2;break;
 }return 0;
}
