/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 11946243ba373da48154ed04cb3bb31e52dad97b
 * Original file: src/0805868C.c
 * Original SHA-256: c31acc51b7fc16c5eb8d1439dccb39d063f32e012333284d4d67159d78f1b671
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred.
 */
#include "ffta.h"

/* 0x0805868C..0x080586E0: 84 bytes / 36 instructions. */
extern void func_0814186C(const void *source, void *destination, u32 control);

void func_0805868C(s16 *tiles, u16 firstTile)
{
    u16 zero;
    u16 *fill = &zero;
    u8 i;
    u16 firstColumn;
    const s16 attributes = 0xC000;

    *fill = 0;
    func_0814186C(fill, tiles, 0x01000014);
    firstColumn = 8;
    for (i = 0; i < 2; i++) {
        u16 columnIndex = i;
        s16 *column;
        s32 tile;

        columnIndex += firstColumn;
        column = (s16 *)(columnIndex * 2 + (u32)tiles);
        tile = firstTile + i * 2;

        column[0] = tile | attributes;
        column[10] = (tile + 1) | attributes;
    }
}
