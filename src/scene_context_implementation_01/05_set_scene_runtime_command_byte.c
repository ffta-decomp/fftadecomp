#include "scene_context_abi.h"
extern void WriteSaveByte(u32 save_index, u32 value);

void SetSceneRuntimeCommandByte(u32 value)
{
    u8 byte_value = (u8)value;
    *scene_root_byte(SCENE_COMMAND_BYTE_OFFSET) = byte_value;
    WriteSaveByte(20u, byte_value);
}
