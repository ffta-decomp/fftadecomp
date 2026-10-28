#include "scene_context_abi.h"


u8 ResolveSceneCommandSelector(u32 ignored_selector)
{
    (void)ignored_selector;
    return *scene_root_byte(SCENE_COMMAND_BYTE_OFFSET);
}
