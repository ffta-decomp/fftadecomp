#include "../../task_tree_core.h"
extern void ManagedChildTask(TaskNode *, u16 *, void *);
__asm__(".global ManagedChildTask\n.thumb_set ManagedChildTask, 0x080d791d\n"
        ".global CreateTaskNode_08005954\n.thumb_set CreateTaskNode_08005954, 0x08005955");
TaskNode *CreateManagedTaskChild(void *owner, u8 mode, TaskNode *parent)
    __asm__("CoreClosure31_000D7A70");
TaskNode *CreateManagedTaskChild(void *owner, u8 mode, TaskNode *parent)
{
    u32 event[7];
    ((u16 *)event)[10] = mode;
    event[1] = (u32)owner;
    return CreateTaskNode_08005954(*(TaskGroup **)0x0200f430, ManagedChildTask,
                                  40, event, parent);
}
