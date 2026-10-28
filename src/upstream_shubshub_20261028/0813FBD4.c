/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0813FBD4.c
 * Original SHA-256: 80c80819b4d132d5adb234f2f2203749f3beefe25679224441f3f1db235ce2c3
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* Clear a rectangle in a tile map with a 32-entry row stride. */
void func_0813FBD4(u16 *tile_map, u8 x, u8 y, u8 width, u8 height)
{
    u16 offset = x + (y << 5);
    u8 row;
    u8 column;

    for (row = 0; row < height; row++)
    {
        for (column = 0; column < width; column++)
            tile_map[offset + column] = 0;
        offset += 32;
    }
}
