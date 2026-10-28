#include "../../task_tree_core.h"

extern u32 IsTaskStateTwo(const TaskNode *node);
__asm__(".global IsTaskStateTwo\n.thumb_set IsTaskStateTwo, 0x08005bb1");

/* Preserve the full helper result comparison before Boolean normalization. */
u32 IsManagedTaskChildComplete(TaskNode *node)
    __asm__("CoreClosure31_000D7A9C");
u32 IsManagedTaskChildComplete(TaskNode *node)
{
    if (IsTaskStateTwo(node) != 0)
        return 1;
    return 0;
}
