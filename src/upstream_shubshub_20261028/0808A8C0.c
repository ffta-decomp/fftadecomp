/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0808A8C0.c
 * Original SHA-256: 28d9e6a56ad30ac9bdb694b0d3d64c62ffc43e110f276fe308a0103ab205356c
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[0x10];
    u16 *first_plane;
    u16 *second_plane;
    u8 unknown_18[0x18];
    s8 left;
    s8 top;
    s8 right;
    s8 bottom;
    u8 unknown_34[0x18];
} TileRenderer;

extern TileRenderer data_030009E0[];
extern void func_08000E40(u16 value, u16 *destination, u16 count);

void func_0808A8C0(u32 index)
{
    u16 value = 0;
    s32 x = data_030009E0[index].left;
    s32 y = data_030009E0[index].top;
    s32 offset = x + (y << 5);
    u16 *first = data_030009E0[index].first_plane + offset;
    u16 *second = data_030009E0[index].second_plane + offset;
    s32 width = data_030009E0[index].right - x;
    s32 height = data_030009E0[index].bottom - y;

    while (height != 0) {
        func_08000E40(value, first, width);
        first += 32;
        func_08000E40(value, second, width);
        second += 32;
        height--;
    }
}
