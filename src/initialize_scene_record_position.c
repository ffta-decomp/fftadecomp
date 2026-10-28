typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern u32 GetSceneRecordPixelX(u32 record_index);
extern u32 GetSceneRecordPixelY(u32 record_index);

#define SCENE_STATE_POINTER ((u32 *)0x03002810)

/* Place a scene record using the observed 20-byte source coordinate table.
 * The selector is one-based. The destination halfwords at +6 and +8 are
 * offset from the table's pixel coordinates by 6 and 4, respectively. */
void InitializeSceneRecordPosition(u32 selector)
{
    u32 index = ((selector << 24) + (255u << 24)) >> 24;
    u32 coordinate;
    u16 *record;

    coordinate = GetSceneRecordPixelX(index);
    {
        register u8 *scene __asm__("r1") = (u8 *)*SCENE_STATE_POINTER;
        /* Preserve the retail pointer-load register without extra code. */
        __asm__ volatile ("" : "+r" (scene));
        record = *(u16 **)(scene + 4);
        record[3] = coordinate + 6;
    }

    coordinate = GetSceneRecordPixelY(index);
    {
        register u8 *scene __asm__("r1") = (u8 *)*SCENE_STATE_POINTER;
        __asm__ volatile ("" : "+r" (scene));
        record = *(u16 **)(scene + 4);
        record[4] = coordinate + 4;
    }
}
