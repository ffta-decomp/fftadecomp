/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08057C88.c
 * Original SHA-256: 43e6779de3866ac30d0f03c36705b30649f89686051c52fe9323226af57a3689
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_0000[0x2FBA];
    u8 coarse;
    u8 fine;
} CounterState;

extern CounterState g_state_02000000;

/* 0x08057C88..0x08057CBE: 54 bytes. */
void func_08057C88(void)
{
    CounterState *state = &g_state_02000000;
    if (state->fine <= 19) {
        state->fine++;
    } else {
        state->fine = 1;
        if (state->coarse <= 4)
            state->coarse++;
        else
            state->coarse = 1;
    }
}
