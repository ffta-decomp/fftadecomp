#include "task_group.h"

/* Remove the callback assigned to one slot without changing its state byte. */
void RecoveredClearTaskCallback(struct TaskGroup *group, TaskU8 slot)
{
    group->callbacks[slot] = (TaskCallback)0;
}
