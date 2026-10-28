/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08055DC4.c
 * Original SHA-256: fb2fab6bc0161085faf5c686ed406c3c411395764bb680f66b0204cb3d4dcd05
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* Complete [0x08055DC4, 0x08055EC0): 252 bytes, 103 instructions. */
typedef struct {
    u8 unknown_00[0x1A];
    u16 position;
    u8 unknown_1C[4];
} MenuWindow08055DC4;

typedef struct {
    u8 unknown_00[0x11];
    u8 row;
} MenuCursor08055DC4;

typedef struct {
    u8 unknown_00[0x14BC];
    MenuWindow08055DC4 window;
    MenuCursor08055DC4 cursor;
    u8 unknown_14F0[0x4D8];
    u8 content[0x1372];
    u8 unitIds[0x1B];
} MenuState08055DC4;

extern MenuState08055DC4 *data_0200F428;
extern u16 data_03000000;
extern u8 func_0805871C(MenuWindow08055DC4 *, u8);
extern void func_08057CDC(MenuWindow08055DC4 *, void *, u8, u32, u32);
extern void func_08058104(MenuWindow08055DC4 *, u8, u8, u8, u16);

void func_08055DC4(void)
{
    MenuWindow08055DC4 *window = &data_0200F428->window;
    MenuCursor08055DC4 *cursor = &data_0200F428->cursor;
    u8 row = cursor->row;

    if (data_03000000 & 0x40) {
        row--;
        row = func_0805871C(window, row);
        window->position--;
        func_08057CDC(window, data_0200F428->content,
                      data_0200F428->unitIds[row], 0, 0);
        func_08058104(window, data_0200F428->unitIds[row], 0, 0, 0x40);
    } else if (data_03000000 & 0x80) {
        row++;
        row = func_0805871C(window, row);
        window->position++;
        func_08057CDC(window, data_0200F428->content,
                      data_0200F428->unitIds[row], 2, 0);
        func_08058104(window, data_0200F428->unitIds[row], 0, 2, 0x80);
    }
}
