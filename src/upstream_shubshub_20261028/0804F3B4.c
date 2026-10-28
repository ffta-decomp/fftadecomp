/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0804F3B4.c
 * Original SHA-256: f3ef62b45b4c3184a5ff3e24e2d8c55d4d54b4e855d488b7a282b0d76974ab88
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u16 held;
    u16 pressed;
} InputState;

typedef struct {
    u8 unknown_00[0x10];
    u8 selection;
    u8 count;
    u8 mode;
} ChoiceState;

typedef struct {
    u8 unknown_00[4];
    u16 state;
    u8 unknown_06[3];
    u8 active;
} MenuState;

extern InputState data_03000000;
extern ChoiceState g_state_020020D0;
extern void func_08141570(u32 channel, u32 sound);
extern void func_08141540(u32 sound);
extern void func_08013364(void);
extern void func_08011B30(u32 index, u32 value);

/* Complete target: [0x0804F3B4, 0x0804F470), 188 bytes. */
u8 func_0804F3B4(MenuState *state)
{
    u8 changed = 0;
    u16 buttons = data_03000000.pressed;

    if (buttons & 2) {
        func_08141570(1, 0x69);
        func_08013364();
        state->active = 0;
        state->state = 0x40;
        return 1;
    }
    if (buttons & 1) {
        func_08141540(0x64);
        func_08013364();
        state->active = 0;
        state->state = 0x40;
        return 1;
    }
    if (buttons & 0x10) {
        if (g_state_020020D0.mode == 3)
            return 0;
        changed = 1;
        if (g_state_020020D0.selection < g_state_020020D0.count - 1)
            g_state_020020D0.selection++;
        else
            g_state_020020D0.selection = 0;
    } else if (buttons & 0x20) {
        u8 selection;
        if (g_state_020020D0.mode == 3)
            return 0;
        changed = 1;
        selection = g_state_020020D0.selection;
        if (selection == 0)
            selection = g_state_020020D0.count;
        g_state_020020D0.selection = selection - 1;
    }
    if (changed) {
        func_08141540(0x6D);
        func_08013364();
        func_08011B30(9, g_state_020020D0.selection);
        return 1;
    }
    return 0;
}
