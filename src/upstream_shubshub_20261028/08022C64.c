/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08022C64.c
 * Original SHA-256: da53fad954ca2ec137738dfbbed07762211001d8eb067a0b9acb233bdc83e319
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 08022C64 .. 08022CD4: 112 bytes. */
typedef struct {
    u16 held;
    u16 unknown_02;
    u16 pressed;
    u8 unknown_06;
    u8 flags;
} Input;

typedef struct {
    u8 unknown_00[0x0F];
    u8 delay;
    u16 held;
    u16 pressed;
    u16 filtered_held;
    u16 filtered_pressed;
    u16 cached_held;
    u16 cached_pressed;
} State;

extern State g_state_0200F390;
extern Input data_03000000;
extern void (*g_callbacks_0836D4B8[])(void *, u32);
extern u8 func_08022C2C(void);

static inline u8 filter_input(State *state)
{
    if (!func_08022C2C()) {
        state->filtered_pressed = 0;
        state->filtered_held = 0;
        return 0;
    }
    state->filtered_held = state->held;
    state->filtered_pressed = state->pressed;
    return 1;
}

u8 func_08022C64(void)
{
    State *state = &g_state_0200F390;
    Input *input = &data_03000000;

    if (input->flags & 1)
        input->flags |= 8;
    if (state->delay) {
        state->delay--;
        g_callbacks_0836D4B8[0](&state->filtered_held, 4);
        return 0;
    }
    state->held = input->held;
    state->pressed = input->pressed;
    state->cached_held = state->held;
    state->cached_pressed = state->pressed;
    return filter_input(state);
}
