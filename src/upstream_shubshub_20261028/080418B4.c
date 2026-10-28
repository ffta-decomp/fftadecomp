/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080418B4.c
 * Original SHA-256: 849dce78890f1ceb682b8d8482140fedcb1c15cfa262643f0ddccf62ae8f7785
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* Complete 0x080418B4..0x08041986: 210 bytes, 104 instructions. */
typedef struct {
    u8 unknown_00[0x0c];
    u16 *tiles;
    u8 unknown_10[5];
    u8 width;
    u8 unknown_16[6];
    u16 first_tile;
    u8 unknown_1e;
    u8 palette;
} TileMap;

void func_080418B4(u16 index, TileMap *map)
{
    u16 width = map->width;
    u32 attributes = (map->palette << 12) + map->first_tile;
    u16 tile;
    u16 *destination;
    u16 column;

    index = (u32)index % 5;
    tile = attributes + index * 32;
    destination = map->tiles + (index << 1) * width;
    destination[0] = tile++;
    destination[width] = tile++;
    destination[1] = tile++;
    destination[width + 1] = tile++;
    for (column = 2; column < 14; column++) {
        destination[column] = tile++;
        (destination + column)[width] = tile++;
    }
    destination[column] = 0;
    destination[column + 1] = 0;
    (destination + column)[width] = 0;
    (destination + column)[width + 1] = 0;
    for (; column < 16; column++) {
        destination[column + 2] = tile++;
        (destination + column)[width + 2] = tile++;
    }
    destination[column + 2] = 0;
    destination[column + 3] = 0;
    (destination + column)[width + 2] = 0;
    (destination + column)[width + 3] = 0;
}
