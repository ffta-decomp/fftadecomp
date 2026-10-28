/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08145B4C.c
 * Original SHA-256: 3e4f3eda941328030f79f79bc56a7ba7f2940fb7552c1ee61879305c55a147f0
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x08145B4C..0x08145BF4: 168 bytes, 77 reachable instructions. */
extern const u8 data_0836D2C0[];
extern const u8 data_0836D224[];
extern const s16 data_0836D2A8[];

static inline s32 decode_sample(u32 index)
{
    const u8 *values = data_0836D224;
    s32 encoded = values[index];
    const s16 *mantissas = data_0836D2A8;

    encoded = mantissas[encoded & 15] >> (encoded >> 4);
    return encoded;
}

s32 func_08145B4C(u8 mode, u8 index, u8 fraction)
{
    s32 first;
    s32 second;

    if (mode == 4) {
        if (index <= 20) {
            index = 0;
        } else {
            index -= 21;
            if (index > 59)
                index = 59;
        }
        return data_0836D2C0[index];
    }
    if (index <= 35) {
        fraction = 0;
        index = 0;
    } else {
        index -= 36;
        if (index > 130) {
            index = 130;
            fraction = 255;
        }
    }
    first = decode_sample(index);
    second = decode_sample(index + 1);
    return first + (((second - first) * fraction) >> 8) + 0x800;
}
