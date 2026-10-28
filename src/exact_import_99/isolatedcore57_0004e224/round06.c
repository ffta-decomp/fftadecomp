#include "interfaces.h"
u32 InterpretInventorySelection(void *task) __asm__("IsolatedCore57_0004E224");
u32 InterpretInventorySelection(void *task)
{
    struct InventoryChoiceState *state = GetInventoryChoiceState(task);
    u16 index = state->selection - 1;
    switch (state->mode) {
    case 1: {
        if (state->selection == -1)
            return state->selection;
        switch (state->owner->content_ids[(s16)index]) {
        case 59: return 1;
        case 60: return 2;
        case 61: return 3;
        case 62: return 4;
        case 79: return 5;
        case 63: return 6;
        default: return (u32)-1;
        }
    }
    case 5:
        /* Mode 5 reads only the low halfword of each four-byte slot. */
        return state->owner->slots.halfwords[(s16)index * 2];
    case 3: case 4: case 6:
        return state->owner->slots.words[(s16)index];
    case 8:
        return gInventoryFixedContentIds[(s16)index];
    default:
        return 0;
    }
}
