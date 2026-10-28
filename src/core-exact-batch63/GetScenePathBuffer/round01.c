#include "scene_context_abi.h"


u8 *GetScenePathBuffer(u32 slot_argument)
{
    u32 slot = (u8)slot_argument;
    volatile u32 *root_address = SCENE_ROOT_POINTER_ADDRESS;
    u32 offset = SCENE_PATH_BASE_OFFSET + slot * SCENE_PATH_SLOT_STRIDE;
    return (u8 *)(u32)(*root_address + offset);
}
