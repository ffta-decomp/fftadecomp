/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 11946243ba373da48154ed04cb3bb31e52dad97b
 * Original file: src/08087554.c
 * Original SHA-256: cfc645abbd6b42214569a3ce200fce24d0e449cc7db427be24dd9e3d883736bf
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred.
 */
#include "abi/interfaces/080008e0_bindings.h"

typedef struct {
    u8 unknown_00[0x28];
    u16 first[256];
    u16 second[256];
} PaletteState08087554;

extern PaletteState08087554 *data_03002818;
extern u16 data_03003860[];
extern s32 func_081426B8(s32, s32);
extern s16 func_08007A60(u8);

/* Complete [0x08087554, 0x08087660): 268 bytes, 127 instructions. */
void func_08087554(u8 period, u8 phase)
{
    u16 *first = data_03002818->first;
    u16 *second = data_03002818->second;
    u16 *out_first = data_03003860;
    u16 *out_second = data_03003860 + 256;
    u16 amount = 32 - (func_08007A60(func_081426B8(64, period) * phase) >> 3);
    u16 i;

    for (i = 0; i < 256; ++i, ++first, ++second) {
        *out_first++ = (*first & 31) * (32 - amount) / 32
            | ((((*first >> 5) & 31) * (32 - amount) / 32) << 5)
            | ((((*first >> 10) & 31) * (32 - amount) / 32) << 10);
        *out_second++ = (*second & 31) * (32 - amount) / 32
            | ((((*second >> 5) & 31) * (32 - amount) / 32) << 5)
            | ((((*second >> 10) & 31) * (32 - amount) / 32) << 10);
    }
}
