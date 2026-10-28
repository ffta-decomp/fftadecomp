/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080105B8.c
 * Original SHA-256: bcb0fcb2e584538116ff1be1d1d07c0c9ab81be36830ca4261ded4a3e572a079
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

extern u8 data_02009160;

/* 0x080105B8 - 12 bytes */
void func_080105B8(void)
{
    data_02009160 = 2;
}
