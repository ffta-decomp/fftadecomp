/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 43f7f78cfe893ab4d99d2004e0740459589bfb5c (PR #20)
 * Original file: src/08079690.c
 * Original SHA-256: d164dc0343cf4177d61e97aa6b33e20d43ebe1c04e01fbeac44b9ccb26ade127
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Validation: data/upstream-imports-20261030.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[0x0c];
    u16 *large_second;
    u16 *large_first;
    u16 *small_second;
    u16 *small_first;
    u16 *buffer;
} ResourceContext08079690;

typedef struct {
    u16 *large_tiles;
    u16 *small_tiles;
    u16 *regions[10];
} TileStorage08079690;

extern ResourceContext08079690 *data_03002818;
extern TileStorage08079690 data_03002740;
extern u16 data_06007000[];
extern u16 data_06005800[];
extern u16 data_06006000[];
extern u16 data_06005000[];

/* Complete target [0x08079690, 0x0807974C): 188 bytes, 71 instructions. */
void func_08079690(u32 mode)
{
    if (mode == 0) {
        u16 *buffer;

        data_03002740.regions[0] = buffer = data_03002818->buffer;
        data_03002740.regions[1] = buffer + 0x120;
        data_03002740.regions[2] = buffer + 0x2a0;
        data_03002740.regions[3] = buffer + 0x40c;
        data_03002740.regions[9] = data_03002740.regions[3];
        data_03002740.regions[5] = data_03002740.regions[2];
        data_03002740.regions[6] = buffer + 0x4a8;
        data_03002740.regions[4] = buffer + 0x6e4;
    } else {
        u16 *buffer;

        data_03002740.large_tiles = data_06007000;
        data_03002740.small_tiles = data_06005800;
        data_03002818->large_first = data_06007000;
        data_03002818->large_second = data_06006000;
        data_03002818->small_first = data_06005800;
        data_03002818->small_second = data_06005000;
        data_03002740.regions[0] = (buffer = data_03002818->buffer) + 0xfc;
        data_03002740.regions[1] = buffer + 0x21c;
        data_03002740.regions[2] = buffer + 0x39c;
        data_03002740.regions[3] = buffer + 0x508;
        data_03002740.regions[9] = data_03002740.regions[3];
        data_03002740.regions[5] = data_03002740.regions[2];
        data_03002740.regions[6] = buffer + 0x5a4;
        data_03002740.regions[4] = buffer + 0x7e0;
    }
}
