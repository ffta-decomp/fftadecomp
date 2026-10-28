/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0813DB44.c
 * Original SHA-256: bf3ac0b0e4ceaaf7e05023befae9124c2cd079b7da693832a40f494780617f60
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* Target: complete [0x0813DB44, 0x0813DC3A), 246 bytes. */
typedef struct {
    u8 phase;
    u8 channel;
    u8 unknown_02[2];
    s16 start[4];
    s16 end[4];
    s16 current[4];
    u32 frame;
    u32 duration;
} TransitionState;

extern u16 g_control_flags_03000940;
extern void func_0813DC3C(const s16 *, u8);
extern s32 func_0813F19C(s16, s16, u16, u16);

void func_0813DB44(TransitionState *state)
{
    switch (state->phase) {
    case 0:
        g_control_flags_03000940 &= state->channel == 0 ? ~0x2000u : ~0x4000u;
        break;
    case 1:
        func_0813DC3C(state->start, state->channel);
        g_control_flags_03000940 |= state->channel == 0 ? 0x2000u : 0x4000u;
        if (state->duration != 0 && ++state->frame > state->duration)
            state->phase = 0;
        break;
    case 2:
        state->current[0] = func_0813F19C(state->start[0], state->end[0],
                                         state->duration, state->frame);
        state->current[1] = func_0813F19C(state->start[1], state->end[1],
                                         state->duration, state->frame);
        state->current[2] = func_0813F19C(state->start[2], state->end[2],
                                         state->duration, state->frame);
        state->current[3] = func_0813F19C(state->start[3], state->end[3],
                                         state->duration, state->frame);
        func_0813DC3C(state->current, state->channel);
        g_control_flags_03000940 |= state->channel == 0 ? 0x2000u : 0x4000u;
        if (state->frame <= state->duration)
            state->frame++;
        break;
    }
}
