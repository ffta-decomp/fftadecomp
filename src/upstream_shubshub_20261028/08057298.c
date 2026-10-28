/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08057298.c
 * Original SHA-256: e4804798507b657f061e6ead8cd81a0361ad1feb1afbdf3c6ab725c6681360ed
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[0x1A];
    u16 position;
    u8 unknown_1C[4];
} MenuList;

typedef struct {
    u8 unknown_00[0x11];
    u8 row;
    u8 unknown_12[2];
} MenuControls;

typedef struct {
    u8 unknown_0000[0x14BC];
    MenuList list;
    MenuControls controls;
    u8 unknown_14F0[0x4D8];
    u8 buffer[0x1372];
    u8 values[256];
} MenuContext;

typedef struct {
    u16 held;
    u16 pressed;
    u16 repeated;
} InputState;

extern MenuContext *data_0200F428;
extern InputState data_03000000;
extern u16 func_0805871C(MenuList *list, u8 row);
extern void func_08057CDC(MenuList *list, u8 *buffer, u8 value, u32 row, u32 mode);
extern void func_08058104(MenuList *list, u8 value, u32 mode, u32 row, u32 direction);

/* Complete target: [0x08057298, 0x08057388), 240 bytes. */
void func_08057298(void)
{
    MenuList *list = &data_0200F428->list;
    MenuControls *controls = &data_0200F428->controls;
    u8 row = controls->row;

    if (data_03000000.held & 0x40) {
        row--;
        row = func_0805871C(list, row);
        list->position--;
        func_08057CDC(list, data_0200F428->buffer,
                      data_0200F428->values[row], 0, 1);
        func_08058104(list, data_0200F428->values[row], 1, 0, 0x40);
    } else if (data_03000000.held & 0x80) {
        row++;
        row = func_0805871C(list, row);
        list->position++;
        func_08057CDC(list, data_0200F428->buffer,
                      data_0200F428->values[row], 2, 1);
        func_08058104(list, data_0200F428->values[row], 1, 2, 0x80);
    }
}
