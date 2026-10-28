/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080204B0.c
 * Original SHA-256: 264d5931aed462f2b5ec1a328a08236ea71574ed9d1a110d06b54916a336994c
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x080204B0..0x080204D0: 32 bytes / 13 instructions. */
struct LoaderState080204B0 {
    u8 unknown_00[0x16C];
    const u8 *current;
};

extern struct LoaderState080204B0 g_state_02007F40;

u32 func_080204B0(void)
{
    u32 idle = 0;

    if (g_state_02007F40.current == 0)
        idle = 1;
    return idle;
}
