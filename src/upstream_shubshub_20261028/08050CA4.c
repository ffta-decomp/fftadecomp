/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08050CA4.c
 * Original SHA-256: da8fa7d749e34d779646f613bbe4859bbbbe1e4ecd0cbbf82c4cfb6f1cec532b
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

struct State08050CA4 {
    u8 unknown_0000[0x1F3C];
    u16 entries[20];
};

extern struct State08050CA4 g_state_02000000;

/* Complete target: [0x08050CA4, 0x08050CDC), 56 bytes. */
u32 func_08050CA4(u32 *destination)
{
    u32 count = 0;
    u32 state_address = (u32)&g_state_02000000;
    const u16 *entry = (const u16 *)(state_address + 0x1F3C);
    u32 *output = destination;
    s32 remaining;

    for (remaining = 19; remaining >= 0; remaining--) {
        if (*entry != 0) {
            if (destination != 0)
                *output = *entry;
            output++;
            count++;
        }
        entry++;
    }
    return count;
}
