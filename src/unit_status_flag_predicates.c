#include "unit_status_flag_view.h"

int UnitField27HasBit3(const UnitStatusFlagView *unit)
{
    return unit != 0 && (unit->status_flags & 0x0008) != 0;
}

int UnitField27HasBit4(const UnitStatusFlagView *unit)
{
    return unit != 0 && (unit->status_flags & 0x0010) != 0;
}

int UnitField27HasBit2(const UnitStatusFlagView *unit)
{
    return unit != 0 && (unit->status_flags & 0x0004) != 0;
}

int UnitField27HasBit6(const UnitStatusFlagView *unit)
{
    return unit != 0 && (unit->status_flags & 0x0040) != 0;
}

int UnitField27HasBit5(const UnitStatusFlagView *unit)
{
    return unit != 0 && (unit->status_flags & 0x0020) != 0;
}
