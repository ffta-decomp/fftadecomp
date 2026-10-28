#include "interfaces.h"

/* The enclosing dispatcher advances by the descriptor length separately. */
void AdvanceScriptForSelectedUnitCondition(struct ScriptContext *context,
                                           const struct ConditionalCommand *command)
{
    struct UnitRecord *unit;
    s8 selected_index = gUnitSelection.selected - 1;
    u32 distance;

    if ((u8)selected_index > 11)
        return;
    unit = &gUnitSelection.units[selected_index];
    if (unit->kind == 0 ||
        (u8)UnitField27HasBit14(unit) == 0 ||
        (u8)UnitField27HasBit8(unit) != 0 ||
        (u8)UnitField27HasBit5(unit) != 0) {
        distance = command->distance_low | command->distance_high << 8;
        context->pc += distance;
    }
}
