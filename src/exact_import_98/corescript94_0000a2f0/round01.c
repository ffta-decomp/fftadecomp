#include "interfaces.h"
void BranchNestedScriptOnCurrentUnitValue(struct NestedUnitValueContext *context,
    const struct NestedUnitValueCommand *command) __asm__("CoreScript94_0000A2F0");
void BranchNestedScriptOnCurrentUnitValue(struct NestedUnitValueContext *context,
    const struct NestedUnitValueCommand *command)
{
    u8 *unit = ResolveScriptUnit(command->unit_selector);
    if (unit) {
        struct CurrentScriptUnit *current = GetContentContextPointerAt4();
        /* The role of this unit byte is still unresolved. */
        if (current->unit == unit && current->unit[0x101] == command->expected_unit_value)
            context->script_pc += command->skip_low | (command->skip_high << 8);
    }
}
