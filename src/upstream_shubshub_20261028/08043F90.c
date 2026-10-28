/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08043F90.c
 * Original SHA-256: 3023f5352627e1f5bb4c662ebaf5ef128cad30f8bee14a27364e8471450f1060
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

struct MenuEntry {
    u16 active : 1;
    u16 pending : 1;
    u16 changed : 1;
    u16 mode : 3;
    u16 type : 4;
    u16 flag10 : 1;
    u16 unknown_0b : 2;
    u16 option : 1;
    u16 unknown_0e : 2;
    u8 unknown_02;
    u8 slot;
    u8 unknown_04[0x30];
};

struct MenuContext {
    u8 unknown_000[0x7B8];
    struct MenuEntry entries[6];
};

struct SelectionState {
    u8 unknown_0000[0x2E54];
    u8 selection : 5;
    u8 unknown_05 : 3;
};

extern struct MenuContext *g_state_03002810;
extern struct SelectionState g_state_02000000;
extern void func_08045390(u8 index);

/* Complete target: [0x08043F90, 0x08044038), 168 bytes. */
void func_08043F90(void)
{
    u8 index;

    g_state_03002810->entries[0].active = 1;
    g_state_03002810->entries[0].slot = g_state_02000000.selection - 1;
    g_state_03002810->entries[0].changed = 0;
    g_state_03002810->entries[0].mode = 0;
    g_state_03002810->entries[0].type = 0;
    g_state_03002810->entries[0].flag10 = 0;
    for (index = 0; index < 6; index++) {
        if (g_state_03002810->entries[index].active)
            func_08045390(index);
    }
}
