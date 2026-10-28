typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef struct TaskNode TaskNode;
typedef void (*Callback)(TaskNode*,u16*,void*);
extern TaskNode *create(Callback,u16,const u32*,TaskNode*);
extern void facing(TaskNode*,u16*,void*);
void SceneActionDependency_00126DFC(u8 *owner,u8 selector,u8 direction,u8 mode)
{
 union {u32 words[7];u16 halves[14];} event;
 owner[6]=0;
 event.words[1]=(u32)owner;
 event.halves[10]=selector;event.halves[11]=direction;event.halves[12]=mode;
 create(facing,12,event.words,0);
}
__asm__(".global create\n.thumb_set create,0x08121b8d\n.global facing\n.thumb_set facing,0x08126bfd");
