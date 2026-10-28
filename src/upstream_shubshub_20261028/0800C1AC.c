/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0800C1AC.c
 * Original SHA-256: 7a13dc50d9656c0cf3b0c3dd91c4ca42092ef3a3ad9c484b2ffa12807de73549
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x0800C1AC..0x0800C1C8: 28 bytes / 13 instructions. */
extern void func_0800C1C8(u8 index);

void func_0800C1AC(void)
{
    u16 index;

    for (index = 0; index < 2; ++index)
        func_0800C1C8(index);
}
