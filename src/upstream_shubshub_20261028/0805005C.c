/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0805005C.c
 * Original SHA-256: 47aa63ddc98c770b199c2377e6d818c801ed78f5ef2ec0d3bc9be95c7872b429
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[0x0c];
    u16 *tiles;
    u8 unknown_10[5];
    u8 stride;
    u8 unknown_16[6];
    u16 tile;
    u8 mode;
} TileMap0805005C;

typedef struct {
    u8 unknown_00[0x48];
    TileMap0805005C map;
} MenuState0805005C;

void func_080157A8(u16 *tilemap, u8 column, u8 row, u8 width,
                   u8 height, u8 stride, u16 tile, u8 palette);
u16 func_080161A0(u8 x, u8 y, u8 mode);

void func_0805005C(MenuState0805005C *state)
{
    TileMap0805005C *map = &state->map;
    u16 *tiles;
    u16 saved;

    func_080157A8(map->tiles, 6, 0, 14, 1, map->mode, map->tile, 12);
    tiles = map->tiles + func_080161A0(6, 0, map->mode);
    saved = tiles[1];
    tiles[1] = tiles[map->stride];
    tiles[map->stride] = saved;
}
