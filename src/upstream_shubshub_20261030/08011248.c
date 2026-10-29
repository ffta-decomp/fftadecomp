/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 43f7f78cfe893ab4d99d2004e0740459589bfb5c (PR #20)
 * Original file: src/08011248.c
 * Original SHA-256: 51fcc603f886b9e58b9bbd7fa94d2d55b9f9f936325cfeb3304c3e16b695d31e
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Validation: data/upstream-imports-20261030.json.
 */
#include "ffta.h"

struct State08011248 {
    u8 unknown_00[0x14];
    u16 flags;
};

/* 0x08011248..0x08011280 - 56 bytes: select one of two state flags. */
void func_08011248(struct State08011248 *state, u8 enabled)
{
    if (enabled) {
        state->flags |= 0x400;
        state->flags &= ~0x800;
    } else {
        state->flags &= ~0x400;
        state->flags |= 0x800;
    }
}
