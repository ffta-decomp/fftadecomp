#include "interfaces.h"
void ApplyMissionUnitSelectionResult(void) __asm__("CoreFrontier_0005E864");
void ApplyMissionUnitSelectionResult(void)
{
    u8 result = ReadMissionSelectorResult();
    switch (result) {
    case 3:
    case 4:
        {
            s16 selected_index = ReadMissionSelectedIndex();
            struct MissionUnitPrefix *participant;
            gMissionChoiceContext->participant = participant = gMissionChoiceContext->unit_slots[selected_index];
            participant->mission_id = gMissionChoiceContext->selected_mission->mission_id;
            gMissionChoiceContext->choice = QueryMissionChoice(1);
            gMissionChoiceContext->followup_state = 9;
            gMissionChoiceContext->phase = 18;
        }
        break;
    case 1:
    case 2:
        if (gMissionChoiceContext->participant)
            gMissionChoiceContext->participant->mission_id = 0;
        gMissionChoiceContext->followup_state = 5;
        gMissionChoiceContext->phase = 19;
        break;
    }
}
