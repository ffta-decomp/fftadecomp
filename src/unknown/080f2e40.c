typedef unsigned short u16; typedef unsigned char u8;
struct Event { u16 state,field2; void *record; unsigned field8,field12,field16; u16 selector,field22; unsigned field24; };
extern void *CreateTask(void *,unsigned,const struct Event *,void *);
asm(".global CreateTask\n.thumb_set CreateTask, 0x08005b6d");
void *RemainingBand43_000F2E40(unsigned selector,void *record,void *parent) { struct Event event; register unsigned index asm("r0")=(u8)selector; event.selector=index; event.record=record; { register void *callback asm("r2")=({ register void **base asm("r2")=(void **)0x0839a8e8; asm("" : "+r"(base), "+r"(index)); base[index]; }); asm("" : "+r"(index), "+r"(callback)); { register u16 *base asm("r1")=(u16 *)0x0839a910; asm("" : "+r"(base), "+r"(index)); { unsigned size=base[index]; return CreateTask(callback,size,&event,parent); } } } }
