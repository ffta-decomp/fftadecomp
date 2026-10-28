#include "unit_model_c01.h"

u32 SelectUnitEquippedStat20Or24Capped(const u8 *unit, u32 selector_raw)
{
    u8 selector = (u8)selector_raw;
    s32 result;

    if (selector & 1)
        result = (s32)UnitModelCall_CA624(unit, 1);
    else if (selector & 2)
        result = (s32)UnitModelCall_CA66C(unit, 1);
    else
        result = 0;

    return (u32)(result > 999 ? 999 : result);
}
