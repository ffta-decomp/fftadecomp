/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080DD56C.c
 * Original SHA-256: ffa4b7843ac32a5aeb5851730adbcab680fceed08e82ffd4c03f60ab408e624d
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x080DD56C..0x080DD572: 6 bytes, 3 instructions. */
typedef struct {
    u8 unknown_00[0x28];
    s16 value;
} State;

s16 func_080DD56C(const State *state)
{
    return state->value;
}
