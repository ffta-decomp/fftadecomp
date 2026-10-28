/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080892D8.c
 * Original SHA-256: 954ff1421a0a092708f3e68e50fee33d5f2c95784bd308fe3b0ec654462559b5
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[0x18];
    u16 *tiles;
    u8 unknown_1c[0x0c];
    u8 stride;
    u8 unknown_29[0x23];
} TileRenderer;

extern TileRenderer data_030009E0[];

void func_080892D8(u32 renderer_index, u16 tile, u16 attributes,
                   u8 x, u8 y, u8 width, u8 height)
{
    u16 value = tile | attributes;
    s32 row;
    s32 column;

    for (row = 0; row < height; row++) {
        u16 *destination = data_030009E0[renderer_index].tiles;
        destination += (row + y) * data_030009E0[renderer_index].stride + x;

        for (column = 0; column < width; column++) {
            destination[column] = value++;
        }
    }
}
