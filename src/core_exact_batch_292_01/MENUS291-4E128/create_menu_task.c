typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef struct TaskNode TaskNode;
typedef struct TaskGroup TaskGroup;
typedef void (*Callback)(TaskNode*,u16*,void*);
extern u8 *owner;
extern TaskNode *create(TaskGroup*,Callback,u32,const u32*,TaskNode*);
extern void mode10(TaskNode*,u16*,void*), mode11(TaskNode*,u16*,void*), mode8(TaskNode*,u16*,void*), other(TaskNode*,u16*,void*);
TaskNode *IsolatedCore57_0004E128(u8 mode)
{
 union {u32 words[7];u16 halfwords[14];} event;
 event.halfwords[10]=mode;
 switch(mode) {
 case 10:return create(*(TaskGroup**)(owner+8),mode10,20,event.words,0);
 case 11:return create(*(TaskGroup**)(owner+8),mode11,48,event.words,0);
 case 8:return create(*(TaskGroup**)(owner+8),mode8,204,event.words,0);
 default:return create(*(TaskGroup**)(owner+8),other,152,event.words,0);
 }
}
__asm__(".global owner\n.set owner,0x0201f548\n.global create\n.thumb_set create,0x08005955\n.global mode10\n.thumb_set mode10,0x0804e6ed\n.global mode11\n.thumb_set mode11,0x0804e5cd\n.global mode8\n.thumb_set mode8,0x0804e859\n.global other\n.thumb_set other,0x0804e409");
