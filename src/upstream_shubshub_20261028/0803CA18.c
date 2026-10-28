/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0803CA18.c
 * Original SHA-256: a9ceea2feba6f9a690aa86ea68fb579ef4fe695ed083dc031a2bedb74324fd04
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x0803CA18..0x0803CDAC: 916 bytes. */
typedef struct {
    u8 flags;
    u8 unknown_01[0x23];
    void *slots[16];
} ResourceSlots;

typedef struct {
    u8 unknown_00[4];
    ResourceSlots *resources;
    u8 unknown_08[0x4B0];
    u8 active[6];
    u8 markers[0x1B6];
    u8 field_674;
    u8 unknown_675[0x31F];
    u16 selected_record;
    u16 mode;
    u8 unknown_998[2];
    u16 selected_slot;
    u8 unknown_99C[0x26C];
    void *window;
} ContextFields;

typedef struct {
    u8 unknown_00[0xCB];
    u8 state;
} TaskState;

typedef struct {
    u8 unknown_00[0x8BC];
    TaskState entries[1];
} ContextTasks;

typedef union {
    ContextFields fields;
    ContextTasks tasks;
} Context;

typedef struct __attribute__((packed)) {
    u16 id : 9;
    u16 unknown_09 : 7;
    u8 unknown_02[4];
} SelectionRecord;

typedef struct {
    u8 unknown_00[0x20D0];
    void *resource;
    u8 unknown_20D4[0xD64];
    SelectionRecord records[1];
} ResourceData;

typedef struct {
    void *resource;
    u8 unknown_04[12];
    u8 selection;
    u8 field_11;
    u8 field_12;
} Selection;

typedef struct {
    u16 held;
    u16 pressed;
} KeyState;

typedef struct __attribute__((packed)) {
    u8 mode : 3;
    u8 unknown_03 : 5;
} DisplayFlags;

typedef struct {
    u8 unknown_00[0x9A];
    DisplayFlags flags_9A;
    u8 unknown_9B[0x4B];
    DisplayFlags flags_E6;
    u8 unknown_E7[0x95];
    u8 busy;
} DisplayState;

extern Context *g_state_03002810;
extern ResourceData g_state_02000000;
extern Selection g_state_020020D0;
extern KeyState data_03000000;
extern DisplayState data_030009E0;
extern u8 data_03000990[];
extern u8 data_030008B0[];
extern u16 data_02003CB0[];
extern u16 data_06010980[];
extern const u8 data_083AF504[];
extern const u8 data_08391A5C[];
extern const u8 data_08391A64[];
extern u8 data_0201F488;
extern u8 data_0201F489;

extern void *func_080D2DE0(u16 id);
extern void func_0803131C(void);
extern void func_080312F0(void);
extern void func_0800543C(void *destination, const void *source);
extern void func_0814186C(const void *source, void *destination, u32 control);
extern void func_0801174C(void *window, s32 id, u8 selection, void *first,
                          void *second, s32 a5, s32 a6, s32 a7, s32 a8, s32 a9);
extern u16 func_08011860(void);
extern void func_08141540(s32 sound);
extern void func_08013364(void);
extern void func_08011B30(s32 id, u8 selection);
extern void func_08001F34(const void *image, s32 x, s32 y, s32 a3, s32 a4,
                          s32 a5, s32 a6, s32 a7, s32 a8, s32 a9, s32 a10);

void func_0803CA18(s32 index)
{
    {
    u8 *destination;
    s32 next_state;
    switch (g_state_03002810->tasks.entries[index].state) {
    case 0:
        {
        u16 *buffer = data_02003CB0;

        g_state_03002810->fields.markers[index] = 0;
        data_0201F489 = 0;
        if (g_state_03002810->fields.mode == 1) {
            g_state_02000000.resource =
                func_080D2DE0(g_state_02000000.records[g_state_03002810->fields.selected_record].id);
        } else {
            g_state_020020D0.resource =
                g_state_03002810->fields.resources->slots[g_state_03002810->fields.selected_slot];
        }
        g_state_020020D0.selection = 0;
        g_state_020020D0.field_11 = 4;
        g_state_020020D0.field_12 = 2;
        func_0803131C();
        g_state_03002810->fields.field_674 = 0;
        func_0800543C(buffer, data_083AF504);
        func_0814186C(buffer, data_06010980, 0x100);
        {
            Context *context = g_state_03002810;
            s32 offset = index * 0xCC;

            destination = (u8 *)context + offset + 0x987;
        }
        next_state = 1;
        goto update_state;
        break;
        }
    case 1:
        func_0801174C(g_state_03002810->fields.window, 9, g_state_020020D0.selection,
                      data_03000990, data_030008B0, 2, 1, 24, 16, 203);
        g_state_03002810->tasks.entries[index].state = 2;
        break;
    case 2:
        if (func_08011860() != 0) {
            data_0201F489 = 1;
            {
            Context *context = g_state_03002810;
            s32 offset = index * 0xCC;

            destination = (u8 *)context + offset + 0x987;
        }
        next_state = 3;
        goto update_state;
        }
        break;
    case 3:
        {
            u16 keys = data_03000000.pressed;
            u16 previous = keys & 0x20;

            if (previous != 0) {
                func_08141540(0x6D);
                if (g_state_020020D0.selection == 0)
                    g_state_020020D0.selection = 3;
                else
                    g_state_020020D0.selection--;
                func_08013364();
                func_08011B30(9, g_state_020020D0.selection);
                {
            Context *context = g_state_03002810;
            s32 offset = index * 0xCC;

            destination = (u8 *)context + offset + 0x987;
        }
                next_state = 2;
                goto update_state;
            } else if (keys & 0x10) {
                func_08141540(0x6D);
                if (g_state_020020D0.selection == 3)
                    g_state_020020D0.selection = 0;
                else
                    g_state_020020D0.selection++;
                func_08013364();
                func_08011B30(9, g_state_020020D0.selection);
                {
            Context *context = g_state_03002810;
            s32 offset = index * 0xCC;

            destination = (u8 *)context + offset + 0x987;
        }
                next_state = 2;
                goto update_state;
            } else if (keys & 3) {
                u32 accept = 1;

                accept &= keys;
                if (accept)
                    func_08141540(0x64);
                else
                    func_08141540(0x68);
                func_08013364();
                data_0201F489 = 0;
                {
            Context *context = g_state_03002810;
            s32 offset = index * 0xCC;

            destination = (u8 *)context + offset + 0x987;
        }
        next_state = 0xFD;
        goto update_state;
            }
        }
        break;
    case 4:
        if (data_030009E0.busy == 0)
            g_state_03002810->tasks.entries[index].state = data_0201F488;
        break;
    case 0xFD:
        if (func_08011860() != 0) {
            func_08141540(0x69);
            {
            Context *context = g_state_03002810;
            s32 offset = index * 0xCC;

            destination = (u8 *)context + offset + 0x987;
        }
        next_state = 0xFF;
        goto update_state;
        }
        break;
    case 0xFF:
        func_080312F0();
        {
            ResourceSlots *resources = g_state_03002810->fields.resources;
            u32 flags = resources->flags;

            resources->flags = flags | 0x20;
        }
        data_030009E0.flags_E6.mode = 5;
        data_030009E0.flags_9A.mode = 5;
        {
            destination = g_state_03002810->fields.active;
            destination += index;
        }
        next_state = 0;
update_state:
        *destination = next_state;
        break;
    }
    }
    if (data_0201F489 != 0) {
        s32 offset = (data_0201F489 - 1) >> 2;

        func_08001F34(data_08391A5C, 17 - offset, 6, 0, 0, 0, 0, 0, 0, 2, 1);
        func_08001F34(data_08391A64, 206 + offset, 6, 0, 0, 0, 0, 0, 0, 2, 1);
        if (data_0201F489++ > 18)
            data_0201F489 = 1;
    }
}
