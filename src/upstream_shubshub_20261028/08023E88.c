/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08023E88.c
 * Original SHA-256: 24968f509e678be12d46d488fafa67dd7a9309a41bea838bcf15fab91f98154c
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct DrawState {
    const void *source;
    s16 x;
    s16 y;
    s16 offset_x;
    s16 offset_y;
    u8 value;
    u8 extra;
    s16 timer;
} DrawState;

typedef struct IndicatorState {
    u8 active;
    u8 unknown_01[0x797];
    DrawState indicators[2];
} IndicatorState;

typedef struct MenuState {
    u8 unknown_00[0x5C];
    IndicatorState *indicators;
} MenuState;

extern MenuState g_state_0200F390;
extern void func_08017FE8(const DrawState *state);

/* 08023E88..08023F00: 120 bytes, 54 instructions, including literal pools. */
void func_08023E88(void)
{
    IndicatorState *state = g_state_0200F390.indicators;

    if (state != 0 && state->active) {
        if (++state->indicators[0].timer > 5) {
            state->indicators[0].timer = 0;
            if (++state->indicators[0].offset_x > 2)
                state->indicators[0].offset_x = 0;
            if (--state->indicators[1].offset_x <= -3)
                state->indicators[1].offset_x = 0;
        }
        func_08017FE8(&state->indicators[0]);
        func_08017FE8(&state->indicators[1]);
    }
}
