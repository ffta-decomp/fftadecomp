#include "../../../src/task_tree_core.h"

typedef signed short s16;

extern u32 IsTaskStateTwo(const TaskNode *);
extern void RemoveCurrentGroupTask(TaskNode *);
extern void *GetTaskPayload(TaskNode *);
TaskNode *PollAndReleaseDefinitionObjectTask(TaskNode *task)
{
    if (task != 0) {
        register u32 state asm("r0") = IsTaskStateTwo(task);
        if (state != 0)
            state = 1;
        /* Preserve the actual initialized numeric result before its LOW8 test. */
        asm("" : "+r" (state));
        if ((u8)state != 0) {
            RemoveCurrentGroupTask(task);
            return 0;
        }
        ((u8 *)GetTaskPayload(task))[0] = 1;
    }
    return task;
}

asm(".global IsTaskStateTwo\n.thumb_set IsTaskStateTwo,0x8005bb1\n"
    ".global RemoveCurrentGroupTask\n.thumb_set RemoveCurrentGroupTask,0x8005b59\n"
    ".global GetTaskPayload\n.thumb_set GetTaskPayload,0x8005bfd\n");
