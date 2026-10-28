/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08001DAC.c
 * Original SHA-256: b20f88c0ce06cc1b12d4e1684662e68779abdcc596e317acfd5632fa8cba8a89
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

extern u8 data_03000028;
extern u8 data_03002C58[][384];
extern s32 data_03002C50[];

extern s32 func_080016D4(const void *source, s32 x, s32 y, s32 depth,
                        u8 mode, u32 extra, void *buffer,
                        s32 capacity, s32 count);

/* 08001DAC..08001E18: 108 bytes, 47 instructions. */
void func_08001DAC(const void *source, s32 x, s32 y, s32 depth,
                   u8 mode, u32 extra)
{
    u8 *current = &data_03000028;
    void *buffer = data_03002C58[*current];
    s32 *counts = data_03002C50;
    s32 previous = counts[*current];

    counts[*current] = func_080016D4(source, x, y, depth, mode, extra,
                                    buffer, 48, previous);
}
