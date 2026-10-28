#include "scene_source_record.h"

/* Read the X byte from a 20-byte scene source record in pixel units. */
u32 GetSceneRecordPixelX(u32 index)
{
    register u32 normalized_index __asm__("r0") = (u8)index;
    SceneSourceRecord *records;

    /* Keep index truncation before the pointer chain, as in retail. */
    __asm__ volatile ("" : "+r" (normalized_index));
    records = (*SCENE_STATE_SOURCE_POINTER)->source_records;
    return (u32)records[normalized_index].x << 3;
}
