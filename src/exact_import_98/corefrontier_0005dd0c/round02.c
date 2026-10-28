#include "interfaces.h"
struct MissionInventoryRecord *FindAvailableMissionItem(u16 item) __asm__("CoreFrontier_0005DD0C");
struct MissionInventoryRecord *FindAvailableMissionItem(u16 item)
{
    u16 inventory_id = item - 375;
    s32 index = 0;
    struct MissionItemChoiceContext *context = gMissionItemChoices;
    if (index < context->item_count) {
        struct MissionInventoryRecord **cursor = context->items;
        s32 count = context->item_count;
        do {
            struct MissionInventoryRecord *record = *cursor;
            if (record->item_id != 0 && record->mission_id == 0 && record->item_id == inventory_id)
                return record;
            cursor++;
            index++;
        } while (index < count);
    }
    return 0;
}
