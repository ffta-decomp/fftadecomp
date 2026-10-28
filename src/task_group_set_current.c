#include "task_group.h"

/*
 * Replace the selected callback and clear its byte state. The volatile
 * descriptor preserves the retail reload of current_slot before clearing it.
 */
void RecoveredSetCurrentTaskCallback(volatile struct TaskGroup *group,
                                     TaskCallback callback)
{
    /* The pinned compiler otherwise swaps these two reload registers. */
    register TaskU8 current_slot __asm__("r1");
    register TaskU8 *state __asm__("r0");
    TaskU8 slot = group->current_slot;

    if (slot != 0xff) {
        group->callbacks[slot] = callback;
        current_slot = group->current_slot;
        state = group->slot_state;
        state[current_slot] = 0;
    }
}
