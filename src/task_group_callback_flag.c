#include "task_group.h"

/* Set the high-bit flag on a callback pointer while a task slot is active. */
void RecoveredSetTaskCallbackHighBit(struct TaskGroup *group, TaskU8 slot)
{
    TaskU32 callback_bits;

    if (group->current_slot != 0xff) {
        callback_bits = (TaskU32)group->callbacks[slot];
        group->callbacks[slot] =
            (TaskCallback)(callback_bits | 0x80000000u);
    }
}
