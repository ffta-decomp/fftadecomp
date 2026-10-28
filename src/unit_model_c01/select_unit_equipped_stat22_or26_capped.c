#include "unit_model_c01.h"

u32 SelectUnitEquippedStat22Or26Capped(const u8 *unit, u32 selector_raw)
{
    u8 selector = (u8)selector_raw;
    s32 result;

    if (selector & 1)
        result = (s32)UnitModelCall_CA6B4(unit, 1);
    else if (selector & 2)
        result = (s32)UnitModelCall_CA6FC(unit, 1);
    else
        result = 0;

    return (u32)(result > 999 ? 999 : result);
}
