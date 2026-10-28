#include "../../../src/task_tree_core.h"

TaskCallback ReadTaskNodeCallback(const TaskNode *node)
    __asm__("Source52_00005C00");

TaskCallback ReadTaskNodeCallback(const TaskNode *node)
{
    return node->callback;
}
