/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 43f7f78cfe893ab4d99d2004e0740459589bfb5c (PR #20)
 * Original file: src/08038820.c
 * Original SHA-256: 8cf08520d6d61ebfd7424213307f362bc4f6b8e71d42579cb61ac5147c72412b
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Validation: data/upstream-imports-20261030.json.
 */
#include "ffta.h"

typedef struct {
    u16 active;
    u8 unknown_02[6];
} StateEntry;

typedef struct {
    u8 unknown_00[0x913];
    u8 count;
    StateEntry entries[16];
} State03002810;

extern State03002810 *g_state_03002810;

/* Target: complete [0x08038820, 0x08038858), 56 bytes, 21 instructions. */
void func_08038820(void)
{
    s32 i;

    g_state_03002810->count = 0;
    for (i = 0; i < 16; i++)
        g_state_03002810->entries[i].active = 0;
}
