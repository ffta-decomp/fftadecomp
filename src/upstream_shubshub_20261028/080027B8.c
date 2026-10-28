/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080027B8.c
 * Original SHA-256: b7534b84e7eb37f6b783e77c2058e98c36425efa2d093eda5ef4a6beb6ecfe25
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x080027B8..0x080027E4: 44 bytes / 22 instructions. */
u16 func_080027B8(const u8 *data, u16 count)
{
    u16 sum = 0;
    u16 index;

    for (index = 0; index < count; ++index)
        sum += *data++;
    return sum;
}
