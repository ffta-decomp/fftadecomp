/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080379A8.c
 * Original SHA-256: 86157ad07c49894dff8b7a0fdf26ef91026a3afd78929e34102e048a5a129ce0
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* Complete target: [0x080379A8, 0x08037A30), 136 bytes. */
typedef struct {
    u8 unknown_00[0x18];
    u16 *first_plane;
    u16 *second_plane;
    u8 unknown_20[8];
    u8 stride;
    u8 unknown_29[0x23];
} TileRenderer;

extern TileRenderer data_030009E0[];
extern u16 *func_0808B8E4(u32 index, u32 plane, s32 x, s32 y);

void func_080379A8(u32 index, s32 x, s32 y, s32 width,
                   s32 height, u16 palette)
{
    u16 *tiles;
    s32 offset;
    s32 row;
    s32 column;

    palette <<= 12;
    tiles = func_0808B8E4(index, 1, x, y);
    offset = 0;
    for (row = 0; row < height; row++) {
        for (column = 0; column < width; column++) {
            tiles[offset + column] =
                (tiles[offset + column] & 0x0FFF) + palette;
        }
        offset += data_030009E0[index].stride;
    }
}
