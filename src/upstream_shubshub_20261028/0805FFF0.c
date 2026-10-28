/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0805FFF0.c
 * Original SHA-256: 69709a3c605f4f60f2d966fdb56235277f7b3be101d546c81b5d1ca9f6c23d9c
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x0805FFF0..0x08060100: 272 bytes. */
typedef struct {
    u8 mode;
    u8 unknown_01[4];
    u8 parameter;
} PanelControl;

typedef struct __attribute__((packed)) {
    u16 id : 10;
    u16 unknown_0A : 6;
} PanelRecord;

typedef struct {
    u8 unknown_00[0x20];
    PanelRecord *records[1];
} PanelState;

typedef struct {
    u8 unknown_00[0x1F69];
    u8 value;
} GameState;

typedef struct DrawContext DrawContext;

extern PanelState *data_0200F44C;
extern GameState g_state_02000000;
extern u8 func_080C9540(u16);
extern u8 *func_08005B28(u32);
extern void func_080CB9B0(u8 *, u32);
extern void func_0814186C(const u8 *, u8 *, u32);
extern void func_08005B40(u8 *);
extern u8 func_08036350(u8);
extern u32 func_080CEC78(u16, u8, u8);
extern void func_0802979C(DrawContext *, u8 *, u32, s32, s32);
extern s32 func_080D2E78(PanelRecord *);

void func_0805FFF0(PanelControl *control, u8 *buffer, u16 index)
{
    u8 *cursor = buffer;

    switch (control->mode) {
    case 2:
        {
            u8 *temporary;

            if (func_080C9540((u8)data_0200F44C->records[index]->id | 0x500))
                break;
            cursor += 0x380;
            temporary = func_08005B28(0x80);
            func_080CB9B0(temporary, 0x1C);
            func_0814186C(temporary, cursor, 0x40);
            func_08005B40(temporary);
        }
        break;
    case 3:
        {
            PanelRecord *record = data_0200F44C->records[index];
            u16 id;
            u8 stat;
            u32 value;

            cursor += 0x340;
            id = record->id;
            stat = func_08036350(g_state_02000000.value);
            value = func_080CEC78(id, stat, control->parameter);
            func_0802979C((DrawContext *)((u8 *)data_0200F44C + 0x148),
                cursor, value, 5, 0);
        }
        break;
    case 7:
        if (func_080D2E78(data_0200F44C->records[index])) {
            u8 *temporary;

            cursor = buffer + 0x300;
            temporary = func_08005B28(0x80);
            func_080CB9B0(temporary, 0x1D);
            func_0814186C(temporary, cursor, 0x40);
            func_08005B40(temporary);
        }
        break;
    }
}
