/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08049ED0.c
 * Original SHA-256: 69f9fa19a41b09eeb258d48ff9d2895cac336f95f8d84ee78e5e259368f55523
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u16 id : 10;
    u16 unknown_0A : 6;
    u8 unknown_02[2];
} __attribute__((packed)) SlotItem;

typedef struct {
    u8 unknown_00[0x24];
    SlotItem *items[16];
    u8 unknown_64[0x48];
    u8 count;
} ItemPanel;

typedef struct {
    void *unknown_00;
    ItemPanel *panel;
} MenuState;

typedef struct {
    u8 unknown_00[2];
    u8 unknown_10 : 3;
    u8 width : 3;
    u8 unknown_16 : 2;
    u8 unknown_03[0x43];
} __attribute__((packed)) ItemDefinition;

extern MenuState *g_state_03002810;
extern const ItemDefinition g_table_0855AE4C[];
extern s32 func_08035FC4(void);
extern void func_08035F8C(void);
extern u32 func_080D1C94(SlotItem **items, u32 limit, u8 advance);

/* Complete target: [0x08049ED0, 0x08049FB2), 226 bytes. */
s32 func_08049ED0(u16 identifier)
{
    s32 slot;
    SlotItem *item;
    u16 item_id;

    for (slot = 0; slot <= 15; slot++) {
        item = g_state_03002810->panel->items[slot];
        if (item != 0 && item->id == identifier)
            g_state_03002810->panel->items[slot] = 0;
    }

    for (slot = 0; slot <= 15; slot++) {
        item = g_state_03002810->panel->items[slot];
        if (item != 0) {
            item_id = item->id;
            if (item_id != identifier && item_id != 0)
                return g_table_0855AE4C[item_id].width;
        }
    }

    if (func_08035FC4() != 0) {
        func_08035F8C();
        if ((g_state_03002810->panel->count =
             func_080D1C94(g_state_03002810->panel->items, 16, 1)) != 0) {
            for (slot = 0; slot <= 15; slot++) {
                item = g_state_03002810->panel->items[slot];
                if (item != 0) {
                    item_id = item->id;
                    if (item_id != identifier && item_id != 0)
                        return g_table_0855AE4C[item_id].width;
                }
            }
        }
    }
    return -1;
}
