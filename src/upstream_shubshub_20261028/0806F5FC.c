/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0806F5FC.c
 * Original SHA-256: 3772524b5c4bc12fcc3de00ed30298680504089f35ab4d0f883503b468a84274
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* Complete [0x0806F5FC, 0x0806F67A): 126 bytes, 63 instructions. */
typedef struct {
    u8 unknown_00[8];
    u16 *destination;
    const u16 *source;
    u8 unknown_10[0xe];
    u8 stride;
} TileTransfer;

void func_0806F5FC(TileTransfer *transfer, u8 width, u8 height)
{
    u16 index = 0;
    u16 row, column;

    for (row = 0; row < height; ++row) {
        u16 offset = transfer->stride * row;
        for (column = 0; column < width; ++column) {
            transfer->destination[offset + column] = transfer->source[index];
            ++index;
        }
    }
}
