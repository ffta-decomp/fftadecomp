/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0804F744.c
 * Original SHA-256: 6aa02cfb4ac3a4b02389385801d0a39c4ade9e2c22936846cc9cbd86e2c912de
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u16 held;
    u16 pressed;
    u16 repeated;
} InputState;

typedef struct {
    u8 unknown_000[0x560];
    u8 group;
    u8 group_count;
    u8 column;
    u8 row;
} MenuData;

typedef struct {
    MenuData *data;
    u16 unknown_04;
    s16 selection;
    u8 unknown_08[3];
    u8 active;
    u8 unknown_0c[0x84];
    s8 *available;
    u8 unknown_94[4];
    u8 cooldown;
} MenuState;

extern InputState data_03000000;
extern void func_08141570(u32 channel, u32 sound);
extern void func_08141540(u32 sound);
extern u16 func_080502EC(MenuState *state);
extern u8 func_0805033C(MenuState *state, u16 buttons);
extern u8 func_08050394(MenuState *state, u16 buttons);
extern void func_080500B0(MenuState *state);

/* Complete target: [0x0804F744, 0x0804F8A4), 352 bytes. */
u8 func_0804F744(MenuState *state)
{
    u8 changed = 0;
    u8 moved;
    u16 selection;
    u16 buttons;

    if (state->cooldown != 0) {
        state->cooldown--;
        return 0;
    }
    buttons = data_03000000.pressed;
    if (buttons & 2) {
        func_08141570(1, 0x69);
        state->active = 0;
        state->selection = -1;
        return 1;
    }
    if (buttons & 1) {
        selection = func_080502EC(state);

        if (state->available[selection - 1] == 0) {
            func_08141570(1, 0x6B);
            return 0;
        }
        func_08141540(0x64);
        state->active = 0;
        state->selection = selection;
        return 1;
    }
    if (buttons & 0x100) {
        changed = 1;
        if (state->data->group < state->data->group_count - 1)
            state->data->group++;
        else
            state->data->group = 0;
    } else if (buttons & 0x200) {
        changed = 1;
        if (state->data->group == 0)
            state->data->group = state->data->group_count - 1;
        else
            state->data->group--;
    }
    if (changed) {
        func_08141540(0x74);
        state->selection = -3;
        return 1;
    }
    moved = 0;
    buttons = data_03000000.repeated & 0xF0;
    if (buttons & 0x30) {
        u8 column = func_0805033C(state, buttons);

        if (column != state->data->column) {
            moved = 1;
            state->data->column = column;
        }
    }
    if (buttons & 0xC0) {
        u8 row = func_08050394(state, buttons);

        if (row != state->data->row) {
            moved = 1;
            state->data->row = row;
        }
    }
    if (moved) {
        state->cooldown = 1;
        func_08141540(0x6D);
        func_080500B0(state);
    }
    return 0;
}
