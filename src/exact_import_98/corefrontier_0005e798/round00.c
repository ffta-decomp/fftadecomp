#include "interfaces.h"

void CancelMissionSelectionAndRefreshOperations(void)
{
    struct MissionOperationView *context;
    void **operations;
    gMissionOperation->selection_flag = 0;
    if (gMissionOperation->selected_mission != 0 &&
        gMissionOperation->cancellation_active != 0) {
        if (gMissionOperation->selected_participant != 0)
            gMissionOperation->selected_participant->field22 = 0;
        ResetSelectedMission();
        gMissionOperation->cancellation_active = 0;
    }
    context = gMissionOperation;
    context->selected_mission = 0;
    operations = context->operations;
    gMissionOperation->operation_count = EnumerateMissionOperations(
        operations, 16, (u8)ResolveCurrentSceneSelector(gMissionSave.selector));
    ConfigureMissionRuntime(gMissionRuntime, 0, 0, 20, 17, 1);
    SetMissionDisplayOptions(0, 0, 0, 0);
    OpenMissionChooser(3);
    SetMissionChooserEntries(gMissionOperation->operations,
                             gMissionOperation->operation_count);
}
