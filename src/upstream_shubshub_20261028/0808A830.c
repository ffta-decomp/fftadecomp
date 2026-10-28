/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0808A830.c
 * Original SHA-256: 01def8d08246f5b2b3c9c4c18daa0365e2e5ed4789119222eb29a261d5e7126d
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    s8 left;
    s8 top;
    s8 right;
    s8 bottom;
} Rect0808A830;

typedef struct {
    u8 unknown_00[4];
    u8 tile_low;
    u8 tile_high;
    u8 unknown_06[0xA];
    u16 *first_tiles;
    u16 *second_tiles;
    u8 unknown_18[0x18];
    Rect0808A830 current;
    u8 unknown_34[0x18];
} Tilemap0808A830;

extern Tilemap0808A830 data_030009E0[];
extern void func_08000E40(u16 value, void *destination, u16 count);

/* 0x0808A830..0x0808A8C0: 144 bytes, 68 instructions. */
void func_0808A830(u32 index)
{
    u16 value = (data_030009E0[index].tile_high << 8) |
                data_030009E0[index].tile_low;
    s32 x = data_030009E0[index].current.left;
    s32 y = data_030009E0[index].current.top;
    s32 offset = x + y * 32;
    u16 *first_destination = data_030009E0[index].first_tiles + offset;
    u16 *second_destination = data_030009E0[index].second_tiles + offset;
    s32 width = data_030009E0[index].current.right - x;
    s32 height = data_030009E0[index].current.bottom - y;

    while (height != 0) {
        func_08000E40(value, first_destination, width);
        first_destination += 32;
        func_08000E40(value, second_destination, width);
        second_destination += 32;
        height--;
    }
}
