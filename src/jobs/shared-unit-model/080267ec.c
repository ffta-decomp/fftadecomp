/* Method-local interface declarations from the frozen build. */
#include "ffta/unsigned_types.h"
#include "items/property_access.h"
struct UnitEquipmentView { u8 unknown[42]; u16 equipment[5]; };
extern u32 GetItemProperty(u16,u8);

u32 UnitHasEquipmentForChoice(const struct UnitEquipmentView *unit, u8 choice)
{
    int slot;
    for (slot=0;slot<5;slot++) {
        u16 item_id = unit->equipment[slot];
        if (item_id != 0) {
            u16 item_class = ReadItemEquipmentCategory(item_id);
            switch (choice) {
            case 2:
                if (item_class == 15) return 1;
                break;
            case 3:
                if ((u16)(item_class-13) <= 1) return 1;
                break;
            }
        }
    }
    return 0;
}
