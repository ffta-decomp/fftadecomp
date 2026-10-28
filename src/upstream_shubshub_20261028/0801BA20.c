/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0801BA20.c
 * Original SHA-256: 8e1dbd4c90e9d21a8eacc7056ef8fd16d974d4403366dc670ba9bdc59bd02bc4
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
    u8 unknown_00[0x24];
    s16 x;
    s16 y;
    u8 unknown_28[0xC];
    u8 moving;
    u8 elapsed;
    s16 target_x;
    s16 target_y;
    u8 unknown_3A[2];
    LineState x_line;
    LineState y_line;
} MapState;

extern MapState g_state_02007F40;

u32 func_08141898(u32 value);
u32 func_08141870(u32 dividend, u32 divisor);
u32 func_08141874(u32 dividend, u32 divisor);
void func_080075CC(LineState *state, s32 x, s32 y, s32 end_x, s32 end_y);

/* Complete target: [0x0801BA20, 0x0801BB0C), 236 bytes. */
u16 func_0801BA20(s16 x, s16 y, u16 speed)
{
    s16 delta_x;
    s16 delta_y;
    u16 distance;
    u16 frames;

    if (x == g_state_02007F40.x && y == g_state_02007F40.y) {
        return 0;
    }

    delta_x = x - g_state_02007F40.x;
    delta_y = y - g_state_02007F40.y;
    distance = (u16)func_08141898((u32)(delta_x * delta_x + delta_y * delta_y) << 8) >> 4;
    frames = func_08141870(distance, speed);
    if (func_08141874(distance, speed) != 0) {
        frames++;
    }

    g_state_02007F40.target_x = x;
    g_state_02007F40.target_y = y;
    func_080075CC(&g_state_02007F40.x_line, g_state_02007F40.x, 0, x, frames - 1);
    func_080075CC(&g_state_02007F40.y_line, g_state_02007F40.y, 0, y, frames - 1);
    g_state_02007F40.moving = 1;
    g_state_02007F40.elapsed = 0;
    return frames;
}
