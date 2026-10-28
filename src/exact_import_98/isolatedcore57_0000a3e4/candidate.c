#include "contract.h"
/* Opcode10 skips only when the resolved unit satisfies both status predicates. */
void IsolatedCore57_0000A3E4(ScriptContext *context, const ConditionalUnitSkip *command)
{
    const UnitStatusFlagView *unit;
    unit = (const UnitStatusFlagView *)FindUnitPoolRecordById(command->unit_id);
    if (unit != 0 && (u8)UnitField27HasBit13(unit) == 0 &&
        (u8)UnitField27HasBit15(unit) == 0)
        context->pc_bits += command->distance_low | (command->distance_high << 8);
}
