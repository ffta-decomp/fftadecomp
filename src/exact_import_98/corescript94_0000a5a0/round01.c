#include "interfaces.h"
void BranchNestedScriptWhenNoEligibleUnits(struct NestedEmptyUnitContext *context,
    const struct NestedEmptyUnitCommand *command) __asm__("CoreScript94_0000A5A0");
void BranchNestedScriptWhenNoEligibleUnits(struct NestedEmptyUnitContext *context,
    const struct NestedEmptyUnitCommand *command)
{
    if (!CountEligibleScriptUnits(GetContentConsumerContext()))
        context->script_pc += command->skip_low | (command->skip_high << 8);
}
