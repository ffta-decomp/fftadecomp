/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08052800.c
 * Original SHA-256: a8ef2e2f8a2fdb5cf4fc97b210b12d98af4b4a798577bdf57d50bc2d120d04ca
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[0x17];
    u8 count;
    s16 limit;
    u8 unknown_1A[0x17];
    s8 row;
    u8 unknown_32[2];
} MenuList;

typedef struct {
    u8 unknown_00;
} MenuCursor;

typedef struct {
    u8 unknown_00[0x2C];
    MenuList list;
    MenuCursor cursor;
} MenuState;

typedef void (*CursorCallback)(MenuCursor *cursor);

extern void func_08017F04(MenuCursor *cursor);
extern void func_08017DB4(MenuCursor *cursor, MenuList *list,
                         CursorCallback callback, u32 mode);
extern s16 func_08017B68(MenuList *list, s8 row);
extern void func_08017FBC(MenuCursor *cursor, u32 amount);
extern void func_08017E28(MenuCursor *cursor);

/* Complete target: [0x08052800, 0x08052870), 112 bytes, 49 instructions. */
void func_08052800(MenuState *menu)
{
    if (menu->list.count - 1 < menu->list.limit)
    {
        s16 count;
        s16 i;

        func_08017DB4(&menu->cursor, &menu->list, func_08017F04, 0);
        count = func_08017B68(&menu->list, menu->list.row);
        for (i = 0; i < count; i++)
        {
            func_08017FBC(&menu->cursor, 0x80);
            func_08017E28(&menu->cursor);
        }
    }
}
