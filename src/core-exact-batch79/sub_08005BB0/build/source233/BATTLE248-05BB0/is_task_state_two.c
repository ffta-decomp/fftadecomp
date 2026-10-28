#include "../../../src/task_tree_core.h"

/* State value 2 is observed; its broader scheduler interpretation is separate. */
u32 IsTaskStateTwo(const TaskNode *node) __asm__("sub_08005BB0");
u32 IsTaskStateTwo(const TaskNode *node)
{
    u32 matches = 0;
    if (node->state == 2)
        matches = 1;
    return matches;
}
