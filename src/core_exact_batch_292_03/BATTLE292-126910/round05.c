typedef unsigned char u8;typedef unsigned short u16;typedef unsigned int u32;
typedef struct {u16 state,pad;u32 untouched[4];u16 selector,persist,timer;} Event;
typedef struct {u8 *actor;u8 timer,slot,persist;} Work;
extern u8 *Unit(u8);extern void *Registry(void);extern u8 *Actor(void*,u8*);extern void *Prepare(Work*);extern void Flag(void*);extern u8 *Slot(u8);extern u16 Value(void*,u8*);
#define PTR(p) (*(void**)(p))
u32 CoreRegion_00126910(u32 ignored,Event *incoming,Work *incoming_work){
 register Event *event asm("r6");register Work *work asm("r5");u8 *unit,*slot;void *node;u32 next,timer;int i;u8 saved,out;
 event=incoming;asm("" : "+r"(event):"r"(incoming_work));work=incoming_work;asm("" : "+r"(work):"r"(event));
 switch(event->state){
 case 0:work->persist=event->persist;work->timer=event->timer;unit=Unit((u8)event->selector);work->actor=Actor(Registry(),unit);break;
 case 256:node=Prepare(work);work->actor[30]=work->slot;if(node)Flag(node);next=257;goto write;
 case 257:timer=work->timer;if(timer){--timer;work->timer=timer;if((u8)timer)break;}if(!work->persist){saved=work->actor[30];i=0;do{slot=Slot((u8)i);if(slot[1]&&slot[1]==saved){slot[1]=0;break;}}while(++i<=6);Value(PTR(work->actor),&out);work->actor[30]=out;}next=258;goto write;
 case 258:next=3;write:event->state=next;break;
 }
 return0: return 0;
}
asm(".global Unit\n.thumb_set Unit,0x8125579\n.global Registry\n.thumb_set Registry,0x8096d7d\n.global Actor\n.thumb_set Actor,0x8099561\n.global Prepare\n.thumb_set Prepare,0x8126765\n.global Flag\n.thumb_set Flag,0x8148601\n.global Slot\n.thumb_set Slot,0x8121c99\n.global Value\n.thumb_set Value,0x8022239\n");
