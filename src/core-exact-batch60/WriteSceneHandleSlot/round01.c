#include "scene_context_abi.h"
/* Tail extent belongs to the caller; this view asserts only the observed base. */
struct SceneHandleSlots {
    u8 prefix[20];
    u32 handles[0];
};
typedef char scene_handle_base_is_20[
    ((u32)&(((struct SceneHandleSlots *)0)->handles) == 20) ? 1 : -1];
void WriteSceneHandleSlot(u32 slot, u32 handle)
{
    volatile struct SceneHandleSlots *root =
        (volatile struct SceneHandleSlots *)*SCENE_ROOT_POINTER_ADDRESS;
    root->handles[slot] = handle;
}
