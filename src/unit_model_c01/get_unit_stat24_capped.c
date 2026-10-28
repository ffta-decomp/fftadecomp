#include "unit_model_c01.h"

u32 GetUnitStat24Capped(const u8 *unit)
{
    s32 result = (s32)UnitModelCall_CA66C(unit, 1);
    return (u32)(result > 999 ? 999 : result);
}
