/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080157A8.c
 * Original SHA-256: 8a79d670bbe941239e8ec27ab0188be6be02307170b499bcdcc22d25913ea04a
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* Complete [0x080157A8, 0x08015858): 176 bytes, 88 instructions. */
void func_080157A8(u16 *tilemap, u8 column, u8 row, u8 width,
                   u8 height, u8 stride, u16 tile, u8 palette)
{
    u16 offset = row * stride + column;
    u16 *destination = tilemap + offset;
    u16 current;
    u16 row_stride;
    u16 remaining;
    u16 index;

    current = tile + (palette << 12);
    row_stride = stride * 2;
    for (remaining = height; remaining != 0; remaining--) {
        for (index = 0; index < width; index++) {
            destination[index] = current++;
            (destination + stride)[index] = current++;
        }
        destination += row_stride;
    }
}
