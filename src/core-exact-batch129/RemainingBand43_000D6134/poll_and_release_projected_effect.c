#include "../../../src/task_tree_core.h"

extern u32 IsTaskStateTwo(const TaskNode *);
extern void RemoveCurrentGroupTask(TaskNode *);
TaskNode *PollAndReleaseProjectedEffect(TaskNode *) asm("RemainingBand43_000D6134");
TaskNode *PollAndReleaseProjectedEffect(TaskNode *task)
{
    u32 complete;
    TaskNode *result;
    if (IsTaskStateTwo(task)!=0) {
        complete=1;
        asm("" : : "r"(complete));
    } else {
        complete=0;
        asm("" : : "r"(complete));
    }
    if (complete==0)
        result=task;
    else {
        RemoveCurrentGroupTask(task);
        result=0;
    }
    return result;
}
asm(".global IsTaskStateTwo\n.thumb_set IsTaskStateTwo,0x08005bb1\n"
    ".global RemoveCurrentGroupTask\n.thumb_set RemoveCurrentGroupTask,0x08005b59\n");
