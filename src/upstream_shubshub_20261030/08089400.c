/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 43f7f78cfe893ab4d99d2004e0740459589bfb5c (PR #20)
 * Original file: src/08089400.c
 * Original SHA-256: e77143580d53c3860a9c34a54baf84c3b6243c63259a07c274d862d2742dde54
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Validation: data/upstream-imports-20261030.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[0x1C];
    u16 *tiles;
    u8 unknown_20[8];
    u8 stride;
    u8 unknown_29[0x23];
} Tilemap08089400;

extern Tilemap08089400 data_030009E0[];

/* Complete [0x08089400, 0x080894AC): 172 bytes, 82 instructions. */
void func_08089400(u32 index, u16 tile_offset, u8 x, u8 y,
                   u8 width, u8 height)
{
    u16 *destination = data_030009E0[index].tiles;
    u16 tile;
    s32 row;
    s32 column;
    s32 offset;

    destination += data_030009E0[index].stride * y + x;
    tile = *destination & 0xFFF;

    for (row = 0; row < height; row++) {
        destination = data_030009E0[index].tiles;
        offset = row + y;
        destination += data_030009E0[index].stride * offset + x;
        for (column = 0; column < width; column++)
            destination[column] = tile++ + tile_offset;
    }
}
