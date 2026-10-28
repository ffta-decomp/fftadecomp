/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0813EF2C.c
 * Original SHA-256: be3643c27d208066d9c62b70473fff7c7d8789f9cfd16b408344f2bcb5bc10b8
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[0x0B];
    u8 value;
} ByteState;

void func_0813EF2C(ByteState *state, u8 value)
{
    state->value = value;
}
