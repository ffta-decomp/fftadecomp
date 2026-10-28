/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08043120.c
 * Original SHA-256: a5a42f37c04aa79f9752e65696f0d665c7df280cc42e808025b8b470be0c2fbd
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x08043120 .. 0x08043468: 840 bytes, 329 instructions. */
typedef struct {
    u32 words[5];
} Record08043120;

typedef struct {
    u8 unknown_00[0x10];
    u16 flags;
    u8 unknown_12[0x0e];
} Menu08043120;

typedef struct {
    u8 unknown_00[0x11];
    s8 cursor;
    u8 unknown_12[2];
} Controls08043120;

typedef struct {
    u8 unknown_00[0x30];
    u16 id;
    u8 phase;
    u8 unknown_33[2];
    u8 delay;
    u8 selection;
    u8 unknown_37;
    u16 key;
    u8 dirty;
    u8 unknown_3b[0x0d];
    void *source;
    u8 display[0x2c];
    Menu08043120 menu;
    s8 controls[0x14];
    Record08043120 record;
    u32 unknown_c0;
    void *data;
    u32 unknown_c8;
} Entry08043120;

typedef struct {
    u8 unknown_000[0x4a0];
    Record08043120 record;
    u8 mode;
    u8 saved;
    u8 unknown_4b6[0x49e];
    Entry08043120 entries[0];
} Context08043120;

extern Context08043120 *g_state_03002810;
extern u8 data_030027A4;
extern u8 data_02003CB0[];
extern u8 data_03000990[];
extern u8 data_030008B0[];
extern void func_08085450(u32, void *, void *, int);
extern void func_080425F8(u32, void *, void *, u8, u8);
extern void func_080430CC(Menu08043120 *);
extern void func_08042FDC(u32);
extern s16 func_08017B68(Menu08043120 *, s8);
extern u16 func_08017B50(Menu08043120 *);
extern void func_08017AF4(Menu08043120 *, s8, int);
extern void func_08042EC4(u32);
extern u8 func_08042774(u32);
extern void func_08017E28(Record08043120 *);
extern void func_08037FB0(u32);
extern u8 func_08038014(u32);
extern void func_08031708(int);
extern void func_08019AE4(void *, u16, void *, void *, int);
extern void func_08013428(int);
extern u16 func_08011860(void);
extern void func_080356A0(u32, u8);
extern void func_0808537C(u16, void *, int);

u8 func_08043120(u32 index)
{
    switch (g_state_03002810->entries[index].phase) {
    case 0:
        func_08085450(index, g_state_03002810->entries[index].data,
                     g_state_03002810->entries[index].source, 4);
        g_state_03002810->entries[index].phase = 1;
        break;
    case 1:
        func_080425F8(index, g_state_03002810->entries[index].display,
                     g_state_03002810->entries[index].source, 0xff, 0xff);
        g_state_03002810->entries[index].phase = 2;
        break;
    case 5:
    {
        u16 count;
        int row;
        func_08085450(index, g_state_03002810->entries[index].data,
                     g_state_03002810->entries[index].source, 4);
        func_080430CC(&g_state_03002810->entries[index].menu);
        func_08042FDC(index);
        func_08017B68(&g_state_03002810->entries[index].menu,
                     ((Controls08043120 *)g_state_03002810->entries[index].controls)->cursor);
        count = func_08017B50(&g_state_03002810->entries[index].menu);
        for (row = 0; row < count; row++)
            func_08017AF4(&g_state_03002810->entries[index].menu, row, 0x0c);
        func_08017AF4(&g_state_03002810->entries[index].menu,
                     ((Controls08043120 *)g_state_03002810->entries[index].controls)->cursor, 0x0b);
        g_state_03002810->entries[index].phase = 3;
        break;
    }
    case 2:
        func_08042EC4(index);
        g_state_03002810->entries[index].menu.flags |= 2;
        func_08017AF4(&g_state_03002810->entries[index].menu,
                     ((Controls08043120 *)g_state_03002810->entries[index].controls)->cursor, 0x0b);
        g_state_03002810->entries[index].phase = 3;
        break;
    case 3:
        g_state_03002810->entries[index].phase = func_08042774(index);
        break;
    case 4:
        func_08017E28(&g_state_03002810->entries[index].record);
        g_state_03002810->entries[index].phase = 3;
        break;
    case 6:
        g_state_03002810->entries[index].selection = 0xff;
        func_08037FB0(index);
        g_state_03002810->entries[index].phase = 7;
    case 7:
        if (func_08038014(index))
            g_state_03002810->entries[index].phase = 0xff;
        break;
    case 8:
        break;
    case 9:
        g_state_03002810->saved = data_030027A4;
        func_08031708(0x37);
        func_08019AE4(data_02003CB0, g_state_03002810->entries[index].key,
                     data_03000990, data_030008B0, 1);
        func_08013428(-0x120);
        g_state_03002810->entries[index].phase = 11;
        break;
    case 11:
        if (func_08011860()) {
            func_08031708(g_state_03002810->saved);
            g_state_03002810->entries[index].dirty = 1;
            func_080356A0(index, g_state_03002810->mode);
            g_state_03002810->entries[index].record = g_state_03002810->record;
            g_state_03002810->entries[index].phase = 3;
        }
        break;
    case 0xff:
        break;
    }
    if (g_state_03002810->entries[index].phase > 2) {
        if (g_state_03002810->entries[index].delay == 0)
            func_0808537C(g_state_03002810->entries[index].id,
                         g_state_03002810->entries[index].display, 1);
        else
            g_state_03002810->entries[index].delay--;
    }
    return g_state_03002810->entries[index].phase;
}
