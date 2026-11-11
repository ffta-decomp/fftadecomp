/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 11946243ba373da48154ed04cb3bb31e52dad97b
 * Original file: src/0803E078.c
 * Original SHA-256: ea6752397c30c818b7543c232f47cacaf12d4013ef2554780f4a833a299ef68b
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred.
 */
#include "abi/interfaces/080008e0_bindings.h"

typedef struct {
    u8 unknown_00[0x90];
    u16 *first;
    u16 *second;
} MenuResources;

typedef struct {
    u8 unknown_00[0x14];
    u16 *tiles;
} TileStorage;

typedef struct {
    u8 unknown_00[0x0e];
    u16 attributes;
    u8 unknown_10[8];
    u16 *second_plane;
    u8 unknown_1c[0x0c];
    u8 width;
    u8 height;
    u8 unknown_2a[2];
    u8 content_width;
    u8 content_height;
    u8 unknown_2e[0x1e];
} TileRenderer;

extern MenuResources *g_state_03002810;
extern TileStorage data_03002740;
extern TileRenderer data_030009E0[];
extern u8 data_0600AFE0[];
extern void *func_0808A268(s32 index, u32 mode, u16 *first_resource,
    u16 *second_resource, u16 *first_tiles, u16 *second_tiles,
    u16 *first_buffer, u16 *second_buffer, u32 x, u32 y, u32 width,
    u32 height, s32 source_x, s32 source_y, u32 source_width,
    u32 source_height, u32 stride, u32 rows);
extern void func_08016800(void *destination, u8 width, u8 height, u16 flags,
    u8 stride, u16 border_tile, u16 fill_tile, u8 palette);
extern u16 *func_0808B8E4(u32 index, u32 plane, s32 x, s32 y);
extern void func_0808B7C0(s32 index, u16 *destination, u16 tile,
    u16 count, u16 flags);
extern void func_0814186C(const void *source, void *destination, u32 control);

/* Complete target 0x0803E078..0x0803E1C0: 328 bytes. */
void func_0803E078(s32 inset)
{
    u16 zero;

    func_0808A268(5, 12, g_state_03002810->second,
        g_state_03002810->first, data_03002740.tiles,
        data_03002740.tiles + 0x6c, 0, 0,
        (u8)((inset >> 1) + 6), 9, (u8)(18 - inset), 6,
        (s8)((inset >> 1) + 6), 9, (u8)(18 - inset), 6,
        (u8)(18 - inset), 6);
    data_030009E0[5].attributes = 0x17f;
    data_030009E0[5].content_width = 16 - inset;
    data_030009E0[5].content_height = 4;
    zero = 0;
    func_0814186C(&zero, data_0600AFE0,
        (((16 - inset) << 6) & 0x1fffff) | 0x01000000);
    func_08016800(data_030009E0[5].second_plane,
        data_030009E0[5].width, data_030009E0[5].height,
        0x800, data_030009E0[5].width, 13, 3, 11);
    func_0808B7C0(5, func_0808B8E4(5, 1, 1, 1),
        0x17f, 16 - inset, 0xb000);
    func_0808B7C0(5, func_0808B8E4(5, 1, 1, 3),
        0x17f + (16 - inset) * 2, 16 - inset, 0xb000);
}
