/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08001CF0.c
 * Original SHA-256: 1658a0702d1c282c68d5de80b88af8c4d6f0f0cee9ea13a9bd3d73b502fece2f
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x08001CF0..0x08001DAC: 188 bytes. */
extern u8 data_03000028;
extern u8 data_03002C58[][384];
extern void *data_03002C50[];

extern void *func_080014C8(const void *, s32, s32, u32, u32, u8, u32,
                          void *, u32, void *);

void func_08001CF0(const void *source, s32 first, s32 second, u8 mode,
                  u8 first_flag, u8 second_flag, u8 third_flag, u8 fourth_flag,
                  u32 value, u8 count, u32 extra)
{
    u8 *current = &data_03000028;
    void *buffer = data_03002C58[*current];
    void **entries = data_03002C50;
    void *previous = entries[*current];
    u32 flags = (u32)mode << 10;

    if (first_flag)
        flags |= 0x1000;
    if (second_flag)
        flags |= 0x2000;
    if (third_flag)
        flags |= 0x10000000;
    if (fourth_flag)
        flags |= 0x20000000;
    entries[*current] = func_080014C8(source, first, second, flags, value,
        count, extra, buffer, 48, previous);
}
