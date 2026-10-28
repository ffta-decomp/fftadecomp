/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080A883C.c
 * Original SHA-256: 85fb92fc85d3c5ca0d267ef5b8c01f82036a36e671b9f3dd250d2d6322523122
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[0x14];
    u8 bits[32];
} PackedBits;

/* 0x080A883C..0x080A8856: 26 bytes. */
u8 func_080A883C(const PackedBits *state, u8 index)
{
    u32 byte_index = index >> 3;
    u32 bit_index = index & 7;

    return (state->bits[byte_index] >> bit_index) & 1;
}
