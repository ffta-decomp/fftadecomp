/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08133A38.c
 * Original SHA-256: e5c1364009521594821642e7e1fb4bb05490f89f2f37482019d93a73cd4a6f16
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x08133A38..0x08133A58: 32 bytes. */
u8 func_08133A38(const u8 *bits, int index)
{
    int byte_index = index >> 3;
    int bit_index = index & 7;

    if (((bits[byte_index] >> bit_index) & 1) == 0)
        return 0;
    return 1;
}
