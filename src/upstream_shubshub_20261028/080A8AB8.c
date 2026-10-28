/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080A8AB8.c
 * Original SHA-256: 5b848ad19876b65fafd044f5772197a904308b195bae12d522b16c1d5325fd93
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x080A8AB8..0x080A8AFC: 68 bytes. */
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

typedef struct {
    LineState first;
    LineState second;
    u8 unknown_28[2];
    s16 unknown_2A;
    u8 unknown_2C[2];
    s16 unknown_2E;
    s16 x;
    s16 y;
    s16 z;
} LinePairState;

s32 func_080A7FE8(LineState *state);

void func_080A8AB8(LinePairState *state)
{
    if (state->unknown_2E >= state->unknown_2A) {
        func_080A7FE8(&state->second);
        func_080A7FE8(&state->first);
    } else {
        if (func_080A7FE8(&state->first))
            func_080A7FE8(&state->second);
    }

    state->x = state->second.x;
    state->z = state->second.y;
    state->y = state->first.y;
}
