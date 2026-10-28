#include "task_group.h"

/* Initialize a task group and clear every callback and per-slot state byte. */
void RecoveredConfigureTaskGroup(struct TaskGroup *group,
                                 TaskCallback *callbacks,
                                 TaskU8 *slot_state,
                                 TaskU32 slot_count)
{
    int slot;

    group->unknown_00 = 0;
    group->processed_count = 0;
    group->run_mode = 0;
    group->configured_slots = (TaskU8)slot_count;
    group->current_slot = 0xff;
    group->callbacks = callbacks;
    group->slot_state = slot_state;

    slot = group->configured_slots - 1;
    for (; slot >= 0; --slot) {
        group->callbacks[slot] = (TaskCallback)0;
        group->slot_state[slot] = 0;
    }
}
