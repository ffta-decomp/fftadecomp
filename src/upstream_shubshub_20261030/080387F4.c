/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 43f7f78cfe893ab4d99d2004e0740459589bfb5c (PR #20)
 * Original file: src/080387F4.c
 * Original SHA-256: 2cfea5e17bde64dd12841ae21bbb629c016ad8e8f9ff1a030305b6b3b1fc882d
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Validation: data/upstream-imports-20261030.json.
 */
#include "ffta.h"

/* Target: complete [0x080387F4, 0x08038820), 44 bytes, 18 instructions. */
typedef struct {
    u16 active;
    u8 unknown_02[6];
} StateEntry;

typedef struct {
    u8 unknown_00[0x914];
    StateEntry entries[4];
} State03002810;

extern State03002810 *g_state_03002810;

u32 func_080387F4(void)
{
    u32 count = 0;
    s32 i;

    for (i = 0; i < 4; i++) {
        if (g_state_03002810->entries[i].active)
            count++;
    }
    return count;
}
