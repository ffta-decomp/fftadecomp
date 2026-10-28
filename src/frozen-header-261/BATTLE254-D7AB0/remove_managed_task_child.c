#include "../../task_tree_core.h"

extern void RemoveCurrentGroupTask(TaskNode *node);
__asm__(".global RemoveCurrentGroupTask\n.thumb_set RemoveCurrentGroupTask, 0x08005b59");

/* The controller clears its child slot after this real removal returns. */
void RemoveManagedTaskChild(TaskNode *node)
    __asm__("CoreClosure31_000D7AB0");
void RemoveManagedTaskChild(TaskNode *node)
{
    RemoveCurrentGroupTask(node);
}
