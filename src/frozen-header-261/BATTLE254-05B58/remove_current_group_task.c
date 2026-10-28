#include "../../task_tree_core.h"

__asm__(".global RemoveTaskSubtree_080058A4\n.thumb_set RemoveTaskSubtree_080058A4, 0x080058a5");

/* Keep the existing callbacks, unlinking and frees in the real subtree remover. */
void RemoveCurrentGroupTask(TaskNode *node)
    __asm__("CoreDependency29_00005B58");
void RemoveCurrentGroupTask(TaskNode *node)
{
    RemoveTaskSubtree_080058A4(CURRENT_GROUP, node);
}
