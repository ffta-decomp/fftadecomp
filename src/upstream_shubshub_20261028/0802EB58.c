/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0802EB58.c
 * Original SHA-256: 7416b32b2160a48d5dae78297314124af52ea5a6b8ff03efa53524db77728bb8
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_000[0xa];
    u8 active;
    u8 unknown_00b[0x45d];
    s16 x;
    s16 y;
    const void *center;
    const void *right;
    s16 phase;
    u8 unknown_476[2];
    const void *left;
} State0802EB58;

extern State0802EB58 *data_0200F444;
extern void func_08001CF0(const void *, s32, s32, u32, u32, u32, u32,
                          u32, u32, u32, u32);

/* Complete [0x0802EB58, 0x0802EC24): 204 bytes, 91 instructions. */
void func_0802EB58(void)
{
    if (data_0200F444->active) {
        if (++data_0200F444->phase > 15)
            data_0200F444->phase = 0;

        func_08001CF0(data_0200F444->left,
                      data_0200F444->x + (data_0200F444->phase >> 1) - 8,
                      data_0200F444->y, 0, 0, 0, 0, 0, 0, 0, 0);
        func_08001CF0(data_0200F444->right, data_0200F444->x + 8,
                      data_0200F444->y, 0, 0, 0, 0, 0, 0, 0, 0);
        func_08001CF0(data_0200F444->center, data_0200F444->x,
                      data_0200F444->y, 0, 0, 0, 0, 0, 0, 0, 0);
    }
}
