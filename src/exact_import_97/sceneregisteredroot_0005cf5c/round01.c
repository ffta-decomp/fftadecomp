#include "interfaces.h"

void UpdateMissionSelectionController(void *unused, u8 *state)
{
    u8 initial_state = *state;
    switch (initial_state) {
    case 0:
        gMissionSelection = AllocateMissionContext(sizeof(*gMissionSelection));
        gMissionClear(gMissionSelection, sizeof(*gMissionSelection));
        gMissionSave.active_mission = initial_state;
        gMissionSelection->message = 62;
        ConfigureMissionRuntime(gRuntimeInterface, 0, 0, 20, 17, 1);
        InitializeMissionLabel(&gMissionSelection->title, gMissionTitle, 216, 14);
        InitializeMissionLabel(&gMissionSelection->subtitle, gMissionSubtitle, 24, 14);
        *state = 1;
        break;
    case 255:
        if (gMissionSelection == 0)
            return;
        FreeMissionContext(gMissionSelection);
        gMissionSelection = 0;
        break;
    case 8:
        if (gMissionSelection->continuation != 0)
            DispatchMissionContinuation(gMissionSelection->continuation);
        CommitMissionContinuation();
        *state = 255;
        break;
    case 1:
        if (gSceneActive == 0) {
            SetupMissionContext(gMissionSelection);
            *state = 2;
        }
        break;
    case 2: *state = StepMissionSelection(); break;
    case 3: *state = StepMissionDetails(); break;
    case 4: *state = StepMissionTransaction(); break;
    case 5: *state = StepMissionConfirmation(); break;
    case 6:
        if ((u8)PollMissionContinuation() != 0)
            *state = 8;
        break;
    case 7: *state = StepMissionCommit(); break;
    }
    if (*state > 1 && gMissionSelection != 0)
        TickMissionInterface();
}
