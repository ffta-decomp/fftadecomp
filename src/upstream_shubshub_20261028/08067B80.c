/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08067B80.c
 * Original SHA-256: 2aa5f523f94d309ebbaf530e36e97a7af48ce404f8b5bf2363a124cdd9ec9e4a
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[0x20];
} MenuList;

typedef struct {
    u8 unknown_00[0x11];
    u8 index;
} Cursor;

typedef struct {
    u8 unknown_00[4];
    u16 flags;
    u16 status;
    u8 unknown_08[2];
    u8 count;
    u8 unknown_0B[0x45];
    MenuList list;
    Cursor cursor;
} Menu;

extern u8 data_03000000[];
extern u8 func_08067994(Menu *menu, u16 buttons);
extern void func_080023D0(void *input);
extern s8 func_08067D6C(Menu *menu, u16 direction);
extern u16 func_08017B68(MenuList *list, u32 index);
extern s16 func_08017BE8(MenuList *list);
extern u16 func_08017B50(MenuList *list);
extern u8 func_08017A90(MenuList *list, u16 direction);
extern void func_08067E9C(Menu *menu, u8 index);
extern void func_08067CF8(Menu *menu, u16 direction, s8 index, s32 wrap);
extern void func_08141540(s32 sound);

/* Complete target: [0x08067B80, 0x08067CF6), 374 bytes, 161 instructions. */
s32 func_08067B80(Menu *menu, u16 buttons, u16 pressed, u16 held)
{
    MenuList *list = &menu->list;
    Cursor *cursor = &menu->cursor;
    s8 current;
    s8 next;

    if ((menu->flags & 4) && func_08067994(menu, buttons))
        return 1;
    if (pressed & 0x80) {
        func_080023D0(data_03000000);
        if (held & 0x200) {
            return func_08067D6C(menu, 0x80);
        } else {
            current = cursor->index;

            if (func_08017B68(list, current) < func_08017BE8(list))
                func_08067E9C(menu, current);
            next = current + 1;
            if (next < func_08017B50(list)) {
                if (menu->count > 1)
                    func_08141540(0x6D);
                func_08067CF8(menu, 0x80, next, 0);
                return 0;
            } else if (func_08017A90(list, 0x80)) {
                func_08141540(0x6D);
                func_08067CF8(menu, 0x80, next, 1);
                menu->status = 0xFFFD;
                return 1;
            }
        }
    } else if (pressed & 0x40) {
        func_080023D0(data_03000000);
        if (held & 0x200) {
            return func_08067D6C(menu, 0x40);
        } else {
            current = cursor->index;

            if (func_08017B68(list, current) != 0)
                func_08067E9C(menu, current);
            next = current - 1;
            if (next >= 0) {
                if (menu->count > 1)
                    func_08141540(0x6D);
                func_08067CF8(menu, 0x40, next, 0);
                return 0;
            } else if (func_08017A90(list, 0x40)) {
                func_08141540(0x6D);
                func_08067CF8(menu, 0x40, next, 1);
                menu->status = 0xFFFD;
                return 1;
            }
        }
    }
    return 0;
}
