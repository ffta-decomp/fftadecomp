#include "task_group.h"

/* Store a callback in the first unused slot and return that slot index. */
TaskU8 RecoveredAddTaskCallback(struct TaskGroup *group, TaskCallback callback)
{
    TaskU8 slot = 0;

    while (slot < group->configured_slots) {
        if (group->callbacks[slot] == (TaskCallback)0) {
            group->callbacks[slot] = callback;
            group->slot_state[slot] = 0;
            break;
        }
        ++slot;
    }

    return slot;
}
