/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 11946243ba373da48154ed04cb3bb31e52dad97b
 * Original file: src/08049C24.c
 * Original SHA-256: fb3c1d17f4b3036096247ebdbd5f784b0bebafc6f2b9c4397e42da95d3578506
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred.
 */
#include "abi/interfaces/080008e0_bindings.h"

typedef struct {
    u8 unknown_00[0xC8];
    void *panel;
} MenuRecord;

typedef struct {
    u8 unknown_00[0x90];
    u16 *first_resource;
    u16 *second_resource;
    u8 unknown_98[0x8BC];
    MenuRecord records[1];
} MenuContext;

typedef struct {
    u8 unknown_00[0x10];
    u16 *tiles;
} TileStorage;

typedef struct {
    u8 unknown_00;
    u8 field_01;
    u8 unknown_02[0xC];
    u16 border_tile;
    u8 unknown_10[8];
    u16 *first_plane;
    u16 *second_plane;
    u8 unknown_20[8];
    u8 width;
    u8 height;
    u8 unknown_2A[2];
    u8 source_width;
    u8 source_height;
    u8 unknown_2E[6];
    u8 x;
    u8 y;
    u8 unknown_36[0x12];
    u8 field_48;
    u8 field_49;
    u8 field_4A;
    u8 field_4B;
} TileWindow;

extern MenuContext *g_state_03002810;
extern TileStorage data_03002740;
extern TileWindow data_030009E0[];
extern u16 data_06009960[];
extern TileWindow *func_0808A268(u32 index, u8 mode, u16 *first_resource,
    u16 *second_resource, u16 *first_tiles, u16 *second_tiles,
    u16 *first_output, u16 *second_output, u8 x, u8 y, u8 width, u8 height,
    u8 source_x, u8 source_y, u8 source_width, u8 source_height,
    u8 stride, u8 rows);
extern void func_08016344(u16 *tiles, u8 width, u8 height, u16 flags,
                         u8 stride, u16 tile, u8 palette);
extern void func_08016560(u16 *tiles, u8 width, u8 height, u16 flags,
                         u8 stride, u16 tile, u8 palette);
extern void func_0814186C(const void *source, void *destination, u32 control);
extern void func_08037C84(u32 index, void *panel, u32 renderer, u32 x,
                         u32 y, u32 row, u8 value, u32 enabled);
extern u32 func_0808A604(u32 renderer, u16 command);

/* Complete owner: 0x08049C24..0x08049E10, 492 bytes. */
void func_08049C24(u32 index, u32 height, u32 alternate)
{
    u16 first_fill;
    u16 second_fill;
    u16 graphics_fill;

    func_0808A268(4, 12, g_state_03002810->second_resource,
        g_state_03002810->first_resource, data_03002740.tiles,
        data_03002740.tiles + 0xD2, 0, 0, 4, 1, 14, height,
        4, 1, 14, height, 14, height);
    first_fill = 0;
    func_0814186C(&first_fill, data_030009E0[4].second_plane, 0x010000D2);
    second_fill = 0;
    func_0814186C(&second_fill, data_030009E0[4].first_plane, 0x010000D2);
    func_08016344(data_030009E0[4].second_plane, data_030009E0[4].width,
        data_030009E0[4].height, 0xC0, data_030009E0[4].width, 5, 12);
    func_08016560(data_030009E0[4].first_plane, 14, height, 0xC0, 14, 1, 12);
    data_030009E0[4].border_tile = 0xCB;
    data_030009E0[4].source_width = 14;
    data_030009E0[4].source_height = height;
    graphics_fill = 0;
    func_0814186C(&graphics_fill, data_06009960,
                 ((height * 14 * 32 / 2) & 0x1FFFFF) | 0x01000000);
    data_030009E0[4].x = 4;
    data_030009E0[4].y = 1;
    data_030009E0[4].border_tile = 0xCB;
    data_030009E0[4].field_01 = 0;
    data_030009E0[4].field_48 = 1;
    data_030009E0[4].field_49 = 1;
    data_030009E0[4].field_4A = 12;
    data_030009E0[4].field_4B = height - 3;
    if (alternate == 0)
        func_08037C84(index, g_state_03002810->records[index].panel,
                     4, 0, 0, 0, 131, 1);
    else
        func_08037C84(index, g_state_03002810->records[index].panel,
                     4, 0, 0, 0, 131, 0);
    func_0808A604(4, 2);
}
