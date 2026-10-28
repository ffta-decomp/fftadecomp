/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0808B8E4.c
 * Original SHA-256: da3a506b42a60c1e33b0bb46b4c46089aded1e7ac3a427b23d25cd3cdaae4c79
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[0x18];
    u16 *first_plane;
    u16 *second_plane;
    u8 unknown_20[8];
    u8 stride;
    u8 unknown_29[0x23];
} TileRenderer;

extern TileRenderer data_030009E0[];

u16 *func_0808B8E4(u32 index, u32 plane, s32 x, s32 y)
{
    u16 *tiles;

    if (plane)
        tiles = data_030009E0[index].second_plane + x
            + data_030009E0[index].stride * y;
    else
        tiles = data_030009E0[index].first_plane + x
            + data_030009E0[index].stride * y;
    return tiles;
}
