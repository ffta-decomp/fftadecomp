/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0801133C.c
 * Original SHA-256: 117e4124f90b0b7201b0750053db21e80da96937c06002e5426c9bddf0addefd
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[4];
    void *value;
    u8 unknown_08[0x0C];
    u16 flags;
} ValueState;

/* 0801133C..08011348: 12 bytes, 6 instructions. */
void func_0801133C(ValueState *state, void *value)
{
    state->value = value;
    state->flags |= 6;
}
