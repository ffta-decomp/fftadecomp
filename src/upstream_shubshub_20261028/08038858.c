/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08038858.c
 * Original SHA-256: c25413731cdf5bbc1090203b0281458cd9061fc04cdb5650d5e4f2eb6889bde4
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
    u8 unknown_000[0x913];
    u8 count;
    MenuEntry entries[16];
} MenuState;

extern MenuState *g_state_03002810;

/* Complete target: 0x08038858..0x080388C8, 112 bytes. */
s32 func_08038858(u16 id, u8 kind, u16 quantity)
{
    s32 i;

    g_state_03002810->count = 0;
    for (i = 0; i < 16; i++)
    {
        if (!g_state_03002810->entries[i].id)
        {
            g_state_03002810->entries[i].id = id;
            g_state_03002810->entries[i].kind = kind;
            g_state_03002810->entries[i].quantity = quantity;
            g_state_03002810->count++;
            return i;
        }
    }
    return -1;
}
