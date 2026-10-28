/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08089EB4.c
 * Original SHA-256: 8492aa34b6c7baf3d814ec0de4307d1adcec748f9546fb9e54b39988150ed2f0
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* Complete [0x08089EB4, 0x08089F20): 108 bytes, 54 instructions. */
void func_08089EB4(u16 *dest, u16 tile, u16 width, u16 height, u16 flags)
{
    s32 y;
    for (y = 0; y < height; y++) {
        s32 x;
        for (x = 0; x < width; ) {
            dest[x] = tile | flags;
            dest[x + 0x20] = (tile + 1) | flags;
            x++;
            tile += 2;
        }
        dest += 0x40;
    }
}
