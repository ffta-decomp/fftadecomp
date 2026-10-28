/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08148600.c
 * Original SHA-256: 2e0e40bcdf5a67dc1736ee0fe4922e9e296cca7201b92d19a617717c16859c57
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x08148600..0x0814860A: 10 bytes, 5 instructions. */
typedef struct {
    u16 unknown_00;
    u16 flags;
} State;

void func_08148600(State *state)
{
    state->flags |= 8;
}
