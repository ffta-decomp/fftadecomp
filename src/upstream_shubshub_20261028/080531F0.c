/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080531F0.c
 * Original SHA-256: a27181390dfcaceb2d9a6326c947464c8c2a4e4bcd1f8aaaf8401cc62d3afc25
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[0x1A];
    u16 position;
    u8 unknown_1C[4];
} MenuWindow;

typedef struct {
    u8 unknown_00[0x11];
    u8 row;
} MenuCursor;

typedef struct {
    u8 bytes[0x2E8];
} MenuContent;

typedef struct {
    u8 unknown_00[0xD1C];
    MenuWindow window;
    MenuCursor cursor;
    u8 unknown_D50[0xD10];
    MenuContent content;
    u8 rowFlags[256];
} MenuState;

typedef struct {
    u8 unknown_00[0x1F3C];
    u16 entries[256];
} UnitState;

extern MenuState *data_0200F428;
extern u16 data_03000000;
extern UnitState g_state_02000000;
extern u8 func_080543CC(MenuWindow *window, u8 row);
extern void func_08053E4C(MenuWindow *window, MenuContent *content, u16 entry,
                         u32 row, u32 flagged);
extern void func_08054284(MenuWindow *window, u16 entry, u32 row, u16 direction);

/* Complete target: [0x080531F0, 0x08053348), 344 bytes, 134 instructions. */
void func_080531F0(void)
{
    MenuWindow *window = &data_0200F428->window;
    MenuCursor *cursor = &data_0200F428->cursor;
    u8 row = cursor->row;

    if (data_03000000 & 0x40)
    {
        row--;
        row = func_080543CC(window, row);
        window->position--;
        if (data_0200F428->rowFlags[row] == 0)
            func_08053E4C(window, &data_0200F428->content,
                         g_state_02000000.entries[row], 0, 0);
        else
            func_08053E4C(window, &data_0200F428->content,
                         g_state_02000000.entries[row], 0, 1);
        func_08054284(window, g_state_02000000.entries[row], 0, 0x40);
    }
    else if (data_03000000 & 0x80)
    {
        row++;
        row = func_080543CC(window, row);
        window->position++;
        if (data_0200F428->rowFlags[row] == 0)
            func_08053E4C(window, &data_0200F428->content,
                         g_state_02000000.entries[row], 3, 0);
        else
            func_08053E4C(window, &data_0200F428->content,
                         g_state_02000000.entries[row], 3, 1);
        func_08054284(window, g_state_02000000.entries[row], 3, 0x80);
    }
}
