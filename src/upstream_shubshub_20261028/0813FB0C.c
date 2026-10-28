/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0813FB0C.c
 * Original SHA-256: ed4efd9114fa4f39a1c0ebb0c0732755f9e97ea76df74d6d9729ffaa306a6673
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* Target: complete [0x0813FB0C, 0x0813FB68), 92 bytes, 46 instructions. */
void func_0813FB0C(const u16 *source, u16 *destination, u16 count,
                  u8 width, u16 offset)
{
    u16 index = 0;
    u16 column = 0;
    u16 row = 0;

    while (index < count) {
        if (width <= column) {
            row += 32;
            column = 0;
        }
        destination[row + column] = source[index] + offset;
        index++;
        column++;
    }
}
