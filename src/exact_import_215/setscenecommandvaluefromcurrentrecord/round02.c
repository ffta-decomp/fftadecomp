#include "interfaces.h"

u32 SetSceneCommandValueFromCurrentRecord(void *scene_context, const u8 *command)
{
    (void)scene_context;
    if (command[1] == 0) {
        u16 content_index = (u16)ReadCurrentContentIndex();
        u32 record_offset = (u32)content_index * 40;
        const ContentDefinition *record =
            (const ContentDefinition *)(record_offset + 0x0854cd54);
        WriteSceneMapId(7, record->map_id);
    } else {
        WriteSceneMapId(7, command[1]);
    }
    SceneRuntimeState = 10;
    return 274;
}
