/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0800D664.c
 * Original SHA-256: 660d6440453f29da0f1d6eb1df9ee20609b690e940d41341fd9298010cf855dd
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x0800D664..0x0800D73C: 216 bytes. */
typedef struct {
    u32 tile : 16;
    u32 layer : 8;
    u32 palette : 8;
    u32 x : 8;
    u32 y : 8;
    u32 unknown_30 : 16;
} PackedEntry;

typedef struct {
    u16 tile;
    u8 unknown_02[2];
    u8 layer;
    u8 palette;
    u8 x;
    u8 y;
    u8 unknown_08[20];
} Entry28;

extern Entry28 *func_0800C614(void *object);

void func_0800D664(void *object, u8 mode, u8 index, u8 x,
                   u8 y, u8 palette, u16 tile, u8 layer)
{
    PackedEntry packed;
    Entry28 *entry = 0;
    const u8 *bytes;

    switch (mode) {
    case 0:
        entry = func_0800C614(object);
        break;
    case 1:
        entry = func_0800C614(object) + index;
        break;
    case 2:
        entry = func_0800C614(object) + index;
        break;
    }
    packed.tile = tile;
    packed.palette = palette;
    packed.x = x;
    packed.y = y;
    packed.layer = layer;
    bytes = (const u8 *)&packed;
    entry->tile = *(const u16 *)bytes;
    entry->layer = bytes[2];
    entry->palette = bytes[3];
    entry->x = bytes[4];
    entry->y = bytes[5];
}
