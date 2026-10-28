#include "interfaces.h"

void RunRosterManagementScene(void *unused_context, u8 *state)
{
    struct RosterSceneRoot *root = gRosterSceneRoot;
    u8 phase;
    root->dispatch_state = *state;
    phase = *state;
    switch (phase) {
    case 0:
        CopyRosterBytes(gRosterSceneRoot->saved_working_region,
                        gRosterWorkingRegion, 80);
        SetupRosterMode(0);
        gRosterSceneRoot->field_095e &= ~1;
        gRosterSceneRoot->field_043a = 3;
        gRosterInterruptState = 255;
        ResetRosterInterruptState();
        InitializeRosterDisplay();
        InitializeRosterDisplayLists();
        ResetRosterObjectRange(gRosterObjectHandles[1], 64);
        ConfigureRosterLayout();
        gRosterSceneRoot->field_0c1e |= 255;
        WriteRosterSceneSaveByte(51, 6);
        InitializeRosterTaskGroup(&gRosterPrimaryGroup, gRosterTaskMemory,
                                  gRosterTaskStates, 8);
        AttachRosterContinuation(&gRosterPrimaryGroup, 0, RosterMainContinuation);
        AttachRosterContinuation(&gRosterPrimaryGroup, 1, RosterEmptyContinuation);
        AttachRosterContinuation(&gRosterPrimaryGroup, 2, RosterEmptyContinuation);
        AttachRosterContinuation(&gRosterPrimaryGroup, 3, RosterEmptyContinuation);
        AttachRosterContinuation(&gRosterPrimaryGroup, 4, RosterDetailContinuation);
        AttachRosterContinuation(&gRosterPrimaryGroup, 7, RosterEmptyContinuation);
        AttachRosterContinuation(&gRosterPrimaryGroup, 5, RosterAuxiliaryContinuation);
        AttachRosterContinuation(&gRosterPrimaryGroup, 6, RosterInputContinuation);
        AttachRosterContinuation(&gRosterSecondaryGroup, 0, RosterSecondaryFirst);
        AttachRosterContinuation(&gRosterSecondaryGroup, 1, RosterSecondarySecond);
        EnableRosterInterruptState();
        CompactPersistentRoster();
        gRosterSceneRoot->pending_state = phase;
        *state = 5;
        break;
    case 5:
        AdvanceRosterTaskGroup(&gRosterPrimaryGroup, 8);
        *state = gRosterSceneRoot->dispatch_state;
        break;
    case 255:
        ResetRosterObjectRange(gRosterObjectHandles[1], 64);
        ClearRosterTaskGroup(&gRosterPrimaryGroup);
        RemoveRosterContinuation(&gRosterSecondaryGroup, 0);
        RemoveRosterContinuation(&gRosterSecondaryGroup, 1);
        TeardownRosterMode(0);
        CopyRosterBytes(gRosterWorkingRegion,
                        gRosterSceneRoot->saved_working_region, 80);
        ResetRosterInterruptState();
        RequestRosterReturnScene(5);
        break;
    }
}
