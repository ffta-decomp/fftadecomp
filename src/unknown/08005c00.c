#include "engine/tasks/task_tree.h"

TaskCallback ReadTaskNodeCallback(const TaskNode *node)
    __asm__("Source52_00005C00");

TaskCallback ReadTaskNodeCallback(const TaskNode *node)
{
    return node->callback;
}
