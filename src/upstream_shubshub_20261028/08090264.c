/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08090264.c
 * Original SHA-256: d0493dc5a265ea9956c67514eb56e80f9cd85db2b09dda668917c9066dfcc613
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* Complete [0x08090264, 0x080902CA): 102 bytes, 51 instructions. */
typedef struct {
    s32 limit;
    s32 velocity;
    s32 unknown_08;
    s32 value;
    s32 acceleration;
    s8 stop_at_turn;
} MotionState;

s32 func_08090264(MotionState *state)
{
    s32 next_velocity;
    if (state->acceleration == 0)
        return 0;

    state->value += state->velocity;
    next_velocity = state->velocity + state->acceleration;
    if (state->stop_at_turn &&
        ((state->velocity > 0 && next_velocity <= 0) ||
         (state->velocity < 0 && next_velocity >= 0))) {
        state->acceleration = 0;
        return 0;
    }
    if ((state->value <= state->limit && state->velocity < 0 &&
         state->acceleration < 0) ||
        (state->value >= state->limit && state->velocity > 0 &&
         state->acceleration > 0)) {
        state->value = state->limit;
        return 0;
    }
    state->velocity = next_velocity;
    return 1;
}
