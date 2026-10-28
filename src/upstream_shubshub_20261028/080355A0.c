/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080355A0.c
 * Original SHA-256: 1697d434f84ce013c195c07b72054aa585e4ed9fde612e45eed52f5183d4016a
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 080355A0..080355E2: 66 bytes, 33 instructions. */
void func_080355A0(const u16 *source, u16 *destination, u32 height,
                   u16 width, u16 stride)
{
    u32 row;
    u32 column;

    for (row = 0; row < height; row++) {
        for (column = 0; column < width; column++)
            destination[column] = *source++;
        destination += stride;
    }
}
