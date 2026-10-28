/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08001E18.c
 * Original SHA-256: ee1d32af69cbfefe1a380f476e4fbf2e746eb8799c4bfb9ebaff54c2c07484b7
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x08001E18 .. 0x08001ED0: 184 bytes. */
extern u8 data_03002F58;
extern u8 data_03002F68[][256];
extern u32 *data_03002F60[];

extern u32 *func_080014C8(const void *source, s32 x, s32 y,
                         u32 flags, u32 value, u8 mode,
                         const void *transform, u8 *entries,
                         u32 capacity, u32 *output);

void func_08001E18(const void *source, s32 x, s32 y, u8 variant,
                   u8 flip_x, u8 flip_y, u8 flag_28, u8 flag_29,
                   u32 value, u8 mode, const void *transform)
{
    u8 *entries = data_03002F68[data_03002F58];
    u32 *output = data_03002F60[data_03002F58];
    u32 flags = variant << 10;

    if (flip_x)
        flags |= 0x1000;
    if (flip_y)
        flags |= 0x2000;
    if (flag_28)
        flags |= 0x10000000;
    if (flag_29)
        flags |= 0x20000000;

    data_03002F60[data_03002F58] = func_080014C8(source, x, y, flags,
        value, mode, transform, entries, 32, output);
}
