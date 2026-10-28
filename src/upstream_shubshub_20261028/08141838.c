/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08141838.c
 * Original SHA-256: e67afaaf04c24d50390c2e10abee5fce0742d7fae41d9760a8516b45c6df2ea1
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u32 unknown_00;
    u32 status;
} MusicPlayer;

extern u8 data_020084D8;
extern MusicPlayer data_0200F2A0;

/* Target: [0x08141838, 0x0814185E), 38 bytes, 14 instructions. */
u8 func_08141838(void)
{
    if (!(data_020084D8 & 1))
        return 0;
    return data_0200F2A0.status >> 31;
}
