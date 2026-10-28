#include "scene_context_abi.h"


void SetSceneCommandTaskContext(u32 task_context)
{
    u32 root = *SCENE_ROOT_POINTER_ADDRESS;
    *(volatile u32 *)(u32)(root + SCENE_TASK_CONTEXT_OFFSET) =
        task_context;
}
