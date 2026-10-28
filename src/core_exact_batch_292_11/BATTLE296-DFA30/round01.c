typedef unsigned short u16;typedef unsigned char u8;
struct Event {u16 state,field2;void *cell;unsigned value,option,field16;u16 x,z,delay,field26;};
extern void *CreateTask(void *,unsigned,const struct Event *,void *);
asm(".global CreateTask\n.thumb_set CreateTask,0x08005b6d");
void *RemainingBand43_000DFA30(void *cell,u16 value,u8 option,u8 x,u8 z,unsigned delay,void *parent){struct Event event;event.cell=cell;event.value=value;event.option=option;event.x=x;event.z=z;event.delay=delay;return CreateTask((void *)0x080df14d,32,&event,parent);}
