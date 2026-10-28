#include "interfaces.h"
void UpdateCurrentUnitAbilityCategory(u8 slot, u8 *state) __asm__("CoreScene34_0007E2C4");
void UpdateCurrentUnitAbilityCategory(u8 slot, u8 *state)
{
    u8 phase = *state;
    switch (phase) {
    case 0:
        gAbilitySelection->selection_result = phase;
        /* The existing helper overwrites unit_kind, but the native caller reads it. */
        PrepareAbilityCategory(1, gAbilitySelection->current_unit->kind,
            gAbilitySelection->candidate_list);
        ResetAbilitySelectionDisplay();
        BeginAbilityWindowOperation(3, 5);
        gAbilitySelection->category = 1;
        AttachAbilityChoiceCallback(&gAbilityChoiceTasks, 7, StepAbilityCategoryChoices);
        *state = 16;
        break;
    case 16:
        if (gAbilityChoiceTasks.slot_state[7] == 18)
            *state = gAbilityChoiceTasks.slot_state[7];
        break;
    case 9:
        if (gAbilitySelectionWindows[gAbilityWaitWindowIndex].state == 0)
            *state = gAbilityWaitContinuation;
        break;
    }
}
