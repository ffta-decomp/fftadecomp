typedef unsigned char u8;typedef unsigned short u16;typedef unsigned int u32;typedef struct Task Task;
typedef struct {u16 phase,unknown2;void *owner;u8 unknown8[12];u16 mode,unknown22;u32 unknown24;}Event;
extern Task *CreateActionTask(void*,u32,const Event*,Task*) asm("0x08005b6d");
Task *RemainingBand43_000EDB98(void *owner,u32 mode,Task *parent)
{
 Event event;
 register Event *partial asm("r2");
 mode=(u8)mode;
 partial=&event;
 asm volatile("" : "+r"(partial) : "r"(owner), "r"(mode), "r"(parent));
 partial->mode=mode;
 event.owner=owner;
 return CreateActionTask((void*)0x080eda01,52,partial,parent);
}
