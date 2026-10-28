/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0801DF8C.c
 * Original SHA-256: dfb6cb4d90824ba2ccbd8f5a7dbdcab157f9182857e09d477b214398ca1d607a
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct ReadinessState {
    u8 unknown_00[0x2C];
    u16 flags;
    u8 unknown_2E[0x1EA];
    u8 first_ready;
    u8 unknown_219[3];
    u8 second_ready;
} ReadinessState;

extern ReadinessState g_state_02007F40;

/* 0801DF8C..0801DFDA: 78 bytes, 37 instructions. */
u8 func_0801DF8C(u8 mode)
{
    if (!(g_state_02007F40.flags & 0x400))
        return 0;
    if ((mode == 1 || mode == 3) && !g_state_02007F40.first_ready)
        return 0;
    if ((mode == 2 || mode == 3) && !g_state_02007F40.second_ready)
        return 0;
    return 1;
}
