#include "interfaces.h"

/* Inferred alias: BranchScriptForUnit13AndTransactionValue. */
void CoreScript94_0000A564(struct NestedScriptContext *context, const u8 *command)
{
    if (FindUnitPoolRecordById(13) != 0 &&
        gEwramBase.transaction_value_3c9c == 320) {
        u32 displacement = command[1] | (command[2] << 8);
        /* The dispatcher adds descriptor length after this halfword update. */
        context->pc = displacement + context->pc;
    }
}
