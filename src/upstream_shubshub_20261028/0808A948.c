/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0808A948.c
 * Original SHA-256: 91e0731da935a97add4866de178c9efc1f3f8c0c592a1cab7d4700ef7ba854b6
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    s8 left;
    s8 top;
    s8 right;
    s8 bottom;
} Rect0808A948;

typedef struct {
    u8 unknown_00[0x10];
    const u16 *first_tiles;
    const u16 *second_tiles;
    u8 unknown_18[8];
    u16 *first_buffer;
    u16 *second_buffer;
    u8 unknown_28[8];
    Rect0808A948 current;
    u8 unknown_34[0x10];
    Rect0808A948 saved;
    u8 unknown_48[4];
} Tilemap0808A948;

extern Tilemap0808A948 data_030009E0[];
extern void func_08000F48(const void *source, void *destination, u16 count);

/* 0x0808A948..0x0808AA18: 208 bytes, 99 instructions. */
void func_0808A948(u32 index)
{
    if (data_030009E0[index].first_buffer) {
        s32 x = data_030009E0[index].current.left;
        s32 y = data_030009E0[index].current.top;
        s32 offset = x + y * 32;
        const u16 *first_source = data_030009E0[index].first_tiles + offset;
        const u16 *second_source = data_030009E0[index].second_tiles + offset;
        u16 *first_destination = data_030009E0[index].first_buffer;
        u16 *second_destination = data_030009E0[index].second_buffer;
        s32 width = data_030009E0[index].current.right - x;
        s32 height = data_030009E0[index].current.bottom - y;

        while (height != 0) {
            func_08000F48(first_source, first_destination, width);
            first_source += 32;
            first_destination += width;
            func_08000F48(second_source, second_destination, width);
            second_source += 32;
            second_destination += width;
            height--;
        }
        data_030009E0[index].saved = data_030009E0[index].current;
    }
}
