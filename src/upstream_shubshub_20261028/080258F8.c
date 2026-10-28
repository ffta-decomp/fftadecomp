/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080258F8.c
 * Original SHA-256: a5b9992338b381fbe3e2c3480e381b62f56ce1238b6dbd55663f01e95ba66efe
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 item;
    u8 unknown_01[3];
} ItemCell;

typedef struct {
    u8 unknown_00[2];
    u8 width;
    u8 unknown_03[0x11];
} PanelLayout;

typedef struct {
    u8 unknown_00[0xA];
    u8 kind;
    u8 unknown_0B[0x75];
    PanelLayout layout;
    const ItemCell *items;
    const u8 *enabled;
} ItemPanel;

typedef struct {
    u8 unknown_00[4];
    u16 table_index;
} ItemInfo;

typedef struct {
    u8 unknown_00[4];
    u8 value_kind;
    u8 unknown_05[0x17];
} ItemRecord;

typedef struct {
    u8 unknown_00[0x18];
    void *inventory;
    u8 unknown_1C[0x10];
    u8 text[0];
} MenuContext;

extern const ItemRecord data_0855187C[];
extern MenuContext *data_0200F438;

const ItemInfo *func_080CD480(u8 kind, u8 item);
u32 func_080258C4(void *inventory, u8 kind);
void func_080142DC(u8 *text, u32 value, u32 digits);
void func_08015110(void *context, s32 position, const u8 *text, u32 mode, u32 style);
u32 func_080CB388(u8 item);
u32 func_080CB2B4(u16 item);

/* Complete target: [0x080258F8, 0x08025A26), 302 bytes. */
void func_080258F8(ItemPanel *panel, void *context, s32 position, u16 index)
{
    PanelLayout *layout = &panel->layout;
    u8 item = panel->items[index].item;
    const ItemInfo *info = func_080CD480(panel->kind, item);
    const ItemRecord *record = &data_0855187C[info->table_index];
    u8 value;
    s32 digits;
    s32 available_columns;

    if (record->value_kind != 0) {
        value = func_080258C4(data_0200F438->inventory, record->value_kind);
        digits = 3;
        if (value <= 99) {
            digits = 1;
            if (value > 9) {
                digits = 2;
            }
        }
        func_080142DC(data_0200F438->text, value, digits);
        available_columns = layout->width - 2;
        position += (available_columns - digits) * 64;
        if (panel->enabled[index] != 0) {
            func_08015110(context, position, data_0200F438->text, 0, 1);
        } else {
            func_08015110(context, position, data_0200F438->text, 1, 1);
        }
    } else if (panel->kind == 0 && item != 15) {
        value = func_080CB2B4((u16)func_080CB388(item));
        digits = 1;
        if (value > 9) {
            digits = 2;
        }
        func_080142DC(data_0200F438->text, value, digits);
        available_columns = layout->width - 2;
        position += (available_columns - digits) * 64;
        if (panel->enabled[index] == 0) {
            func_08015110(context, position, data_0200F438->text, 1, 1);
        } else {
            func_08015110(context, position, data_0200F438->text, 0, 1);
        }
    }
}
