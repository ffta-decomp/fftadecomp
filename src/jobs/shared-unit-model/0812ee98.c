/* Method-local interface declarations from the frozen build. */
#include "ffta/unsigned_types.h"
#include "items/property_access.h"
extern u32 GetUnitProperty(const u8 *unit, u8 property);
extern u32 GetItemProperty(u16 item_id, u8 property);


u32 SelectUnitItemCategory(const u8 *unit, u16 item_id)
{
    u32 value;
    if (unit != 0 && (GetUnitProperty(unit, 40) & 4))
        return 19;
    if (item_id != 0)
        value = (u8)ReadItemEquipmentCategory(item_id);
    else
        value = 17;
    return value;
}
