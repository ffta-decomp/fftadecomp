/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08053FE0.c
 * Original SHA-256: 442da4e769e6d6e6a19aecd092ed6bfb937e42bbb4758d9e5772be36fceedc4e
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[0x18];
    s16 count;
    s16 top;
} ScrollList08053FE0;

typedef struct {
    u8 unknown_00[0x0E];
    u16 offset;
    u8 unknown_10;
    u8 row;
} MenuCursor08053FE0;

typedef struct {
    u8 unknown_00[0x2C];
    ScrollList08053FE0 list;
    u8 unknown_48[4];
    MenuCursor08053FE0 cursor;
    u8 unknown_60[1];
} Menu08053FE0;

typedef struct {
    u16 held;
    u16 pressed;
    u16 repeated;
} Input08053FE0;

typedef struct {
    void (*callback)(void *);
    void *context;
    u16 keys;
} KeyBinding08053FE0;

extern Input08053FE0 data_03000000;
extern void func_080023D0(Input08053FE0 *input);
extern void func_08141540(u32 sound);
extern void func_080543DC(MenuCursor08053FE0 *cursor, u8 row);
extern u8 func_0805417C(ScrollList08053FE0 *list, u16 keys);
extern void func_08017FBC(void *context, u16 keys);

/* Complete target: [0x08053FE0, 0x0805417C), 412 bytes. */
void func_08053FE0(Menu08053FE0 *menu, void (*scroll)(void *),
                   void *scroll_context, u8 row_count,
                   KeyBinding08053FE0 *bindings, u8 binding_count)
{
    s8 row;
    s8 index;

    if (row_count > 4) {
        if (data_03000000.repeated & 0x80) {
            func_080023D0(&data_03000000);
            row = menu->cursor.row + 1;
            if (row <= 3) {
                func_08141540(0x6D);
                func_080543DC(&menu->cursor, row);
                func_08017FBC(menu->unknown_60, 0x80);
            } else if (func_0805417C(&menu->list, 0x80)) {
                func_08141540(0x6D);
                scroll(scroll_context);
                func_08017FBC(menu->unknown_60, 0x80);
            }
        }
        if (data_03000000.repeated & 0x40) {
            func_080023D0(&data_03000000);
            row = menu->cursor.row - 1;
            if (row >= 0) {
                func_08141540(0x6D);
                func_080543DC(&menu->cursor, row);
            } else if (func_0805417C(&menu->list, 0x40)) {
                func_08141540(0x6D);
                scroll(scroll_context);
            } else {
                goto dispatch;
            }
            func_08017FBC(menu->unknown_60, 0x40);
        }
    } else {
        if (data_03000000.repeated & 0x80) {
            func_080023D0(&data_03000000);
            row = menu->cursor.row + 1;
            if (row > row_count - 1)
                row = row_count - 1;
            else
                func_08141540(0x6D);
            func_080543DC(&menu->cursor, row);
        } else if (data_03000000.repeated & 0x40) {
            func_080023D0(&data_03000000);
            row = menu->cursor.row - 1;
            if (row < 0)
                row = 0;
            else
                func_08141540(0x6D);
            func_080543DC(&menu->cursor, row);
        }
    }

dispatch:
    for (index = 0; index < binding_count; index++) {
        if (data_03000000.pressed & bindings[index].keys)
            bindings[index].callback(bindings[index].context);
    }
}
