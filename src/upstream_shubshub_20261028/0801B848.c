/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0801B848.c
 * Original SHA-256: eb1bca46c3eac18cfcb619820367259366b8f5b8b3a5ff006a6cfff63b4c7c50
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x0801B848..0x0801B878: 48 bytes. */
extern u16 *func_0801AD1C(u8 layer);

void func_0801B848(u8 layer, u16 x, u16 y, u16 value)
{
    u16 *tiles = func_0801AD1C(layer);

    if (x < 64 && y < 64) {
        tiles += y * 64 + x;
        *tiles = value;
    }
}
