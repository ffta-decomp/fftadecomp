/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08053C74.c
 * Original SHA-256: 8742d7d6fc006842fb3a52a75b3a700a93498d524218efd875d50b496dcbf7ed
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[0x0C];
    u16 *tiles;
    u8 unknown_10[5];
    u8 count;
    u8 unknown_16[6];
    u16 tile;
    u8 unknown_1E;
    u8 tag;
} TileMap;

typedef struct {
    u8 unknown_00[0x10];
    u8 x;
    u8 y;
    u8 width;
    u8 height;
    u8 unknown_14[0x18];
    TileMap tilemap;
} Menu;

typedef struct {
    u8 unknown_00[0x10];
    u8 *tiles;
} GraphicsState;

extern GraphicsState data_030008B0;
extern const u8 *const data_083937F8[];

void func_08013A88(void *destination, u16 count);
void func_08015110(void *context, void *destination, const void *source,
                   u32 mode, u32 enabled);
void func_0802979C(void *context, void *destination, u8 layer,
                   u32 first, u32 second);
void func_0802AB64(TileMap *tilemap, u16 x, u16 tile, u8 width,
                   u8 rows, u16 palette, u8 enabled);
void func_0802AC14(Menu *menu, u16 *source, u8 x, u8 y, u8 height);

/* Complete target: [0x08053C74, 0x08053DE8), 372 bytes. */
void func_08053C74(Menu *menu, void *context, u8 first_layer,
                   u8 second_layer, u8 rebuild)
{
    u8 *tiles;

    if (rebuild) {
        tiles = data_030008B0.tiles + menu->tilemap.tile * 32;
        func_08013A88(tiles, menu->tilemap.count * 2);
        func_08015110(context, tiles, data_083937F8[2], 5, 1);
        func_0802979C(context, tiles + 0x1C0, first_layer, 2, 5);

        tiles = data_030008B0.tiles +
                (menu->tilemap.count * 2 + menu->tilemap.tile) * 32;
        func_08013A88(tiles, menu->tilemap.count * 2);
        func_08015110(context, tiles, data_083937F8[3], 5, 1);
        func_0802979C(context, tiles + 0x1C0, second_layer, 2, 5);

        func_0802AB64(&menu->tilemap, 0, menu->tilemap.tile, menu->width,
                       menu->tilemap.count, menu->tilemap.tag, 1);
        func_0802AB64(&menu->tilemap, menu->width * 2,
                       menu->tilemap.count * 2 + menu->tilemap.tile,
                       menu->width, menu->tilemap.count, menu->tilemap.tag, 1);
        func_0802AC14(menu, menu->tilemap.tiles, menu->x + 1,
                       menu->y, menu->height);
    } else {
        tiles = data_030008B0.tiles + menu->tilemap.tile * 32;
        func_0802979C(context, tiles + 0x1C0, first_layer, 2, 5);
        tiles = data_030008B0.tiles +
                (menu->tilemap.count * 2 + menu->tilemap.tile) * 32;
        func_0802979C(context, tiles + 0x1C0, second_layer, 2, 5);
    }
}
