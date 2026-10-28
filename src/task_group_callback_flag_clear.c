#include "task_group.h"

/* Clear bit 31 from one callback pointer while the group has an active slot. */
void RecoveredClearTaskCallbackHighBit(struct TaskGroup *group, TaskU8 slot)
{
    if (group->current_slot != 0xff) {
        TaskCallback *callbacks = group->callbacks;
        TaskU32 callback_bits = (TaskU32)callbacks[slot];

        callbacks[slot] =
            (TaskCallback)(callback_bits & 0x7fffffffu);
    }
}
