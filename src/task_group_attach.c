#include "task_group.h"

/* Attach a callback to an explicit slot and reset that slot's state byte. */
void RecoveredAttachTaskCallback(struct TaskGroup *group, TaskU8 slot,
                                 TaskCallback callback)
{
    group->callbacks[slot] = callback;
    group->slot_state[slot] = 0;
}
