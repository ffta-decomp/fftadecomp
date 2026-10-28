/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080A7FE8.c
 * Original SHA-256: 5facdc65de77dd3cac3cfa6e65fa85c484a3ef3bd914ceff97bec5f379c2f5c5
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x080A7FE8: 104 bytes. */
typedef struct {
    s16 x;
    s16 y;
    u8 unknown_04[4];
    s16 error;
    s16 period;
    s16 step_x;
    s16 step_y;
    s16 distance_x;
    s16 distance_y;
} LineState;

u8 func_080A7FE8(LineState *state)
{
    if (state->distance_x >= state->distance_y) {
        state->x += state->step_x;
        state->error -= state->distance_y;
        if (state->error < 0) {
            state->error += state->period;
            state->y += state->step_y;
            return 1;
        }
    } else {
        state->y += state->step_y;
        state->error -= state->distance_x;
        if (state->error < 0) {
            state->error += state->period;
            state->x += state->step_x;
            return 1;
        }
    }
    return 0;
}
