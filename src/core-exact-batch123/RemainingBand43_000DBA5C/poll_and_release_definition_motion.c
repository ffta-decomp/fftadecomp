#include "../../../src/task_tree_core.h"

extern u32 IsTaskStateTwo(const TaskNode *task);
extern void RemoveCurrentGroupTask(TaskNode *task);

TaskNode *PollAndReleaseDefinitionMotion(TaskNode *task)
{
    if (task != 0) {
        u32 completed;
        if (IsTaskStateTwo(task) != 0) {
            /* Keep this native assignment after the predicate branch. */
            asm volatile ("movs %0,#1" : "=r" (completed) : : "cc");
        } else {
            /* The native false arm explicitly defines zero before the join. */
            asm volatile ("movs %0,#0" : "=r" (completed) : : "cc");
        }
        /* Preserve the defined full Boolean value at its original shared test. */
        asm("" : "+r" (completed));
        if (completed != 0) {
            RemoveCurrentGroupTask(task);
            return 0;
        }
    }
    return task;
}

asm(".global IsTaskStateTwo\n.thumb_set IsTaskStateTwo,0x08005BB1\n"
    ".global RemoveCurrentGroupTask\n.thumb_set RemoveCurrentGroupTask,0x08005B59\n");
