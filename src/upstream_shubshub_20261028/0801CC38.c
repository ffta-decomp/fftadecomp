/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0801CC38.c
 * Original SHA-256: d8a94fb37a61366a3818846c7313c8e99e0f1f44809944aecdd1f96760837e95
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u32 unknown_00;
    u8 *entries;
    u8 width;
} MapState;

s16 func_0801CC38(u8 column, u8 row, u8 mode)
{
    MapState *state = (MapState *)0x02007F10;
    s32 offset = row * state->width;
    u8 *entries;
    s16 height;

    offset *= 2;
    entries = state->entries + offset;
    entries += column * 2;
    height = entries[0];
    if (!(mode & 1) && (entries[1] & 2))
        height--;
    return height;
}
