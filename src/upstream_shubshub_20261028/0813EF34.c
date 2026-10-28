/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0813EF34.c
 * Original SHA-256: ea8e39ada0c87b24d7e9b246c1e40c1385d35a0cf47ac1819b87ecdc75a04c4a
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x0813EF34..0x0813EF38: 4 bytes. */
typedef struct {
    u8 unknown_00[0xA];
    u8 value;
} ByteState;

void func_0813EF34(ByteState *state, u8 value)
{
    state->value = value;
}
