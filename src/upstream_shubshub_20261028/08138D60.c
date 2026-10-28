/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08138D60.c
 * Original SHA-256: c3cbb99941fcde01d8726ffe248bc83a141278897f6136282b7f44da26f15d45
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* Target: complete [0x08138D60, 0x08138DA4), 68 bytes, 28 instructions. */
extern u8 data_02003CB0[];
extern u32 func_0813B480(u32, const void *);

u8 func_08138D60(void)
{
    u8 mask = func_0813B480(0, data_02003CB0) != 0;

    if (func_0813B480(1, data_02003CB0))
        mask |= 2;
    if (func_0813B480(2, data_02003CB0))
        mask |= 4;
    return mask;
}
