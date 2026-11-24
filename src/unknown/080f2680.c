typedef unsigned char u8;typedef unsigned short u16;typedef signed short s16;typedef unsigned int u32;
typedef struct {u16 phase,pad;void *record;} Event;
typedef struct {s16 x,y;u8 time,pad[3];void *handles[10],*blend,*scripts[5],*record,*aux;} Work;
typedef struct {u8 time,kind;s16 x,y;u16 pad;} Spawn;
extern void CpuSet(const void*,void*,u32) __asm__("0x0814186C");
extern void Model(const void*,int,int,int,int,int) __asm__("0x080D7220");
extern void *Blend(const void*,void*) __asm__("0x080D3E9C");
extern void ConfigureBlend(void*,int,int) __asm__("0x080D3F84");
extern void *Script(const void*,void*) __asm__("0x080D4704");
extern void ConfigureScript(void*,int) __asm__("0x080D47A0");
extern void *Aux(const void*,int,int,int,void*) __asm__("0x080DFD8C");
extern void *Sprite(const void*,int,int,int,int,int,int,void*) __asm__("0x080D5CC0");
extern void Activate(void*) __asm__("0x08011198");
extern u32 PollAll(void**,int) __asm__("0x080D5F24");
extern void *PollBlend(void*) __asm__("0x080D3F08");
extern void *PollScript(void*) __asm__("0x080D4774");
extern void Cleanup(void**,int) __asm__("0x080D4938");
extern u32 Mask(u32) __asm__("0x080035A8");
extern const Spawn SpawnTable[] __asm__("0x0839A7CC");
u32 RemainingBand43_000F2680(void *parent,Event *event,Work *work)
{
 switch(event->phase) {
 case 0:{u16 zero;work->record=event->record;work->x=120;work->y=96;zero=0;CpuSet(&zero,(void*)0x03003920,0x01000010);break;}
 case 256:{void *blend;
 Model((void*)0x088F5BD4,1,3,work->x,work->y,0);
 blend=Blend((void*)0x0894DB58,parent);work->blend=blend;ConfigureBlend(blend,8,255);
 work->scripts[0]=Script((void*)0x0894B850,parent);
 work->scripts[1]=Script((void*)0x0894B6F0,parent);
 work->scripts[2]=Script((void*)0x0894B744,parent);
 work->scripts[3]=Script((void*)0x0894B7A0,parent);
 work->scripts[4]=Script((void*)0x0894B7FC,parent);
 ConfigureScript(work->scripts[1],1);ConfigureScript(work->scripts[2],1);ConfigureScript(work->scripts[3],1);ConfigureScript(work->scripts[4],1);
 work->aux=Aux((void*)0x0839A8C8,1,4,0,parent);++event->phase;break;}
 case 257:{u8 i;register u32 count __asm__("r8");register void **handles __asm__("r10");++work->time;i=0;count=0;__asm__("" : "+r"(count));handles=work->handles;__asm__("" : "+r"(handles));
 do {void **slot=&handles[i];void *old=*slot;
 if(old)count=(u8)(count+1);
 else {register const Spawn *base __asm__("r0")=SpawnTable;const Spawn *spawn;__asm__("" : "+r"(base));spawn=(const Spawn *)((u32)(i*8)+(u32)base);
 if(work->time==spawn->time) {void *created=Sprite((void*)0x0850341C,spawn->kind,spawn->x,spawn->y,967,7,1,old);*slot=created;Activate(created);}}
 ++i;}while(i<=9);
 if(count>9)++event->phase;break;}
 case 258:
 if((u8)PollAll(work->handles,10)) {
 work->blend=PollBlend(work->blend);if(work->blend)break;
 work->scripts[0]=PollScript(work->scripts[0]);if(work->scripts[0])break;
 Cleanup(&work->scripts[1],4);
 {u32 mask=Mask(3);*(u16*)0x03000940&=~mask;}
 event->phase=2;
 }break;
 }
 return 0;
}
