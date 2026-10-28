/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0806D300.c
 * Original SHA-256: c2c35e1f627c57887de7ca66441fef21184271bdb8f40dad97f947c6cee1e0b9
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u16 held;
    u16 pressed;
    u16 repeated;
} InputState0806D300;

typedef struct {
    u8 unknown_00[0x20];
} MenuList0806D300;

typedef struct {
    u8 unknown_00[0x11];
    u8 row;
    u8 unknown_12[2];
} MenuControls0806D300;

typedef struct {
    u16 item;
    u8 quantity;
    u8 unknown_03;
} Item0806D300;

typedef struct {
    u8 unknown_0000[0x14c0];
    MenuList0806D300 list;
    MenuControls0806D300 controls;
    u8 cursor[0x10];
    u8 unknown_1504[0x3000];
    Item0806D300 items[0x178];
} State0806D300;

extern State0806D300 *data_0200F428;
extern InputState0806D300 data_03000000;
extern void func_08017FBC(void *cursor, u32 direction);
extern u16 func_08017B68(MenuList0806D300 *list, s8 row);
extern void func_0802B07C(MenuList0806D300 *list, u16 direction);
extern void func_0806E66C(MenuList0806D300 *list, u16 item, u8 flags,
                        u8 quantity, u32 mode, u32 row, u32 option);
extern void func_0806E528(void);
extern void func_08017E28(void *cursor);

/* Complete target [0x0806D300, 0x0806D428): 296 bytes, 119 instructions. */
void func_0806D300(void)
{
    MenuControls0806D300 *controls = &data_0200F428->controls;
    u8 row = controls->row;
    u16 up = data_03000000.held & 0x40;
    u8 selected;

    if (up) {
        row--;
        func_08017FBC(data_0200F428->cursor, 0x40);
        selected = func_08017B68(&data_0200F428->list, (s8)row);
        func_0802B07C(&data_0200F428->list, 0x40);
        func_0806E66C(&data_0200F428->list,
                      data_0200F428->items[selected].item,
                      data_0200F428->items[selected].unknown_03,
                      data_0200F428->items[selected].quantity, 2, 0, 0);
        func_0806E528();
        func_08017E28(data_0200F428->cursor);
    } else if (data_03000000.held & 0x80) {
        row++;
        func_08017FBC(data_0200F428->cursor, 0x80);
        selected = func_08017B68(&data_0200F428->list, (s8)row);
        func_0802B07C(&data_0200F428->list, 0x80);
        func_0806E66C(&data_0200F428->list,
                      data_0200F428->items[selected].item,
                      data_0200F428->items[selected].unknown_03,
                      data_0200F428->items[selected].quantity, 2, 3, 0);
        func_0806E528();
        func_08017E28(data_0200F428->cursor);
    }
}
