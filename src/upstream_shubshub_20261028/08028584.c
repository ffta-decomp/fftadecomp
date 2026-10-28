/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08028584.c
 * Original SHA-256: 99c1ee2f678252cdd55eab51f55e409e7e3d2bf77059fa76c8b903dd0ff901fa
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[0x20];
} NavigationUnit;

typedef struct {
    u8 unknown_00[0x11];
    s8 row;
    u8 unknown_12[0x2A];
} NavigationCursor;

typedef struct {
    u8 unknown_00[9];
    s8 kind;
    u8 unknown_0A[0x2E];
    NavigationUnit unit;
    NavigationCursor cursor;
    u32 *entries;
} NavigationState;

typedef struct {
    u16 status;
    u8 unknown_02[2];
    u8 mode;
    u8 unknown_05[0x13];
    u32 selected;
} NavigationControl;

extern u8 data_03000000;
extern NavigationControl *data_0200F438;
extern void func_080023D0(void *state);
extern void func_080284A0(NavigationState *state, u16 direction);
extern u16 func_08017B68(NavigationUnit *unit, u32 row);
extern s16 func_08017BE8(NavigationUnit *unit);
extern void func_08017AF4(NavigationUnit *unit, u32 row, u32 value);
extern u16 func_08017B50(NavigationUnit *unit);
extern u8 func_08017A90(NavigationUnit *unit, u16 direction);
extern void func_08141540(u32 sound);
extern void func_08028434(NavigationState *state, u16 direction, s32 row, u32 wrap);

/* Complete target: [0x08028584, 0x08028708), 388 bytes. */
u32 func_08028584(NavigationState *state, u16 pressed, u16 held)
{
    NavigationUnit *unit = &state->unit;
    NavigationCursor *cursor = &state->cursor;

    if (pressed & 0x80)
    {
        func_080023D0(&data_03000000);
        if (held & 0x200)
            func_080284A0(state, 0x80);
        else
        {
            s8 row = cursor->row;
            u16 value = func_08017B68(unit, row);

            if (value < func_08017BE8(unit))
                func_08017AF4(unit, row, 0xFF);
            row++;
            if (row < func_08017B50(unit))
            {
                if (state->kind > 1)
                    func_08141540(0x6D);
                func_08028434(state, 0x80, row, 0);
                if (data_0200F438->mode == 2)
                    data_0200F438->selected = state->entries[func_08017B68(unit, row)];
            }
            else if (func_08017A90(unit, 0x80))
            {
                func_08141540(0x6D);
                func_08028434(state, 0x80, row, 1);
                data_0200F438->status = 0xFFFD;
                return 1;
            }
        }
    }
    else if (pressed & 0x40)
    {
        func_080023D0(&data_03000000);
        if (held & 0x200)
            func_080284A0(state, 0x40);
        else
        {
            s8 row = cursor->row;

            if (func_08017B68(unit, row))
                func_08017AF4(unit, row, 0xFF);
            row--;
            if (row >= 0)
            {
                if (state->kind > 1)
                    func_08141540(0x6D);
                func_08028434(state, 0x40, row, 0);
                if (data_0200F438->mode == 2)
                    data_0200F438->selected = state->entries[func_08017B68(unit, row)];
            }
            else if (func_08017A90(unit, 0x40))
            {
                func_08141540(0x6D);
                func_08028434(state, 0x40, row, 1);
                data_0200F438->status = 0xFFFD;
                return 1;
            }
        }
    }
    return 0;
}
