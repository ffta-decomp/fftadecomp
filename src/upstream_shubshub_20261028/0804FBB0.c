/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0804FBB0.c
 * Original SHA-256: bbe3c1effaecf2a99f8e5c62a661978b663f81328d45c97ccbce0b4906e04244
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* Complete [0x0804FBB0, 0x0804FD24): 372 bytes, 160 instructions. */
typedef struct {
    u8 unknown_00[0x10];
    void *resource;
    u8 data[0];
} Source0804FBB0;

typedef struct {
    u8 width;
    u8 height;
    u8 rows;
    u8 unknown_03;
    u16 count;
    u16 palette;
    u8 unknown_08[6];
    u16 tile;
} Settings0804FBB0;

typedef struct {
    u8 unknown_00[8];
    u16 *tiles;
    u8 unknown_0c[9];
    u8 row_height;
    u8 unknown_16[10];
} Menu0804FBB0;

typedef struct {
    Source0804FBB0 *source;
    u8 unknown_04[4];
    u8 mode;
    u8 unknown_09[3];
    Settings0804FBB0 settings;
    u8 panel[0x2c];
    Menu0804FBB0 menu;
    u8 unknown_68[0x2c];
    void *resource;
} State0804FBB0;

typedef struct {
    u8 unknown_00[0x10];
    u8 *tiles;
} Graphics0804FBB0;

extern Graphics0804FBB0 data_030008B0;
extern void *g_state_020020D0;
extern u8 data_084C3798[];
extern u8 *func_08005B28(u32);
extern void func_08005B40(void *);
extern void func_08013E9C(void *, void *, void *, u32, u32, u32);
extern void func_08016210(void *, void *, u16, u16);
extern u16 func_08017B50(Menu0804FBB0 *);
extern void func_08013A88(void *, u16);
extern void func_08017AD8(Menu0804FBB0 *);
extern void func_080154D8(void *, void *, void *, u8, u8, u8, u32,
                         Graphics0804FBB0 *, u16);
extern u8 func_080CECF4(void);
extern u16 func_080CE8A8(void);
extern u16 func_080CED2C(void);
extern u16 func_080161A0(u32, u32, u32);
extern void func_080C9574(u32, u32);

void func_0804FBB0(State0804FBB0 *state)
{
    u8 *panel = state->panel;
    Settings0804FBB0 *settings = &state->settings;
    Menu0804FBB0 *menu = &state->menu;
    u8 *destination = data_030008B0.tiles + (settings->tile + 0x140) * 32;
    u8 *buffer = func_08005B28(0x200);
    u8 *work = buffer + 0x100;
    u32 depth;

    if (state->mode == 2)
        depth = 4;
    else {
        depth = 8;
        g_state_020020D0 = state->source->resource;
    }
    func_08013E9C(buffer, data_084C3798, work, depth, 0, 0);
    func_08016210(panel, state->resource, settings->tile + 0x140,
                  settings->count);
    func_08013A88(destination, menu->row_height * func_08017B50(menu) * 2);
    func_08017AD8(menu);
    func_080154D8(state->source->data, destination, buffer, settings->rows - 2,
                  settings->width, settings->height, 0, &data_030008B0,
                  settings->palette);
    if (state->mode == 2) {
        if (func_080CECF4() == 30) {
            u16 tile = 0xe0a7;
            u16 *map = menu->tiles + func_080161A0(11, 2, 32);
            map[0] = tile++;
            map[32] = tile++;
            map[1] = tile++;
            map[33] = tile++;
        }
        if (func_080CE8A8() == func_080CED2C()) {
            u16 tile = 0xe0a1;
            u16 *map = menu->tiles + func_080161A0(10, 4, 32);
            map[0] = tile++;
            map[32] = tile++;
            map[1] = tile++;
            map[33] = tile++;
            map[2] = tile++;
            map[34] = tile++;
            func_080C9574(0x5ae, 1);
        }
    }
    func_08005B40(buffer);
}
