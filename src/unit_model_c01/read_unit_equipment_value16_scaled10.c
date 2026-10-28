#include "unit_model_c01.h"

u32 ReadUnitEquipmentValue16Scaled10(const u8 *unit)
{
    /* The retail Thumb sequence performs an unbounded modulo-32 multiply. */
    return UnitModelCall_CA394(unit) * 10u;
}
