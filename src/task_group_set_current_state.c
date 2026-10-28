#include "task_group.h"

/* Assign a state byte to the current slot when a task callback is active. */
void RecoveredSetCurrentTaskSlotState(struct TaskGroup *group, TaskU8 state)
{
    /* Retail reloads the slot after testing the inactive 0xff sentinel. */
    if (group->current_slot != 0xff)
        group->slot_state[group->current_slot] = state;
}
