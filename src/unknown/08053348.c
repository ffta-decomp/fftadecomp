/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 11946243ba373da48154ed04cb3bb31e52dad97b
 * Original file: src/08053348.c
 * Original SHA-256: daf1c7d37ef4b1aac1ffe1b2959e2ac4f46c9119d3426548f272919d1d3e087d
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred.
 */
#include "abi/interfaces/080008e0_bindings.h"

typedef struct {
    u8 unknown_00[8];
    u16 *destination;
    u16 *source;
    u8 unknown_10[5];
    u8 rows;
    u8 columns;
    u8 unknown_17;
    s16 count;
    u16 position;
    u16 base;
    u8 stride;
    u8 unknown_1F;
} MenuList;

typedef struct {
    u8 unknown_00[0x11];
    u8 row;
    u8 unknown_12[0x16];
} MenuCursor;

typedef struct {
    u8 unknown_0000[0xCF0];
    u8 window[0x2C];
    MenuList list;
    MenuCursor cursor;
    u8 unknown_D64[0x1A60 - 0xD64];
    u8 content[0x1D47 - 0x1A60];
    u8 count;
    u8 active[20];
    u8 selected;
} MenuState;

typedef struct {
    u8 unknown_00[0x10];
    const u8 *tiles;
} GraphicsState;

typedef void (*MenuCallback)(void *);
extern MenuState *data_0200F428;
extern GraphicsState data_030008B0;
extern u8 data_0600B400[];
extern u16 data_02001F3C[];
extern u32 func_080CCA80(void);
extern void func_0814186C(const void *, void *, u32);
extern void func_08016210(void *, const void *, u16, u16);
extern void func_08053E4C(MenuList *, void *, u16, u8, u8);
extern void func_08053DE8(MenuList *, const u16 *);
extern u8 func_080543CC(MenuList *, u8);
extern void func_080543DC(MenuCursor *, u8);
extern void func_08015D58(void *, MenuCallback, MenuCallback);
extern void func_08017E80(void *);
extern void func_08017F04(void *);
extern void func_080534F4(void);

/* Complete owner: 0x08053348..0x080534F4, 428 bytes. */
void func_08053348(u16 position, u16 row)
{
    MenuList *list = &data_0200F428->list;
    MenuState *state;
    u8 *window;
    u8 *resource;
    u16 fill;
    u16 *source;
    u8 count;
    u8 i;
    u8 item;

    source = &fill;
    *source = 0;
    func_0814186C(source, list->source,
                  0x01000000 | (list->rows * list->columns * 2));
    data_0200F428->count = func_080CCA80();
    state = data_0200F428;
    window = state->window;
    resource = (u8 *)state + 0xD64;
    func_08016210(window, resource,
                  (s32)((u32)data_0600B400 - (u32)data_030008B0.tiles) / 32,
                  state->count);
    list->position = position;
    count = (u8)func_080CCA80() <= 4 ? (u8)func_080CCA80() : 4;
    for (i = 0, item = (u8)list->position; i < count; i++, item++) {
        if (data_0200F428->active[item] == 0)
            func_08053E4C(list, data_0200F428->content,
                          data_02001F3C[item], i, 0);
        else
            func_08053E4C(list, data_0200F428->content,
                          data_02001F3C[item], i, 1);
    }
    func_08053DE8(list, data_02001F3C);
    data_0200F428->selected = func_080543CC(&data_0200F428->list, row);
    if (data_0200F428->count <= 4)
        func_08015D58(data_0200F428->window, func_08017E80, 0);
    else
        func_08015D58(data_0200F428->window, func_08017E80, func_08017F04);
    func_080543DC(&data_0200F428->cursor, row);
    func_080534F4();
}
