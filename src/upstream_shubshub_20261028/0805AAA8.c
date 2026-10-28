/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0805AAA8.c
 * Original SHA-256: 32e6af9025acefdd1c3322c7f8d1de3237016e5b6c74b2ca47716bb9592976d8
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[0x18];
    u16 count;
    u16 scroll;
    u8 unknown_1C[4];
} MenuPanel;

typedef struct {
    u8 unknown_00[0x11];
    s8 selection;
    u8 unknown_12[0xE];
} MenuControls;

typedef struct {
    u8 unknown_0000[0xD20];
    MenuPanel panel;
    MenuControls controls;
    u8 unknown_0D60[0xE54];
    u8 saved_selection;
    u8 saved_scroll;
    u8 selection;
} MenuState;

typedef struct {
    u8 unknown_00[7];
    u8 identifier;
    u8 unknown_08[8];
} MenuEntry;

typedef struct {
    u8 unknown_0000[0x2E78];
    MenuEntry entries[256];
} EntryState;

extern MenuState *data_0200F428;
extern EntryState g_state_02000000;
extern u16 func_08017B68(MenuPanel *panel, u32 index);
extern void func_080593E0(u8 selection);
extern void func_0805C4BC(u8 identifier, u32 enabled);

/* Complete [0x0805AAA8, 0x0805AB34): 140 bytes, 55 reachable Thumb instructions. */
void func_0805AAA8(void)
{
    MenuControls *controls = &data_0200F428->controls;
    u16 selection = func_08017B68(&data_0200F428->panel, controls->selection);

    func_080593E0(selection);
    data_0200F428->selection = selection;
    {
        u32 state_address = (u32)&g_state_02000000;
        u32 entry_offset = data_0200F428->selection * sizeof(MenuEntry);
        u8 *identifiers = (u8 *)(state_address + 0x2E7F);
        func_0805C4BC(identifiers[entry_offset], 1);
    }
    {
        MenuControls *current_controls = &data_0200F428->controls;
        data_0200F428->saved_selection = current_controls->selection;
    }
    {
        MenuPanel *panel = &data_0200F428->panel;
        data_0200F428->saved_scroll = panel->scroll;
    }
}
