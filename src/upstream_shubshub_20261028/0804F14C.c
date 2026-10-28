/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0804F14C.c
 * Original SHA-256: e06cb5ea91031f5d3559e9300ea3fd2f5a7380dd7e8f095d3de1cdc193b861b2
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x0804F14C .. 0x0804F28A: 318 bytes, 139 instructions. */
typedef struct {
    u16 held;
    u16 pressed;
    u16 repeated;
} Input0804F14C;

typedef struct {
    u8 unknown_00[6];
    u16 remaining;
} Selection0804F14C;

typedef struct {
    u8 unknown_00[10];
    u16 first;
    u16 unknown_0c;
    u16 second;
    u8 flags;
    s8 cursor;
} Controls0804F14C;

typedef struct {
    Selection0804F14C *selection;
    u16 flags;
    u16 result;
    u8 mode;
    u8 unknown_09[0x3f];
    u8 menu[0x20];
    Controls0804F14C controls;
    u8 unknown_7c[0x14];
    s8 *enabled;
} State0804F14C;

extern Input0804F14C data_03000000;
extern s16 func_08017B68(void *, s8);
extern u16 func_0804EFD0(State0804F14C *, s16);
extern void func_08141570(int, int);
extern void func_08141540(int);
extern void func_08017D18(Controls0804F14C *, int);
extern u8 func_0805093C(State0804F14C *, u16, u16);
extern void func_08050844(State0804F14C *, u16, u16);

u8 func_0804F14C(State0804F14C *state)
{
    Controls0804F14C *controls = &state->controls;
    u16 pressed = data_03000000.pressed;
    u16 repeated = data_03000000.repeated;
    u16 held = data_03000000.held;

    if (pressed & 4) {
        state->selection->remaining = func_0804EFD0(
            state, func_08017B68(state->menu, state->controls.cursor));
        if (state->selection->remaining) {
            state->selection->remaining--;
            state->result = 0xfffc;
            return 1;
        }
    }
    if (pressed & 2) {
        func_08141570(1, 0x69);
        if (controls->flags & 1)
            func_08017D18(controls, 1);
        state->result = 0xffff;
        return 1;
    }
    if (pressed & 1) {
        s16 index = func_08017B68(state->menu, controls->cursor);
        if (!state->enabled[index]) {
            func_08141570(1, 0x6b);
            return 0;
        }
        func_08141540(0x64);
        state->result = index + 1;
        if (controls->flags & 1) {
            if (state->mode != 1) {
                if (controls->first + controls->second <= 0x3f)
                    func_08017D18(controls, 0);
                else
                    func_08017D18(controls, 1);
            } else
                func_08017D18(controls, 1);
        }
        return 1;
    }
    if (!(state->flags & 8)) {
        if (!(state->flags & 0x10))
            return func_0805093C(state, repeated, held);
        func_08050844(state, repeated, held);
    }
    return 0;
}
