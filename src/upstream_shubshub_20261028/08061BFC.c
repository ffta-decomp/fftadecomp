/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08061BFC.c
 * Original SHA-256: daf1eb43c3dc50891dde0d14df1888261721b7e780f51dd5ff34da78bd9ef696
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x08061BFC..0x08061C22: 38 bytes, 19 instructions. */
s32 func_08061BFC(const u8 *first, const u8 *second)
{
    while (*first == *second) {
        if (*first == 0 || *second == 0)
            return 0;
        first++;
        second++;
    }
    return *first - *second;
}
