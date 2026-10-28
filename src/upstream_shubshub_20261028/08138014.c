/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08138014.c
 * Original SHA-256: cdb4d0fe8a4dcb7c2a4452ebcc7afc88e6b3d4ae1f5364a7f94ba7cb046b80ff
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

struct Layer08138014 {
    u32 unknown_00[6];
    u16 *first;
    u16 *second;
    u32 unknown_20[11];
};

extern struct Layer08138014 data_030009E0[];

/* Target: [0x08138014, 0x081380A6), 146 bytes, 63 instructions. */
void func_08138014(s32 layer, s32 alternate, s32 screens)
{
    u16 *output;
    s32 i;

    if (alternate == 0)
        output = data_030009E0[layer].first;
    else
        output = data_030009E0[layer].second;
    for (i = 0; i < (screens << 10); i++) {
        u16 tile;

        if (i & 2) {
            tile = (i & 1) ? 0xa43c : 0xa43d;
            tile |= (i & 0x20) ? 0x800 : 0;
        } else {
            tile = (i & 1) ? 0xa03d : 0xa03c;
            tile |= (i & 0x20) ? 0x800 : 0;
        }
        *output++ = tile;
    }
}
