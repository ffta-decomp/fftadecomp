/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0806B4C4.c
 * Original SHA-256: def7005c9a513be64464fea605420ecaf03fadb90244157f292e01fdefe72566
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[0x1a];
    u16 item;
    u8 unknown_1c[0x15];
    s8 selection;
} Panel0806B4C4;

typedef struct {
    u8 count;
    u8 unknown_01[0x7b];
} Menu0806B4C4;

typedef struct {
    u16 item;
    u8 quantity;
    u8 unknown_03;
} Item0806B4C4;

typedef struct {
    u8 unknown_0000[0x14c0];
    Panel0806B4C4 panel;
    u8 unknown_14f4[0x594];
    u8 context[0x29e4];
    u8 next;
    u8 unknown_446d[3];
    Menu0806B4C4 menu;
    u16 item;
    u8 selection;
    u8 unknown_44ef;
    u8 menu_index;
    u8 values[6];
    u8 choices[6];
    u8 unknown_44fd[7];
    Item0806B4C4 items[0x178];
    u16 error;
    u8 unknown_4ae6[0x115];
    u8 type;
    u8 unknown_4bfc[3];
    u8 saved_count;
} State0806B4C4;

typedef struct {
    u8 unknown_0000[0x1f64];
    u32 funds;
} Global0806B4C4;

typedef struct {
    u8 unknown_00[0x11];
    s8 selection;
} Selection0806B4C4;

typedef struct {
    u8 current;
} Command0806B4C4;

#define selection_panel(state) \
    ((Selection0806B4C4 *)((u8 *)(state) + 0x14e0))

extern State0806B4C4 *data_0200F428;
extern Global0806B4C4 g_state_02000000;
extern u16 func_08017B68(Panel0806B4C4 *, s8);
extern u8 func_0806EFE4(Menu0806B4C4 *);
extern Item0806B4C4 *func_080CB210(u16, u32);
extern u16 func_080CC86C(u16);
extern u32 func_080CBC14(u8, u16);
extern void func_08141540(u16);
extern u8 func_0806FE14(void *);

/* Complete [0x0806B4C4, 0x0806B6CE): 522 bytes, 189 instructions. */
void func_0806B4C4(Command0806B4C4 *command)
{
    Item0806B4C4 *items;
    u16 selection;
    u32 quantity;
    u32 next;
    u8 *state;
    s8 panel_selection = selection_panel(data_0200F428)->selection;

    data_0200F428->selection = func_08017B68((Panel0806B4C4 *)((u8 *)data_0200F428 + 0x14c0),
                                          panel_selection);
    data_0200F428->item = data_0200F428->items[data_0200F428->selection].item;
    data_0200F428->values[func_0806EFE4(&data_0200F428->menu)] =
        data_0200F428->panel.item;
    data_0200F428->choices[func_0806EFE4(&data_0200F428->menu)] =
        selection_panel(data_0200F428)->selection;
    data_0200F428->saved_count = data_0200F428->menu.count;

    state = &command->current;
    items = func_080CB210(data_0200F428->item, 0);
    selection = func_080CC86C(data_0200F428->item);
    if (selection != 0xffff)
        quantity = items[selection].quantity;
    else
        quantity = 0;

    if (func_080CBC14(data_0200F428->type, data_0200F428->item) <=
        g_state_02000000.funds && quantity < 99) {
        data_0200F428->menu_index = func_0806EFE4(&data_0200F428->menu);
        data_0200F428->choices[func_0806EFE4(&data_0200F428->menu)] =
            data_0200F428->panel.item;
        data_0200F428->choices[func_0806EFE4(&data_0200F428->menu)] =
            selection_panel(data_0200F428)->selection;
        next = 40;
    } else {
        func_08141540(100);
        if (func_080CBC14(data_0200F428->type, data_0200F428->item) <=
            g_state_02000000.funds)
            data_0200F428->error = 2;
        else
            data_0200F428->error = 1;
        next = 120;
    }

    if (func_0806FE14(data_0200F428->context) == 1) {
        *state = 62;
        data_0200F428->next = next;
    } else {
        *state = next;
    }
}
