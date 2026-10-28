/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0808B768.c
 * Original SHA-256: d1d65091d551f787dd21d37810ac5c54f7c8af1b842d442b0e45cfa005dba7c2
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[0x18];
    u16 *first_tiles;
    u16 *second_tiles;
    u8 unknown_20[8];
    u8 width;
    u8 unknown_29[0x23];
} Tilemap0808B768;

extern Tilemap0808B768 data_030009E0[];

/* 0x0808B768..0x0808B7C0: 88 bytes, 36 instructions. */
u16 *func_0808B768(u32 index, u32 layer, u32 x, u32 y)
{
    u16 *tiles;

    if (layer == 0) {
        tiles = data_030009E0[index].first_tiles;
    } else if (layer == 1) {
        tiles = data_030009E0[index].second_tiles;
    } else {
        tiles = 0;
    }
    return tiles + x + data_030009E0[index].width * y;
}
