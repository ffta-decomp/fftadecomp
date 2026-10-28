/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08011280.c
 * Original SHA-256: b1c20d9e6e55541c14c8330f26e60cb2a0f41010e36c8760289576e3e8897a8e
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x08011280 - 36 bytes. Set or clear bit 6 of the state flags. */
typedef struct {
    u8 unknown_00[0x14];
    u16 flags;
} State08011280;

void func_08011280(State08011280 *state, u8 enabled)
{
    if (enabled)
        state->flags |= 0x40;
    else
        state->flags &= ~0x40;
}
