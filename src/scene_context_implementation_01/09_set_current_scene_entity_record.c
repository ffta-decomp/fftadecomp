#include "scene_context_abi.h"


void SetCurrentSceneEntityRecord(u32 entity_record)
{
    u32 root = *SCENE_ROOT_POINTER_ADDRESS;
    *(volatile u32 *)(u32)(root + SCENE_ENTITY_RECORD_OFFSET) =
        entity_record;
}
