/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080053D4.c
 * Original SHA-256: 301f00034b78341db9cec22ae14c5f6dcab31b3cc688be9189f5f8a5c90413ff
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

extern u32 data_03002BB8;
extern u32 data_03002BB4;
extern u32 data_03002BB0;

u16 func_080053D4(const u8 *data)
{
    u32 cleared = 0;
    data_03002BB8 = cleared;
    data_03002BB4 = cleared;
    data_03002BB0 = cleared;
    if (!data)
        return 0;
    return (data[2] << 8) | data[3];
}
