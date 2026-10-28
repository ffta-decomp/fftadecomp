/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0801CBF8.c
 * Original SHA-256: 0f79c6492eea30c49043ab55493c6f70af615800ebac76bcc0c7924e95595de5
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u32 unknown_00;
    u8 *entries;
    u8 width;
} MapState;

u8 *func_0801CBF8(u8 column, u8 row)
{
    MapState *state = (MapState *)0x02007F10;

    return state->entries + row * state->width * 2 + column * 2;
}
