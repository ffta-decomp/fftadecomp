#include "task_group.h"

/* Reset task-group markers and release every configured callback slot. */
void RecoveredClearTaskGroup(struct TaskGroup *group)
{
    int slot;

    group->unknown_00 = 0;
    group->current_slot = 0xff;

    slot = group->configured_slots - 1;
    for (; slot >= 0; --slot)
        group->callbacks[slot] = (TaskCallback)0;
}
