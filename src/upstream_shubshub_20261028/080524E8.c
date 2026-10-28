/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080524E8.c
 * Original SHA-256: e725d11f4fdb09f319ef9a88a4db4c79b1543ef061871cdc7b25d0eda3a025c3
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u16 held;
    u16 pressed;
    u16 repeated;
} InputState;

typedef struct {
    u8 unknown_00[0x20];
} MenuList;

typedef struct {
    u8 unknown_00[0x11];
    u8 row;
    u8 unknown_12[2];
} MenuControls;

typedef struct {
    u8 unknown_000[0xD1C];
    MenuList list;
    MenuControls controls;
    u8 cursor[0x10];
    u8 unknown_d60[0xD00];
    u8 buffer[1];
} MenuContext;

extern MenuContext *data_0200F428;
extern InputState data_03000000;
typedef struct {
    u8 unknown_0000[0x2E64];
    u8 values[256];
} ValueState;

extern ValueState g_state_02000000;
extern void func_08017FBC(void *cursor, u32 direction);
extern u16 func_08017B68(MenuList *list, s8 row);
extern void func_0802B07C(MenuList *list, u16 direction);
extern void func_08054314(MenuList *list, u8 *buffer, u8 row, u8 value, u32 mode);
extern void func_08053674(MenuList *list, u8 row, u8 selected, u8 value);
extern void func_08052790(void);
extern void func_0802B108(MenuList *list);
extern void func_08017E28(void *cursor);

/* Complete target: [0x080524E8, 0x0805262C), 324 bytes. */
void func_080524E8(void)
{
    MenuControls *controls = &data_0200F428->controls;
    u8 row = controls->row;
    u16 up = data_03000000.held & 0x40;
    u8 selected;

    if (up) {
        row--;
        func_08017FBC(data_0200F428->cursor, 0x40);
        selected = func_08017B68(&data_0200F428->list, (s8)row);
        func_0802B07C(&data_0200F428->list, 0x40);
        func_08054314(&data_0200F428->list, data_0200F428->buffer,
                      0, g_state_02000000.values[selected], 0);
        func_08053674(&data_0200F428->list, 0, selected, g_state_02000000.values[selected]);
        func_08052790();
        func_0802B108(&data_0200F428->list);
        func_08017E28(data_0200F428->cursor);
    } else if (data_03000000.held & 0x80) {
        row++;
        func_08017FBC(data_0200F428->cursor, 0x80);
        selected = func_08017B68(&data_0200F428->list, (s8)row);
        func_0802B07C(&data_0200F428->list, 0x80);
        func_08054314(&data_0200F428->list, data_0200F428->buffer,
                      6, g_state_02000000.values[selected], 0);
        func_08053674(&data_0200F428->list, 6, selected, g_state_02000000.values[selected]);
        func_08052790();
        func_0802B108(&data_0200F428->list);
        func_08017E28(data_0200F428->cursor);
    }
}
