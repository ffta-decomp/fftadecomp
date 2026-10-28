/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08038734.c
 * Original SHA-256: 205ffcfdc900c8a155c550f8c22ced6d61277f3a7738c02b9e7d4859af27e244
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u16 id;
    u16 kind;
    u16 quantity;
    u16 unknown_06;
} MenuEntry;

typedef struct {
    u8 unknown_000[0x914];
    MenuEntry entries[4];
} MenuState;

extern MenuState *g_state_03002810;

/* Complete target: 0x08038734..0x080387F2, 190 bytes. */
s32 func_08038734(void)
{
    s32 count = 0;
    s32 i;
    s32 j;

    for (i = 0; i < 4; i++)
        if (g_state_03002810->entries[i].id)
            count++;

    if (count == 4)
        return 4;

    for (i = 0; i < 3; i++)
    {
        if (!g_state_03002810->entries[i].id)
        {
            for (j = i + 1; j < 4; j++)
            {
                if (g_state_03002810->entries[j].id)
                {
                    g_state_03002810->entries[i] = g_state_03002810->entries[j];
                    g_state_03002810->entries[j].id = 0;
                    g_state_03002810->entries[j].kind = 0;
                    g_state_03002810->entries[j].quantity = 0;
                    break;
                }
            }
        }
    }
    return count;
}
