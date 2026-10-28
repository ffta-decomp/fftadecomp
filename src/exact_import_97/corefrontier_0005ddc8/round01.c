#include "interfaces.h"
void DetachMissionStatusSelection(u16 assignment_slot) __asm__("CoreFrontier_0005DDC8");
void DetachMissionStatusSelection(u16 assignment_slot)
{
    struct MissionStatusRecord *status =
        gMissionSelectionContext->status_records[gMissionSelectionContext->status_count + assignment_slot];
    if (status) {
        status->mission_id = 0;
        status->flags &= ~1;
        gMissionSelectionContext->status_records[gMissionSelectionContext->status_count + assignment_slot] = 0;
    }
    gMissionSelectionContext->selected_mission->assignments[assignment_slot] = 0;
}
