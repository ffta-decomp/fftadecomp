/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08133BE0.c
 * Original SHA-256: aaf305ff26da77d5f3baf39565fa9e3e72c5d49c1006269251bc91c2d8f6a5ce
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* Complete [0x08133BE0, 0x08133C00): 32 bytes, 16 instructions. */
u8 func_08133BE0(const u8 *flags, s32 index)
{
    s32 byte_index = index >> 3;
    s32 bit_index = index & 7;
    u8 value = flags[byte_index];
    if ((value >> bit_index) & 1)
        return 1;
    return 0;
}
