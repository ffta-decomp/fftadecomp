/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080897C4.c
 * Original SHA-256: 3d8cffc720eb8a8889b558aac1a7956e4eb3d027f52294c288c92f003ea37afb
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

void func_080897C4(u16 *destination, u16 value, u16 stride,
                   u16 width, u16 height, u16 attributes, s32 step)
{
    s32 row_stride = stride - 2;
    s32 row;
    s32 column;

    for (row = 0; row < height; row++) {
        for (column = 0; column < width; column++) {
            destination[column] = value | attributes;
            value += step;
        }
        destination += row_stride;
    }
}
