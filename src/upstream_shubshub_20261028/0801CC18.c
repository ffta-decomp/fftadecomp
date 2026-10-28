/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0801CC18.c
 * Original SHA-256: 189d1660d847bc89a8874ecc68ea562040b7803f34229832d88a9a27545e6ab3
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u32 unknown_00;
    u8 *entries;
    u8 width;
} MapState;

u8 func_0801CC18(u8 column, u8 row)
{
    MapState *state = (MapState *)0x02007F10;
    s32 offset = state->width;
    u8 *entries;

    offset *= row;
    offset *= 2;
    entries = state->entries + offset;
    entries += column * 2;
    return entries[0];
}
