/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0801B814.c
 * Original SHA-256: f4757ad4e3030380b635a481f141e4d09cc6371b121fb743b6b87f34518b644d
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x0801B814..0x0801B848: 52 bytes. */
extern u16 *func_0801AD1C(u8 layer);

u16 func_0801B814(u8 layer, u16 x, u16 y)
{
    u16 *tiles = func_0801AD1C(layer);

    if (x >= 64 || y >= 64) {
        return 0xFFFF;
    }
    tiles += y * 64 + x;
    return *tiles;
}
