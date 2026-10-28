/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08140A20.c
 * Original SHA-256: 7f4b081ffe29d87b1e896bb1a0842dc64231101d088aabd62a860f7f3edb3e51
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    s32 target_x;
    s32 target_y;
    s32 current_x;
    s32 current_y;
    s32 angle;
    s32 turn_percent;
    s32 speed;
} MotionState;

typedef struct {
    const void *image;
    MotionState motion;
    u16 scale;
    u16 tile;
} SpriteState;

extern void func_08007AD0(MotionState *state);
extern void func_080018A0(const void *, s32, s32, u32, u32, u32, u32,
                          u32, u32, s16, s16, u16, u32);

/* Complete target: [0x08140A20, 0x08140AB4), 148 bytes, 70 instructions. */
void func_08140A20(SpriteState *state)
{
    s32 dx;
    s32 dy;
    s32 distance;
    s32 angle;

    func_08007AD0(&state->motion);
    dx = state->motion.target_x - state->motion.current_x;
    if (dx < 0)
        dx = -dx;
    dy = state->motion.target_y - state->motion.current_y;
    if (dy < 0)
        dy = -dy;
    distance = dy;
    if (dx >= distance)
        distance = dx;
    if (distance < state->motion.speed)
        state->image = 0;
    else
    {
        state->scale += 6;
        if (state->scale > 511)
            state->scale = 512;
        angle = state->motion.angle;
        angle = -angle;
        angle += 128;
        if (angle > 255)
            angle -= 255;
        func_080018A0(state->image, state->motion.current_x >> 8,
                      state->motion.current_y >> 8, 0, 0, 0, state->tile,
                      2, 0, (s16)state->scale, (s16)state->scale,
                      (u8)angle << 8, 1);
    }
}
