/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08025B54.c
 * Original SHA-256: 003752f579dc9585f89f4d2a2fe353f53b83509ce79f79a4f033fcf8be0d5620
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[0x15];
    u8 height;
    u8 unknown_16[10];
} RowList08025B54;

typedef struct {
    u8 unknown_00[2];
    u8 count;
    u8 unknown_03[6];
    u8 flags;
    u8 unknown_0a[10];
} RowOptions08025B54;

typedef union {
    u32 value;
    u16 id;
    void *object;
} RowEntry08025B54;

typedef struct {
    u8 unknown_00[0x38];
    RowList08025B54 list;
    u8 unknown_58[0x28];
    RowOptions08025B54 options;
    RowEntry08025B54 *entries;
    u8 *available;
    u8 unknown_9c[4];
    void *resource;
} RowState08025B54;

typedef struct {
    u8 unknown_00[4];
    u8 mode;
    u8 unknown_05[0x27];
    u8 number_text[8];
    u8 text_state[1];
} MenuState08025B54;

typedef struct {
    u8 unknown_00[0x10];
    u8 *tiles;
} TileState08025B54;

extern TileState08025B54 data_030008B0;
extern MenuState08025B54 *data_0200F438;

u16 func_08017B9C(RowList08025B54 *list, u32 index);
u16 func_08017B68(RowList08025B54 *list, u32 index);
void func_08013A88(void *destination, u32 rows);
void *func_08025758(RowState08025B54 *state, s16 index);
void func_080142DC(void *destination, u16 value, u32 digits);
void func_08015110(void *state, void *tiles, void *text, u32 style, u32 spacing);
void func_0801539C(void *state, void *tiles, void *text, u32 style, u32 count);
u8 func_080C8240(void *object);
void func_080CB980(void *resource, u32 id);
void func_0814186C(void *source, void *destination, u32 count);
void func_080258F8(RowState08025B54 *state, void *text_state, void *tiles, u16 index);
void func_08025A28(RowState08025B54 *state, void *text_state, void *tiles, u16 index);

void func_08025B54(RowState08025B54 *state, s8 row)
{
    RowList08025B54 *list = &state->list;
    RowOptions08025B54 *options = &state->options;
    u32 style = 0;
    u8 *tiles;
    u16 index;
    void *text;

    tiles = data_030008B0.tiles + func_08017B9C(list, row) * 32;
    func_08013A88(tiles, list->height << 1);
    index = func_08017B68(list, row);
    text = func_08025758(state, (s16)index);

    switch (data_0200F438->mode) {
    case 2:
        func_080142DC(data_0200F438->number_text, (u16)(index + 1), 2);
        func_08015110(data_0200F438->text_state, tiles,
                      data_0200F438->number_text, 0, 1);
        tiles += 0xc0;
        if (func_080C8240(state->entries[index].object))
            style = 4;
        break;
    case 3:
        func_080CB980(state->resource, state->entries[index].value > 0x55 ? 0x18a : 0x189);
        func_0814186C(state->resource, tiles, 0x40);
        tiles += 0x80;
        break;
    case 13:
    case 14:
        func_080CB980(state->resource, state->entries[index].id);
        func_0814186C(state->resource, tiles, 0x40);
        tiles += 0x80;
        break;
    }

    if (state->available != 0) {
        if (state->available[index] == 0)
            style = 1;
        func_08015110(data_0200F438->text_state, tiles, text, style, 1);
    } else if (options->flags & 4) {
        func_0801539C(data_0200F438->text_state, tiles, text, 5,
                     (u8)(options->count - 2));
    } else {
        func_08015110(data_0200F438->text_state, tiles, text, style, 1);
    }

    if ((u8)(data_0200F438->mode - 6) <= 2 || data_0200F438->mode == 15)
        func_080258F8(state, data_0200F438->text_state, tiles, index);
    else if ((u8)(data_0200F438->mode - 13) <= 1)
        func_08025A28(state, data_0200F438->text_state, tiles, index);
}
