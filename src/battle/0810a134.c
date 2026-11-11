typedef unsigned char u8;typedef unsigned short u16;typedef signed short s16;typedef unsigned int u32;
typedef struct {u16 phase,pad;} Event;
typedef struct {u8 pad[4];u16 frame;u8 spawned,cadence;void *objects[15],*blend,*aux;} Work;
typedef struct {u8 frame,kind;s16 x;} Spawn;
extern const Spawn SpawnTable[] __asm__("0x083A1B38");
extern void Model(const void*,int,int,int,int,int) __asm__("0x080D7220");
extern void *Blend(const void*,void*) __asm__("0x080D3E9C");
extern void *Aux(const void*,int,int,int,void*) __asm__("0x080DFD8C");
extern void *Sprite(const void*,int,int,int,int,int,int,void*) __asm__("0x080D5CC0");
extern void Position(void*,u16*,u16*,u16*) __asm__("0x08011040");
extern void Move(void*,int,int,int) __asm__("0x080107D4");
extern u32 PollAll(void**,int) __asm__("0x080D5F24");
extern void *PollBlend(void*) __asm__("0x080D3F08");
u32 RemainingBand43_0010A134(void *parent,Event *event,Work *work)
{
 switch(event->phase) {
 case 1:break;
 case 256:
 Model((void*)0x088F669C,0,2,120,0,0);
 work->blend=Blend((void*)0x0894DDDC,parent);
 work->aux=Aux((void*)0x083A1B30,1,4,0,parent);
 work->cadence=3;++event->phase;break;
 case 257:{u8 i=work->spawned;void **handles=work->objects;
 for(;i<=14;++i) {register const Spawn *table __asm__("r0")=SpawnTable;const Spawn *spawn;u32 offset;__asm__("" : "+r"(table));offset=(u32)i*4;__asm__("add %0, %1, %2" : "=l"(spawn) : "l"(offset),"l"(table) : "cc");
 if(work->frame==spawn->frame) {
 void *created=Sprite((void*)0x085080A8,spawn->kind,spawn->x,8,1020,6,1,0);void **slot;
 __asm__("add %0, %1, %2" : "=l"(slot) : "l"(handles),"l"(offset) : "cc");*slot=created;
 ++work->spawned;
 }}
 if(--work->cadence) {u16 x,y,z;
 i=0;do {void **slot=&handles[i];
 if(*slot) {Position(*slot,&x,&y,&z);++y;Move(*slot,(s16)x,(s16)y,(s16)z);}
 ++i;}while(i<=14);
 }else work->cadence=3;
 ++work->frame;
 if((u8)PollAll(handles,15)&&work->spawned>14)++event->phase;
 break;}
 case 258:
 work->blend=PollBlend(work->blend);if(!work->blend)event->phase=2;
 break;
 }
 return 0;
}
