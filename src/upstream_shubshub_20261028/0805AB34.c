/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0805AB34.c
 * Original SHA-256: 1b60c7dcc4d2acd7f981789e30f47436b7ff397d24211a93fc91797731dfd2bf
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[0x20];
} MenuList;

typedef struct {
    u8 unknown_00[0x11];
    s8 row;
    u8 unknown_12[2];
} MenuControls;

typedef struct {
    u8 unknown_0000[0xD20];
    MenuList list;
    MenuControls controls;
    u8 unknown_0D54[0x1BB6 - 0xD54];
    u8 selected;
    u8 unknown_1BB7[0x2CA0 - 0x1BB7];
    u8 timer;
} MenuContext;

typedef struct {
    u32 value;
    u8 unknown_04[0xC];
} SelectionEntry;

typedef struct {
    u8 unknown_0000[0x2E78];
    SelectionEntry entries[256];
} SelectionState;

extern MenuContext *data_0200F428;
extern SelectionState g_state_02000000;
extern void func_08141540(u32 sound);
extern s16 func_08017B68(MenuList *list, s8 row);
extern void func_08017D18(MenuControls *controls, u8 flags);

/* Complete target: [0x0805AB34, 0x0805ABB0), 124 bytes, 48 instructions. */
void func_0805AB34(u8 *state)
{
    u8 selected;

    func_08141540(100);
    {
        MenuControls *controls = &data_0200F428->controls;

        selected = func_08017B68(&data_0200F428->list, controls->row);
    }
    {
        u32 state_address = (u32)&g_state_02000000;
        SelectionEntry *entry = (SelectionEntry *)(state_address +
                               selected * sizeof(SelectionEntry) + 0x2E78);

        if (entry->value == 0) {
            *state = 0x2C;
        } else {
            func_08017D18(&data_0200F428->controls, 1);
            data_0200F428->selected = selected;
            *state = 0x28;
            data_0200F428->timer = 0x3C;
        }
    }
}
