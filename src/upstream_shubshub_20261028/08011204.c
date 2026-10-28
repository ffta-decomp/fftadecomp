/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08011204.c
 * Original SHA-256: 1ce605c0b53fc4fb3a3783f0d48a85ff50b097f2496e5bf3189fa0a15072bfb7
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[0x14];
    u16 flags;
} FlagState;

/* 08011204..0801121C: 24 bytes, 12 instructions. */
void func_08011204(FlagState *state)
{
    if (state->flags & 0x18)
        state->flags ^= 0x20;
}
