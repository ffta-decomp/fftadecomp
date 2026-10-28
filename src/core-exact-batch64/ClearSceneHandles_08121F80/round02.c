#include "scene_vm_abi.h"
typedef signed int s32;
/* Only the root word and the handle tail are accessed by this cleanup. */
struct SceneHandleState {
    u32 root_handle;
    u8 unaccessed_04[16];
    u32 handles[0];
};
typedef char scene_handle_tail_is_20[
    ((u32)&(((struct SceneHandleState *)0)->handles) == 20) ? 1 : -1];
void ClearSceneHandles_08121F80(void)
{
    s32 index;
    for (index = 0; index < 16; ++index) {
        volatile struct SceneHandleState *state =
            (volatile struct SceneHandleState *)STATE_POINTER;
        void *handle = (void *)state->handles[index];
        if (handle) {
            SceneHelper_080058A4((void *)state->root_handle, handle);
            /* The callback may replace the state that owns this slot. */
            ((volatile struct SceneHandleState *)STATE_POINTER)->handles[index] = 0;
        }
    }
}
