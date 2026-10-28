/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08042C10.c
 * Original SHA-256: 5be088b2420b8ebf68ee1604a1e00a4f85149727266fcf816e8a1ee6912ec84c
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[0xC];
    u16 *tiles;
    u8 unknown_10[5];
    u8 width;
    u8 unknown_16[6];
    u16 first_tile;
    u8 unknown_1E;
    u8 palette;
} TileMap08042C10;

/* 0x08042C10..0x08042CB2: 162 bytes, 80 instructions. */
void func_08042C10(u16 index, TileMap08042C10 *map, u16 offset)
{
    u16 width = map->width;
    u16 tile;
    u16 *destination;
    u16 column;

    index %= 7u;
    tile = index * 26 + map->first_tile;
    destination = map->tiles + (index << 1) * width;
    destination[0] = tile++ + offset;
    destination[1] = tile++ + offset;
    destination[width] = tile++ + offset;
    destination[width + 1] = tile++ + offset;
    for (column = 2; column <= 12; column++) {
        u16 *entry = destination + column;
        entry[0] = tile++ + (map->palette << 12);
        entry[width] = tile++ + (map->palette << 12);
    }
}
