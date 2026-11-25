#include "ffta/unsigned_types.h"
#include "items/property_access.h"
#include "jobs/unit_property_access.h"

extern u32 GetUnitProperty(const u8 *unit, u8 selector);
extern u32 GetItemProperty(u16 item_id, u8 selector);
extern const u32 gEquipmentClassMasks[];

/* Test the item category bit against the observed unit class equipment mask. */
u8 UnitItemCategoryAllowed(const u8 *unit, u16 item_id)
{
    u32 class_mask = gEquipmentClassMasks[ReadUnitJobEquipmentClassMaskIndex(unit)];
    u8 item_category = ReadItemEquipmentCategory(item_id);
    return (class_mask & (1u << (item_category - 1))) != 0;
}
