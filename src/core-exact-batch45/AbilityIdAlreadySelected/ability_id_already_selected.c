#include "retail_calls.h"

u32 AbilityIdAlreadySelected(u32 ability_id, const u16 *selected_ids,
                             s32 selected_count)
{
    s32 index;
    const u16 *cursor;
    u16 narrowed_id;

    narrowed_id = (u16)ability_id;
    index = 0;
    cursor = selected_ids;

    while (index < selected_count) {
        if (narrowed_id == *cursor)
            return 1;
        ++index;
        ++cursor;
    }
    return 0;
}
