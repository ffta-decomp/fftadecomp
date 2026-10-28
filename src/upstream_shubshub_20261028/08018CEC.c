/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08018CEC.c
 * Original SHA-256: dc3ace40d56856a3d44d8bb0b9ea372be5c76d39dafa8c1e90e2f57aa4ede573
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x08018CEC..0x08018D10: 36 bytes / 14 instructions. */
typedef u32 (*TextFormatter)(u8 *destination, u8 code);

extern TextFormatter const data_0836D768[];

u8 func_08018CEC(u8 *destination, u8 code)
{
    *destination = 0;
    return data_0836D768[code](destination, code);
}
