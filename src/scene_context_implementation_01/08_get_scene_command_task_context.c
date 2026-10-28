#include "scene_context_abi.h"


u32 GetSceneCommandTaskContext(void)
{
    u32 root = *SCENE_ROOT_POINTER_ADDRESS;
    return *(volatile u32 *)(u32)(root + SCENE_TASK_CONTEXT_OFFSET);
}
