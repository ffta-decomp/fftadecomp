#include "task_group.h"

/* Release the configured callback slots and mark the group unconfigured. */
void RecoveredResetTaskGroup(struct TaskGroup *group)
{
    int slot;

    group->unknown_00 = 0;
    group->current_slot = 0xff;

    slot = group->configured_slots - 1;
    for (; slot >= 0; --slot)
        group->callbacks[slot] = (TaskCallback)0;

    group->configured_slots = 0;
}
