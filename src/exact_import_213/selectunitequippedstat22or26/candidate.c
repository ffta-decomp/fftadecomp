#include "interfaces.h"

u32 SelectUnitEquippedStat22Or26(const u8 *unit, u32 selector_raw,
                                u32 include_equipment_raw)
{
    u8 selector = selector_raw;
    u8 include_equipment = include_equipment_raw;

    if (1 & selector)
        return GetEquippedStat22(unit, include_equipment);
    if (2 & selector)
        return GetEquippedStat26(unit, include_equipment);
    return 0;
}
