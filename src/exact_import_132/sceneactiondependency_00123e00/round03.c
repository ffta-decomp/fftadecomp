#include "interfaces.h"

void SceneActionDependency_00123E00(u8 mode)
{
    int index;
    SceneUnit *unit;
    if (mode == 7) {
        RestorePreviousSceneMode();
        return;
    }
    WriteSceneSaveByte(53, 0);
    gSceneClearRoutine(gSceneUnitsToClear, 3168);
    ResetSceneUnits();
    ClearSceneObject(&gSceneObjectCell);
    for (index = 580; index <= 589; ++index)
        SetSceneGameFlag((u16)index, 0);
    SetSceneGameFlag(595, 0);
    gSceneContent.counter_aa = 0;
    gSceneContent.counter_a9 = 0;
    gSceneContent.counter_a8 = 0;
    gSceneContent.reference_1bd6 = 0;
    switch (mode) {
    case 0:
        WriteSceneSaveByte(51, 0);
        InitializeSceneObject(&gSceneObjectCell, 0);
        EnsureSceneRuntimeObject();
        AttachSceneContinuation(&gSceneTaskGroup, 4, SceneCoreCallback);
        AttachSceneContinuation(&gSceneTaskGroup, 2, BattleFrameCallback);
        AttachSceneContinuation(&gSceneTaskGroup, 5, SceneAuxiliaryCallback);
        AttachSceneContinuation(&gSceneTaskGroup, 6, SceneFinishCallback);
        AttachSceneContinuation(&gSceneTaskGroup, 7, 0);
        break;
    case 1:
        WriteSceneSaveByte(51, 0);
        EnsureSceneRuntimeObject();
        gSceneRuntime.field_96 = 0;
        gSceneRuntime.field_94 = 0;
        gSceneSave.pending_operations &= ~23u;
        gSceneSave.reference_3c2e = 0xffff;
        gSceneSave.reference_3c9c = -1;
        gSceneSave.marker_3c9f = 0;
        gSceneSave.marker_3c9e = 0;
        unit = gSceneSave.units;
        for (index = 0; index < 24; ++index, ++unit) {
            if (unit->identity != 0) {
                if ((unit->flags & 0x400) != 0)
                    unit->flags &= 0xfbff;
                if ((unit->flags & 0x80) != 0)
                    unit->flags &= 0xff7f;
            }
        }
        for (index = 544; index <= 550; ++index)
            SetSceneGameFlag((u16)index, 0);
        FinishSceneUnitReset();
        AttachSceneContinuation(&gSceneTaskGroup, 4, SceneCoreCallback);
        AttachSceneContinuation(&gSceneTaskGroup, 2, BattleFrameCallback);
        AttachSceneContinuation(&gSceneTaskGroup, 5, SceneAuxiliaryCallback);
        AttachSceneContinuation(&gSceneTaskGroup, 6, SceneFinishCallback);
        AttachSceneContinuation(&gSceneTaskGroup, 7, UnitSelectionCallback);
        break;
    case 2:
        WriteSceneSaveByte(51, 1);
        InitializeSceneObject(&gSceneObjectCell, 0);
        EnsureSceneRuntimeObject();
        gSceneSave.mode_marker = 0;
        AttachSceneContinuation(&gSceneTaskGroup, 4, SceneCoreCallback);
        AttachSceneContinuation(&gSceneTaskGroup, 2, BattleFrameCallback);
        AttachSceneContinuation(&gSceneTaskGroup, 6, SceneFinishCallback);
        if ((u8)ReadSceneGameFlag(64) != 0) {
            AttachSceneContinuation(&gSceneTaskGroup, 5, MissionSceneCallback);
            AttachSceneContinuation(&gSceneTaskGroup, 7, MissionSceneFinalCallback);
        } else {
            AttachSceneContinuation(&gSceneTaskGroup, 5, BattleSceneCallback);
            AttachSceneContinuation(&gSceneTaskGroup, 7, BattleSceneFinalCallback);
        }
        break;
    case 3:
        WriteSceneSaveByte(51, 3);
        InitializeSceneObject(&gSceneObjectCell, 0);
        gSceneSave.mode_marker = 0;
        AttachSceneContinuation(&gSceneTaskGroup, 4, SceneCoreCallback);
        AttachSceneContinuation(&gSceneTaskGroup, 2, BattleFrameCallback);
        AttachSceneContinuation(&gSceneTaskGroup, 5, CollectionSceneCallback);
        AttachSceneContinuation(&gSceneTaskGroup, 6, SceneFinishCallback);
        break;
    case 4:
        WriteSceneSaveByte(51, 2);
        InitializeSceneObject(&gSceneObjectCell, 0);
        gSceneSave.mode_marker = 0;
        AttachSceneContinuation(&gSceneTaskGroup, 4, SceneCoreCallback);
        AttachSceneContinuation(&gSceneTaskGroup, 2, BattleFrameCallback);
        AttachSceneContinuation(&gSceneTaskGroup, 5, SaveSceneCallback);
        AttachSceneContinuation(&gSceneTaskGroup, 6, SceneFinishCallback);
        break;
    case 5:
        WriteSceneSaveByte(51, 4);
        InitializeSceneObject(&gSceneObjectCell, 0);
        gSceneSave.mode_marker = 0;
        AttachSceneContinuation(&gSceneTaskGroup, 4, SceneCoreCallback);
        AttachSceneContinuation(&gSceneTaskGroup, 2, BattleFrameCallback);
        AttachSceneContinuation(&gSceneTaskGroup, 5, GameControllerCallback);
        AttachSceneContinuation(&gSceneTaskGroup, 6, SceneFinishCallback);
        break;
    case 6:
        WriteSceneSaveByte(51, 5);
        InitializeSceneObject(&gSceneObjectCell, 0);
        gSceneSave.mode_marker = 0;
        AttachSceneContinuation(&gSceneTaskGroup, 4, SceneCoreCallback);
        AttachSceneContinuation(&gSceneTaskGroup, 2, BattleFrameCallback);
        AttachSceneContinuation(&gSceneTaskGroup, 5, ScenePolicyCallback);
        AttachSceneContinuation(&gSceneTaskGroup, 6, SceneFinishCallback);
        break;
    }
}
