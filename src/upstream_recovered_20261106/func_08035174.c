/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 11946243ba373da48154ed04cb3bb31e52dad97b
 * Original file: src/08035174.c
 * Original SHA-256: d8aeb27942d47afaea0a01fcbe51a7753e55d98daaca31ca05f51368101f1016
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred.
 */
#include "ffta.h"

/* 0x08035174, 824 bytes. State dispatch and palette-transition updates. */
typedef struct {
    u8 unknown_flag0 : 1;
    u8 flag1 : 1;
    u8 unknown_flags2 : 6;
    u8 unknown_01[2];
    u8 frame;
    u8 unknown_04[0x0d];
    u8 busy;
    u8 unknown_12[0x7c];
    u8 unknown_flags8e : 4;
    u8 flag4_8e : 1;
    u8 unknown_flags8e_high : 3;
} DispatchSecondary;

typedef struct {
    u8 active : 1;
    u8 unknown_flags : 7;
    u8 unknown_01[4];
    u8 field_05;
    u8 unknown_06[0x2e];
} DispatchEntry;

typedef struct {
    u32 unknown_00;
    DispatchSecondary *secondary;
    u8 unknown_08[0x79];
    u8 field_81;
    u8 unknown_82[0x1c];
    u16 timer;
    u16 palette[0x100];
    u8 unknown_2a0[0x3d4];
    u8 field_674;
    u8 unknown_675[0x143];
    DispatchEntry entries[5];
    u8 unknown_8bc[0x681];
    u8 modes[3];
} DispatchState;

typedef struct {
    u16 count;
    u16 unknown_02;
    void *entries;
} DispatchList;

extern DispatchState *g_state_03002810;
extern DispatchList data_03000E30;
extern Table data_03002720;
extern u16 data_03000000[];
extern u16 data_03003860[];
extern u8 data_02003CB0[];
extern u8 data_03000990[];
extern u8 data_030008B0[];
extern u8 data_0201F465, data_0201F466, data_0201F467;

extern void func_0804C044(void);
extern void func_0804C834(void *, s32);
extern void func_08038324(void);
extern void func_08006AF8(Table *, u8, void (*)(void), u8);
extern void func_080358B0(u32);
extern void func_08035844(u32);
extern void func_08031708(u8);
extern void func_0801174C(void *, u8, u16, void *, void *, u16, u16, u8, u8, u16);
extern void func_08013428(s16);
extern void func_08037428(void);
extern u16 func_08011860(void);
extern void func_08013364(void);
extern s8 func_08013380(void);
extern void func_08141540(u16);
extern void func_08031714(void);
extern void func_0814186C(const void *, void *, u32);
extern void func_0804BDDC(u8, u8);
extern void func_08038B58(void);
extern void func_080365B8(void);
extern void func_0803701C(u32);

void func_08035174(void *unused, u8 *state)
{
    s32 i;
    u16 clear;
    switch (*state) {
    case 0:
        data_03000E30.count = 0x40;
        g_state_03002810->field_674 = 0;
        g_state_03002810->modes[0] = 0;
        g_state_03002810->modes[2] = 0;
        g_state_03002810->secondary->flag4_8e = 0;
        g_state_03002810->entries[0].field_05 = 0;
        func_0804C834(data_03000E30.entries, 0x40);
        func_08038324();
        for (i = 0; i < 5; i++)
            g_state_03002810->entries[i].active = 0;
        func_08006AF8(&data_03002720, 3, func_0804C044, 1);
        func_080358B0(1);
        g_state_03002810->modes[1] = 0;
        g_state_03002810->timer = 8;
        data_0201F466 = 5;
        data_0201F465 = 5;
        *state = 0x2b;
        break;
    case 5:
        if (data_03000000[1] & 1) {
            func_08035844(0);
            func_08031708(0x80);
            func_0801174C(data_02003CB0, 1, 0x2a, data_03000990,
                          data_030008B0, 2, 6, 24, 4, 0x30d);
            func_08013428(-0x120);
            *state = 6;
        } else {
            func_08037428();
        }
        break;
    case 6:
        if (func_08011860() != 0) {
            func_08013364();
            if (func_08013380() == 0) {
                func_08141540(0x69);
                g_state_03002810->timer = 0;
                data_0201F466 = 0xff;
                data_0201F465 = 0xff;
                *state = 0x2d;
            } else {
                func_08031714();
                func_080358B0(1);
                g_state_03002810->modes[1] = 2;
                *state = 5;
            }
        }
        break;
    case 0x2b:
        if (--g_state_03002810->timer == 0) {
            func_0814186C(g_state_03002810->palette, data_03003860, 0x100);
            *state = data_0201F465;
            data_0201F465 = data_0201F466;
        } else {
            func_0804BDDC(8, g_state_03002810->timer);
        }
        break;
    case 0x2c:
        if (--g_state_03002810->timer == 0) {
            func_080358B0(1);
            g_state_03002810->modes[1] = 30;
            func_0814186C(g_state_03002810->palette, data_03003860, 0x100);
            *state = data_0201F465;
            data_0201F465 = data_0201F466;
        } else {
            func_0804BDDC(8, g_state_03002810->timer);
        }
        break;
    case 0x2d:
        if (++g_state_03002810->timer > 7) {
            clear = 0;
            func_0814186C(&clear, data_03003860, 0x01000200);
            *state = data_0201F465;
            data_0201F465 = data_0201F466;
        } else {
            func_0804BDDC(8, g_state_03002810->timer);
        }
        break;
    case 0x38:
        if (data_0201F467 == 0)
            *state = 0x22;
        else
            data_0201F467--;
        break;
    case 0x35:
        if (g_state_03002810->secondary->busy == 0) {
            *state = data_0201F465;
            data_0201F465 = data_0201F466;
        }
        break;
    case 0x36:
        if (g_state_03002810->secondary->busy == 0) {
            g_state_03002810->secondary->flag1 = 0;
            *state = data_0201F465;
            data_0201F465 = data_0201F466;
        }
        break;
    case 0xff:
        g_state_03002810->field_81 = 0xfd;
        return;
    }
    func_08038B58();
    g_state_03002810->secondary->frame++;
    func_080365B8();
    func_0803701C(1);
}
