/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08054204.c
 * Original SHA-256: 31234aaf6d93cbd9e84b27c118a223d21001f4b505451ee2634df13f98adf223
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[0x0C];
    u16 *tiles;
    u8 unknown_10[5];
    u8 width;
    u8 unknown_16[9];
    u8 palette;
} Window;

/* Complete target: [0x08054204, 0x08054284), 128 bytes, 62 instructions. */
void func_08054204(Window *window, s8 row, u8 palette, u8 column, u8 length)
{
    u16 rowIndex = row;
    u16 *tiles = window->tiles + column + rowIndex * window->width;
    s32 i;
    s32 j;

    if (palette == 0xFF)
        palette = window->palette;
    for (i = 0; i < 2; i++)
    {
        for (j = 0; j < length; j++)
            tiles[j] = (tiles[j] & 0xFFF) | (palette << 12);
        tiles += window->width;
    }
}
