/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0801BB94.c
 * Original SHA-256: bce757873f12ef469809e4ec352113d94b65107c39dbcc27ff6a40e6c7d3325f
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    s32 x;
    s32 y;
    s32 end_x;
    s32 end_y;
    s32 step_x;
    s32 step_y;
    s32 delta_x;
    s32 delta_y;
    s32 accumulator;
    s32 error;
    s32 remaining;
} LineState;

typedef struct {
    u8 active;
    u8 moving;
    u16 target_x;
    u16 target_y;
    u16 unknown_06;
    LineState horizontal;
    LineState vertical;
    u8 mode;
    u8 effect;
    u8 option;
    u8 initial_mode;
    u32 midpoint;
    u8 elapsed;
} ViewportTransition;

typedef struct {
    u8 unknown_00[0x24];
    s16 focus_x;
    s16 focus_y;
    u8 unknown_28[0xc];
    ViewportTransition transition;
} ViewportState;

extern ViewportState g_state_02007F40;
extern u16 func_08141898(u32 value);
extern void func_080075CC(LineState *state, s32 x, s32 y, s32 end_x, s32 end_y);

/* Complete target: [0x0801BB94, 0x0801BC94), 256 bytes. */
u8 func_0801BB94(u16 x, u16 y, u8 mode, u8 effect, u8 option)
{
    ViewportTransition *transition = &g_state_02007F40.transition;
    ViewportState *state;
    s16 target_x;
    s16 target_y;
    s16 delta_x;
    s16 delta_y;
    u16 distance;
    u16 duration;

    if ((s16)x == g_state_02007F40.focus_x && (s16)y == g_state_02007F40.focus_y)
        return 0;

    state = &g_state_02007F40;
    target_x = x;
    target_y = y;
    delta_x = target_x - state->focus_x;
    delta_y = target_y - state->focus_y;
    distance = func_08141898((delta_x * delta_x + delta_y * delta_y) << 8);
    duration = distance >> 4;

    transition->target_x = x;
    transition->target_y = y;
    transition->mode = mode;
    transition->effect = effect;
    transition->option = option;
    transition->initial_mode = mode;
    transition->midpoint = distance >> 5;
    transition->elapsed = 0;

    func_080075CC(&transition->horizontal, state->focus_x, 0, target_x, duration);
    func_080075CC(&transition->vertical, state->focus_y, 0, target_y, duration);
    transition->active = 1;
    transition->moving = 1;
    return 1;
}
