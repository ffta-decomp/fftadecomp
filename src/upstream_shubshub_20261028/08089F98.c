/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08089F98.c
 * Original SHA-256: a3306fe671da0108052805cb13bda9fc82b78c25e527cc4fe8c3e8934acbc445
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

void func_08089F98(u16 *destination, u16 value, u16 stride,
                   u16 width, u16 height, u16 attributes, s32 step)
{
    s32 row;
    s32 column;

    for (row = 0; row < height; row++) {
        for (column = 0; column < width; column++) {
            destination[column] = value | attributes;
            value += step;
        }
        destination += stride;
    }
}
