/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 11946243ba373da48154ed04cb3bb31e52dad97b
 * Original file: src/0804A15C.c
 * Original SHA-256: 692b4e06e361494ce6bc9998158f05e2bc346bf34a523c1134da2904e2cb507d
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred.
 */
/* 0x0804A15C, complete 392-byte Thumb owner.
 * Conditional incoming-call transport and local BIOS fill source units.
 */
#include "abi/interfaces/080008e0_bindings.h"

typedef struct {
    u8 unknown_00[0x90];
    void *field_90;
    void *field_94;
} Resources;

typedef struct {
    u8 unknown_00[0x10];
    u8 *tiles;
} TileStorage;

typedef struct {
    u8 unknown_00[0x0E];
    u16 status;
    u8 unknown_10[8];
    u16 *first_plane;
    u16 *second_plane;
    u8 unknown_20[8];
    u8 width;
    u8 height;
    u8 unknown_2A[2];
    u8 field_2C;
    u8 field_2D;
    u8 unknown_2E[0x1E];
} Window;

extern Resources *g_state_03002810;
extern TileStorage data_03002740;
extern Window data_030009E0[];
extern u8 data_02003CB0[];
extern u8 data_06009960[];

void func_0814186C(const void *source, void *destination, u32 control);
void *func_0808A268(s32 index, u8 kind, void *first, void *second,
                    void *third, void *fourth, void *fifth, void *sixth,
                    u8 x, u8 y, u8 width, u8 height,
                    u32 x2, u32 y2, u32 width2, u32 height2,
                    u8 row_width, u8 row_height);
void func_08016344(u16 *destination, u8 width, u8 height, u16 flags,
                    u8 stride, u16 tile, u8 palette);
void func_08016560(u16 *destination, u8 width, u8 height, u16 flags,
                    u8 stride, u16 tile, u8 palette);
u16 *func_0808B8E4(u32 index, u32 plane, s32 x, s32 y);
void func_0808B7C0(s32 index, u16 *destination, u16 tile, u16 count, u16 flags);
u32 func_08018524(u8 *buffer, u16 tile, u8 resource);
void func_08035678(u16 tile, u16 *destination, u32 count, u16 step);

void func_0804A15C(s32 first_row, s32 rows)
{
    u16 zero_second;
    u16 zero_first;
    u16 zero_vram;
    u16 tile;
    u16 *destination;
    u32 count;
    s32 row;

    func_0808A268(4, 12, g_state_03002810->field_94,
                    g_state_03002810->field_90,
                    data_03002740.tiles, data_03002740.tiles + 0x268,
                    0, 0, 1, (u8)(first_row + 1), 28, 11, 1, (s8)(first_row + 1), 28, 11, 28, 11);
    zero_second = 0;
    func_0814186C(&zero_second, data_030009E0[4].second_plane, 0x01000134);
    zero_first = 0;
    func_0814186C(&zero_first, data_030009E0[4].first_plane, 0x01000134);
    data_030009E0[4].status = 203;
    data_030009E0[4].field_2C = 26;
    data_030009E0[4].field_2D = 6;
    func_08016344(data_030009E0[4].second_plane,
                    data_030009E0[4].width, (u8)(rows * 2 + 3),
                    0xC0, data_030009E0[4].width, 5, 12);
    func_08016560(data_030009E0[4].first_plane,
                    28, (u8)(rows * 2 + 3), 0xC0, 28, 1, 12);
    tile = 0xC03E;
    destination = func_0808B8E4(4, 1, 1, 1);
    count = func_08018524(data_02003CB0, 0x3E, 0x17);
    func_08035678(tile, destination, count, 1);
    for (row = 0; row < rows * 2; row += 2) {
        func_0808B7C0(4, func_0808B8E4(4, 1, 1, row + 2),
                        (u16)(203 + 26 * row), 26, 0xC000);
    }
    zero_vram = 0;
    func_0814186C(&zero_vram, data_06009960, 0x01000D00);
}
