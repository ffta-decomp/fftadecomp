typedef unsigned short u16;typedef unsigned char u8;
struct Event {u16 state,field2;void *action;unsigned field8,field12,field16;u16 mode,field22;unsigned field24;};
extern void *CreateTask(void *,unsigned,const struct Event *,void *);
asm(".global CreateTask\n.thumb_set CreateTask,0x08005b6d");
void *RemainingBand43_000F11CC(void *action,u8 mode,void *parent){struct Event event;event.mode=(u8)mode;event.action=action;return CreateTask((void *)0x080f0ef5,48,&event,parent);}
