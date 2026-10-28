#include "unit_status_flag_view.h"

int UnitField27HasBit14(const UnitStatusFlagView *unit)
{
    return unit != 0 && (unit->status_flags & 0x4000) != 0;
}
