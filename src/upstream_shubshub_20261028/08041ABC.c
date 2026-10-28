/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08041ABC.c
 * Original SHA-256: 86b063ec7ad2472aa7b9b3f8a46b52e0632ee839a84b845f0bb9f975bc84f0f3
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

struct State08041ABC {
    u8 unknown_00[0xc];
    u16 *tilemap;
    u8 unknown_10[5];
    u8 width;
    u8 unknown_16;
    u8 height;
    u8 unknown_18[4];
    u16 first_tile;
    u8 unknown_1e;
    u8 palette;
};

/* Target: [0x08041ABC, 0x08041BB0), 244 bytes, 122 instructions. */
void func_08041ABC(struct State08041ABC *state)
{
    u16 *dest = state->tilemap;
    u16 tile = state->first_tile + (state->palette << 12);
    s32 width = state->width;
    s32 rows = state->height;
    s32 i;

    while (rows) {
        dest[0] = tile++;
        dest[1] = tile++;
        dest[width] = tile++;
        dest[width + 1] = tile++;
        for (i = 2; i < 14; i++) {
            dest[i] = tile++;
            (dest + i)[width] = tile++;
        }
        dest[i] = 0;
        dest[i + 1] = 0;
        (dest + i)[width] = 0;
        (dest + i)[width + 1] = 0;
        for (; i < 16; i++) {
            dest[i + 2] = tile++;
            (dest + i + 2)[width] = tile++;
        }
        dest[i + 2] = 0;
        dest[i + 3] = 0;
        (dest + i + 2)[width] = 0;
        (dest + i + 2)[width + 1] = 0;
        dest += width * 2;
        rows--;
    }
}
