/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08089248.c
 * Original SHA-256: 373a3dd4a805e6a11f8a9d2039578be43fa759b1fa648122a49c76816e945153
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[0x1c];
    u16 *tiles;
    u8 unknown_20[8];
    u8 stride;
    u8 unknown_29[0x23];
} Tilemap08089248;

extern Tilemap08089248 data_030009E0[];

/* 0x08089248..0x080892D8: 144 bytes, 70 instructions. */
void func_08089248(u32 index, u16 tile, u16 attributes,
                    u8 x, u8 y, u8 width, u8 height)
{
    s32 row;
    s32 column;
    s32 offset;
    u16 *destination;

    tile |= attributes;
    for (row = 0; row < height; row++) {
        destination = data_030009E0[index].tiles;
        offset = row + y;
        destination += data_030009E0[index].stride * offset + x;
        for (column = 0; column < width; column++)
            destination[column] = tile++;
    }
}
