/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08044770.c
 * Original SHA-256: 3017480563576bd9cdd39a5cf189b11f821ef24c826edbf5681885266b965e72
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

struct MenuEntry08044770 {
    u16 active : 1;
    u16 pending : 1;
    u16 changed : 1;
    u16 mode : 3;
    u16 type : 4;
    u16 unknown_0a : 3;
    u16 option : 1;
    u16 unknown_0e : 2;
    u8 unknown_02[0x32];
};

struct MenuContext08044770 {
    u8 unknown_000[0x7b8];
    struct MenuEntry08044770 entries[8];
};

extern struct MenuContext08044770 *g_state_03002810;

/* Target: [0x08044770, 0x080447B4), 68 bytes, 30 instructions. */
void func_08044770(void)
{
    int i;

    for (i = 0; i <= 4; i++) {
        if (g_state_03002810->entries[i + 1].active)
            g_state_03002810->entries[i + 1].option = 0;
    }
}
