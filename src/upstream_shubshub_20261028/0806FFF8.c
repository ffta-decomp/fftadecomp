/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0806FFF8.c
 * Original SHA-256: 7b54b0d6b18d7fef10554bca1e394ae125524186b180417d50007799ca91e26c
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x0806FFF8..0x08070070: 120 bytes. */
typedef struct {
    u8 unknown_00[0x0C];
    u8 stride;
    u8 unknown_0d[7];
    u16 *tiles;
} TileSurface;

void func_0806FFF8(TileSurface *surface, const u16 *source,
                   u8 x, u8 y, u8 width, u8 height)
{
    u8 row;
    u8 column;

    for (row = 0; row < height; ++row) {
        u16 offset = surface->stride * (row + y);

        for (column = 0; column < width; ++column) {
            u16 index = offset + x + column;

            surface->tiles[index] = source[index];
        }
    }
}
