/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 43f7f78cfe893ab4d99d2004e0740459589bfb5c (PR #20)
 * Original file: src/08079838.c
 * Original SHA-256: 8ab023aa8b9465de4ddc15013dfa1d8c65f654bfa96128fef45518612e8063c2
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Validation: data/upstream-imports-20261030.json.
 */
#include "ffta.h"

/* Complete 0x08079838..0x080799C0: 392 bytes, 165 instructions. */
typedef struct {
    u8 unknown_00[0x14];
    u16 *second_plane;
    u16 *first_plane;
    u8 unknown_1c[0x2d50 - 0x1c];
    void *resource_2d50;
} ResourceContext08079838;

typedef struct {
    u8 unknown_00[0x14];
    u16 *first_tiles;
    u8 unknown_18[0x14];
    u16 *second_tiles;
} TileStorage08079838;

typedef struct {
    u8 unknown_00;
    u8 mode;
    u8 unknown_02[0x0c];
    u16 attributes;
    u8 unknown_10[8];
    void *second_text;
    void *first_text;
    u8 unknown_20[8];
    u8 text_x;
    u8 text_y;
    u8 unknown_2a[0x0a];
    u8 x;
    u8 y;
    u8 unknown_36[0x12];
    u8 source_x;
    u8 source_y;
    u8 width;
    u8 height;
} TileRenderer08079838;

extern ResourceContext08079838 *data_03002818;
extern TileStorage08079838 data_03002740;
extern TileRenderer08079838 data_030009E0[];
extern u8 data_02003CB0[];

extern void func_0808A268(u32 index, u32 mode, u16 *first_resource,
    u16 *second_resource, u16 *first_tiles, u16 *second_tiles,
    u32 first_offset, u32 second_offset, u32 x, u32 y, u32 width, u32 height,
    u32 source_x, u32 source_y, u32 source_width, u32 source_height,
    u32 stride, u32 rows);
extern void func_0808136C(u32 index, void *resource, u32 count, u32 mode,
                          u32 first, u32 second);
extern void func_08016344(void *, u8, u8, u16, u8, u16, u8);
extern void func_08016560(void *, u8, u8, u16, u8, u16, u8);
extern u16 *func_0808B8E4(u32 index, u32 plane, s32 x, s32 y);
extern u32 func_08018524(u8 *destination, u16 code, u8 variant);
extern void func_08035678(u16 value, u16 *destination, u32 count, u16 step);

void func_08079838(void)
{
    func_0808A268(5, 12, data_03002818->first_plane,
        data_03002818->second_plane, data_03002740.first_tiles,
        data_03002740.first_tiles + 0x111, 0, 0, 2, 6, 21, 13,
        2, 6, 21, 13, 21, 13);
    func_0808A268(11, 12, data_03002818->second_plane,
        data_03002818->second_plane, data_03002740.second_tiles,
        data_03002740.second_tiles + 0xbe, 0, 0, 3, 8, 19, 10,
        3, 8, 19, 10, 19, 10);
    data_030009E0[5].x = 2;
    data_030009E0[5].y = 6;
    data_030009E0[5].attributes = 0x229;
    data_030009E0[5].mode = 0;
    data_030009E0[5].source_x = 1;
    data_030009E0[5].source_y = 1;
    data_030009E0[5].width = 19;
    data_030009E0[5].height = 12;
    func_0808136C(0, data_03002818->resource_2d50, 5, 0, 0, 0);
    func_08016344(data_030009E0[5].first_text,
        data_030009E0[5].text_x, data_030009E0[5].text_y,
        0xc0, data_030009E0[5].text_x, 5, 12);
    func_08016560(data_030009E0[5].second_text, 21, 13, 0xc0, 21, 1, 12);
    func_08035678(0xc044, func_0808B8E4(5, 1, 1, 1),
        func_08018524(data_02003CB0, 0x44, 15), 1);
}
