#include "interfaces.h"
/* Opcode9: selected-unit state plus absolute/percentage threshold skip.
 * The dispatcher separately advances by the five-byte descriptor length. */
void Script94_0000A36C(struct NestedScript *script,const u8 *command)
{
    struct Unit *unit=NResolveUnit(command[1]);
    u8 threshold;
    int accepted;
    if (!unit || !unit->present || (u8)NUnitHasStatusBit8(unit) || (u8)NUnitHasStatusBit5(unit)) return;
    threshold=command[2];
    accepted=0;
    if (threshold<=9) {
        if (unit->current_value<threshold) goto test_result;
        goto skip;
    } else {
        if (unit->current_value>=unit->maximum_value*threshold/100) accepted=1;
    }
test_result:
    if (!accepted) return;
skip:
    script->pc+=command[3] | (command[4]<<8);
}
