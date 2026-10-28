#include "scene_context_abi.h"


void SetSceneRuntimeControlByte(u32 value)
{
    *scene_root_byte(SCENE_RUNTIME_CONTROL_OFFSET) = (u8)value;
}
