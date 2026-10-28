/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08145098.c
 * Original SHA-256: eb216f69682859fe9b17adc2b055c2a085570d1440a60f8ed13112b426835c5a
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u32 unknown_00;
    u32 frequency;
} WaveData;

extern const u8 data_0836D128[];
extern const u32 data_0836D1DC[];
extern u32 func_08144500(u32 first, u32 second);

/* Complete [0x08145098, 0x081450FC): 100 bytes, 44 instructions. */
u32 func_08145098(const WaveData *wave, u8 key, u8 fine_adjustment)
{
    u32 first;
    u32 second;
    u32 fraction = (u32)fine_adjustment << 24;

    if (key > 178) {
        key = 178;
        fraction = 255u << 24;
    }
    first = data_0836D128[key];
    first = data_0836D1DC[first & 15] >> (first >> 4);
    second = data_0836D128[key + 1];
    second = data_0836D1DC[second & 15] >> (second >> 4);
    return func_08144500(wave->frequency,
        first + func_08144500(second - first, fraction));
}
