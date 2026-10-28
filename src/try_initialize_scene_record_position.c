typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern u32 GetSceneSelectorValueByIndex(u32 selector);
extern u32 GetSceneRecordPixelX(u32 record_index);
extern u32 GetSceneRecordPixelY(u32 record_index);

#define SCENE_STATE_POINTER ((u32 *)0x03002810)

/* Resolve a one-based selector before writing the current scene position.
 * Retail reads the selector three times: once for the gate and once per
 * coordinate. Preserve those reads in case the backing state changes. */
u32 TryInitializeSceneRecordPosition(u32 selector)
{
    u8 slot = (u8)selector;
    u32 selected;
    u32 coordinate;
    u16 *record;

    if ((u8)GetSceneSelectorValueByIndex(slot) != 0) {
        selected = (u8)(GetSceneSelectorValueByIndex(slot) - 1);
        coordinate = GetSceneRecordPixelX(selected);
        {
            register u8 *scene __asm__("r1") = (u8 *)*SCENE_STATE_POINTER;
            /* Preserve the retail pointer-load register without extra code. */
            __asm__ volatile ("" : "+r" (scene));
            record = *(u16 **)(scene + 4);
            record[3] = coordinate + 6;
        }

        selected = (u8)(GetSceneSelectorValueByIndex(slot) - 1);
        coordinate = GetSceneRecordPixelY(selected);
        {
            register u8 *scene __asm__("r1") = (u8 *)*SCENE_STATE_POINTER;
            __asm__ volatile ("" : "+r" (scene));
            record = *(u16 **)(scene + 4);
            record[4] = coordinate + 4;
        }
        return 1;
    }
    return 0;
}
