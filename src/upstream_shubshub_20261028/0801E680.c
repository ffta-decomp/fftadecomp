/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0801E680.c
 * Original SHA-256: 75301209dc2aea306a7caf4b8d3e4ae8c120ed98fd92f7dc8ac3fcda97089975
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct State02007F40 {
    u8 unknown_00[0x0A];
    u16 value;
} State02007F40;

extern State02007F40 g_state_02007F40;

/* 0801E680..0801E68C: 12 bytes, 3 instructions. */
u16 func_0801E680(void)
{
    return g_state_02007F40.value;
}
