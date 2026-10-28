typedef unsigned char u8;typedef unsigned short u16;typedef unsigned int u32;
typedef struct {u16 event;u16 reserved;u8 *owner;} Event;
typedef struct {u8 *owner;void *sequence;} Workspace;
extern void *Registry(void);extern void *Create(void*);extern u32 Poll(void*,u16);extern void Destroy(void*);extern u16 Input[] asm("Input");
u32 CoreRegion_0012B980(u32 ignored,Event *event,Workspace *work){
 u32 next;register u8 *owner asm("r0");
 switch(event->event){
 case 1:case 2:case 3:break;
 case 0:work->owner=event->owner;break;
 case 256:work->sequence=Create(Registry());next=257;goto write;
 case 257:if((u8)Poll(work->sequence,Input[1]))break;Destroy(work->sequence);event->event=258;break;
 case 258:next=259;goto write;
 case 259:owner=work->owner;asm("" : "+r"(owner));owner[6]=1;next=3;write:event->event=next;break;
 }
 return 0;
}
asm(".global Registry\n.thumb_set Registry,0x8096d7d\n.global Create\n.thumb_set Create,0x80bca25\n.global Poll\n.thumb_set Poll,0x80bca41\n.global Destroy\n.thumb_set Destroy,0x80bca55\n.global Input\n.set Input,0x3000000\n");
