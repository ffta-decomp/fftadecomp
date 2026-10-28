/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08001F34.c
 * Original SHA-256: d76a4353cbbd0971fd00b08c9eb0813e3537632a57856d3fa017aa6a060bbf4e
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x08001F34 .. 0x08001FEC: 184 bytes. */
extern u8 data_03000028;
extern u8 data_03000030[][1024];
extern u32 *data_03000020[];

extern u32 *func_080014C8(const void *source, s32 x, s32 y,
                         u32 flags, u32 value, u8 mode,
                         const void *transform, u8 *entries,
                         u32 capacity, u32 *output);

void func_08001F34(const void *source, s32 x, s32 y, u8 variant,
                   u8 flip_x, u8 flip_y, u8 flag_28, u8 flag_29,
                   u32 value, u8 mode, const void *transform)
{
    u8 *entries = data_03000030[data_03000028];
    u32 *output = data_03000020[data_03000028];
    u32 flags = variant << 10;

    if (flip_x)
        flags |= 0x1000;
    if (flip_y)
        flags |= 0x2000;
    if (flag_28)
        flags |= 0x10000000;
    if (flag_29)
        flags |= 0x20000000;

    data_03000020[data_03000028] = func_080014C8(source, x, y, flags,
        value, mode, transform, entries, 128, output);
}
