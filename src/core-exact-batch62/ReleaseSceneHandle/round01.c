#include "scene_context_abi.h"
extern u32 ReadSceneHandleSlot(u32 slot);
extern void WriteSceneHandleSlot(u32 slot, u32 handle);


u32 ReleaseSceneHandle(u32 handle)
{
    s32 slot;
    for (slot = 0; slot < (s32)SCENE_HANDLE_SLOT_COUNT; ++slot) {
        u32 current = ReadSceneHandleSlot(slot);
        if (current != 0 && current == handle) {
            WriteSceneHandleSlot(slot, 0);
            return 1;
        }
    }
    return 0;
}
