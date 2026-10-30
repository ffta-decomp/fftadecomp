/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 43f7f78cfe893ab4d99d2004e0740459589bfb5c (PR #20)
 * Original file: src/08037A30.c
 * Original SHA-256: c58d6f4734d66b8210d8198bbf15501e245c4455bc524fadf7c1c4b048bb9339
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Validation: data/upstream-imports-20261030.json.
 */
#include "ffta.h"

struct Window08037A30 {
    u8 unknown_00[0x0e];
    u16 first_tile;
    u8 unknown_10[0x18];
    u8 map_stride;
    u8 unknown_29[3];
    u8 graphics_stride;
    u8 unknown_2d[0x1f];
};

struct Entry08037A30 {
    u16 text_index;
    u8 unknown_02[0x1e];
};

struct Item08037A30 {
    u16 index;
    u8 graphic;
    u8 unknown_03[0x0d];
};

struct Menu08037A30 {
    u8 unknown_000[0xc4c];
    u8 text_state[1];
};

extern u8 data_02003CB0[];
extern struct Window08037A30 data_030009E0[];
extern struct Menu08037A30 *g_state_03002810;
extern const struct Entry08037A30 g_table_0851D180[];
extern const struct Item08037A30 g_table_08521214[];
extern const u8 *g_table_08526680[];

extern u16 *func_0808B8E4(u32 index, u32 plane, s32 x, s32 y);
extern u8 *func_0808B92C(u32 index, u8 *tiles, u32 column, u32 row);
extern u8 func_080CB99C(u16 index);
extern void func_080CB980(void *buffer, u32 index);
extern void func_0814186C(const void *source, void *destination, u32 control);
extern void func_08015110(void *context, void *tiles, const void *text,
                         u32 mode, u32 spacing);

/* Complete [0x08037A30, 0x08037C84): 596 bytes, 248 instructions. */
const u8 *func_08037A30(u32 window, u8 *tiles, s32 x, s32 y, u16 index,
                        const u8 *initial_text, s32 kind, s32 orientation, u8 mode)
{
    u16 attributes = 0;
    u8 *buffer = data_02003CB0;
    const u8 *text = initial_text;
    u16 *map;
    u16 graphic;
    const struct Item08037A30 *items;
    u16 tile;

    if (orientation == 0)
        map = func_0808B8E4(window, 1, x + 1, y + 2);
    else if (orientation == 1)
        map = func_0808B8E4(window, 1, x, y + 1);
    else
        map = func_0808B8E4(window, 1, x + 1, y + 1);

    tiles = func_0808B92C(window, tiles, x, y);

    switch (kind) {
    case 0:
        attributes = (func_080CB99C(index) + 13) << 12;
        func_080CB980(buffer, index);
        func_0814186C(buffer, tiles, 0x40);
        tiles += 0x80;
        if (text == 0)
            text = g_table_08526680[g_table_0851D180[index].text_index];
        func_08015110(g_state_03002810->text_state, tiles, text, mode, 1);
        break;
    case 1:
        index = g_table_08521214[index].index;
        items = (const struct Item08037A30 *)
            ((const u8 *)g_table_08521214 + index * sizeof(*items) - 0x1770);
        graphic = items->graphic ? items->graphic + 394 : 0;
        func_080CB980(buffer, graphic);
        func_0814186C(buffer, tiles, 0x40);
        attributes = (func_080CB99C(graphic) + 13) << 12;
        tiles += 0x80;
        if (text == 0)
            text = g_table_08526680[index + 123];
        func_08015110(g_state_03002810->text_state, tiles, text, mode, 1);
        break;
    case 2:
        if (index <= 85) {
            graphic = 393;
        } else {
            index += (u16)-85;
            graphic = 394;
        }
        func_080CB980(buffer, graphic);
        func_0814186C(buffer, tiles, 0x40);
        attributes = (func_080CB99C(graphic) + 13) << 12;
        text = g_table_08526680[index + 625];
        tiles += 0x80;
        func_08015110(g_state_03002810->text_state, tiles, text, mode, 1);
        break;
    }

    tile = data_030009E0[window].graphics_stride * y
        + data_030009E0[window].first_tile + x * 2;
    map[0] = tile++ | attributes;
    map[1] = tile++ | attributes;
    map[data_030009E0[window].map_stride] = tile++ | attributes;
    map[data_030009E0[window].map_stride + 1] = tile | attributes;
    return text;
}
