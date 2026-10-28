#include "scene_source_record.h"

/* Read the Y byte from the same scene source record in pixel units. */
u32 GetSceneRecordPixelY(u32 index)
{
    register u32 normalized_index __asm__("r0") = (u8)index;
    SceneSourceRecord *records;

    __asm__ volatile ("" : "+r" (normalized_index));
    records = (*SCENE_STATE_SOURCE_POINTER)->source_records;
    return (u32)records[normalized_index].y << 3;
}
