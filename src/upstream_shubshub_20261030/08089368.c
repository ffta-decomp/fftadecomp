/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 43f7f78cfe893ab4d99d2004e0740459589bfb5c (PR #20)
 * Original file: src/08089368.c
 * Original SHA-256: 320332401be70597686a1b08cc405a84b562ea5d3546d8dc76b896af97ff1b45
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Validation: data/upstream-imports-20261030.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[0x1C];
    u16 *tiles;
    u8 unknown_20[8];
    u8 stride;
    u8 unknown_29[0x23];
} Tilemap08089368;

extern Tilemap08089368 data_030009E0[];

/* Complete [0x08089368, 0x08089400): 152 bytes, 71 instructions. */
void func_08089368(u32 index, u16 attributes, u8 x, u8 y,
                   u8 width, u8 height)
{
    s32 row;
    s32 column;

    for (row = 0; row < height; row++) {
        u16 *destination = data_030009E0[index].tiles;
        destination += x + (row + y) * data_030009E0[index].stride;

        for (column = 0; column < width; column++)
            destination[column] = (destination[column] & 0x0FFF) + attributes;
    }
}
