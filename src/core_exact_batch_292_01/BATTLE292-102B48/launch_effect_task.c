typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef struct TaskNode TaskNode;
typedef void (*Callback)(TaskNode*,u16*,void*);
extern unsigned blocked(void*);
extern void effect(TaskNode*,u16*,void*);
extern TaskNode *create(Callback,u16,const u32*,TaskNode*);
TaskNode *RemainingBand43_00102B48(void *record,u8 mode,void *argument,TaskNode *parent)
{
 union {u32 words[7];u16 halfwords[14];} event;
 if((u8)blocked(record)) return 0;
 event.halfwords[10]=mode;
 event.words[1]=(u32)record;
 event.words[2]=(u32)argument;
 return create(effect,604,event.words,parent);
}
__asm__(".global blocked\n.thumb_set blocked,0x080d3b55\n.global effect\n.thumb_set effect,0x081023e9\n.global create\n.thumb_set create,0x08005b6d");
