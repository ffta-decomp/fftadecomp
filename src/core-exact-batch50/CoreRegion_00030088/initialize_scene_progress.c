#include "interfaces.h"

/* Field captions remain tentative. Byte writes can alias the published root;
 * keep each later record/view access live instead of taking a snapshot. */
void InitializeSceneProgress(u32 retain_existing)
{
    s32 remaining;
    s32 record_offset;

    gSceneProgress->records = gSceneProgressData;
    gSceneProgress->view = (SceneProgressView *)gSceneProgressData;
    gSceneProgress->configuration_67c = gSceneConfiguration67c;
    gSceneProgress->configuration_680 = gSceneConfiguration680;
    ((SceneProgressView *)gSceneProgressData)->flag_20 = 0;
    gSceneProgress->view->flag_40 = 0;
    if (retain_existing != 0)
        return;

    gSceneProgress->view->field_10 = 40;
    gSceneProgress->view->field_06 = 120;
    gSceneProgress->view->field_08 = 216;
    gSceneProgress->view->field_0c = 156;
    SelectInitialProgressRegion();
    gSceneProgressData[0x3aa] = 1;
    gSceneProgressData[0x3ab] = 1;
    {
        SceneProgressContext **progress_cell = &gSceneProgress;
        u32 cleared = 0;
        record_offset = 0;
        for (remaining = 29; remaining >= 0; --remaining) {
            ((*progress_cell)->records + record_offset)[177] = cleared;
            ((*progress_cell)->records + record_offset)[176] = cleared;
            ((*progress_cell)->records + record_offset)[179] = cleared;
            ((*progress_cell)->records + record_offset)[178] = cleared;
            record_offset += 12;
        }
    }
    InitializeSceneSlot(7, 19, 1);
    InitializeSceneSlot(1, 17, 1);
    ResetRegionRecords();
    ClearMissionWorkingRecords();
    ResetMissionRecordMode();
    RefreshProgressionState();
}
