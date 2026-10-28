#include "interfaces.h"
u8 CollectAvailableMissionItems(struct MissionInventoryRecord **output) __asm__("CoreFrontier_000612C8");
u8 CollectAvailableMissionItems(struct MissionInventoryRecord **output)
{
    struct MissionInventoryRecord *record;
    u32 count;
    s32 remaining;
    gMissionInventoryClear((u8 *)output, 264);
    record = gMissionInventory;
    count = 0;
    remaining = 63;
    do {
        if (record->item_id != 0 && record->mission_id == 0) {
            *output++ = record;
            count++;
        }
        remaining--;
        record++;
    } while (remaining >= 0);
    return count;
}
