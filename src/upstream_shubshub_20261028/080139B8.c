/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080139B8.c
 * Original SHA-256: 55ef863e063125bf45459bf38af07bc27d885acc036ddf4b4d3e0fa4eabbd1cf
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* Complete 0x080139B8..0x08013A5A: 162 bytes, 79 instructions. */
typedef unsigned long long u64;

void func_080139B8(u8 *buffer, int word_column, int source_block,
                   int nibble_shift)
{
    u32 *source = (u32 *)(buffer + 0x210) + source_block * 16;
    u32 *destination = (u32 *)(buffer + 0x10) + word_column;
    int shift = nibble_shift * 4;
    int row = (s8)buffer[0xb];
    int count;

    if (row >= 0) {
        for (count = 0; count < 16 && row < 16; count++, row++)
            *(u64 *)(destination + row * 8) |= (u64)source[count] << shift;
    } else {
        row = -row;
        for (count = 0; count < 16 && row < 16; count++, row++)
            *(u64 *)(destination + count * 8) |= (u64)source[row] << shift;
    }
}
