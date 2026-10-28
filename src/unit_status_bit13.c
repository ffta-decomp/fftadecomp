#include "unit_status_flag_view.h"

int UnitField27HasBit13(const UnitStatusFlagView *unit)
{
    return unit != 0 && (unit->status_flags & 0x2000) != 0;
}
