#include "../../../src/task_tree_core.h"

extern u32 IsTaskStateTwo(const TaskNode *task);

TaskNode *PollAndReleaseDefinitionChild(TaskNode *task)
{
    if (task != 0) {
        if (IsTaskStateTwo(task) != 0) {
            RemoveCurrentGroupTask(task);
            return 0;
        }
    }
    return task;
}

asm(".global IsTaskStateTwo\n.thumb_set IsTaskStateTwo,0x08005BB1\n"
    ".global RemoveCurrentGroupTask\n.thumb_set RemoveCurrentGroupTask,0x08005B59\n");
