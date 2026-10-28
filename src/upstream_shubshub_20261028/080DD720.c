/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080DD720.c
 * Original SHA-256: 2d5574cb2e9aab0f250023dfb552e3e911762a667fe6a755c2a1953557814c36
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

struct State080DD720 {
    u8 unknown_00[0x30];
    u32 flags;
};

/* Complete [0x080DD720, 0x080DD728): 8 bytes, 4 instructions. */
void func_080DD720(struct State080DD720 *state, u32 mask)
{
    state->flags |= mask;
}
