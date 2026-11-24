/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 11946243ba373da48154ed04cb3bb31e52dad97b
 * Original file: src/080454A8.c
 * Original SHA-256: a2c79049600856e7f6e9c2ee434f91b9fcd44df6e5ad2db8c5dc9397e1181ba9
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred.
 */
#include "abi/interfaces/080008e0_bindings.h"

/* Complete 0x080454A8..0x08045668: 448 bytes. */
typedef struct {
    u8 unknown_00[0x90];
    u16 *first;
    u16 *second;
    u8 unknown_98[0xbb4];
    u8 text_context[0];
} MenuResources;

typedef struct {
    u8 unknown_00[0x10];
    u16 *tiles;
} TileStorage;

typedef struct {
    u8 unknown_00[0x0e];
    u16 attributes;
    u8 unknown_10[8];
    u16 *first_plane;
    u16 *second_plane;
    u8 unknown_20[8];
    u8 width;
    u8 height;
    u8 unknown_2a[2];
    u8 content_width;
    u8 content_height;
    u8 unknown_2e[0x1e];
} TileRenderer;

typedef struct {
    u8 unknown_00[0x124];
    const u8 *first;
    const u8 *second;
} Labels;

extern MenuResources *g_state_03002810;
extern TileStorage data_03002740;
extern TileRenderer data_030009E0[];
extern u8 data_02003CB0[];
extern u8 data_06009960[];
extern u8 data_06009FE0[];
extern const Labels data_085668B0;
extern void *func_0808A268(s32 index, u32 mode, u16 *first_resource,
    u16 *second_resource, u16 *first_tiles, u16 *second_tiles,
    u16 *first_buffer, u16 *second_buffer, u32 x, u32 y, u32 width,
    u32 height, s32 source_x, s32 source_y, u32 source_width,
    u32 source_height, u32 stride, u32 rows);
extern void func_0814186C(const void *source, void *destination, u32 control);
extern void func_08016344(u16 *destination, u8 width, u8 height, u16 flags,
    u8 stride, u16 tile, u8 palette);
extern void func_08016560(u16 *destination, u8 width, u8 height, u16 flags,
    u8 stride, u16 tile, u8 palette);
extern u16 *func_0808B8E4(u32 index, u32 plane, s32 x, s32 y);
extern void func_0808B7C0(s32 index, u16 *destination, u16 tile,
    u16 count, u16 flags);
extern u32 func_08018524(u8 *buffer, u16 tile, u8 variant);
extern void func_08035678(u16 value, u16 *destination, u32 count, u16 step);
extern u16 func_08015110(void *context, void *destination,
    const u8 *text, u8 mode, u8 reset);

void func_080454A8(void)
{
    s32 row;
    u16 second_zero;
    u16 first_zero;
    u16 graphics_zero;

    func_0808A268(4, 12, g_state_03002810->second,
        g_state_03002810->first, data_03002740.tiles,
        data_03002740.tiles + 0x134, 0, 0,
        1, 1, 28, 11, 1, 1, 28, 11, 28, 11);
    second_zero = 0;
    func_0814186C(&second_zero, data_030009E0[4].second_plane, 0x01000134);
    first_zero = 0;
    func_0814186C(&first_zero, data_030009E0[4].first_plane, 0x01000134);
    func_08016344(data_030009E0[4].second_plane,
        data_030009E0[4].width, data_030009E0[4].height - 4,
        0xc0, data_030009E0[4].width, 5, 12);
    func_08016560(data_030009E0[4].first_plane,
        28, 7, 0xc0, 28, 1, 12);
    data_030009E0[4].attributes = 0xcb;
    data_030009E0[4].content_width = 26;
    data_030009E0[4].content_height = 6;
    for (row = 0; row < 4; row += 2)
        func_0808B7C0(4, func_0808B8E4(4, 1, 1, row + 2),
            0xcb + row * 26, 26, 0xc000);
    func_08035678(0xc03e, func_0808B8E4(4, 1, 1, 1),
        func_08018524(data_02003CB0, 0x3e, 23), 1);
    graphics_zero = 0;
    func_0814186C(&graphics_zero, data_06009960, 0x01000d00);
    func_08015110(g_state_03002810->text_context,
        data_06009960, data_085668B0.first, 0, 1);
    func_08015110(g_state_03002810->text_context,
        data_06009FE0, data_085668B0.second, 0, 1);
}
