#include "unit_model_c01.h"

u32 RefreshAndReadUnitDerivedByte(u8 *unit)
{
    const signed char *unit_bytes_at_fc;

    UnitModelCall_CA2E8(unit);
    unit_bytes_at_fc = (const signed char *)(unit + 0xfc);
    /* The retail load addresses the third byte from the unit+0xFC base. */
    return (u32)(s32)unit_bytes_at_fc[2];
}
