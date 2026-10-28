#include "unit_status_flag_view.h"

int UnitField27HasBit8(const UnitStatusFlagView *unit)
{
    return unit != 0 && (unit->status_flags & 0x0100) != 0;
}
