#include "unit_status_flag_view.h"

int UnitField27HasBit15(const UnitStatusFlagView *unit)
{
    return unit != 0 && (unit->status_flags & 0x8000) != 0;
}
