/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08013060.c
 * Original SHA-256: 5eb5e196786310bf02337152dc1a6e6b97f9e287801c43b1a142b85d692adc61
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

struct Context08013060 {
    u8 unknown_00[0x24];
    s16 value;
    u8 unknown_26[0x0e];
    u16 first_offset;
    u16 second_offset;
    s8 phase;
    u8 timer;
    u16 flags;
    u8 unknown_3c[5];
    u8 stride;
    u8 unknown_42;
    u8 count;
};

extern struct Context08013060 *data_0200918C;
extern const u8 data_0836D62C[];
extern const u8 data_0851BA5A[];
extern void func_08001CF0(const u8 *, u32, u16, u32,
                          u32, u32, u32, u32, s32, u32, u32);

/* Target: [0x08013060, 0x08013108), 168 bytes, 76 instructions. */
void func_08013060(void)
{
    if (data_0200918C->flags & 1) {
        if (data_0200918C->timer++ >= data_0836D62C[data_0200918C->phase]) {
            data_0200918C->phase++;
            if (data_0200918C->phase > 2)
                data_0200918C->phase = 0;
            data_0200918C->timer = 0;
        }
        func_08001CF0(data_0851BA5A,
                       data_0200918C->stride * (data_0200918C->count + 11) +
                           data_0200918C->first_offset,
                       data_0200918C->second_offset, 0, 0, 0, 0, 0,
                       data_0200918C->phase + data_0200918C->value, 0, 0);
    }
}
