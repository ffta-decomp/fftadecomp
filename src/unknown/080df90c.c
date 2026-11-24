typedef unsigned short u16;
struct Event { u16 state,field2; void *record; unsigned field8,field12,field16; u16 delay,field22; unsigned field24; };
extern void *CreateTask(void *,unsigned,const struct Event *,void *);
asm(".global CreateTask\n.thumb_set CreateTask, 0x08005b6d");
void *RemainingBand43_000DF90C(void *record,unsigned delay,void *parent) { struct Event event; event.record=record; event.delay=delay; return CreateTask((void *)0x080de819,48,&event,parent); }
