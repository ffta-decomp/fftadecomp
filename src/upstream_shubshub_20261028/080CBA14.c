/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080CBA14.c
 * Original SHA-256: 6781bfeb510a95da9e5e9d93b79857e73315fd5785a9b958929b7e5c77e0c36f
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x080CBA14..0x080CBA3C: 40 bytes, 18 instructions, including a pool. */
extern const u8 data_083B8F50[];

u32 func_080CBA14(u8 index)
{
    if (index > 0x52) {
        index = 0x2D;
    } else if (index > 0x2B) {
        index = 0x2C;
    }
    return data_083B8F50[index * 4 - 4] >> 4;
}
