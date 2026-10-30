/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 43f7f78cfe893ab4d99d2004e0740459589bfb5c (PR #20)
 * Original file: src/0808A008.c
 * Original SHA-256: 3ca9e7b5ea3f2aac96caeae226d2da536b7604e430af1d9e307b0f21969ee004
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Validation: data/upstream-imports-20261030.json.
 */
#include "ffta.h"

/* 0x0808A008 .. 0x0808A084: 124 bytes, including literal pool. */
void func_0808A008(u16 *tiles, u16 start, u16 stride, u16 end,
                   u16 height, u16 flags)
{
    int row;
    int column;

    for (row = 0; row < height; row++) {
        for (column = start; column < end; column++)
            tiles[column] = (tiles[column] & 0x0FFF) | flags;
        tiles += stride;
    }
}
