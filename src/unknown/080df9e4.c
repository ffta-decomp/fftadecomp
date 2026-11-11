typedef unsigned char u8;typedef unsigned short u16;typedef unsigned int u32;
typedef struct {u32 event;void *record;u32 untouched[3];u16 delay,flags;u32 tail;} Template;
extern u32 Eligible(void*);extern u32 HasChild(void*);extern void *Create(void*,u16,Template*,void*);extern u8 Callback[];
void *RemainingBand43_000DF9E4(void *record,u16 flags,u16 delay,void *parent){Template data;if((u8)Eligible(record)&&(u8)HasChild(record)){data.record=record;data.delay=delay;data.flags=flags;return Create(Callback,8,&data,parent);}return 0;}
asm(".global Eligible\n.thumb_set Eligible,0x80dd581\n.global HasChild\n.thumb_set HasChild,0x80dd599\n.global Create\n.thumb_set Create,0x8005b6d\n.global Callback\n.set Callback,0x80df081\n");
