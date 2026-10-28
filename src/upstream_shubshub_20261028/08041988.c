/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08041988.c
 * Original SHA-256: 46e09e27a2d28c406845e201616986a3bbc378cbe587a1789eef6e5f8a498ede
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 08041988 .. 08041ABA: 306 bytes. */
typedef struct {
    u8 unknown_00[0x0C];
    u16 *tiles;
    u8 unknown_10[5];
    u8 width;
    u8 unknown_16[6];
    u16 first_tile;
    u8 unknown_1E;
    u8 palette;
} TileSurface;

void func_08041988(u16 frame, TileSurface *surface, u16 first_palette,
                   u32 show_suffix)
{
    u16 width = surface->width;
    u16 variant = frame % 5u;
    u16 tile = surface->first_tile + variant * 32;
    u16 *destination = &surface->tiles[(variant << 1) * width];
    u16 column;

    destination[0] = tile++ + first_palette;
    destination[1] = tile++ + first_palette;
    destination[width] = tile++ + first_palette;
    destination[width + 1] = tile++ + first_palette;
    for (column = 2; column < 14; column++) {
        destination[column] = tile++ + (surface->palette << 12);
        (destination + column)[width] = tile++ + (surface->palette << 12);
    }
    destination[column] = 0;
    destination[column + 1] = 0;
    (destination + column)[width] = 0;
    (destination + column)[width + 1] = 0;
    for (; column < 16; column++) {
        destination[column + 2] = tile++ + (surface->palette << 12);
        (destination + column)[width + 2] = tile++ + (surface->palette << 12);
    }
    if (show_suffix == 0) {
        destination[column + 2] = 0;
        destination[column + 3] = 0;
        (destination + column)[width + 2] = 0;
        (destination + column)[width + 3] = 0;
    } else {
        destination[column + 2] = 0;
        destination[column + 3] = 0;
        (destination + column)[width + 2] = 0x52 + (surface->palette << 12);
        (destination + column)[width + 3] = 0x53 + (surface->palette << 12);
    }
}
