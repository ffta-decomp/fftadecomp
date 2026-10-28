#include "interfaces.h"
u32 FinishSceneAndApplyPendingRosterCleanup(void *unused,const u8 *command)
{
    if(command[1]!=0) {
        u8 *buffer;
        DestroySceneRestoreChild(&gSceneRestoreChild);
        ReleaseCurrentSceneState();
        RefreshSceneRestoreResources();
        buffer=gSceneRestoreBuffer;
        DecodeSceneRestoreResource(buffer,gSceneRestoreResource);
        CpuFastSetSceneRestore(buffer,gSceneRestoreVram,1088);
        if((u8)ReadSceneRestoreFlag(64)!=0) {
            UpdateCurrentContentFlag(0);
            RefreshSceneRestoreDisplay();
        }
        if(gSceneSaveBlock.pending_operations&8) {
            CompactSavedUnitRoster();
            gSceneSaveBlock.pending_operations&=~8;
        }
    } else {
        EnsureSceneRestoreActor();
    }
    return 0x110;
}
