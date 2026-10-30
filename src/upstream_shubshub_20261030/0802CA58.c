/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 43f7f78cfe893ab4d99d2004e0740459589bfb5c (PR #20)
 * Original file: src/0802CA58.c
 * Original SHA-256: 46a8631c04a89d639ab5bb3fc6c020d8aa16165e7a417774d898ed3ee78bc564
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Validation: data/upstream-imports-20261030.json.
 */
#include "ffta.h"

/* Target: complete [0x0802CA58, 0x0802CABC), 100 bytes, 47 instructions. */
void func_0802CA58(u16 *tiles)
{
    s32 i;

    for (i = 6; i < 10; i++) {
        tiles[i] = (tiles[i] & 0x0fff) + 0xd000;
        tiles[i + 17] = (tiles[i + 17] & 0x0fff) + 0xd000;
    }
    for (i = 11; i < 16; i++) {
        tiles[i] = (tiles[i] & 0x0fff) + 0xd000;
        tiles[i + 17] = (tiles[i + 17] & 0x0fff) + 0xd000;
    }
}
