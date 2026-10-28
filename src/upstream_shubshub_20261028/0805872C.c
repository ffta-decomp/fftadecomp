/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0805872C.c
 * Original SHA-256: f25b961b4212934c6b270f2bcef684840d90568791404a283e39a353d00933de
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[0xE];
    u16 extent;
    u8 unknown_10;
    u8 value;
} ScaledState;

/* Complete target: 0x0805872C..0x0805873C, 16 bytes. */
void func_0805872C(ScaledState *state, u8 value)
{
    state->value = value;
    state->extent = value * 40;
}
