/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 43f7f78cfe893ab4d99d2004e0740459589bfb5c (PR #20)
 * Original file: src/080415EC.c
 * Original SHA-256: 829f43bbbc2a3fa3679501886ca3733f55c0657cf917e6917118d46064c2d1fe
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Validation: data/upstream-imports-20261030.json.
 */
#include "ffta.h"

typedef struct {
    u16 unknown_00;
    u16 pressed;
    u16 repeat;
} MenuInput;

typedef struct {
    u16 unknown_00;
    u16 flags;
    u16 value;
    u8 unknown_06[6];
    u16 id;
    u8 parameter_0E;
    u8 unknown_0F;
    u16 parameter_10;
    u8 parameter_12;
    u8 unknown_13;
} MenuItem;

typedef struct {
    u8 unknown_00[9];
    u8 flags;
    u8 unknown_0A[14];
    MenuItem *items;
} MenuData;

typedef struct {
    u8 unknown_00[0x20];
} MenuList;

typedef struct {
    u8 unknown_00[0x11];
    u8 row;
    u8 unknown_12[0x1E];
} MenuCursor;

typedef struct {
    u8 unknown_00[0x36];
    u8 canceled;
    u8 unknown_37;
    u16 selected;
    u8 reset;
    u8 unknown_3B[3];
    u16 event;
    u16 value;
    u16 parameter_42;
    u16 parameter_44;
    u16 parameter_46;
    MenuData *data;
    u8 unknown_4C[0x2C];
    MenuList list;
    MenuCursor cursor;
    MenuData *choices;
} MenuSlot;

typedef struct {
    u8 unknown_00[0x4B4];
    u8 result;
    u8 unknown_4B5[0x49F];
    MenuSlot slots[1];
} MenuState;

extern MenuInput data_03000000;
extern MenuState *g_state_03002810;
extern u16 func_08017B68(MenuList *list, u32 row);
extern u16 func_08017B50(MenuList *list);
extern void func_08017AF4(MenuList *list, u32 row, u32 value);
extern u8 func_08017A90(MenuList *list, u16 direction);
extern void func_08037FB0(u32 index);
extern void func_08085374(void);
extern void func_08141540(u32 sound);
extern void func_080412D0(u32 index, u16 direction, s32 row, u32 scroll);

/* Complete target: [0x080415EC, 0x08041848), 604 bytes, 243 instructions. */
u32 func_080415EC(u32 index)
{
    u32 oldRow;

    if (data_03000000.pressed & 1)
    {
        MenuData *choices = g_state_03002810->slots[index].choices;
        MenuCursor *cursor = (MenuCursor *)(index * sizeof(MenuSlot) + (u32)g_state_03002810 + 0x9EC);
        u16 row = func_08017B68(&g_state_03002810->slots[index].list, (s8)cursor->row);

        if (choices->items[row].flags)
        {
            MenuState *state = g_state_03002810;
            state->slots[index].value = choices->items[row].value;
            state->slots[index].parameter_42 = choices->items[row].parameter_0E;
            state->slots[index].parameter_44 = choices->items[row].parameter_10;
            state->slots[index].parameter_46 = choices->items[row].parameter_12;
            state->slots[index].event = 1;
        }
        else
        {
            func_08141540(0x6A);
        }
    }

    if (data_03000000.pressed & 2)
    {
        g_state_03002810->slots[index].event = 2;
        g_state_03002810->slots[index].canceled = 0xFF;
        func_08037FB0(index);
        return 7;
    }

    if (data_03000000.repeat & 0x80)
    {
        s8 row;

        g_state_03002810->slots[index].event = 0x80;
        func_08085374();
        oldRow = ((MenuCursor *)(index * sizeof(MenuSlot) +
            (u8 *)g_state_03002810 + 0x9EC))->row;
        row = oldRow + 1;
        if (row < func_08017B50(&g_state_03002810->slots[index].list))
        {
            func_08141540(0x6D);
            func_08017AF4(&g_state_03002810->slots[index].list, (s8)oldRow, 12);
            func_080412D0(index, 0x80, row, 0);
        }
        else if (func_08017A90(&g_state_03002810->slots[index].list, 0x80))
        {
            func_08141540(0x6D);
            func_08017AF4(&g_state_03002810->slots[index].list, (s8)oldRow, 12);
            func_080412D0(index, 0x80, row, 1);
            return 4;
        }
    }
    else if (data_03000000.repeat & 0x40)
    {
        s8 row;

        g_state_03002810->slots[index].event = 0x40;
        func_08085374();
        row = ((MenuCursor *)(index * sizeof(MenuSlot) +
            (u8 *)g_state_03002810 + 0x9EC))->row - 1;
        oldRow = ((MenuCursor *)(index * sizeof(MenuSlot) +
            (u8 *)g_state_03002810 + 0x9EC))->row;
        if (row < 0)
        {
            if (func_08017A90(&g_state_03002810->slots[index].list, 0x40))
            {
                func_08141540(0x6D);
                func_08017AF4(&g_state_03002810->slots[index].list, (s8)oldRow, 12);
                func_080412D0(index, 0x40, row, 1);
                return 4;
            }
        }
        else
        {
            func_08141540(0x6D);
            func_08017AF4(&g_state_03002810->slots[index].list, (s8)oldRow, 12);
            func_080412D0(index, 0x40, row, 0);
        }
    }
    return 3;
}
