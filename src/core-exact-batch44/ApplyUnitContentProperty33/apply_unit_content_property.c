#include "interfaces.h"

void ApplyUnitContentProperty33(struct LiveUnitContentState *unit)
{
    u32 property;

    property = GetUnitProperty(unit, 33);
    if (property != 0)
        unit->content_markers[property] = 228;

    if (unit->kind != 0) {
        if ((u8)(unit->kind - 68) <= 1)
            unit->flags |= 0x0800;
    }
}
