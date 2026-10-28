#include "scene_context_abi.h"
extern u32 ReadSceneHandleSlot(u32 slot);
extern void WriteSceneHandleSlot(u32 slot, u32 handle);
extern u32 HandleRecordBaseFromToken(u32 handle);

u32 TryRegisterSceneHandle(u32 candidate)
{
    u32 candidate_record;
    s32 slot;
    candidate_record = HandleRecordBaseFromToken(candidate);
    for (slot = 0; slot < (s32)SCENE_HANDLE_SLOT_COUNT; ++slot) {
        u32 existing;
        s32 candidate_id_before_helper;
        u32 existing_record;
        s32 candidate_id_after_helper;
        s32 existing_id;
        existing = ReadSceneHandleSlot(slot);
        if (existing != 0) {
            candidate_id_before_helper = *(s16 *)
                (u32)(candidate_record + 2u);
            if (candidate_id_before_helper != 255 &&
                candidate_id_before_helper != 128) {
                existing_record = HandleRecordBaseFromToken(existing);
                candidate_id_after_helper = *(s16 *)
                    (u32)(candidate_record + 2u);
                existing_id = *(s16 *)(u32)(existing_record + 2u);
                if (candidate_id_after_helper == existing_id)
                    return 0;
            }
        } else {
            WriteSceneHandleSlot(slot, candidate);
            return 1;
        }
    }
    return 0;
}
