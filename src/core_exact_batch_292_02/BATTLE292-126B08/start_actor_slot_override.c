typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct ActorSlotEvent {u32 unknown0,unknown4,selector,unknown12,unknown16;u16 first,condition,delay,unknown26;};
extern void *CreateActorSlotTask(void *,u16,const struct ActorSlotEvent *,void *);
void StartActorSlotOverride(u8 selector,u8 first,u8 condition,u8 delay) {
 struct ActorSlotEvent event;
 event.selector=selector;
 event.first=first;
 event.condition=condition;
 event.delay=delay;
 CreateActorSlotTask((void *)0x0812682d,72,&event,0);
}
__asm__(".global CreateActorSlotTask\n.thumb_set CreateActorSlotTask,0x08121b8d");
