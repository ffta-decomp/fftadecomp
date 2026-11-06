/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 11946243ba373da48154ed04cb3bb31e52dad97b
 * Original file: src/0813839C.c
 * Original SHA-256: 2d986d512d803503d82d4e246cf99ddff3b63c5393b3d6268c11c60ecbfd6926
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred.
 */
#include "ffta.h"

struct BufferState {
    u8 unknown_000[0xA1C];
    u16 first[256];
    u16 second[256];
};

extern struct BufferState *data_030027D8;
extern u16 data_03003860[];
extern s16 func_08007A60(u8 index);

/* Complete target [0x0813839C, 0x081384B0), 276 bytes. */
void func_0813839C(u8 steps, u8 phase)
{
    u16 *first = data_030027D8->first;
    u16 *second = data_030027D8->second;
    u16 *first_output = data_03003860;
    u16 *second_output = data_03003860 + 256;
    u16 inverse = 32 - (func_08007A60((64 / steps) * phase) >> 3);
    u16 i;

    for (i = 0; i < 256; i++, first++, second++) {
        *first_output++ = ((*first & 31) * (32 - inverse)) / 32 |
            ((((*first >> 5) & 31) * (32 - inverse)) / 32) << 5 |
            ((((*first >> 10) & 31) * (32 - inverse)) / 32) << 10;
        *second_output++ = ((*second & 31) * (32 - inverse)) / 32 |
            ((((*second >> 5) & 31) * (32 - inverse)) / 32) << 5 |
            ((((*second >> 10) & 31) * (32 - inverse)) / 32) << 10;
    }
}
