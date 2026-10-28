#include "scene_context_abi.h"
extern u32 ReadSceneHandleSlot(u32 slot);
extern u32 HandleRecordBaseFromToken(u32 handle);


u32 HasSceneHandle(u32 handle_id_argument)
{
    u8 requested_id = (u8)handle_id_argument;
    s32 slot;
    for (slot = 0; slot < (s32)SCENE_HANDLE_SLOT_COUNT; ++slot) {
        u32 handle;
        u32 record;
        s16 record_id;
        handle = ReadSceneHandleSlot(slot);
        if (handle == 0)
            continue;
        if (requested_id == 0xffu)
            return 1;
        record = HandleRecordBaseFromToken(handle);
        record_id = *(s16 *)(u32)(record + 2u);
        if (record_id == requested_id)
            return 1;
    }
    return 0;
}
