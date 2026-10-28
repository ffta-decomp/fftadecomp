/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0801AE9C.c
 * Original SHA-256: 2c024d354ee9fd01c77935bcdf9c7fdedc1caebb4ded0137c2f14424dad6ede9
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct State0801AE9C {
    u8 unknown_0000[0x2FC2];
    u8 flags;
} State0801AE9C;

extern State0801AE9C g_state_02000000;

/* Complete [0x0801AE9C, 0x0801AECA): 46 bytes, 18 instructions. */
u32 func_0801AE9C(void)
{
    u8 mode = g_state_02000000.flags & 3;

    if (mode == 2)
        return 1;
    if (mode == 1)
        return 2;
    return 0;
}
