#include "interfaces.h"
u32 ClearSceneStoryUnitState(void *scene, const u8 *command) __asm__("Scene51_00123860");
u32 ClearSceneStoryUnitState(void *scene, const u8 *command)
{
    struct StoryCleanupState *cleanup = &gStoryCleanup;
    cleanup->cleanup_flag = 0;
    ClearStoryUnitFlags();
    CommitStoryUnitPropertyFlags();
    CommitOccupiedUnitCountFlag();
    /* Both physical views share the native saved-game state allocation. */
    RefreshStoryUnitValues((void *)((u32)cleanup - 0x2050),24);
    return 0x110;
}
