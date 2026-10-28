/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08001FEC.c
 * Original SHA-256: 2418f5ec672948485ed25c1d4241acc5fde721eb70f7aa8c683666eebc76ecbe
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

extern u8 data_03000028;
extern u8 data_03000030[][1024];
extern s32 data_03000020[];

extern s32 func_080016D4(const void *source, s32 x, s32 y, s32 depth,
                        u8 mode, u32 extra, void *buffer,
                        s32 capacity, s32 count);

/* 08001FEC..08002050: 100 bytes, 43 instructions. */
void func_08001FEC(const void *source, s32 x, s32 y, s32 depth,
                   u8 mode, u32 extra)
{
    u8 *current = &data_03000028;
    void *buffer = data_03000030[*current];
    s32 *counts = data_03000020;
    s32 previous = counts[*current];

    counts[*current] = func_080016D4(source, x, y, depth, mode, extra,
                                    buffer, 128, previous);
}
