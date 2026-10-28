/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0802E0DC.c
 * Original SHA-256: fb1ce16821510cefdde9abd11b1a7f7f6a54baae951f04fe216ce319a72e8e1e
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct DisplayEntry {
    s16 x;
    s16 y;
    const void *data;
} DisplayEntry;

typedef struct DisplayState {
    u8 unknown_00[0xE];
    u8 active;
    u8 unknown_0F[0x46D];
    DisplayEntry entries[0];
} DisplayState;

typedef struct EventList {
    u8 unknown_0000[0x3C32];
    u8 count;
} EventList;

extern DisplayState *data_0200F444;
extern EventList g_state_02000000;
extern void func_08001CF0(const void *, s32, s32, u8,
                         u8, u8, u8, u8, u32, u8, u32);

/* 0802E0DC..0802E160: 132 bytes, 56 reachable instructions. */
void func_0802E0DC(void)
{
    s32 i;

    if (data_0200F444 && data_0200F444->active) {
        for (i = 0; i < g_state_02000000.count; i++) {
            DisplayEntry *entry = &data_0200F444->entries[i];

            if (entry->data)
                func_08001CF0(entry->data, entry->x, entry->y,
                              0, 0, 0, 0, 0, 0, 0, 0);
        }
    }
}
