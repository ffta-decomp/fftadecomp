/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080BD06C.c
 * Original SHA-256: a98807dfb2ac0b4f62b180a1d8ea84041ef1fef7f5b77a1f23614b199b84fc87
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct DrawEntry {
    s32 x;
    s32 y;
    u8 unknown_08[9];
    u8 active;
    u8 unknown_12[6];
    struct DrawEntry *next;
} DrawEntry;

typedef struct {
    u8 unknown_00[0x1C0];
    DrawEntry *head;
    u8 unknown_1C4[4];
    u8 mode;
    u8 priority;
    u8 unknown_1CA;
    u8 flags;
} DrawState;

extern DrawState *data_020101F0;
extern const u8 data_08394650[];
extern void func_080BCDF8(DrawState *state);
extern void func_08001F34(const void *image, s32 x, s32 y, u32 priority,
                          u32 a4, u32 a5, u32 a6, u32 a7, u32 option,
                          u32 a9, u32 a10);

static inline void draw_entries(DrawEntry *entry, const void *image,
                                u32 priority, u32 option, u32 layer, u32 flags)
{
    while (entry != 0) {
        if (entry->active != 0)
            func_08001F34(image, entry->x >> 8, entry->y >> 8,
                           priority, 0, 0, 0, 0, option, layer, flags);
        entry = entry->next;
    }
}

/* 0x080BD06C..0x080BD11C: 176 bytes. */
void func_080BD06C(void)
{
    if (data_020101F0 != 0 && !(data_020101F0->flags & 4)) {
        func_080BCDF8(data_020101F0);
        if (data_020101F0->mode != 0)
            draw_entries(data_020101F0->head, data_08394650,
                           data_020101F0->priority, data_020101F0->mode != 1,
                           2, 0);
    }
}
