/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 43f7f78cfe893ab4d99d2004e0740459589bfb5c (PR #20)
 * Original file: src/080111CC.c
 * Original SHA-256: e8827f056e5762830a96d56f0aaa4a9a12f9b68c2f5b78765b2058f5399d4b71
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Validation: data/upstream-imports-20261030.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00;
    u8 value_01;
    u8 value_02;
    u8 value_03;
    u8 unknown_04[0x10];
    u16 flags;
} State080111CC;

/* Complete [0x080111CC, 0x08011204): 56 bytes, 25 instructions. */
void func_080111CC(State080111CC *state, u8 enabled, u8 first, u8 second)
{
    if (enabled) {
        state->flags |= 0x10;
        state->value_01 = first;
        state->value_02 = second;
        state->value_03 = 0;
    } else {
        state->flags &= ~0x10;
    }
}
