/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 11946243ba373da48154ed04cb3bb31e52dad97b
 * Original file: src/08027750.c
 * Original SHA-256: f82e3c69c4baad16cbd9cd3edc27eca49df1c7f19b792dc746cbeb5ee7b44969
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred.
 */
#include "ffta.h"

typedef struct {
    u16 identifier;
    u8 quantity;
    u8 previous_quantity;
} InventoryRecord08027750;

typedef struct {
    u8 unknown_00;
    u8 rows;
    u8 unknown_02;
    u8 visible_count;
    u16 count;
} Menu08027750;

typedef struct {
    u8 unknown_00[0x80];
    Menu08027750 menu;
    u8 unknown_88[0x0c];
    u32 *entries;
    u8 *flags;
    u8 unknown_9c[4];
    u8 *allocation;
} State08027750;

extern const u8 data_083A9CA4[];
extern const u8 data_0839144E[];
extern void *func_08005B28(u32 byte_count);
extern void func_08005318(const void *source, void *destination, u32 size, u32 mode);
extern InventoryRecord08027750 *func_080CB210(u32 identifier, s32 *count);
extern u8 func_080CB1F4(u16 identifier);

/* Complete [0x08027750, 0x08027800): 176 bytes. */
void func_08027750(State08027750 *state)
{
    Menu08027750 *menu = &state->menu;
    InventoryRecord08027750 *record;
    u8 *tiles;
    s32 count;
    s32 written;
    s32 i;

    tiles = func_08005B28(0xc0);
    state->allocation = tiles;
    tiles += 0x80;
    func_08005318(data_083A9CA4, tiles, 0x20, 1);
    record = func_080CB210(0, &count);
    for (written = 0, i = 0; i < count; i++, record++) {
        if (func_080CB1F4(record->identifier) && record->quantity != 0) {
            state->entries[written] = record->identifier;
            if (record->quantity == record->previous_quantity)
                state->flags[written] = 0;
            written++;
        }
    }
    menu->count = written;
    if (menu->count <= 5) {
        menu->visible_count = menu->count;
        menu->rows = data_0839144E[menu->count - 1];
    }
}
