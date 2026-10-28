typedef unsigned char u8;typedef unsigned short u16;typedef signed short s16;typedef unsigned int u32;
typedef struct {u16 phase,pad;void *record;u8 reserved[12];u16 mode,ordinal;} Event;
typedef struct {u8 mode,ordinal;s16 x,y;u16 untouched;void *record,*coordinates,*layer;u32 output;void *first,*script,*second,*always,*aux;} Work;
extern u16 DisplayControl __asm__("0x03000940");
extern void *Coordinates(void *,s16 *,s16 *,int) __asm__("0x080DD748");
extern void Setup(int,int,int,int,int) __asm__("0x080D49FC");
extern void *CreateLayer(int,const void *,int,int) __asm__("0x080D4B64");
extern u32 LayerMask(u32) __asm__("0x080035A8");
extern void *CreateScript(const void *,void *) __asm__("0x080D3E9C");
extern void *CreateChild(void *,const void *,int,int,int,void *,int) __asm__("0x080DCFE4");
extern void *Aux(const void *,int,int,int,void *) __asm__("0x080DFD8C");
extern void *PollLayer(void *,int) __asm__("0x080D4D2C");
extern void *PollScript(void *) __asm__("0x080D3F08");
extern void *PollChild(void *) __asm__("0x080DBA5C");
extern u32 Predicate(void *) __asm__("0x080DD580");
extern void *CreateFirst_unused(const void *,void *) __asm__("0x080D4704");
extern void *PollFirst(void *) __asm__("0x080D4774");
extern void ResetLayer(void) __asm__("0x080D4020");
extern void *CreateFirst(int,int,int,int,int,void*,const void*,void*) __asm__("0x080D6098");
extern void *PollAnimation(void*) __asm__("0x080D6134");
u32 RemainingBand43_000EEF98(void *parent,Event *event,Work *work)
{
 switch(event->phase){
 case 0:work->mode=event->mode;work->record=event->record;work->coordinates=Coordinates(work->record,&work->x,&work->y,0);break;
 case 256:{int flags,channel;
 Setup(0,2,0,work->x,work->y);
 work->layer=CreateLayer(0,(void*)0x088ED7EC,957,6);
 {u32 mask=LayerMask(2);u16 *control=&DisplayControl;register u32 combined __asm__("r1")=*control|mask;__asm__("" : "+r"(combined));*control=combined;}
 work->first=CreateFirst(work->x,work->y,0,1,1,&work->output,(void*)0x08399A04,parent);
 work->script=CreateScript((void*)0x0894D690,parent);
 work->second=CreateFirst_unused((void*)0x08949474,parent);
 if(work->mode&1)flags=4;else flags=2;
 work->always=CreateChild(work->record,0,12,0,flags,parent,55);
 if(work->mode&1)channel=16;else channel=8;
 work->aux=Aux((void*)0x08399A1C,1,channel|4,0,parent);++event->phase;break;}
 case 257:{u32 bits,was;void *old;
 work->layer=PollLayer(work->layer,0);if(work->layer)break;
 work->script=PollScript(work->script);if(work->script)break;
 old=work->second;bits=(u32)old;was=((0U-bits)|bits)>>31;
 work->second=PollFirst(old);if(work->second)break;
 if(was){u32 mask=LayerMask(2);u16 *control=&DisplayControl;*control&=~mask;}
 work->first=PollAnimation(work->first);if(work->first)break;
 ++event->phase;break;}
 case 258:work->always=PollChild(work->always);if(work->always)break;event->phase=2;break;
 }return 0;
}
