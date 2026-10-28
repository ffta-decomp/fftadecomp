#include "contract.h"
/* Game-owned scene-slot condition; the dispatcher adds command length later. */
void CoreScript94_0000A490(ScriptContext *context, const SceneSkipCommand *command)
{
    u8 matches = 0;
    u8 slot;
    u8 current_slot;
    current_slot = ResolveCurrentSceneSelector(gSave.scene_selector);
    if (command->selector == 0) {
        slot = 1;
        while (current_slot != slot) {
            slot++;
            if (slot > 6)
                goto check_match;
        }
        goto advance_pc;
    } else if (current_slot == command->selector)
        matches = 1;
check_match:
    if (matches == 0)
        return;
advance_pc:
    context->pc_bits += command->distance_low | (command->distance_high << 8);
}
