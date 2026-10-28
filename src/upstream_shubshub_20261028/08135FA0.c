/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08135FA0.c
 * Original SHA-256: 94f599f5157c94dd422f8f074deda676be01ff018a4e521e8b6be98732cea9a4
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x08135FA0..0x08135FFC: 92 bytes. */
void func_08135FA0(const u16 *source, u16 *destination, u16 count,
                   u8 width, u16 offset)
{
    u16 index = 0;
    u16 column = 0;
    u16 row = 0;

    for (; index < count; index++, column++) {
        if (width <= column) {
            row += 32;
            column = 0;
        }
        destination[row + column] = source[index] + offset;
    }
}
