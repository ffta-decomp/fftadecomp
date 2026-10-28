/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0801CF10.c
 * Original SHA-256: d0d126a9357c9ae4d79bc700783caba9018d7caed615454000284ecb346a07af
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

struct State0801CF10 {
    u8 unknown_000[0x22a];
    u8 style;
    u8 unknown_22b[5];
    u16 blank_tile;
    u8 unknown_232[0x1e];
    u8 cells[0][16][16];
};

extern struct State0801CF10 g_state_02007F40;
extern const u8 data_081498D0[][4][4];
extern const u8 data_081498F0[];
extern const u16 data_08149890[][4][4];
extern u8 func_0801CC18(u8, u8);

/* Target: [0x0801CF10, 0x0801D130), 544 bytes, 252 instructions. */
void func_0801CF10(u8 kind, u8 x, u8 y, u8 direction, u8 layer,
                   u16 base_tile, u16 *output)
{
    s32 neighbor_exists = 0;
    s32 draw = 1;
    s32 side = 0;
    u32 style = g_state_02007F40.style;
    u8 neighbor_x = x;
    u8 neighbor_y = y;
    u32 tile_step;
    u16 tile_flags;
    u16 flipped;
    u16 tile;
    s32 opposite;

    if (kind == 0)
        side = 1;
    tile = base_tile + data_081498D0[side][style][direction];
    tile_step = data_081498F0[style];
    tile_flags = data_08149890[side][style][direction];
    flipped = tile_flags & 0x400;
    flipped = flipped != 0;
    tile |= tile_flags;

    opposite = 0;
    switch (direction) {
    case 0:
        if (neighbor_x != 0) {
            neighbor_exists = 1;
            neighbor_x--;
            opposite = 3;
        }
        break;
    case 1:
        if (neighbor_y != 0) {
            neighbor_exists = 1;
            neighbor_y--;
            opposite = 2;
        }
        break;
    case 2:
        if (neighbor_y < 15) {
            neighbor_exists = 1;
            neighbor_y++;
            opposite = 1;
        }
        break;
    case 3:
        if (neighbor_x < 15) {
            neighbor_exists = 1;
            neighbor_x++;
        }
        break;
    }

    if (neighbor_exists) {
        u8 neighbor = g_state_02007F40.cells[layer][neighbor_y][neighbor_x];

        switch (opposite) {
        case 0:
            neighbor >>= 6;
            break;
        case 1:
            neighbor = (neighbor >> 4) & 3;
            break;
        case 2:
            neighbor = (neighbor >> 2) & 3;
            break;
        case 3:
            neighbor &= 3;
            break;
        }
        if (kind != 0) {
            if (neighbor != 0 &&
                func_0801CC18(x, y) == func_0801CC18(neighbor_x, neighbor_y)) {
                if (kind == neighbor)
                    tile += tile_step;
                else
                    tile += 2 * tile_step;
            }
        } else {
            if (neighbor == 0 ||
                func_0801CC18(x, y) != func_0801CC18(neighbor_x, neighbor_y))
                goto empty;
            if (neighbor == 2)
                tile += 3 * tile_step;
        }
    } else if (kind == 0) {
        draw = 0;
    }

    if (draw) {
        if (flipped) {
            output[0] = tile + 1;
            output[1] = tile;
        } else {
            output[0] = tile;
            output[1] = tile + 1;
        }
        return;
    }

empty:
    output[0] = g_state_02007F40.blank_tile;
    output[1] = g_state_02007F40.blank_tile;
}
