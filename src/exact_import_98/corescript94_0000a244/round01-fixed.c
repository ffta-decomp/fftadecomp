#include "interfaces-linkage.h"
void BranchNestedScriptOnUnitEligibility(struct NestedUnitBranchContext *context,
    const struct NestedUnitBranchCommand *command) __asm__("CoreScript94_0000A244");
void BranchNestedScriptOnUnitEligibility(struct NestedUnitBranchContext *context,
    const struct NestedUnitBranchCommand *command)
{
    u8 *unit = ResolveScriptUnit(command->unit_selector);
    if (unit && !(u8)UnitField27HasBit5(unit) && !(u8)UnitField27HasBit8(unit)) {
        if (command->unit_selector == 128) {
            if ((u8)UnitField27HasBit15(unit) && (u8)UnitField27HasBit14(unit)) {
                if ((u8)UnitField19IsZero(unit) || UnitStateE8HasBit6(unit))
                    return;
            }
        } else {
            if ((u8)UnitField19IsZero(unit) || UnitStateE8HasBit6(unit) ||
                UnitStateE9HasBit0(unit) || UnitStateE9HasBit3(unit) ||
                UnitStateE9HasBit4(unit))
                return;
        }
        /* The dispatcher interprets this stored halfword as a signed PC. */
        context->script_pc += command->skip_low | (command->skip_high << 8);
    }
}
