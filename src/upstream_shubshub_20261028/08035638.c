/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08035638.c
 * Original SHA-256: 71d604992209d1326ef1342e329c0b73ff49a94e5dd9c3ed91ce5496de708801
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x08035638..0x08035678: 64 bytes / 32 instructions. */
void func_08035638(const u16 *source, u16 *destination, u32 height,
                   u16 width, u16 stride, u16 value)
{
    u32 row;
    u32 column;

    for (row = 0; row < height; row++) {
        for (column = 0; column < width; column++)
            destination[column] = value;
        destination += stride;
    }
}
