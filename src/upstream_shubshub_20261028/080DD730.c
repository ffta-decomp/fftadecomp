/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080DD730.c
 * Original SHA-256: 263270a8c3a129ba62a5453b3d02b7c894caf5f3d6799cdff566b1b9162daa70
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

struct State080DD730 {
    u8 unknown_00[0x30];
    u32 flags;
};

/* Complete [0x080DD730, 0x080DD73A): 10 bytes, 5 instructions. */
u32 func_080DD730(struct State080DD730 *state)
{
    return (state->flags >> 6) & 1;
}
