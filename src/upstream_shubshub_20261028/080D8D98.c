/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080D8D98.c
 * Original SHA-256: dc4e8149b756c95bedc1083f2ba64caa3b631debffa1379880dc0bbaca629ba5
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

extern u16 func_0801BB94(s16 x, s16 y, u8 mode, u8 effect, u8 option);

/* 080D8D98..080D8DC0: 40 bytes, 19 instructions. */
u8 func_080D8D98(s16 x, s16 y)
{
    return func_0801BB94(x, y, 4, 16, 4) != 0;
}
