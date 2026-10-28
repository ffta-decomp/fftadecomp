/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0813EE18.c
 * Original SHA-256: 21ff6e52c80d95d467672c787a1c87430111e5543c60e09a029c4af269a9fa76
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x0813EE18..0x0813EE1E: 6 bytes. */
typedef struct {
    u8 unknown_00[0x8C];
    u8 value;
} State;

void func_0813EE18(State *state, u8 value)
{
    state->value = value;
}
