/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08002050.c
 * Original SHA-256: 310e2e25a4c83f668750ecaad7c8f0e7bb6e695c16a84595441ed39318f02d11
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x08002050..0x08002108: 184 bytes, 84 instructions. */
extern u8 data_03002F58;
extern u8 data_03003170[2][128];
extern u32 data_03003168[2];

extern u32 func_080014C8(const void *source, s32 x, s32 y, u32 flags,
                         u32 attributes, u8 priority, u32 layer, void *buffer,
                         u32 count, u32 cursor);

void func_08002050(const void *source, s32 x, s32 y, u8 palette,
                   u8 flip_x, u8 flip_y, u8 option_a, u8 option_b,
                   u32 attributes, u8 priority, u32 layer)
{
    u8 *buffer_index = &data_03002F58;
    u8 *buffer = data_03003170[*buffer_index];
    u32 *cursors = data_03003168;
    u32 cursor = cursors[*buffer_index];
    u32 flags = (u32)palette << 10;

    if (flip_x) {
        flags |= 0x1000;
    }
    if (flip_y) {
        flags |= 0x2000;
    }
    if (option_a) {
        flags |= 0x10000000;
    }
    if (option_b) {
        flags |= 0x20000000;
    }
    cursors[*buffer_index] = func_080014C8(source, x, y, flags, attributes,
                                         priority, layer, buffer, 16, cursor);
}
