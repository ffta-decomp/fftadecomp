/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0802B460.c
 * Original SHA-256: e289da218bdde03a144c5018d43301ebd59f69fe6a34e93a06e2b6406e348337
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[0xC];
    u8 width;
    u8 unknown_0D[7];
    u16 *tiles;
} TileGrid0802B460;

void func_0802ACA0(u16 *entries, u16 first, u8 palette, u16 count);

void func_0802B460(TileGrid0802B460 *grid, u8 x, u8 y)
{
    func_0802ACA0(grid->tiles + (grid->width * y + x), 0x63, 0xD, 3);
    func_0802ACA0(grid->tiles + (grid->width * (y + 1) + x), 0x66, 0xD, 3);
}
