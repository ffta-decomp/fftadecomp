/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0813F12C.c
 * Original SHA-256: de3043f84b31fcd4159c9ffa5c6ea060ea8d137e9b529acd64c783e802c3c8e0
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

struct State0813F12C {
    u8 unknown_00[4];
    u8 value;
};

/* Complete [0x0813F12C, 0x0813F132): 6 bytes, 3 instructions. */
void func_0813F12C(struct State0813F12C *state)
{
    state->value = 0;
}
