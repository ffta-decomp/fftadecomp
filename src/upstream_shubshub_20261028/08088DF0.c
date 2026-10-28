/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08088DF0.c
 * Original SHA-256: b0e47754d807b69364891c0d23ca645cbd9470f78fd4015192702f9f6d8328e6
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u32 first;
    u32 second;
} Record08088DF0;

typedef struct {
    u32 active : 1;
    u32 enabled : 1;
    u32 visible : 1;
    u32 palette : 4;
    u32 unknown_07 : 1;
    u32 mode : 2;
    u32 variant : 1;
    u32 style : 2;
    u32 pending : 1;
    u32 reserved : 4;
    u32 unknown_12 : 14;
    Record08088DF0 entries[32];
    u8 count;
    u8 option;
    u8 selection;
    u8 unknown_107;
    u16 timer;
    u16 delay;
    u8 counter;
    u8 graphic;
    u8 state;
    u8 unknown_10f;
    u8 width;
    u8 height;
} Object08088DF0;

typedef struct {
    u32 unknown_00;
    Entry *surface;
} Render08088DF0;

extern Render08088DF0 data_03000E30;
extern const u8 data_08950D38[];
extern const u8 data_089514F4[];
extern void func_0804C598(Entry *base, u16 index, u16 selector,
                          u8 width, u8 count, u8 mode, u8 delay,
                          const u8 *graphics, const u8 *layout, u16 attributes);

/* 0x08088DF0..0x08088F5C: 364 bytes, 167 instructions. */
void func_08088DF0(Object08088DF0 *object, const Record08088DF0 *entries,
                    s32 count, s32 graphic, u32 palette, u32 visible,
                    u32 enabled, u32 mode, u32 variant, u32 style, u32 option)
{
    s32 i;
    u16 attributes;
    u16 selector;

    object->count = count;
    object->option = option;
    object->selection = 0xff;
    for (i = 0; i < count; i++)
        object->entries[i] = entries[i];
    object->graphic = graphic;
    object->state = 0;
    object->unknown_10f = 0;
    object->palette = palette;
    object->visible = visible;
    object->enabled = enabled;
    object->mode = mode;
    object->variant = variant;
    object->style = style;
    object->pending = 0;
    object->reserved = 0;

    if (mode == 3) {
        attributes = 0x1f0;
        selector = object->variant;
    } else if (mode == 2) {
        attributes = 0x1f2;
        selector = object->variant;
    } else {
        attributes = 0x120;
        selector = (object->mode << 1) | object->variant;
    }
    object->delay = 0;
    object->timer = 0;
    object->counter = 0;
    object->height = 0xf0;
    object->width = 0xf0;
    if (graphic != 0xff) {
        func_0804C598(data_03000E30.surface, object->graphic, selector,
                      0xf0, object->height, 1, object->palette,
                      data_08950D38, data_089514F4, attributes);
    }
    object->active = 1;
}
