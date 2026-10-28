#include "interfaces.h"

u32 SelectUnitEquippedStat20Or24(const u8 *unit, u32 selector_raw,
                                u32 include_equipment_raw)
{
    u8 selector = (u8)selector_raw;
    u8 include_equipment = (u8)include_equipment_raw;
    u32 selected_stat;

    /* Bit zero takes precedence when both stat choices are requested. */
    if (selector & 1) {
        selected_stat = ReadEquippedStat20(unit, include_equipment);
    } else if ((selector & 2) == 0) {
        selected_stat = 0;
    } else {
        selected_stat = ReadEquippedStat24(unit, include_equipment);
    }
    return selected_stat;
}
