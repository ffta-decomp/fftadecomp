/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080029CC.c
 * Original SHA-256: 9b11c48175f1928f42c2a4cc4e9255a741419b5bd99d4192c743df13761ee59a
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x080029CC..0x08002A08: 60 bytes / 30 instructions. */
s32 func_080029CC(const u8 *first, const u8 *second, u32 count)
{
    while (count-- != 0) {
        if (*first > *second)
            return 1;
        if (*first < *second++)
            return -1;
        if (*first++ == 0)
            break;
    }
    return 0;
}
